#include "bootloader.h"

#define DLY_100US  488
#define DLY_10US  47
#define DLY_1US  4

#define ADC_REF_MV         600.0
#define ADC_CODE_MAX       (4096.0)

u32 adc_val_code;
u8 hw_version;

u16 CRC16_FILL( const u8 *pBuf, u32 uiLength, u16 fill )
{
    register u8 Lo, Hi, ucSym;
 
    if (!uiLength){
        return 1;
    }
   
    Lo = fill & 0xFF;
    Hi = (fill & 0xFF00) >> 8;
 
    do {
        ucSym = *(pBuf++);
        ucSym ^= Hi;
          
        Hi = ( ucSym & 0x02 ) ? (Lo - 0x80) : Lo;
          
        if ( ucSym & 0x01 )
            Hi ^= 0xC0;
          
        Lo = ucSym;
        Lo >>= 1;
        Lo ^= ucSym;
        Lo >>= 1;
        ucSym ^= Lo;
          
        if ( ucSym & 0x08 )
            --ucSym;
          
        if ( ucSym & 0x40 )
            --ucSym;
          
        ucSym &= 0x01;
  
        if ( ucSym )
            Lo ^= 0xC0;
  
        Hi ^= ucSym;
    } while ( --uiLength );
  
    return (u16)((((u16)Hi)<<8) | Lo);
}

u16 CRC16( const u8 *pBuf, u32 uiLength )
{
    return CRC16_FILL(pBuf, uiLength, 0xFFFF);
}

void Delay100us(u32 Dly)
{
	for(; Dly; Dly--)
	{
		for(volatile u32 j = DLY_100US; j; j--)//7 operations per cycle
		{
		}
	}
}

void Delay10us(u32 Dly)
{
	for(; Dly; Dly--)
	{
		for(volatile u32 j = DLY_10US; j; j--)//7 operations per cycle
		{
		}
	}
}

void Delay1us(u32 Dly)
{
	for(; Dly; Dly--)
	{
		for(volatile u32 j = DLY_1US; j; j--)//7 operations per cycle
		{
		}
	}
}

void EnableCHRG(ECHRG_TYPE max_current)
{
  if (max_current == CHRG_MAX_CURRENT)
  {
#ifdef CHARGE_250MA_MAX
    nrf_gpio_cfg_input(CHRG_EN_PIN, NRF_GPIO_PIN_NOPULL);
#else
    nrf_gpio_cfg_output(CHRG_EN_PIN);
    nrf_gpio_pin_clear(CHRG_EN_PIN);
#endif
  }
  else if (max_current == CHRG_MEDIUM_CURRENT)
  {
    nrf_gpio_cfg_input(CHRG_EN_PIN, NRF_GPIO_PIN_NOPULL);
  }
  else
  {
    nrf_gpio_cfg_input(CHRG_EN_PIN, NRF_GPIO_PIN_PULLUP);
  }
}

void DisableCHRG()
{
  nrf_gpio_cfg_input(CHRG_EN_PIN, NRF_GPIO_PIN_PULLUP);
}

void nrf_drv_common_irq_enable(IRQn_Type IRQn, uint8_t priority)
{
  NVIC_SetPriority(IRQn, priority);
  NVIC_ClearPendingIRQ(IRQn);
  NVIC_EnableIRQ(IRQn);
}

void clock_initialization()
{
  u32 cnt = 0;
#define INIT_CLCK_TIMEOUT       10000
  /* Start 16 MHz crystal oscillator */
  NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  NRF_CLOCK->TASKS_HFCLKSTART    = 1;

  /* Wait for the external oscillator to start up */
  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0 && cnt < INIT_CLCK_TIMEOUT)
  {
    Delay100us(1);
    cnt++;
  }
}

void ADC_DeInit()
{
  for (u8 i = 0; i < 6; i++)
  {
    NRF_SAADC->CH[0].PSELP = 0;
    NRF_SAADC->CH[0].CONFIG = 0;
  }
  
  NRF_SAADC->TASKS_STOP = 1;
  NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Disabled;
  nrf_gpio_cfg_input(RF_PDET_PIN, NRF_GPIO_PIN_PULLDOWN);
}

