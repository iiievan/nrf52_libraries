#include "include.h"
#include "i2s.h"

i2s::i2s()
{

}

i2s::i2s(uint32_t mck_pin, uint32_t lrck_pin, uint32_t sck_pin, uint32_t sdin_pin, uint32_t sdout_pin)
{   
    _mck_pin   = mck_pin;  
    _lrck_pin  = lrck_pin;  
    _sck_pin   = sck_pin;  
    _sdin_pin  = sdin_pin;  
    _sdout_pin = sdout_pin;

#if defined (RECEIVER_LEFT) || defined(RECEIVER_RIGHT) || defined (TRANSMITTER_CH2)
    _is_master = false;  // по умолчанию мы в режиме слейв
#endif
#if defined(TRANSMITTER_CH1)   
    _is_master = true;  // по умолчанию мы в режиме мастер
#endif
 }

 i2s::i2s(uint32_t lrck_pin, uint32_t sck_pin, uint32_t sdin_pin, uint32_t sdout_pin)
{   
    // этот конструктор нужен только в случае когда нужно инициализировать шину i2s в режиме слейв только дл€ прослушивани€ аудиопотока.
    _mck_pin   = PIN_DISCONNECTED;  
    _lrck_pin  = lrck_pin;  
    _sck_pin   = sck_pin;  
    _sdin_pin  = sdin_pin;  
    _sdout_pin = sdout_pin;

    _is_master = false;
 }

