#ifndef __TIMER_H
#define __TIMER_H

#include <intrinsics.h>
#include "nrf.h"
#include "utils.h"

#define I2S_INT_PRIORITY        (2)
#define TIMER_RF_INT_PRIORITY   (3)
#define RADIO_RX_INT_PRIORITY   (4)
#define TIMER_1MS_INT_PRIORITY  (5)
#define SOFTWARE_INT_PRIORITY   (6)
#define RTC_INT_PRIORITY        (7)
#define GPIO_INT_PRIORITY       (7)

#define DELAY_1US               (4)

typedef enum 
{
    TIMER = 0,
    COUNTER,
    LP_COUNTER  
}eTimerMode;

typedef enum 
{
    TMR_CLEAR = 0,
    TMR_STOP
}eTimerShorts;

typedef enum 
{
    DEINIT = 0,
    RUN,
    STOP,
    END
}eTimerSts;

class Timer
{
public:
                     Timer(unsigned int Hz, uint8_t tmr_num = 0, eTimerMode mode = TIMER);

      unsigned int   setFrequency(unsigned int freq = 1000000);     // frequency in Hz
              void   setPeriod(uint8_t cc_num, double period);      // period in useconds
              void   setPeriod(uint8_t cc_num, uint32_t period);    // period in mseconds

              void   setShorts(uint8_t cc_num, eTimerShorts short);
              void   setCaptureCompare(uint8_t cc_num, uint8_t value, bool circulary = false);

              void   init(uint32_t presc, uint32_t compare_val, bool circulary = false); 
              void   deinit();
              void   pause();
              void   resume();

              bool   checkBusy()  const  { return _is_paused; }
          uint64_t   get_ms(void) const;
          uint64_t   get_us(void);
              void   delay_ms(uint32_t ms);
              void   delay_us(uint32_t us);

              void   onIRQ(uint32_t dT);
              void   setIRQ(uint8_t cc_num, uint8_t priority);   // cc_num:0..5, priority:0..7
              
              void   setCallback(void(*function)(uint32_t)) { _on_irq_callback = function; }
            
private:
    NRF_TIMER_Type  *_TIMER;
         IRQn_Type   _IRQn;         // irq module
              void (*_on_irq_callback)(uint32_t value) { nullptr };   // callback on request event user function

          uint64_t  _time {0}; // the timer itself
      unsigned int  _clk_frequency {0}; // frequency of timer clocks
              bool  _is_paused { true };
}; 

extern void sys_timer_callback(uint32_t value);
extern Timer sys_timer;
extern Timer anyTimer;

//extern "C" void TIMER0_IRQHandler();
//extern "C" void TIMER1_IRQHandler();
//extern "C" void TIMER2_IRQHandler();
//extern "C" void TIMER3_IRQHandler();
extern "C" void TIMER4_IRQHandler();

#endif // __TIMER_H