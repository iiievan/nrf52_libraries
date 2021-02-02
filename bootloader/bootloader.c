#define __ALLOCATE_NOW__
#include "string.h"
#include "bootloader.h"


/* These are set to zero as ShockBurst packets don't have corresponding fields. */
#define PACKET_S1_FIELD_SIZE      (0UL)  /**< Packet S1 field size in bits. */
#define PACKET_S0_FIELD_SIZE      (0UL)  /**< Packet S0 field size in bits. */
#define PACKET_LENGTH_FIELD_SIZE  (0UL)  /**< Packet length field size in bits. */
#define PACKET_MAX_LENGTH          64

u8      ble_payload[PACKET_MAX_LENGTH];
u8      ucRF_Packet_received = 0;
TRFData BLE_Update_packet;
u8      uiCRC_write_to_flash = 0;
#define DATA_WAIT_PERIOD_DEF        2000
u32     data_wait_max = DATA_WAIT_PERIOD_DEF;
u16     pg_size = 0, pg_num = 0;

#ifdef TRANSMITTER
#pragma location="firmware_type"
  const u32 __firmware_type = 0x01;
#endif
#ifdef RECEIVER
#pragma location="firmware_type"
  const u32 __firmware_type = 0x02;
#endif
#ifdef RECEIVER_SD
#pragma location="firmware_type"
  const u32 __firmware_type = 0x03;
#endif

u8 channel_resolver_get_frequency(u8 channel)
{
  u8 freq;

  /* Special cases for the advertise channels */
  if (channel == 37)
    freq = 2;
  else if (channel == 38)
    freq = 26;
  else if (channel == 39)
    freq = 80;
  else
    freq = 2*channel + (channel < 11 ? 4 : 6);

  return freq;
}

void ble_config_radio(u8 ch)
{
  //адрес для ble и служебного канала
  NRF_RADIO->PREFIX1 = 0x0000AA8e;
  NRF_RADIO->BASE1 = 0x89bed600;

  // Radio config
  NRF_RADIO->TXPOWER   = (RADIO_TXPOWER_TXPOWER_Neg20dBm << RADIO_TXPOWER_TXPOWER_Pos);
  NRF_RADIO->MODE      = (RADIO_MODE_MODE_Ble_1Mbit << RADIO_MODE_MODE_Pos);

  // Radio address config
  NRF_RADIO->TXADDRESS   = 0x04UL;  
  NRF_RADIO->RXADDRESSES = BIT(4);
  
  NRF_RADIO->FREQUENCY = channel_resolver_get_frequency(ch);  
  NRF_RADIO->DATAWHITEIV  = ch;
  
  // Packet configuration
  NRF_RADIO->PCNF0 = (PACKET_S1_FIELD_SIZE     << RADIO_PCNF0_S1LEN_Pos) |
                     (PACKET_S0_FIELD_SIZE     << RADIO_PCNF0_S0LEN_Pos) |
                     (PACKET_LENGTH_FIELD_SIZE << RADIO_PCNF0_LFLEN_Pos) |
                     (RADIO_PCNF0_PLEN_8bit    << RADIO_PCNF0_PLEN_Pos);
  
  NRF_RADIO->PCNF1 = (RADIO_PCNF1_WHITEEN_Enabled  << RADIO_PCNF1_WHITEEN_Pos) |
                     (RADIO_PCNF1_ENDIAN_Little    << RADIO_PCNF1_ENDIAN_Pos)  |
                     (3UL   << RADIO_PCNF1_BALEN_Pos) |
                     (BLE_PACKET_LEN    << RADIO_PCNF1_STATLEN_Pos) |
                     (PACKET_MAX_LENGTH    << RADIO_PCNF1_MAXLEN_Pos);
  
  NRF_RADIO->CRCCNF = (RADIO_CRCCNF_SKIPADDR_Skip << RADIO_CRCCNF_SKIPADDR_Pos) |
                      (RADIO_CRCCNF_LEN_Three << RADIO_CRCCNF_LEN_Pos); 
  NRF_RADIO->CRCINIT = 0x555555UL;  
  NRF_RADIO->CRCPOLY = BIT(24) | BIT(10) | BIT(9) | BIT(6) | BIT(4) | BIT(3) | BIT(1) | 1;
  
  NRF_RADIO->PACKETPTR = (u32)&ble_payload[0];
}

