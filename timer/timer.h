#ifndef __TIMER_H
#define __TIMER_H

#include <intrinsics.h>
#include "nrf.h"

#define I2S_INT_PRIORITY        (2)
#define TIMER_RF_INT_PRIORITY   (3)
#define RADIO_RX_INT_PRIORITY   (4)
#define TIMER_1MS_INT_PRIORITY  (5)
#define SOFTWARE_INT_PRIORITY   (6)
#define RTC_INT_PRIORITY        (7)
#define GPIO_INT_PRIORITY       (7)

#define DELAY_1US               (4)

class Timer
{
public:
                     Timer(uint8_t tmr_num = 0);

              void   init(uint32_t presc, uint32_t compare_val, bool circulary = false); 
              void   deinit();
              void   pause();
              void   resume();

              void   increment(uint32_t dT);
              bool   checkBusy()  const  { return _is_paused; }
          uint64_t   get_ms(void) const;
          uint64_t   get_us(void);
              void   delay_ms(uint32_t ms);
              void   delay_us(uint32_t us);

              void   onIRQ();
              void   setIRQ(uint8_t cc_num, uint8_t priority);   // cc_num:0..5, priority:0..7
              void   setCaptureCompare(uint8_t cc_num, uint8_t value, bool circulary);
              void   setCallback(void(*function)(uint32_t)) { _on_irq_callback = function; }
            
private:
    NRF_TIMER_Type  *_TIMER;
         IRQn_Type   _IRQn;         // irq module
              void (*_on_irq_callback)(uint32_t) { nullptr };   // callback on request event user function

          uint64_t  _time {0}; // the timer itself
              bool  _is_paused { true };
}; 

extern void sys_timer_callback(uint32_t value);
extern Timer sys_timer;

extern "C" void TIMER0_IRQHandler();
extern "C" void TIMER1_IRQHandler();
extern "C" void TIMER2_IRQHandler();
extern "C" void TIMER3_IRQHandler();
extern "C" void TIMER4_IRQHandler();

#endif // __TIMER_H