#include "PowerControl.h"

void    PowerControl::config(EChargeCurrents chargeCurrent)
{
    if(_supply3V0_ctrl_pin != PIN_DISCONNECTED)
    {
        nrf_gpio_cfg_output(_supply3V0_ctrl_pin);
        NRF_GPIO->PIN_CNF[_supply3V0_ctrl_pin] |=  GPIO_PIN_CNF_DRIVE_S0H1 << GPIO_PIN_CNF_DRIVE_Pos; 
    }
    
    if(_module_power_ctrl_pin != PIN_DISCONNECTED)
    {
        nrf_gpio_cfg_output(_module_power_ctrl_pin);

        enableCharge(chargeCurrent);
        disableSupply3V0();
        disableModulePwr();
    }
}

void    PowerControl::enableCharge(EChargeCurrents current)
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

EChargeStatus    PowerControl::getChargerStatus()
{
    if ((NRF_GPIO->DIR & BIT(_charge_ctrl_pin)) &&
        (NRF_GPIO->OUT & BIT(_charge_ctrl_pin)))
        return CHRG_OFF;
    else
        return CHRG_ON;
}

float PowerControl::getBatteryVoltagePercent()
{
    static float prev_vbat = 0.0;
    
           float vin  = _ADC.get(VIN_ADC_VALUE);
           float vbat;
           float vdown, vup, dv = 0.0;
     const float points[] = {2800, 3500, 3600, 3700, 3800, 4000};  
      
    if (chargerConnected)
      vbat = _vbat_real;
    else
      vbat = _ADC.get(VBAT_ADC_VALUE);
    
    // calculate upper boundary 
    vdown = points[0];
    for (uint8_t i = 1; i < sizeof(points)/sizeof(float); i++)
    {
        vup = points[i];

        if (vbat <= vup)
          break;

        dv += 0.2;

        vdown = vup;
    }

    //line approximation
    if (vdown < vbat && vbat <= vup)
      dv += 0.2 * (vbat - vdown) / (vup - vdown);
    
    //get current voltage in %
    if (dv > 1.0)
        dv = 1.0;

    if (dv < 0)
        dv = 0;
    
    //hysteresis in case battery finished charge
    if (prev_vbat < 1.0)
    {
        if (dv > CHRG_BAT_OK)
            dv = 1.0;
    }
    else
    {
        if (dv > CHRG_BAT_HYST_OK)
            dv = 1.0;
    }
    
    prev_vbat = dv;
        
    return 100.0*dv;
}

void    PowerControl::handle()
{
    static uint64_t chargingTmr = 0;
    float vin  = _ADC.get(VIN_ADC_VALUE);
    float vbat = _ADC.get(VBAT_ADC_VALUE);

    if (_vin_plug_cnt)
        --_vin_plug_cnt;

    // periodically turn off charging to find out the real battery voltage during charge
    if((_ms_timer.get_ms() - chargingTmr) > (CHARGING_VBAT_MEAS_INTERVAL * 1000))
    {
        chargingTmr = _ms_timer.get_ms();
        disableCharge();        
        _ms_timer.delay_ms(10);
        _ADC.measure();
        _ms_timer.delay_ms(2);
    }
    
    // update the charger status
    if ((vin > 3000 && 
         vin > vbat + 20) || 
        vin > 4400)
        chargerConnected = true;
    else
        chargerConnected = false;

    // delay to enable full charge
    if ((chargerConnected == false && powerDown) || 
         _ms_timer.get_ms() < ADC_MEAS_INTERVAL/2)
    {
        if ((vin > 3000 && 
             vin > vbat + 20) ||
            vin > 4400)
        {
            _vin_plug_cnt = rnd_max(VINPLUG_CNT_DEF) + (int)(VINPLUG_CNT_DEF * 0.5);
            disableCharge();
        }
    }

    //turn on charge 
    if ((CHRG_OFF == getChargerStatus() && 
         vbat < CHRG_BAT_OFF_MV) || 
        chargerConnected == false || 
        _vin_plug_cnt) 
    {
         _vbat_real = vbat;
         
        //turn on charging with delay so that there is not a large surge of current on the charging,
        // on which many devices are installed
        if (_vin_plug_cnt <= 1) 
            enableCharge(CHRG_MAX_CURRENT);
        else if (1 < _vin_plug_cnt && _vin_plug_cnt < VINPLUG_CNT_DEF/2)
            enableCharge(CHRG_MEDIUM_CURRENT);
        else if (vbat < 3000)
            enableCharge(CHRG_MEDIUM_CURRENT);
        else
            disableCharge();
    }
    
    if(chargerConnected)
        showBatt();
    else
        hideBatt();
}

void PowerControl::showBatt()
{
    static int8_t   current_bar_value {SHTDWN};
    static int8_t   last_bar_value {CHARGE_LED_1};
    
    float vbat_proc = getBatteryVoltagePercent(); 
    
    if (vbat_proc > 80 && vbat_proc <= 100)
        current_bar_value = CHARGE_LED_5;
    if (vbat_proc > 60 && vbat_proc <= 80)
        current_bar_value = CHARGE_LED_4;
    if (vbat_proc > 40 && vbat_proc <= 60)
        current_bar_value = CHARGE_LED_3;
    if (vbat_proc > 20 && vbat_proc <= 40)
        current_bar_value = CHARGE_LED_2; 
    if (vbat_proc > 6 && vbat_proc <= 20)
        current_bar_value = CHARGE_LED_1;  

#ifdef _AUDIOGUDE_V2_BOARD
    // LED_BAT_1 is reference on charge_bar object in led_list 
    _chargeLeds[LED_BAT_1]->set_chrg_bar(current_bar_value);
    
    UNUSED(last_bar_value);
#endif  //_AUDIOGUDE_V2_BOARD

#ifdef _AUDIOGUDE_V3_BOARD    
    if(current_bar_value > last_bar_value)
    {
        for(int i = last_bar_value; i <= current_bar_value; i++)
          _chargeLeds[i]->light_up();
    }
    else
    {
        for(int i = last_bar_value; i > current_bar_value; i--)
          _chargeLeds[i]->turn_off();
    }
    
    if (vbat_proc <= 6)
        _chargeLeds[LED_BAT_1]->run();   // just blinkin the only (first) LED
#endif
    
   _batteryShown = true; 
}

void PowerControl::hideBatt()
{
    if(_batteryShown)
    {    
#ifdef _AUDIOGUDE_V2_BOARD
        _chargeLeds[LED_BAT_1]->set_chrg_bar(SHTDWN);
#endif  //_AUDIOGUDE_V2_BOARD

#ifdef _AUDIOGUDE_V3_BOARD
        for(uint8_t i = CHARGE_LED_1; i < LEDS_NUM; i++)
            _chargeLeds[i]->turn_off();
#endif //_AUDIOGUDE_V3_BOARD
        _batteryShown = false;
    }
}