void radio_init()
{
  ble_config_radio(BLUETOOTH_CH_NUM);
  
  //конечный автомат для радио
  NRF_RADIO->SHORTS = (RADIO_SHORTS_ADDRESS_RSSISTART_Enabled << RADIO_SHORTS_ADDRESS_RSSISTART_Pos) |
                      (RADIO_SHORTS_DISABLED_RSSISTOP_Enabled << RADIO_SHORTS_DISABLED_RSSISTOP_Pos) |
                      (RADIO_SHORTS_END_DISABLE_Enabled << RADIO_SHORTS_END_DISABLE_Pos);
  
  //прерывания для радио
  NRF_RADIO->INTENSET |= (RADIO_INTENSET_CRCOK_Set << RADIO_INTENSET_CRCOK_Pos) |
                         (RADIO_INTENSET_END_Enabled << RADIO_INTENSET_END_Pos) |
                         (RADIO_INTENSET_READY_Enabled << RADIO_INTENSET_READY_Pos);

                           
  nrf_drv_common_irq_enable(RADIO_IRQn, 3);
}

void RADIO_IRQHandler()
{
  if (NRF_RADIO->EVENTS_CRCOK)
  {
    __disable_interrupt();
    //получили валидный пакет с данными
    TRFData *ptr = (TRFData *)NRF_RADIO->PACKETPTR;
    
    NRF_RADIO->EVENTS_CRCOK = 0;
    //обрабатываем принятый пакет
    ptr->RSSI = -NRF_RADIO->RSSISAMPLE;
    __enable_interrupt();
    //сохраняем пакет с данными для дальнейшей обработки
    memcpy(&BLE_Update_packet, ptr, sizeof(TRFData));
    ucRF_Packet_received = 1;
  }
  
  //управляем работой усилителя
  if (NRF_RADIO->EVENTS_END)
  {
    NRF_RADIO->EVENTS_END = 0;
    RF_OFF();
  }
  if (NRF_RADIO->EVENTS_READY)
  {
    NRF_RADIO->EVENTS_READY = 0;
    RF_RX();
    NRF_RADIO->TASKS_START = 1U;
  }
}

/********************************************************

  настраиваемся на прием заданного канала
  до 140мкс, когда меняем канал

 ********************************************************/
void radio_rx(u8 ch)
{
  //канал и скорость передачи
  ble_config_radio(ch);
  //errata radio rx packet miss -3db sensivity
  //*(volatile uint32_t *) 0x40001774 = ((*(volatile uint32_t *)
  //0x40001774) & 0xfffffffe) | 0x01000000;
  // Enable radio and wait for ready
  NRF_RADIO->TASKS_RXEN = 1U;
}

/********************************************************

  выключаем радиочасть
  до 6мкс

 ********************************************************/
void radio_off()
{
  u8 cnt = 10;
  NRF_RADIO->EVENTS_DISABLED = 0;
  NRF_RADIO->TASKS_DISABLE = 1;
  while (NRF_RADIO->EVENTS_DISABLED == 0 && cnt > 0)
  {
    Delay10us(1);
    cnt--;
  }
}

//время на стирание одной страницы 2,05 - 89мс
//прошивка 30 страниц по 4096 байт
//стирается за 2,7сек.
void flash_page_erase(u32 *page_address)
{
    // Turn on flash erase enable and wait until the NVMC is ready:
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos);

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Erase page:
    NRF_NVMC->ERASEPAGE = (u32)page_address;

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Turn off flash erase enable and wait until the NVMC is ready:
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }
}

//время на запись одного слова 6,72мкс - 338мкс
void flash_word_write(u32 *address, u32 *value)
{
    // Turn on flash write enable and wait until the NVMC is ready:
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos);

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    *address = *value;

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }

    // Turn off flash write enable and wait until the NVMC is ready:
    NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);

    while (NRF_NVMC->READY == NVMC_READY_READY_Busy)
    {
        // Do nothing.
    }
}

/******************************************************************************

флеш стерается меньше чем за 1,5 сек

******************************************************************************/
void EraseProgrammFlash()
{
  u32 *adr;
  
  //проверим нужно ли стерать флеш
  for (adr = (u32*)PRORGAMM_START; adr < (u32*)(PROGRAMM_END + CHECKSUM_SIZE); adr++)
    if (*adr != 0xFFFFFFFF)
      break;
  
  if (adr >= (u32*)(PROGRAMM_END + CHECKSUM_SIZE))
    return;
  
  for (u32 i = PRORGAMM_START; i < PROGRAMM_END; i+= pg_size)
      flash_page_erase((u32*)i);
}

