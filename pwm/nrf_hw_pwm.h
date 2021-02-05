#ifndef __NRF_HW_PWM_H_
#define __NRF_HW_PWM_H_

#include <intrinsics.h>
#include <string.h>
#include "nrf.h"
#include "board.h"

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

#define LED_PERIOD_MAX_MS  (1500UL)
#define LED_SHORT_BLINK_MS (330UL)
#define LED_FAST_BLINK_MS  (560UL)
#define LED_BLINK_MS       (780UL)

enum 
{
    STATE_OK     =  1,   /* pin added*/
    ALRDY_IS     =  0,   /* pin already is in sequence*/
    STATE_NA     = -1,   /* no avalable channel */
    CHNL_NA      = -2,   /* pin not included in module */
    REMOVED      = -3,   /* pin removed from sequence*/
};

enum
{
   PIN_NUM = 0,
   CHN_NUM,
   PWM_NUM,
   INFO_MAP_NUM
};

class nrf_hw_pwm
{
public:
                         nrf_hw_pwm();  // конструктор по умолчанию дл€ производных классов led_driver.
                         nrf_hw_pwm(uint16_t clock_div);
                         nrf_hw_pwm(uint16_t clock_div, uint32_t pin_1, uint32_t pin_2, uint32_t pin_3);  // конструктор на случай наличи€ модул€ управлени€ индикатором зар€да
              
                    // оставлю на вс€кий случай на будущее, но в целом оперировать uint8_t типом удобно
                    // при задании Ў»ћ.
                    void set_max_value(uint8_t pwm_index, uint32_t value);       // задает максимальное значение, до которого регулируетс€ Ў»ћ
                    void set_clock_div(uint8_t div = 1);                         // 1:2:4:8:16:32:64:128
                  int8_t add_pin(uint32_t pin);                                  // добавл€ет пин в модуль
                  int8_t remove_pin(uint8_t led);                                // убрать пин соответствующий светодиоду
                                 
                    void start(uint8_t  pwm_index);                              // запустить модуль Ў»ћ
                    void stop (uint8_t  pwm_index);                              // остановить модуль Ў»ћ
              
                  // Generate PWM and read values
                  int8_t write_chnl   (uint8_t  led, uint32_t value, bool inverted = false);  // записать в конкретный светодиод(канал)
                  int8_t write_pin    (uint32_t pin, uint32_t value, bool inverted = false);  // записать в конкретный пин
        
                     int read_pin     (uint32_t pin);                                         // прочитать конкретный пин    
                     int read_chnl    (uint8_t  led);                                         // проичитать конкретный светодиод(канал)
                     int get_channel  (uint32_t pin);                                         // получить канал соответствующий конкретному пину     
                     int get_pwm_num  (uint32_t pin);                                         // получить номер Ў»ћ модул€, соответствующего конкретному пину.  
                     int get_led_num  (uint32_t pin);                                         // получить номер светодиода, соответствующего конкретному пину.      
#ifdef THREE_PIN_CHARGE_BAR             
                    void set_chrg_bar(int16_t led_num);                                       // управление зар€дной полоской.
#endif  
 private:
                    void _run_sequence(uint8_t pwm_index);
                    void _setup(uint8_t pwm_index);
                    bool _is_enabled (uint8_t  pwm_index);
                  int8_t _pin_2_all_channels(uint32_t pin);
                  int8_t _pin_2_channel(uint32_t pin);
        
                 int16_t _led_2_channel(uint8_t led);
                 int16_t _pin_2_led(uint32_t pin);
                    bool _check_pin(uint32_t pin) { return _pin_2_channel(pin) >= 0; }
 
    static      uint16_t _seq_0[HWPWM_MODULE_NUM][MAX_CHANNELS];    // массив текущих значений PWM дл€ каждого канала.
    static       int16_t _pin_allocation_map[LEDS_NUM][3];          // карта соответстви€ led_num = pin, channel, pwm
    static       int16_t _old_chrg_bar_state;                       // старое состо€ние чардж бара
  
                uint16_t _max_value;                                // максимальное числовое значение соответствующее максимальной скважности PWM
                 uint8_t _clock_div;                                // предделитель дл€ задачи частоты Ў»ћ
                                      
    static NRF_PWM_Type* _pwm_dev[];                                // массив указателей на модули Ў»ћ

                  int16_t _chctrl_1;                                // пин 1 управлени€ светодиодным индикатором зар€да
                  int16_t _chctrl_2;                                // пин 2 управлени€ светодиодным индикатором зар€да
                  int16_t _chctrl_3;                                // пин 3 управлени€ светодиодным индикатором зар€да

};

#endif /* __NRF_HW_PWM_H_ */
