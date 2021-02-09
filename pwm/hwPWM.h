#ifndef __HW_PWM_H
#define __HW_PWM_H

#include <intrinsics.h>
#include <string.h>
#include "nrf.h"
#include "utils.h"
#include "board.h"
#include "ledDriver.h"

class ledDriver;

#ifdef NRF52840_XXAA
#define HWPWM_MODULE_NUM   (4)
#else
#define HWPWM_MODULE_NUM   (3)
#endif

#define MAX_CHANNELS       (4) // Max channel per group

#ifndef PIN_DISCONNECTED
#define PIN_DISCONNECTED   (0xFFFFFFFFUL)    // Define that pin is disconnected from hardware
#endif

#define LIGHT_UP           (0xFFUL)
#define TURN_OFF           (0x00UL)
#define MAX_PWM_VALUE      (0xFFUL)

class hwPWM
{
public:
                         hwPWM(uint16_t clock_div);

                         hwPWM(uint16_t clock_div, ledDriver *driver_1, ledDriver *driver_2, ledDriver *driver_3);  // constructor for specially three pin charge bar module 
                    void setChrgBar(int led_num);      // specially three pin charge bar module    

                    void setMaxValue(uint8_t pwm_index, uint32_t value);       // sets the maximum value to which the PWM is regulated
                    void setClockDiv(uint8_t div = 1);                         // 1:2:4:8:16:32:64:128

                     int addDriver(ledDriver *driver);   // register led driver
                     int setDriver(ledDriver *driver, uint32_t value, bool inverted = false);  // set pwm value to driver
                    void powerDown(void);   // puts the pwm module into low power mode 
                    
 private:
                    void _start(uint8_t  pwm_index);                    // run PWM module
                    void _stop (uint8_t  pwm_index);                    // stop PWM module and turn it to low power
                    void _run_sequence(uint8_t pwm_index);
                    void _setup(uint8_t pwm_index);
                    bool _is_enabled (uint8_t  pwm_index);
 
    static      uint16_t _seq_0[HWPWM_MODULE_NUM][MAX_CHANNELS];    // current PWM values for all channels.
  
                uint16_t _max_value;                                    // maximum numerical value corresponding to the maximum duty cycle PWM
                 uint8_t _clock_div;                                    // prescaler for PWM frequency target
                                      
    static NRF_PWM_Type* _pwm_dev[];                                    // array of pointers to PWM modules
              ledDriver* _charge_bar_led_list[3];

};

extern hwPWM pwm_module;

#endif /* __HW_PWM_H */
