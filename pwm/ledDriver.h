#ifndef _LED_DRIVER_H
#define _LED_DRIVER_H

#include <intrinsics.h>
#include <math.h>
#include "nrf.h"
#include "hwPWM.h"
#include "Timer.h"
#include "board.h"

class hwPWM;

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
} ELedBright;

typedef enum 
{
    STATE_OK     =  1,   /* pin added*/
    ALRDY_IS     =  0,   /* pin already is in sequence*/
    STATE_NA     = -1,   /* no avalable channel */
    CHNL_NA      = -2,   /* pin not included in module */
    REMOVED      = -3,   /* pin removed from sequence*/
} ELEDChannelState;

typedef enum 
{
    STS_NA       = -1,  
    STS_FINISHED =  0,   
    STS_RUN,   
    STS_RUN_UP,  
    STS_RUN_DOWN   
} ELEDDriver_sts;

#define LED_PERIOD_MAX_MS  (1500UL)   
#define LED_SHORT_BLINK_MS (330UL)
#define LED_FAST_BLINK_MS  (560UL)
#define LED_BLINK_MS       (780UL)

class ledDriver
{
public:
             int    pin            {PIN_DISCONNECTED};
             int    led            {-1};
ELEDChannelState    channel        {CHNL_NA};
             int    pwm_module_num {-1};
             bool   inversion;              // PWN output inversion flag

                    ledDriver(uint32_t  pin_, 
                                 Timer &rTmr,
                                 hwPWM &rPWM,
                              uint32_t  f_time  = LED_SHORT_BLINK_MS, // msec - rise and fall time to max value 
                            ELedBright  max_val = LED_BRIGHT_100,
                                  bool  inverted = false); 

            void    run(int repetitions = -1);  // infinite fade by default
            void    run_up(void);
            void    run_down(void);

            void    set_fadetime(uint32_t f_time);

            void    light_up();            // turn on led to his maximum value
            void    turn_off();            // turn off led 
            void    bright_set(uint32_t);  // set led brightness    
                    
            bool    handle(void);          // please handle in 1ms cycle

private:      
            bool    _isNeedFinish(void);   // do need to complete immediately before the next launch?
            void    _stop(void);           // stop current action an turn led off

  ELEDDriver_sts    _status         {STS_NA};   // driver action status
             int    _num_of_rptions {-1};       // number of repetitions of one action

        uint64_t    _timer;               // таймер для измерения промежутков и шагов изменения ШИМ.
           Timer   &_rTimer;
           hwPWM   &_rPWM_module;

        uint16_t    _max_val;             // максимальное значения до которго увеличивается ШИМ (0xFF) 
        uint32_t    _tout;                // таймаут до изменения шага ШИМ     
         uint8_t    _step;                // шаг изменения ШИМ
    
         uint8_t    _led;                 // номер светодиода соответствующего пину. 
            bool    _fade_dir   {true};   // true - увеличиваем яркость, false - уменьшаем
             int    _bright_val { 0 };    // текущее значение яркости светодиода (значения ШИМ);
};

// шаблон нахождения наименьшего общего делителя двух чисел.
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
