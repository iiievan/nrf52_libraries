#ifndef __POWER_CONTROL_H
#define __POWER_CONTROL_H

#include "board.h"
#include "utils.h"
#include "Timer.h"
#include "ADC.h"
#include "led_driver.h"

//#define CHARGE_250MA_MAX  // limit current 250mA  for sales
#define CHRG_BAT_OK                 (0.95)
#define CHRG_BAT_HYST_OK            (0.87)
#define CHRG_BAT_OFF_MV             (4000)
#define CHARGING_VBAT_MEAS_INTERVAL (50)   // in seconds
#define VINPLUG_CNT_DEF             (20)


typedef enum {
  CHRG_MAX_CURRENT,
  CHRG_MEDIUM_CURRENT,
  CHRG_MIN_CURRENT,
}EChargeCurrents;

typedef enum {
  CHRG_OFF,
  CHRG_ON
}EChargeStatus;

class PowerControl
{
public:
                         PowerControl(uint32_t  charge,                              // charge control pin
                         ADC<ADC_CHANNELS_NUM> &rADC,
                                         Timer &rTmr,
                                   led_driver **chargeLeds, 
                                      uint32_t  battery_meas = PIN_DISCONNECTED,     // battery meas pin
                                      uint32_t  input_meas = PIN_DISCONNECTED,       // input voltage meas pin
                                      uint32_t  supply3V0   = PIN_DISCONNECTED,             // rf power control pin
                                      uint32_t  module = PIN_DISCONNECTED)           // module power control pin
                         : _charge_ctrl_pin(charge),
                           _ADC(rADC),
                           _ms_timer(rTmr),
                           _chargeLeds(chargeLeds),
                           _supply3V0_ctrl_pin(supply3V0),
                           _module_power_ctrl_pin(module),
                           _battery_meas_pin(battery_meas),
                           _input_voltage_meas_pin(input_meas)
                         {}
                  void   config(EChargeCurrents chargeCurrent);    
                  void   enableCharge(EChargeCurrents current);
         EChargeStatus   getChargerStatus();    
                  void   disableCharge()
                         {
                             nrf_gpio_cfg_output(_charge_ctrl_pin);
                             nrf_gpio_pin_set(_charge_ctrl_pin);                    
                         }

                  void   enableModulePwr()  { nrf_gpio_pin_set(_module_power_ctrl_pin); }
                  void   disableModulePwr() { nrf_gpio_pin_clear(_module_power_ctrl_pin);}
                  void   enableSupply3V0()  { nrf_gpio_pin_set(_supply3V0_ctrl_pin); }
                  void   disableSupply3V0() { nrf_gpio_pin_clear(_supply3V0_ctrl_pin);}                
                 float   getBatteryVoltagePercent();
                  void   showBatt(); 
                  void   hideBatt();

                  void   handle(); 

                  bool   chargerConnected {false};
                  bool   powerDown        {false}; 

private:
ADC<ADC_CHANNELS_NUM>   &_ADC;
                Timer   &_ms_timer; 
           led_driver  **_chargeLeds;

              uint32_t   _charge_ctrl_pin ;
              uint32_t   _supply3V0_ctrl_pin       { PIN_DISCONNECTED };
              uint32_t   _module_power_ctrl_pin    { PIN_DISCONNECTED };
       
              uint32_t   _battery_meas_pin         { PIN_DISCONNECTED };
              uint32_t   _input_voltage_meas_pin   { PIN_DISCONNECTED };
       
                   int   _vin_plug_cnt { 0 };
                  bool   _batteryShown {false};
                  float  _vbat_real {0.0f};
};

extern PowerControl power_manager;

#endif // __POWER_CONTROL_H