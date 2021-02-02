#ifndef _TWI_H_
#define _TWI_H_

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

class twi 
{
public:    
                     twi();   // конструктор по умолчанию для производных классов.
	                 twi(uint32_t sda_pin, uint32_t scl_pin, uint8_t i2c_num = 0);           

              void   init(uint32_t freq = 400 );                              // frequency = 100, 250 or 400(by default)
              void   init(uint32_t address, uint32_t freq = 400);

              void   set_clock(uint32_t freq);
              void   set_address(uint32_t address); 
              void   enable(void);          
              void   disable(void);

              bool   write(uint8_t *buf, uint16_t len, bool stop_bit);  // true - generate stop bit, false - no generate
              bool   read(uint8_t *buf, uint16_t len);

              bool   is_busy();

private:
              bool   _bus_busy;     // flag meaning that bus is busy now
          uint32_t   _sda_pin;      // pin SDA
          uint32_t   _clck_pin;     // pin SCL      
        
     NRF_TWI_Type    *_TWI;          // i2c without dma support
};

#endif  // _TWI_H_