void i2s::init()
{    
    //Pin configuration
    if (_mck_pin != PIN_DISCONNECTED)
    {      
        nrf_gpio_cfg_output(_mck_pin);
        nrf_gpio_pin_clear(_mck_pin);
    }
    
    if(_is_master)
    {
        nrf_gpio_cfg_output(_lrck_pin);
        nrf_gpio_cfg_output(_sck_pin);
        nrf_gpio_pin_clear(_lrck_pin);
        nrf_gpio_pin_clear(_sck_pin);
    }
    else
    {
        nrf_gpio_cfg_input(_lrck_pin,  NRF_GPIO_PIN_NOPULL);
        nrf_gpio_cfg_input(_sck_pin, NRF_GPIO_PIN_NOPULL);
    }        

    nrf_gpio_cfg_input(_sdin_pin, NRF_GPIO_PIN_NOPULL); // allways input
    nrf_gpio_cfg_output(_sdout_pin);                    // allways output
    nrf_gpio_pin_clear(_sdout_pin);

    /***********for board testing*****/
//  nrf_gpio_cfg_output(_mck_pin);
//  nrf_gpio_cfg_output(_lrck_pin);
//  nrf_gpio_cfg_output(_sck_pin);
//  nrf_gpio_cfg_output(_sdin_pin);
//  nrf_gpio_cfg_output(_sdout_pin);
//  
//  nrf_gpio_pin_clear(_mck_pin);
//  nrf_gpio_pin_set  (_mck_pin);
//  nrf_gpio_pin_clear(_mck_pin);
//  
//  nrf_gpio_pin_clear(_sck_pin);
//  nrf_gpio_pin_set  (_sck_pin);
//  nrf_gpio_pin_clear(_sck_pin);
//  
//  nrf_gpio_pin_clear(_lrck_pin);
//  nrf_gpio_pin_set  (_lrck_pin);
//  nrf_gpio_pin_clear(_lrck_pin);
//  
//  nrf_gpio_pin_clear(_sdin_pin);
//  nrf_gpio_pin_set  (_sdin_pin);
//  nrf_gpio_pin_clear(_sdin_pin);
//  
//  nrf_gpio_pin_clear(_sdout_pin);
//  nrf_gpio_pin_set  (_sdout_pin);
//  nrf_gpio_pin_clear(_sdout_pin);
  /***********for board testing*****/

    //Map IO pins using the PINSEL registers
#ifndef TRANSMITTER_CH1 // первый передатчик просто генерит MCK дл€ всех
    NRF_I2S->PSEL.MCK   = (_mck_pin   |  (I2S_PSEL_MCK_CONNECT_Disconnected << I2S_PSEL_MCK_CONNECT_Pos));
#else
	NRF_I2S->PSEL.MCK   = (_mck_pin   |  (I2S_PSEL_SCK_CONNECT_Connected << I2S_PSEL_MCK_CONNECT_Pos));
#endif
    
    NRF_I2S->PSEL.SCK   = (_sck_pin   |  (I2S_PSEL_SCK_CONNECT_Connected << I2S_PSEL_SCK_CONNECT_Pos));
    NRF_I2S->PSEL.LRCK  = (_lrck_pin  |  (I2S_PSEL_LRCK_CONNECT_Connected <<I2S_PSEL_LRCK_CONNECT_Pos));
    NRF_I2S->PSEL.SDOUT = (_sdout_pin |  (I2S_PSEL_SDOUT_CONNECT_Connected << I2S_PSEL_SDOUT_CONNECT_Pos));
    NRF_I2S->PSEL.SDIN  = (_sdin_pin  |  (I2S_PSEL_SDIN_CONNECT_Connected << I2S_PSEL_SDIN_CONNECT_Pos));   

    NRF_I2S->CONFIG.ALIGN = I2S_CONFIG_ALIGN_ALIGN_Left <<  I2S_CONFIG_ALIGN_ALIGN_Pos;                   // Alignment = Left
    NRF_I2S->CONFIG.FORMAT = I2S_CONFIG_FORMAT_FORMAT_I2S <<  I2S_CONFIG_FORMAT_FORMAT_Pos;               // Format = I2S
    NRF_I2S->CONFIG.CHANNELS = I2S_CONFIG_CHANNELS_CHANNELS_Stereo << I2S_CONFIG_CHANNELS_CHANNELS_Pos;   // Use stereo
    
#if defined (RECEIVER_LEFT) || defined(RECEIVER_RIGHT)  || defined (TRANSMITTER_CH2)
    // несмотр€ на то что мы в режиме slave, может быть полезно генерировать внутренний MCK, потому что MCK
    NRF_I2S->CONFIG.MCKEN = (I2S_CONFIG_MCKEN_MCKEN_Enabled << I2S_CONFIG_MCKEN_MCKEN_Pos);          
    // c макса идти не будет.“олько LRCLK и BCLK.
    NRF_I2S->CONFIG.MODE = (I2S_CONFIG_MODE_MODE_Slave << I2S_CONFIG_MODE_MODE_Pos);  
     
    //no need for slave mode - LRCK and BCLK are always supplied by the Master to the Slave.
    //set_mck_clock(3);            // MCKFREQ = 8 MHz    
    //_ratio = set_ratio(512);     // LRCLK 15.625KHz 
     
    set_swidth(16);              // Sample width = 16 bit
#endif // RECEIVER_LEFT || RECEIVER_RIGHT || TRANSMITTER_CH2
    
#if defined(TRANSMITTER_CH1) 
    NRF_I2S->CONFIG.MODE = (I2S_CONFIG_MODE_MODE_Master << I2S_CONFIG_MODE_MODE_Pos);
    // Enable MCK generator in master and slave mode.
    NRF_I2S->CONFIG.MCKEN = (I2S_CONFIG_MCKEN_MCKEN_Enabled << I2S_CONFIG_MCKEN_MCKEN_Pos);               // Enable MCK generator 
    
    set_mck_clock(4);            // MCKFREQ = 8 MHz    
    _ratio = set_ratio(512);     // LRCLK 15.625KHz    
    set_swidth(16);              // Sample width = 16 bit    

#endif  // TRANSMITTER_CH1
    
#if  defined (RECEIVER_LEFT) || defined(RECEIVER_RIGHT)        // приемники передедают по шине i2s
    // ѕриемник только принимает звук с ридо-канала и передает его в наушники макса
    NRF_I2S->CONFIG.TXEN = (I2S_CONFIG_TXEN_TXEN_Enabled << I2S_CONFIG_TXEN_TXEN_Pos);     // Enable transmission 
    
    NRF_I2S->TXD.PTR = (uint32_t)output_frame.get_complete_frame();
    NRF_I2S->RXD.PTR = NULL;    
    NRF_I2S->RXTXD.MAXCNT = RAW_FRAMESIZE - 1;
    // configure interrupts
    NRF_I2S->INTENSET = I2S_INTENSET_TXPTRUPD_Msk;
    NRF_I2S->EVENTS_TXPTRUPD = 0;
#endif  // RECEIVER_LEFT || RECEIVER_RIGHT
    
#if defined(TRANSMITTER_CH1) || defined(TRANSMITTER_CH2)   
    // ѕередатчик принимает звук с микрофона и транслирует его в радиоэфир. 
    NRF_I2S->CONFIG.RXEN = (I2S_CONFIG_RXEN_RXEN_Enabled << I2S_CONFIG_RXEN_RXEN_Pos);  // Enable Reception
    
    NRF_I2S->TXD.PTR = NULL;
    NRF_I2S->RXD.PTR = (uint32_t)input_frame.get_empty_frame();    
    NRF_I2S->RXTXD.MAXCNT = RAW_FRAMESIZE - 1;
    // configure interrupts
    NRF_I2S->INTENSET = I2S_INTENSET_RXPTRUPD_Msk;
    NRF_I2S->EVENTS_RXPTRUPD = 0;
#endif  // TRANSMITTER_CH1 || TRANSMITTER_CH2
    
    pause();  // на вс€кий случай приостановим работу прерываний.
    
    nrf_drv_common_irq_enable(I2S_IRQn, I2S_INT_PRIORITY); 
    
    resume(); // «апускаем аудиопоток
}

