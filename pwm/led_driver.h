#ifndef _LED_DRIVER_H
#define _LED_DRIVER_H

#include "include.h"
#include "nrf_hw_pwm.h"

class led_driver : public nrf_hw_pwm
{
public:
            led_driver(uint32_t pin, uint16_t max_val = LED_BRIGHT_100,  uint32_t f_time = LED_SHORT_BLINK_MS);                              // msec - rise and fall time to max value
            led_driver(uint32_t pin_1, uint32_t pin_2, uint32_t pin_3, uint16_t clock_div,  uint16_t max_val = LED_BRIGHT_100,  uint32_t f_time = LED_SHORT_BLINK_MS); 
            
            void go_power_down(void);   // ��������� ������ pwm � ����� ������� �����������, ����� ���� ������ ���������� �� ������ ������ ����������

            void run(void);
            void run(int repetitions);
            void run_up(void);
            void run_down(void);

            void set_max_val(uint16_t max_val)  { _max_val = max_val; }
            void set_step(uint8_t  step)        { _step    = step;    }
            void set_tout(uint32_t tout)        { _tout    = tout;    }
            void set_fadetime(uint32_t f_time);

            void light_up();            // ������ ��������� �� ��������
            void turn_off();            // �������� ��������� ���������
            void bright_set(uint32_t);  // ���������� �������
    
            // ����������� � �����.
            bool handle(void);          // ������� ��� ��������� � �����    
    
private:

             bool _fade(void);          // ������� ���������� � ���������� �������  
             bool _fade_up(void);       // ������� ���������� �������   
             bool _fade_down(void);     // ������� ���������� ������� 
             bool _need_finish(void);   // ����� �� ��������� ����� ����������� �������� 
             void _stop(void);          // �������� ���������
    
             bool _run;                 // ��������� �� ���������� � ����������� ���������� �������
             bool _run_up;              // ��������� �� ���������� �������
             bool _run_down;            // �� ���������� �������
              int _num_of_rptions;      // ���������� ��������� ������ ����� ��������
    
         uint64_t _timer;               // ������ ��� ��������� ����������� � ����� ��������� ���.
         uint32_t _tout;                // ������� �� ��������� ���� ���
         uint16_t _max_val;             // ������������ �������� �� ������� ������������� ��� (0xFF)      
          uint8_t _step;                // ��� ��������� ���
         uint32_t _fade_time;   
    
          uint8_t _led;                 // ����� ���������� ���������������� ����.
    
             bool _fade_dir;            // true - ����������� �������, false - ���������
             int  _bright_val;                 // ������� �������� ������� ���������� (�������� ���);
};

// ������ ���������� ����������� ������ �������� ���� �����.
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

extern led_driver red_led;       
extern led_driver bl_btn_led; 
extern led_driver btn_pr_led;  
extern led_driver kb_led;
extern led_driver bat_led_1;
extern led_driver bat_led_2;
extern led_driver bat_led_3;
extern led_driver bat_led_4;
extern led_driver bat_led_5;
// LED_BAT_1..3 ������ � ������������� ������ ���� �������� �����
// ����������� �������� � set_chrg_bar
// LED_BAT_2 ����� ��� ��������� ������������ ������� ������� ���������, ������ ��� ���� ������� ������� charge_bar.
//extern led_driver charge_bar;     

extern led_driver* led_list[];

extern uint8_t led_drivers_handle(void);

#endif