int GetPCBVER()
{
#if HW_VERSION == 2
  NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Enabled;
  NRF_SAADC->CH[0].PSELP = SAADC_CH_PSELP_PSELP_AnalogInput4;   //RF_POWER
  
  NRF_SAADC->CH[0].CONFIG = (SAADC_CH_CONFIG_TACQ_20us << SAADC_CH_CONFIG_TACQ_Pos) |
                            (SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos) |
                            (SAADC_CH_CONFIG_GAIN_Gain1_4 << SAADC_CH_CONFIG_GAIN_Pos) |
                            (SAADC_CH_CONFIG_RESP_Pullup << SAADC_CH_CONFIG_RESP_Pos);
  
  NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_12bit << SAADC_RESOLUTION_VAL_Pos;
  
  NRF_SAADC->RESULT.PTR = (u32)&adc_val_code;
  NRF_SAADC->RESULT.MAXCNT = 1;
  
  //запускаем калибровку АЦП
  NRF_SAADC->EVENTS_CALIBRATEDONE = 0;
  NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;
  while (NRF_SAADC->EVENTS_CALIBRATEDONE == 0); 
  Delay10us(8);
  
  //запускаем измерение
  NRF_SAADC->EVENTS_END = 0;
  NRF_SAADC->EVENTS_STARTED = 0;
  NRF_SAADC->TASKS_START = 1;
  while (NRF_SAADC->EVENTS_STARTED == 0);
  
  NRF_SAADC->TASKS_SAMPLE = 1;
  while (NRF_SAADC->EVENTS_END == 0);
  
  float VPDET = adc_val_code*4*ADC_REF_MV/ADC_CODE_MAX;
  
  ADC_DeInit();
  
  if (VPDET > 1000)
    return 0;
  else
    return 1;
#else 
  return HW_VERSION;
#endif
}

void InitGPIO()
{
  hw_version = GetPCBVER();
  
  //LEDS
  nrf_gpio_cfg_input(BAT_LED_1_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(BAT_LED_2_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(BAT_LED_3_PIN, NRF_GPIO_PIN_PULLDOWN);
  //nrf_gpio_cfg_input(BAT_LED_4_PIN, NRF_GPIO_PIN_PULLDOWN);
  //nrf_gpio_cfg_input(BAT_LED_5_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(LED_RED_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(LED_GREEN_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(BAT_LED_BTN_PIN, NRF_GPIO_PIN_PULLDOWN);

  //RF amplifier
  if (hw_version == 1)
  {
    nrf_gpio_cfg_output(RF_POWER_ENABLE);
    nrf_gpio_pin_set(RF_POWER_ENABLE);
  }
  RF_OFF();
  nrf_gpio_cfg_input(RF_PDET_PIN, NRF_GPIO_PIN_PULLDOWN);
  
  //enable charge
  EnableCHRG(CHRG_MAX_CURRENT);
  
  //buttons
  //nrf_gpio_cfg_input(BUTTON_UP_PIN, NRF_GPIO_PIN_PULLUP);
  //nrf_gpio_cfg_input(BUTTON_DOWN_PIN, NRF_GPIO_PIN_PULLUP);
}

void RF_RX()
{
  RF_OFF();
  Delay1us(4);
  //nrf_gpio_cfg_input(RF_SWANT_PIN, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(RF_MODE_PIN, NRF_GPIO_PIN_PULLUP);
  //nrf_gpio_cfg_input(RF_RX_EN_PIN, NRF_GPIO_PIN_PULLUP);
}

void RF_OFF()
{
  nrf_gpio_pin_clear(RF_TX_EN_PIN);
  nrf_gpio_cfg_output(RF_TX_EN_PIN);
  nrf_gpio_pin_clear(RF_TX_EN_PIN);
  
  nrf_gpio_pin_clear(RF_RX_EN_PIN);
  nrf_gpio_cfg_output(RF_RX_EN_PIN);
  nrf_gpio_pin_clear(RF_RX_EN_PIN);
  
  nrf_gpio_pin_clear(RF_MODE_PIN);
  nrf_gpio_cfg_output(RF_MODE_PIN);
  nrf_gpio_pin_clear(RF_MODE_PIN);

  //nrf_gpio_pin_clear(RF_SWANT_PIN);
  //nrf_gpio_cfg_output(RF_SWANT_PIN);
  //nrf_gpio_pin_clear(RF_SWANT_PIN);
}

void Reset()
{
  __disable_interrupt();
  NVIC_SystemReset();
}