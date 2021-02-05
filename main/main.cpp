#include <string.h>
#include <ctype.h>
#include <intrinsics.h>
#include "nrf.h"
#include "nrf_gpio.h"

#include "led_driver.h"
#include "nrf_hw_pwm.h"
#include "ADC.h"
#include "timer.h"
#include "PowerControl.h"

ADC<ADC_CHANNELS_NUM> adc_unite(RES_12B);
PowerControl power_manager(CHRG_EN_PIN, adc_unite, sys_timer, led_list, VBAT_MEAS_PIN, MAIN_MEAS_PIN, SYS_3V0_PIN, MODULE_PWR);

int main()
{
    sys_timer.setIRQ(0, TIMER_1MS_INT_PRIORITY);
    sys_timer.setCallback(sys_timer_callback);
    sys_timer.init(7, 125, true);
    
    power_manager.config(CHRG_MAX_CURRENT);
    
#ifdef _AUDIOGUDE_V2_BOARD    
    charge_bar.set_chrg_bar(CHARGE_LED_1);
    sys_timer.delay_ms(1300);
    charge_bar.set_chrg_bar(SHTDWN);
    charge_bar.set_chrg_bar(CHARGE_LED_2);
    sys_timer.delay_ms(1300);
    charge_bar.set_chrg_bar(SHTDWN);
    charge_bar.set_chrg_bar(CHARGE_LED_3);
    sys_timer.delay_ms(1300);
    charge_bar.set_chrg_bar(SHTDWN);
    charge_bar.set_chrg_bar(CHARGE_LED_4);
    sys_timer.delay_ms(1300);
    charge_bar.set_chrg_bar(SHTDWN);
    charge_bar.set_chrg_bar(CHARGE_LED_5);
    sys_timer.delay_ms(1300);
    charge_bar.set_chrg_bar(SHTDWN);
    charge_bar.run(1);
    red_led.run(5);
#endif //_AUDIOGUDE_V2_BOARD
    
#ifdef _AUDIOGUDE_V3_BOARD  
    charge_led_1.run(1);
    sys_timer.delay_ms(1300);
    charge_led_1.run(2);
    sys_timer.delay_ms(1300);
    charge_led_1.run(3);
    sys_timer.delay_ms(1300);
    charge_led_1.run(4);
    sys_timer.delay_ms(1300);
    charge_led_1.run(5);
    sys_timer.delay_ms(1300);
#endif //_AUDIOGUDE_V3_BOARD
    
    bl_btn_led.run(1);
    kb_led.run(3);
    btn_pr_led.run(7);
    
  	while(1)
  	{   
        green_led.run(1);
        power_manager.handle();
  	}
}

// because this is template of class, definition of irqhandler done in file where implementation of template is.
void adc_callback(uint32_t value) { return; }
extern "C" void SAADC_IRQHandler() { adc_unite.onIRQ(); }   



