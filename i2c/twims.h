#ifndef _TWIMS_H_
#define _TWIMS_H_

#include "include.h"
#include "ring_buffer.h"

#ifndef PIN_DISCONNECTED
#define PIN_DISCONNECTED       (0xFFFFFFFFUL)    // Define that pin is disconnected from hardware
#endif

#ifndef SCL_PIN_INIT_CONF
#define SCL_PIN_INIT_CONF     ( (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
                              | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                              | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
                              | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                              | (GPIO_PIN_CNF_DIR_Input      << GPIO_PIN_CNF_DIR_Pos))
#define SDA_PIN_INIT_CONF        SCL_PIN_INIT_CONF
#endif  // SCL_PIN_INIT_CONF

#define TWIMS_MODULE_NUM 1
#define MAIN_I2C_REQ_TOUT   (5)	//периодичность опроса рабов на шине		

class twims
{
public:    
	             twims(uint32_t sda_pin, uint32_t scl_pin, uint8_t i2c_num = 0);           

              void   init_master(uint32_t freq = 400);                        // frequency = 100, 250 or 400(by default)
              void   init_slave(uint32_t address);       // frequency = 100, 250 or 400(by default)

              void   set_clock(uint32_t freq);
              void   set_address(uint32_t address); 
              void   enable(void);          
              void   disable(void);

           uint8_t   request_from(uint8_t address, size_t len, bool stop_bit);
           uint8_t   request_from(uint8_t address, size_t len);
              void   start_transmission(uint8_t address);
           uint8_t   end_transmission(bool stop_bit);
           uint8_t   end_transmission();
            size_t   write(char data_char);
            size_t   write(const char *data, size_t len);

         uint32_t    get_avail(void) { return _rx_buffer.get_avail(); }
             char    get_one(void)   { return _rx_buffer.get_one(); }
 
              void   on_request(void(*function)(void)) { on_request_callback = function; }
              void   on_receive(void(*function)(int))  { on_receive_callback = function; }
              void   on_irq(void);

              bool   is_busy();
              bool   reqData{false};

private:
              bool   _bus_busy;     // flag meaning that bus is busy now
              bool   _is_master;    // we are master or slave?
          uint32_t   _sda_pin;      // pin SDA
          uint32_t   _clck_pin;     // pin SCL
      
     NRF_TWIM_Type   *_TWIM;        // i2c master with dma.
     NRF_TWIS_Type   *_TWIS;        // i2c slave with dma
         IRQn_Type   _IRQn;         // i2c nvic
     
 ring_buffer<32UL>   _rx_buffer;
ring_buffer<128UL>   _tx_buffer;
           uint8_t   _tx_address;
  
              void   (*on_request_callback)(void);   // callback on request event user function
              void   (*on_receive_callback)(int);    // callback on receive event user function      
};

extern twims i2c_main;



#if TWIMS_MODULE_NUM == 0
extern "C" void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler();
#endif
#if TWIMS_MODULE_NUM == 1
extern "C" void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler();
#endif

#endif  // _TWIMS_H_

