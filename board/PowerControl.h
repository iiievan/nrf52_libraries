#ifndef __POWER_CONTROL_H
#define __POWER_CONTROL_H

#include "board.h"
#include "utils.h"

//#define CHARGE_250MA_MAX  // limit current 250mA  for sales

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
                        PowerControl(uint32_t charge,                              // charge control pin
                                     uint32_t battery_meas = PIN_DISCONNECTED,     // battery meas pin
                                     uint32_t input_meas = PIN_DISCONNECTED,       // input voltage meas pin
                                     uint32_t supply3V0   = PIN_DISCONNECTED,             // rf power control pin
                                     uint32_t module = PIN_DISCONNECTED)           // module power control pin
                        : _charge_ctrl_pin(charge),
                        _supply3V0_ctrl_pin(supply3V0),
                        _module_power_ctrl_pin(module),
                        _battery_meas_pin(battery_meas),
                        _input_voltage_meas_pin(input_meas)
                        {}

                void    config(EChargeCurrents chargeCurrent)
                        {
                            if(_supply3V0_ctrl_pin != PIN_DISCONNECTED)
                            {
                                nrf_gpio_cfg_output(_supply3V0_ctrl_pin);
                                NRF_GPIO->PIN_CNF[_supply3V0_ctrl_pin] |=  GPIO_PIN_CNF_DRIVE_S0H1 << GPIO_PIN_CNF_DRIVE_Pos; 
                            }

                            if(_module_power_ctrl_pin != PIN_DISCONNECTED)
                            {
                                nrf_gpio_cfg_output(_module_power_ctrl_pin);
                            }

                            enableCharge(chargeCurrent);
                            disableSupply3V0();
                            disableModulePwr();
                        }
    
                void    enableCharge(EChargeCurrents current)
                        {
                            switch(current)
                            {
                                case CHRG_MAX_CURRENT:
                                    nrf_gpio_cfg_output(_charge_ctrl_pin);
                                    nrf_gpio_pin_clear(_charge_ctrl_pin);
                                    break;
                                case CHRG_MEDIUM_CURRENT:
                                    nrf_gpio_cfg_input(_charge_ctrl_pin, NRF_GPIO_PIN_NOPULL);
                                    break;
                                case CHRG_MIN_CURRENT:
                                    nrf_gpio_cfg_input(_charge_ctrl_pin, NRF_GPIO_PIN_PULLUP);
                                    break;
                                default:
                                    nrf_gpio_cfg_input(_charge_ctrl_pin, NRF_GPIO_PIN_NOPULL);  // medium 250mA by default
                                    break;
                            }        
                        }
    
                void    disableCharge()
                        {
                            nrf_gpio_cfg_output(_charge_ctrl_pin);
                            nrf_gpio_pin_set(_charge_ctrl_pin);                    
                        }
    
       EChargeStatus    getStatus()
                        {
                            if ((NRF_GPIO->DIR & BIT(_charge_ctrl_pin)) &&
                                (NRF_GPIO->OUT & BIT(_charge_ctrl_pin)))
                                return CHRG_OFF;
                            else
                                return CHRG_ON;
                        }

                void    enableModulePwr()  { nrf_gpio_pin_set(_module_power_ctrl_pin); }
                void    disableModulePwr() { nrf_gpio_pin_clear(_module_power_ctrl_pin);}
                void    enableSupply3V0()  { nrf_gpio_pin_set(_supply3V0_ctrl_pin); }
                void    disableSupply3V0() { nrf_gpio_pin_clear(_supply3V0_ctrl_pin);}

//AnalogDigitalConverter  *pADC;     // for the future implementation
private:
        uint32_t  _charge_ctrl_pin ;
        uint32_t  _supply3V0_ctrl_pin       { PIN_DISCONNECTED };
        uint32_t  _module_power_ctrl_pin    { PIN_DISCONNECTED };

        uint32_t  _battery_meas_pin         { PIN_DISCONNECTED };
        uint32_t  _input_voltage_meas_pin   { PIN_DISCONNECTED };
};

extern PowerControl board_power;

#endif // __POWER_CONTROL_H