#ifndef _I2S_H_
#define _I2S_H_

#include "include.h"
#include "frame_buffer.h"

class i2s
{
public:    
           i2s();   // конструктор по умолчанию для производных классов.
	       i2s(uint32_t mck_pin, uint32_t lrck_pin, uint32_t sck_pin, uint32_t sdin_pin, uint32_t sdout_pin);
           i2s(uint32_t lrck_pin, uint32_t sck_pin, uint32_t sdin_pin, uint32_t sdout_pin);
        void   init();

     uint8_t   set_mck_clock(uint8_t div);      // 2:3:4:5:6:8:10:11:15:16:21:23:30:31:32:42:63:125
    uint16_t   set_ratio(uint16_t ratio);       // 32:48:64:96:128:192:256:384:512
     uint8_t   set_swidth(uint8_t swidth);      // 8:16:24
       float   get_mclkfreq();                  // return value in KHz
       float   get_lrclk_freq();                // return value in KHz
    
        void   pause();
        void   resume();
        void   get_input_data(void);
        
        bool   i2s_paused{false};
        bool   i2s_busy{false};
        
        void   irq();  

   frame_buffer<i2s_sample_t, RAW_FRAMESIZE>     output_frame;    // сдвоенный выходной буфер 
   frame_buffer<i2s_sample_t, RAW_FRAMESIZE>      input_frame;     // сдвоенный входной буфер
private:

        bool   _is_master;      // we are master or slave
       float   _mclkfreq;       // master clock frequency value in KHz
       float   _ratio;          // master clock divider for LRCLK frequency
       
    uint32_t   _mck_pin;  
    uint32_t   _lrck_pin;  
    uint32_t   _sck_pin;  
    uint32_t   _sdin_pin;  
    uint32_t   _sdout_pin;
};

#ifdef TRANSMITTER_CH2
extern  i2s  i2s_input_stream;
extern "C" void I2S_IRQHandler();
extern "C" void SWI0_EGU0_IRQHandler();
#endif // TRANSMITTER_CH2

#endif