//  оэффициент делени€ 32Mhz дл€ получени€ MCLK
// возможны следующие коффициенты: 2:3:4:5:6:8:10:11:15:16:21:23:30:31:32:42:63:125
uint8_t i2s::set_mck_clock(uint8_t div)
{
    uint8_t ret;
  
    switch(div)
    {
        case 2 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV2 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 16000.0; //  Mhz
          ret = div;
          break;
        case 3 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV3 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 10666.7; // 10.6666667 MHz
          ret = div;
          break;
        case 4 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV4 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 8000.0; // 8.0 MHz
          ret = div;
          break;
        case 5 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV5 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 6400.0; // 6.4 MHz
          ret = div;
          break;
        case 6 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV6 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 5333.3; // 5.3333333 MHz
          ret = div;
          break;
        case 8 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV8 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 4000.0; // 4.0 MHz
          ret = div;
          break;
        case 10 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV10 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 3200.0; // 3.2 MHz
          ret = div;
          break;
        case 11 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV11 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq =  2909.1; // 2.9090909 MHz
          ret = div;
          break;
        case 15 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV15 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq =  2133.3; // 2.1333333 MHz
          ret = div;
          break;
        case 16 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV16 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 2000.0; // 2.0 MHz
          ret = div;
          break;
        case 21 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV21 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq =  1523.8; // 1.5238095 Mhz
          ret = div;
          break;
        case 23 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV23 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 1391.3; // 1.3913043 MHz
          ret = div;
          break;
        case 30 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV30 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 1066.7; // 1.0666667 MHz
          ret = div;
          break;
        case 31 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV31 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 1032.3; // 1.0322581 MHz
          ret = div;
          break;
        case 32 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV32 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 1000.0; // 1.0 MHz
          ret = div;
          break;
        case 42 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV42 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 761.9; // 0.7619048 MHz
          ret = div;
          break;
        case 63 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV63 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 507.9; // 0.5079365 MHz
          ret = div;
          break;
        case 125 :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV125 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 256.0; // 0.256 MHz
          ret = div;
          break;

        default :
          NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV4 << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
          _mclkfreq = 8000.0; //  8.0 Mhz
          ret = 4;
          break;
    }
  
    return ret; 

}

//  оэффициент делени€ MCLK дл€ получени€ LRCLK
// возможны следующие коффициенты: 32:48:64:96:128:192:256:384:512
uint16_t i2s::set_ratio(uint16_t ratio)
{
    uint16_t ret;
  
    switch(ratio)
    {
        case 32 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_32X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        case 48 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_48X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        case 64 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_64X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        case 96 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_96X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        case 128 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_128X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        case 192 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_192X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        case 256 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_256X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        case 384 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_384X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        case 512 :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_512X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = ratio;
          break;
        default :
          NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_256X << I2S_CONFIG_RATIO_RATIO_Pos;
          ret = 256;
          break;
    }
  
    return ret;  
}

// задает длину кадра, тактируемого LRCLK
// возможны следующие значени€: 8:16:24 в битах, косвенно определ€ет BCLK
uint8_t i2s::set_swidth(uint8_t swidth)
{
    uint8_t ret;
  
    switch(swidth)
    {
        case 8 :
          NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_8Bit << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
          ret = swidth;
          break;
        case 16 :
          NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_16Bit << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
          ret = swidth;
          break;
        case 24 :
          NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_24Bit << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
          ret = swidth;
          break;
        default :
          NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_16Bit << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
          ret = 16;
          break;
    }

    return ret;
}

// return value in KHz
float i2s::get_mclkfreq()
{    
    return _mclkfreq; 
}

// return value in KHz
float i2s::get_lrclk_freq()
{    
    return _mclkfreq/_ratio; 
}
    
void i2s::pause()
{
    NRF_I2S->INTENCLR = I2S_INTENSET_RXPTRUPD_Msk | I2S_INTENSET_TXPTRUPD_Msk;
    NRF_I2S->ENABLE = 0;
    NRF_I2S->TASKS_STOP = 1;
    i2s_paused = true;
}

