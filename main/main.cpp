#include <string.h>
#include <ctype.h>
#include <intrinsics.h>
#include "nrf.h"
#include "nrf_gpio.h"

#include "led_driver.h"
#include "nrf_hw_pwm.h"
#include "ADC.h"
#include "ADC.cpp"
#include "timer.h"
#include "PowerControl.h"

ADC<6> adc_unite(GAIN_1DIV6, BYPASS, ACQ_20us, RES_12B);
PowerControl board_power(CHRG_EN_PIN, VBAT_MEAS_PIN, MAIN_MEAS_PIN, SYS_3V0_PIN, MODULE_PWR);

int main()
{
    sys_timer.setIRQ(0, TIMER_1MS_INT_PRIORITY);
    sys_timer.setCallback(sys_timer_callback);
    sys_timer.init(7, 125, true);
    
    adc_unite.configChannel(AIN_4,GAIN_1DIV4, BYPASS);
    adc_unite.configChannel(AIN_5,GAIN_1DIV4, PULLDOWN);
    adc_unite.configChannel(AIN_6,GAIN_1DIV6, PULLUP);
    adc_unite.configChannel(AIN_7,GAIN_1DIV6, PULLUP);
    
    board_power.config(CHRG_MAX_CURRENT);
    
    bl_btn_led.run(1);
    kb_led.run(3);
    btn_pr_led.run(7);
    
  	while(1)
  	{        
        red_led.run(1);
  	}
}

// because this is template of class, definition of irqhandler done in file where implementation of template is.
void adc_callback(uint32_t value) { return; }
extern "C" void SAADC_IRQHandler() { adc_unite.onIRQ(); }   



