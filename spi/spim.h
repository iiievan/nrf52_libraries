#ifndef _SPIM_H_
#define _SPIM_H_

#include "include.h"
#include "ring_buffer.h"

#define SPIM_MODULE_NUM     (0)

#ifndef PIN_DISCONNECTED
#define PIN_DISCONNECTED    (0xFFFFFFFFUL)    // Define that pin is disconnected from hardware
#endif

struct SPIPins_t
{
    uint32_t  mosi_pin;
    uint32_t  miso_pin;
    uint32_t  sck_pin;
    uint32_t  cs_pin;
    int32_t   reset_pin;

       SPIPins_t(uint32_t mosi  = PIN_DISCONNECTED, 
                 uint32_t sck   = PIN_DISCONNECTED, 
                 uint32_t cs    = PIN_DISCONNECTED, 
                 uint32_t miso  = PIN_DISCONNECTED, 
                 uint32_t reset = PIN_DISCONNECTED)
       : mosi_pin(mosi), miso_pin(miso), sck_pin(sck), cs_pin(cs), reset_pin(reset_pin)
       { }

void    config()
        {
            if(miso_pin != PIN_DISCONNECTED)
                nrf_gpio_cfg_input(miso_pin, NRF_GPIO_PIN_PULLUP);
    
            if(mosi_pin != PIN_DISCONNECTED)
            {
                nrf_gpio_cfg_output(mosi_pin);
                nrf_gpio_pin_set(mosi_pin);
            }
        
            if(sck_pin != PIN_DISCONNECTED)
            {
                nrf_gpio_cfg_output(sck_pin);
                nrf_gpio_pin_set(sck_pin);
            }
          
            if(cs_pin != PIN_DISCONNECTED)
            {
                nrf_gpio_cfg_output(cs_pin);
                nrf_gpio_pin_set(cs_pin);
            }

            if(reset_pin != PIN_DISCONNECTED)
            {
                nrf_gpio_cfg_output(reset_pin);
            }
        }

void    hiz()
        {
            hi_z(mosi_pin);
            hi_z(miso_pin);
            hi_z(sck_pin);
            hi_z(cs_pin);
            hi_z(reset_pin);
        }
};	

class spim
{
public:    
	                 spim(SPIPins_t &rPins, uint8_t spi_num = 0);          

              void   init(uint32_t freq = 1000); //freq = 125:250:500:1000:2000:4000:8000
              void   deinit();
			  void   enableSPI(void) { _SPI->ENABLE  = SPI_ENABLE_ENABLE_Enabled; }
			  void   enableSPIM(void){ _SPIM->ENABLE = SPIM_ENABLE_ENABLE_Enabled; }
			         
              void   disable(void)   {   
                                         _SPI->ENABLE = SPI_ENABLE_ENABLE_Disabled;                                       
                                     }

           uint8_t   set_speed(uint32_t freq = 1000);  //freq = 125:250:500:1000:2000:4000:8000

           uint8_t   write(char c);
		   uint8_t   write(const char *data, size_t len);
              void   transfer(const char *out, uint16_t out_len, uint8_t *in, uint16_t in_len);
			  void   isrTransfer(const char *out, uint16_t len);
 
              void   on_irq(void);
		   	  bool   getStartEvent() { return (bool)_SPIM->EVENTS_STARTED; }  //check if spi is busy now

        SPIPins_t   *pins;
			 void    select()        { nrf_gpio_pin_clear(pins->cs_pin); }
			 void    deselect()      { 
			  							    // in case when last sending package
			  							    // is still being send over DMA but PC already exited function
			  							    while(getStartEvent()) {};
  						 				    nrf_gpio_pin_set(pins->cs_pin);
					   				 }
			 void 	 reset_active()  { nrf_gpio_pin_set(pins->reset_pin);}
			 void 	 reset_clear()   { nrf_gpio_pin_clear(pins->reset_pin);}

private:  
  
      NRF_SPI_Type  *_SPI;          // SPI module pointer
     NRF_SPIM_Type  *_SPIM;         // SPIM module pointer
         IRQn_Type   _IRQn;         // irq module
       
              void   (*on_irq_callback)(void);   // callback on request event user function   
};

extern SPIPins_t    SPIpins;
extern      spim    threeLineSPI;

#if(SPIM_MODULE_NUM == 0) 
extern "C" void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler();
#elif (SPIM_MODULE_NUM == 1)
extern "C" void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler();
#elif (SPIM_MODULE_NUM == 2)
extern "C" void SPIM2_SPIS2_SPI2_IRQHandler();
#endif
#endif  //_SPIM_H_