void i2s::resume()
{  
#if defined (TRANSMITTER_CH1) || defined (TRANSMITTER_CH2)
   NRF_I2S->INTENSET = I2S_INTENSET_RXPTRUPD_Msk;
#endif
#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT)  
   NRF_I2S->INTENSET = I2S_INTENSET_TXPTRUPD_Msk;
#endif
   
    NRF_I2S->ENABLE = 1;
    i2s_paused = false;
    NRF_I2S->TASKS_START = 1;    
    
}

void   i2s::get_input_data()
{
    return;
}
//static uint32_t empty_frame[RAW_FRAMESIZE] = {0};
#pragma optimize=none
void i2s::irq()
{  
      //static int16_t frame_80[RAW_FRAMESIZE] = {0};
      //uint32_t *ptr_left_ch = output_frame.get_left_chnl(output_frame.get_empty_frame());
      //uint32_t *ptr_left_ch;
	  //uint32_t *ptr_right_ch;
      nrf_gpio_pin_set(DBG_PIN_2);
	  
#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
  //Handle received and transmitted data when receiving the TXPTRUPD and RXPTRUPD events
    
  if(NRF_I2S->EVENTS_TXPTRUPD != 0)
  {      
      NRF_I2S->EVENTS_TXPTRUPD = 0; 
      
      i2s_busy = true;
      
      // если нет готовых данных тормозим шину.
      if(!bv32_codec.sound_decode_ready)
      {
          i2s_busy = false;
          
          //NRF_I2S->TXD.PTR = (uint32_t)empty_frame;
          //NRF_I2S->RXTXD.MAXCNT = RECEIVER_SUB_FRAME;
          nrf_gpio_pin_clear(DBG_PIN_2);
      }
      else
      {  
           //NRF_I2S->RXTXD.MAXCNT = RAW_FRAMESIZE - 1;
           NRF_I2S->TXD.PTR = (uint32_t)output_frame.get_complete_frame();
           bv32_codec.sound_decode_ready = false; 
		   
           //ptr_left_ch = output_frame.get_left_chnl(output_frame.get_complete_frame());
			
           // чтобы посмотреть что там в левом и правом каналах на отладке.
           //for(int i = 0; i < RAW_FRAMESIZE; i++)
           //{ 
           //    frame_80[i] = *((int16_t*)ptr_left_ch);
           //    ptr_left_ch++;
           //}
           
           nrf_gpio_pin_clear(DBG_PIN_2);
      }
      
      //output_frame.call_filling_irq();            
  }
  
#endif  // RECEIVER_LEFT ||  RECEIVER_RIGHT

#if defined(TRANSMITTER_CH1) || defined(TRANSMITTER_CH2)
    if(NRF_I2S->EVENTS_RXPTRUPD != 0)
    {
        NRF_I2S->EVENTS_RXPTRUPD = 0;
		
 		i2s_busy = true; 

		// мен€ем заполенный на пустой 
      	input_frame.switch_frames();
		// и отдаем пустой кадр на заполнение данными до следующего прерывани€.
      	NRF_I2S->RXD.PTR = (uint32_t)input_frame.get_empty_frame();
      	//bv32_codec.sound_encode_ready = false;
		NRF_TIMER3->TASKS_CLEAR = 1;	// запускаем последоваетльность отсчетов дл€ передачи пакетов
      	 
      	// чтобы посмотреть что там в левом и правом каналах на отладке.
		//ptr_left_ch = input_frame.get_left_chnl(input_frame.get_complete_frame());
		//ptr_right_ch = input_frame.get_right_chnl(input_frame.get_complete_frame());
      	//for(int i = 0; i < RAW_FRAMESIZE; i++)
      	//{ 
      	//    frame_80[i] = *((int16_t*)ptr_left_ch);
      	//    ptr_left_ch++;
      	//}
      	     
      	nrf_gpio_pin_clear(DBG_PIN_2);     
        //вызываем кодирование прин€тых данных от макса   
        input_frame.call_filling_irq();
    }
#endif
}

// просто инициализируем шину дл€ приема данных с микрофонов или центрального кодека.
#ifdef TRANSMITTER_CH2
extern  i2s  i2s_input_stream(LRCLK_PIN, BCLK_PIN, SDIN_PIN, SDOUT_PIN);

void I2S_IRQHandler(void)
{
    i2s_input_stream.irq();  // обработка прерывани€ шины I2S, тут же вызываетс€ и софтварное прерывание, дл€ заполнени€ буфера кадров.
}

void SWI0_EGU0_IRQHandler()
{
    NRF_EGU0->EVENTS_TRIGGERED[0] = 0;

    // кодируем при€нтые по i2s данные
	bv32_codec.record_handler(&i2s_input_stream.input_frame, radio_unit.radio_encoded_snd_tx);
}
#endif // TRANSMITTER_CH2
