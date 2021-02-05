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
                         nrf_hw_pwm();  // ����������� �� ��������� ��� ����������� ������� led_driver.
                         nrf_hw_pwm(uint16_t clock_div);
                         nrf_hw_pwm(uint16_t clock_div, uint32_t pin_1, uint32_t pin_2, uint32_t pin_3);  // ����������� �� ������ ������� ������ ���������� ����������� ������
              
                    // ������� �� ������ ������ �� �������, �� � ����� ����������� uint8_t ����� ������
                    // ��� ������� ���.
                    void set_max_value(uint8_t pwm_index, uint32_t value);       // ������ ������������ ��������, �� �������� ������������ ���
                    void set_clock_div(uint8_t div = 1);                         // 1:2:4:8:16:32:64:128
                  int8_t add_pin(uint32_t pin);                                  // ��������� ��� � ������
                  int8_t remove_pin(uint8_t led);                                // ������ ��� ��������������� ����������
                                 
                    void start(uint8_t  pwm_index);                              // ��������� ������ ���
                    void stop (uint8_t  pwm_index);                              // ���������� ������ ���
              
                  // Generate PWM and read values
                  int8_t write_chnl   (uint8_t  led, uint32_t value, bool inverted = false);  // �������� � ���������� ���������(�����)
                  int8_t write_pin    (uint32_t pin, uint32_t value, bool inverted = false);  // �������� � ���������� ���
        
                     int read_pin     (uint32_t pin);                                         // ��������� ���������� ���    
                     int read_chnl    (uint8_t  led);                                         // ���������� ���������� ���������(�����)
                     int get_channel  (uint32_t pin);                                         // �������� ����� ��������������� ����������� ����     
                     int get_pwm_num  (uint32_t pin);                                         // �������� ����� ��� ������, ���������������� ����������� ����.  
                     int get_led_num  (uint32_t pin);                                         // �������� ����� ����������, ���������������� ����������� ����.      
#ifdef THREE_PIN_CHARGE_BAR             
                    void set_chrg_bar(int16_t led_num);                                       // ���������� �������� ��������.
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
 
    static      uint16_t _seq_0[HWPWM_MODULE_NUM][MAX_CHANNELS];    // ������ ������� �������� PWM ��� ������� ������.
    static       int16_t _pin_allocation_map[LEDS_NUM][3];          // ����� ������������ led_num = pin, channel, pwm
    static       int16_t _old_chrg_bar_state;                       // ������ ��������� ����� ����
  
                uint16_t _max_value;                                // ������������ �������� �������� ��������������� ������������ ���������� PWM
                 uint8_t _clock_div;                                // ������������ ��� ������ ������� ���
                                      
    static NRF_PWM_Type* _pwm_dev[];                                // ������ ���������� �� ������ ���

                  int16_t _chctrl_1;                                // ��� 1 ���������� ������������ ����������� ������
                  int16_t _chctrl_2;                                // ��� 2 ���������� ������������ ����������� ������
                  int16_t _chctrl_3;                                // ��� 3 ���������� ������������ ����������� ������

};

#endif /* __NRF_HW_PWM_H_ */
