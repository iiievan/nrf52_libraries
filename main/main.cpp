#include <string.h>
#include <ctype.h>
#include <intrinsics.h>
#include "nrf.h"
#include "nrf_gpio.h"

#include "led_driver.h"
#include "nrf_hw_pwm.h"
#include "timer.h"
#include "PowerControl.h"

PowerControl board_power(CHRG_EN_PIN, VBAT_MEAS_PIN, MAIN_MEAS_PIN, SYS_3V0_PIN, MODULE_PWR);

int main()
{
    sys_timer.setIRQ(0, TIMER_1MS_INT_PRIORITY);
    sys_timer.setCallback(sys_timer_callback);
    sys_timer.init(7, 125, true);
    
    board_power.config(CHRG_MAX_CURRENT);
    
    bl_btn_led.run(1);
    kb_led.run(3);
    btn_pr_led.run(7);
    
  	while(1)
  	{        
        red_led.run(1);
  	}
}
