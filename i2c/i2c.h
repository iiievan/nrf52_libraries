#ifndef _I2C_H_
#define _I2C_H_

#include "include.h"
#include "ring_buffer.h"

#ifndef PIN_DISCONNECTED
#define PIN_DISCONNECTED       (0xFFFFFFFFUL)    // Define that pin is disconnected from hardware
#endif

#define SCL_PIN_INIT_CONF     ( (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
                              | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                              | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
                              | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                              | (GPIO_PIN_CNF_DIR_Input      << GPIO_PIN_CNF_DIR_Pos))
#define SDA_PIN_INIT_CONF        SCL_PIN_INIT_CONF

typedef enum
{
    I2C_OK = 0,
    I2C_OVFLOW
}e_i2c_state;

class i2c 
{
public:    
                     i2c();   // конструктор по умолчанию для производных классов.
	                 i2c(uint32_t sda_pin, uint32_t scl_pin, uint8_t i2c_num = 0);           
#if defined(NRF52)
              void   init_master(uint32_t freq = 400);                        // frequency = 100, 250 or 400(by default)
              void   init_slave(uint32_t address);       // frequency = 100, 250 or 400(by default)
#else
              void   init(uint32_t freq = 400 );                              // frequency = 100, 250 or 400(by default)
              void   init(uint32_t address, uint32_t freq = 400);
#endif
              void   set_clock(uint32_t freq);
              void   set_address(uint32_t address); 
              void   enable(void);          
              void   disable(void);

#if defined(NRF52)
           uint8_t   request_from(uint8_t address, size_t len, bool stop_bit);
           uint8_t   request_from(uint8_t address, size_t len);
              void   start_transmission(uint8_t address);
           uint8_t   end_transmission(bool stop_bit);
           uint8_t   end_transmission();
            size_t   write(char data_char);
            size_t   write(const uint8_t *data, size_t len);
 
              void   on_request(void(*function)(void)) { on_request_callback = function; }
              void   on_receive(void(*function)(int))  { on_receive_callback = function; }
              void   on_irq(void);
#else
              bool   write(uint8_t *buf, uint16_t len, bool stop_bit);
              bool   read(uint8_t *buf, uint16_t len);
#endif
              bool   is_busy();

private:
              bool   _bus_busy;     // flag meaning that bus is busy now
              bool   _is_master;    // we are master or slave?
          uint32_t   _sda_pin;      // pin SDA
          uint32_t   _clck_pin;     // pin SCL
      
#if defined(NRF52)
     NRF_TWIM_Type   *_TWIM;        // i2c master with dma.
     NRF_TWIS_Type   *_TWIS;        // i2c slave with dma
         IRQn_Type   _IRQn;         // i2c nvic
     
 ring_buffer<32UL>   _rx_buffer;
ring_buffer<128UL>   _tx_buffer;
           uint8_t   _tx_address;
  
              void   (*on_request_callback)(void);   // callback on request event user function
              void   (*on_receive_callback)(int);    // callback on receive event user function      
#else        
     NRF_TWI_Type    *_TWI;          // i2c without dma support
#endif

};

#endif  // _I2C_H_