void RF_Packet_Handle(TRFData *packet)
{
  static u8 flash_erased = 0;
    
#ifdef TRANSMITTER
  if (packet->header.transmitter_id == TRANSMITTER_UDTADE_ID && packet->header.receiver_id == 0)
#endif
#ifdef RECEIVER
  if (packet->header.transmitter_id == TRANSMITTER_UDTADE_ID && packet->header.receiver_id)
#endif
#ifdef RECEIVER_SD
  if (packet->header.transmitter_id == TRANSMITTER_UDTADE_ID_SD && packet->header.receiver_id)
#endif
  {
    //увеличиваем время ожидания пакета по радиоканалу
    data_wait_max = 5 * DATA_WAIT_PERIOD_DEF;
    
    u32 adr = ((u32)packet->header.flash_adr) + PRORGAMM_START;
    if (adr == PRORGAMM_START && flash_erased == 0)
    {
      EraseProgrammFlash();
      flash_erased = 1;
    }
    if (flash_erased == 0)
      return;
    for (u32 i = 0; i < PAYLOAD_DATA_SIZE; i += 4, adr += 4)
    {
      if (adr < PRORGAMM_START || adr >= PROGRAMM_END + CHECKSUM_SIZE)
        break;
      if (adr == CHECKSUM_ADR-2)
        uiCRC_write_to_flash = 1;
      u32 *ptr = (u32*)&packet->payload[i];
      u32 *mem_val = (u32*)adr;
      //данные отличаются и выравнены по 4 байта
      if (*ptr != *mem_val && (adr & 0x3) == 0)
        flash_word_write((u32*)adr, ptr);
    }
  }
}


s8 CheckProgrammCRC()
{
    //проверяем целостность прошивки
  u16 uiCRC_flash =  *((u8*)CHECKSUM_ADR+1) + (*((u8*)CHECKSUM_ADR) << 8);
  u16 uiCRC_calc = CRC16((u8*)PRORGAMM_START, PROGRAMM_END - PRORGAMM_START);
  
  if (uiCRC_flash != uiCRC_calc)
    return FAIL;
  else
    return OK;
}
/******************************************************************************

функция запускается при старте. При необходимости обновляет прошивку

*******************************************************************************/
void StartProgram();

void main()
{
  u32 no_data_cnt = 0;
  
  //InitGPIO();
  /*clock_initialization();
  radio_init();
  radio_rx(BLUETOOTH_CH_NUM);
  pg_size = NRF_FICR->CODEPAGESIZE;
  pg_num  = NRF_FICR->CODESIZE - 1;
  
  //ждем пакеты по радиоканалу
  while (no_data_cnt++ < data_wait_max)
  {
    if (ucRF_Packet_received)
    {
      LED_G_ON;
      RF_Packet_Handle(&BLE_Update_packet);
      LED_G_OFF;
      if (BLE_Update_packet.header.transmitter_id == TRANSMITTER_UDTADE_ID || BLE_Update_packet.header.transmitter_id == TRANSMITTER_UDTADE_ID_SD)
        no_data_cnt = 0;
      if (uiCRC_write_to_flash)
      {
        //записали всю прошивку - выходим из процедуры обновления
        if (CheckProgrammCRC() == OK)
          break;
        uiCRC_write_to_flash = 0;
      }
      ucRF_Packet_received = 0;
      radio_rx(BLUETOOTH_CH_NUM);
    }
    else
    {
      Delay100us(2);
      if (NRF_RADIO->STATE != RADIO_STATE_STATE_Rx && ucRF_Packet_received == 0)
      {
        radio_off();
        radio_rx(BLUETOOTH_CH_NUM);
      }
    }
  }
  LED_G_OFF;
  LED_R_OFF;
  RF_OFF();
  
  //если битая прошивка - уходим на ресет
  if (CheckProgrammCRC() != OK)
  {
    LED_R_ON;
    Delay100us(500);
    LED_R_OFF;
    Reset();
  }
  else
  {
    LED_G_ON;
    Delay100us(500);
    LED_G_OFF;
  }*/
  
  //делаем деинициализацию радио части
  NVIC_DisableIRQ(RADIO_IRQn);
  //NRF_RADIO->POWER = 0;
    
  //прыгаем в основную программу
  StartProgram();
}

#pragma optimize=none
void StartProgram()
{
  pFunction Jump_To_Application;
  __disable_interrupt();
  
  Jump_To_Application = (pFunction) *((__IO u32*) (PRORGAMM_START + 4));        //Адресс вектора Reset                
  __set_MSP(*(__IO u32*) PRORGAMM_START);                                       //Устанавливаем SP приложения  
  Jump_To_Application(); 
}
