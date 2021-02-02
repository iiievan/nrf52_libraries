#include "include.h"
#include "spim.h"

 spim::spim(SPIPins_t &rPins, uint8_t spi_num) 
 :pins(&rPins)
{ 	
    switch(spi_num)
    {        
        case 0:
          	 _SPI = NRF_SPI0;
          	_SPIM = NRF_SPIM0;
          	_IRQn = SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn;
            break;
        case 1:
          	 _SPI = NRF_SPI1;
          	_SPIM = NRF_SPIM1;
          	_IRQn = SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn;
            break;
        case 2:
           	_SPI = NRF_SPI2;
           	_SPIM = NRF_SPIM2;
           	_IRQn = SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn;
            break;
        default:
           	 _SPI = NULL;
           	_SPIM = NULL;
            break;
    }
}	

//freq = 125:250:500:1000:2000:4000:8000
void spim::init(uint32_t freq)
{
  	pins->config();
	
	_SPIM->PSEL.MISO = pins->miso_pin;
    _SPIM->PSEL.MOSI = pins->mosi_pin;
    _SPIM->PSEL.SCK  = pins->sck_pin;
	
    set_speed(freq);

    _SPIM->CONFIG    =  (SPI_CONFIG_CPOL_ActiveHigh << SPI_CONFIG_CPOL_Pos) | 
                        (SPI_CONFIG_CPHA_Leading << SPI_CONFIG_CPHA_Pos) | 
                        SPI_CONFIG_ORDER_MsbFirst;
    _SPIM->ORC       = 0xFF;
	
	_SPIM->INTENSET = SPIM_INTENSET_ENDTX_Msk;

    nrf_drv_common_irq_enable(_IRQn,SPI_INT_PRIORITY);
}

void  spim::deinit(void) 
{  
	pins->hiz();
	    
    _SPIM->PSEL.MISO = PIN_DISCONNECTED;
    _SPIM->PSEL.MOSI = PIN_DISCONNECTED;
    _SPIM->PSEL.SCK  = PIN_DISCONNECTED;
	
	disable();
}

//freq = 125:250:500:1000:2000:4000:8000
uint8_t  spim::set_speed(uint32_t freq)
{
    uint8_t ret;
  
    switch(freq)
    {
        case 125 :
          _SPIM->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_K125;
          ret = freq;
          break;
        case 250 :
          _SPIM->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_K250;
          ret = freq;
          break;
        case 500 :
          _SPIM->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_K500;
          ret = freq;
          break;
        case 1000 :
         _SPIM->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_M1;
          ret = freq;
          break;
        case 2000 :
          _SPIM->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_M2;
          ret = freq;
          break;
        case 4000 :
          _SPIM->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_M4;
          ret = freq;
          break;
        case 8000 :
          _SPIM->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_M8;
          ret = freq;
          break;
        default :
          _SPIM->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_K125;
          ret = 125;
          break;
    }
  
    return ret; 
}

uint8_t spim::write(char c)
{
    uint8_t res;

    enableSPI();
    
    _SPI->EVENTS_READY = 0;
    _SPI->TXD = c;

    while (_SPI->EVENTS_READY == 0);
        _SPI->EVENTS_READY = 0;
    
    res = _SPI->RXD;
    
    return res;
}

uint8_t spim::write(const char *data, size_t len)
{    
    for(size_t i = 0; i < len; ++i)
    {
      //Return the number of data stored, when the buffer is full (if write return 0)
      if(!write(data[i]))
          return i;
    }
    
    //All data stored
    return len;
}

void spim::transfer(const char *out, uint16_t out_len, uint8_t *in, uint16_t in_len)
{
    enableSPIM();
  
    //SPI errata  [58] SPIM: An additional byte is clocked out when RXD.MAXCNT = 1
    if (in_len == 1 && out_len <= 1)
        *in = write(*out);
    else
    {
        while (out_len > 0 || in_len > 0)
        {
            _SPIM->TXD.PTR = (uint32_t)out;

            if (out_len >= 255)
              _SPIM->TXD.MAXCNT = 250;
            else
              _SPIM->TXD.MAXCNT = out_len;

            out_len -= _SPIM->TXD.MAXCNT;
            out += _SPIM->TXD.MAXCNT;            
            _SPIM->RXD.PTR = (uint32_t)in;

            if (in_len >= 255)
              _SPIM->RXD.MAXCNT = 250;
            else
              _SPIM->RXD.MAXCNT = in_len;

            in_len -= _SPIM->RXD.MAXCNT;
            in += _SPIM->RXD.MAXCNT;
            
            _SPIM->EVENTS_END = 0;
            _SPIM->TASKS_START = 1;

            while (_SPIM->EVENTS_END == 0);
        }
    }
}

void spim::isrTransfer(const char *out, uint16_t len)
{
  	 static uint8_t inputDummy = 0xFF;	 

     enableSPIM();  

     _SPIM->TXD.PTR = (uint32_t)out;
     _SPIM->TXD.MAXCNT = len;
            
     _SPIM->RXD.PTR = (uint32_t)&inputDummy;
     _SPIM->RXD.MAXCNT = 1UL;
   
     _SPIM->EVENTS_END = 0UL;
     _SPIM->TASKS_START = 1UL;
	 
	 while(!getStartEvent()){};	   
}

void spim::on_irq(void)
{
  	if(_SPIM->EVENTS_ENDTX)
  	{
	  	_SPIM->EVENTS_ENDTX = 0x0UL;
		_SPIM->EVENTS_STARTED = 0x0UL;
		
		if (on_irq_callback)
  	  	{
  	      	on_irq_callback();
  	  	}
  	}	
} 

//3-line SPI with reset optionally
SPIPins_t SPIpins(TFT_SDA, TFT_SCL ,TFT_CS, PIN_DISCONNECTED, TFT_RESET);	//3-line SPI with reset optionally
spim threeLineSPI(SPIpins, SPIM_MODULE_NUM);

#if(SPIM_MODULE_NUM == 0) 
extern "C" void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(){ threeLineSPI.on_irq(); }
#elif (SPIM_MODULE_NUM == 1)
extern "C" void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler(){ threeLineSPI.on_irq(); }
#elif (SPIM_MODULE_NUM == 2)
SPIM2_SPIS2_SPI2_IRQHandler(){ threeLineSPI.on_irq(); }
#endif



