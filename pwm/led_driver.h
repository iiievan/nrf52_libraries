#ifndef _LED_DRIVER_H
#define _LED_DRIVER_H

#include <intrinsics.h>
#include <math.h>
#include "nrf.h"
#include "nrf_hw_pwm.h"
#include "Timer.h"
#include "board.h"

typedef enum
{
    LED_BRIGHT_0   = 0x00, 
    LED_BRIGHT_10  = 0x19,
    LED_BRIGHT_20  = 0x32,
    LED_BRIGHT_30  = 0x4B, 
    LED_BRIGHT_40  = 0x64,   
    LED_BRIGHT_50  = 0x7D,     
    LED_BRIGHT_60  = 0x96,    
    LED_BRIGHT_70  = 0xAF,    
    LED_BRIGHT_80  = 0xC8,
    LED_BRIGHT_90  = 0xE1,
    LED_BRIGHT_100 = 0xFF
} leds_bright_e;

class led_driver : public nrf_hw_pwm
{
public:
            led_driver(uint32_t pin, Timer *pTmr, uint16_t max_val = LED_BRIGHT_100,  uint32_t f_time = LED_SHORT_BLINK_MS); // msec - rise and fall time to max value
            led_driver(uint32_t pin_1, 
                       uint32_t pin_2, 
                       uint32_t pin_3, 
                       uint16_t clock_div, 
                         Timer *pTmr,  
                       uint16_t max_val = LED_BRIGHT_100,  
                       uint32_t f_time = LED_SHORT_BLINK_MS); 
            
            void go_power_down(void);   // переводит модуль pwm в режим низкого потреблени€, может быть вызван однократно из любого модул€ светодиода

            void run(void);
            void run(int repetitions);
            void run_up(void);
            void run_down(void);

            void set_max_val(uint16_t max_val)  { _max_val = max_val; }
            void set_step(uint8_t  step)        { _step    = step;    }
            void set_tout(uint32_t tout)        { _tout    = tout;    }
            void set_fadetime(uint32_t f_time);

            void light_up();            // зачечь светодиод на максимум
            void turn_off();            // погасить светодиод полностью
            void bright_set(uint32_t);  // установить €ркость
    
            // размещаетс€ в цикле.
            bool handle(void);          // функци€ дл€ обработки в цикле    
            
           Timer *pTimer;
private:

             bool _fade(void);          // плавное увеличение и уменьшение €ркости  
             bool _fade_up(void);       // плавное увеличение €ркости   
             bool _fade_down(void);     // плавное уменьшение €ркости 
             bool _need_finish(void);   // нужно ли завершить перед последующим запуском 
             void _stop(void);          // вырубает светодиод
    
             bool _run;                 // запустить на увеличение и последующее уменьшение €ркости
             bool _run_up;              // запустить на увеличение €ркости
             bool _run_down;            // на уменьшение €ркости
              int _num_of_rptions;      // количество повтроний одного цикла свечени€
    
         uint64_t _timer;               // таймер дл€ измерени€ промежутков и шагов изменени€ Ў»ћ.
         uint32_t _tout;                // таймаут до изменени€ шага Ў»ћ
         uint16_t _max_val;             // максимальное значени€ до которго увеличиваетс€ Ў»ћ (0xFF)      
          uint8_t _step;                // шаг изменени€ Ў»ћ
         uint32_t _fade_time;   
    
          uint8_t _led;                 // номер светодиода соответствующего пину.
    
             bool _fade_dir;            // true - увеличиваем €ркость, false - уменьшаем
             int  _bright_val;                 // текущее значение €ркости светодиода (значени€ Ў»ћ);
};

// шаблон нахождени€ наименьшего общего делител€ двух чисел.
template <typename T>
T nod(T a, T b)
{
    while(a != b)
    { 
        if(a > b)
        { a -= b; }
        else
        { b -=a; }
    }
    
    return a;
}

extern uint8_t led_drivers_handle(void);

#endif
