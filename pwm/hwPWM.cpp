#include "hwPWM.h"

NRF_PWM_Type* hwPWM::_pwm_dev[] =
{
    NRF_PWM0,
    NRF_PWM1,
    NRF_PWM2,
    NRF_PWM3
};

uint16_t  hwPWM::_seq_0[HWPWM_MODULE_NUM][MAX_CHANNELS]      = {0};

hwPWM::hwPWM(uint16_t clock_div)
{       
    setClockDiv(clock_div);    

    for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
    {
        setMaxValue(pwm, (uint32_t)MAX_PWM_VALUE);
        _setup(pwm);
    }
}

hwPWM::hwPWM(uint16_t clock_div, ledDriver **drivers_list)
: _charge_bar_led_list(drivers_list)
{          
    setClockDiv(clock_div);    

    for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
    {
        setMaxValue(pwm, (uint32_t)MAX_PWM_VALUE);
        _setup(pwm);
    }
}

void hwPWM::setChrgBar(int led_num)
{
    static int _old_chrg_bar_state = SHTDWN;  

    // for module work is need tree leds drivers
    for(int i = 0; i < 3; i++)
    {
        if(_charge_bar_led_list[i] == nullptr)
            return;
    }

    // antistrobe
    if (_old_chrg_bar_state != led_num)
    {
        switch(led_num)
        {
            case CHARGE_LED_1:
                setDriver(_charge_bar_led_list[1], 220, true);
                break;
    
            case CHARGE_LED_2:
                setDriver(_charge_bar_led_list[1], 220, true);
                setDriver(_charge_bar_led_list[0], 220, true);
                break;
    
            case CHARGE_LED_3:
                setDriver(_charge_bar_led_list[1], 220, true);
                setDriver(_charge_bar_led_list[0], 220, true);
                setDriver(_charge_bar_led_list[2],        32);
                break;
    
            case CHARGE_LED_4:
                setDriver(_charge_bar_led_list[1], 220, true);
                setDriver(_charge_bar_led_list[0],   0, true);
                setDriver(_charge_bar_led_list[2],        32);
                break;
    
            case CHARGE_LED_5:
                setDriver(_charge_bar_led_list[1], 32);
                setDriver(_charge_bar_led_list[0], 32);
                setDriver(_charge_bar_led_list[2], 45);
                break;
                
            case SHTDWN:
            default:
                setDriver(_charge_bar_led_list[1], 0);
                setDriver(_charge_bar_led_list[0], 0);
                setDriver(_charge_bar_led_list[2], 0);
                break;
        }
    
        _old_chrg_bar_state = led_num;

    }
}

void hwPWM::setMaxValue(uint8_t pwm_index, uint32_t value)
{
    _max_value = value;

    _pwm_dev[pwm_index]->COUNTERTOP = value;
}


// 1:2:4:8:16:32:64:128
void hwPWM::setClockDiv(uint8_t div )
{
    switch (div) {
        case 1:
            _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_1;
            break;
        case 2:
            _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_2;
            break;
        case 4:
            _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_4;
            break;
        case 8:
            _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_8;
            break;
        case 16:
            _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_16;
            break;
        case 32:
            _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_32;
            break;
        case 64:
            _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_64;
            break;
        case 128:
            _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_128;
            break;
        default:
            // by default 16MHz
            _clock_div = PWM_PRESCALER_PRESCALER_DIV_1;
    }
}

int hwPWM::linkDriver(ledDriver *driver)
{
    if(driver->channel != CHNL_NA)
    { return ALRDY_IS; } 

    // find free slot which is not connected
    for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
    {
        for(int i = 0; i < MAX_CHANNELS; i++)
        {
            // this is free slot
            if (_pwm_dev[pwm]->PSEL.OUT[i] & PWM_PSEL_OUT_CONNECT_Msk)
            {
                driver->channel = (ELEDChannelState)i;
                driver->pwm_module_num = pwm;   
                break;
            }
        }
            
        if(driver->channel >= 0)
        { break; }        
     }    
    
    // failed to allocate channel
    if(driver->channel < 0)
    { return driver->channel; } 

        
    // Must disable before changing PSEL
    if (_is_enabled(driver->pwm_module_num))
    {
        _pwm_dev[driver->pwm_module_num]->ENABLE = 0;
        _pwm_dev[driver->pwm_module_num]->PSEL.OUT[driver->channel] = driver->pin;
        _pwm_dev[driver->pwm_module_num]->ENABLE = 1;
    }
    else
    {
        _pwm_dev[driver->pwm_module_num]->PSEL.OUT[driver->channel] = driver->pin;
    }
    
    // stop pwm to avoid random output generation just need set 0 value to sequence
    // and depending on inversion flag
    if(driver->inversion)
        _seq_0[driver->pwm_module_num][driver->channel] = 0x0000; 
    else
        _seq_0[driver->pwm_module_num][driver->channel] = 0x8000; 
    _stop(driver->pwm_module_num);
    
    return STATE_OK;
}

inline int hwPWM::setDriver(ledDriver *driver, uint32_t value, bool inverted)
{
    _seq_0[driver->pwm_module_num][driver->channel] = value | (inverted ? 0 : 1UL << 15);

    // Start PWM if not already
    if (!_is_enabled(driver->pwm_module_num))  
    { _start(driver->pwm_module_num); }
    
    _run_sequence(driver->pwm_module_num);    
    
    return STATE_OK;
}

void hwPWM::powerDown(void)
{  
    for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
    { _stop(pwm); }
}

void hwPWM::_start(uint8_t  pwm_index)
{
    _pwm_dev[pwm_index]->ENABLE  = (PWM_ENABLE_ENABLE_Enabled << PWM_ENABLE_ENABLE_Pos);
}

void hwPWM::_stop(uint8_t  pwm_index)
{
    _pwm_dev[pwm_index]->ENABLE  = (PWM_ENABLE_ENABLE_Disabled << PWM_ENABLE_ENABLE_Pos);
}

void hwPWM::_low_power(uint8_t  pwm_index)
{ 
    uint32_t pin;

    // stop only if module was activated, 
    // otherwise it will just hang on while as TASKS_STOP doesn't work
    // if the module is not active.
    if(_is_enabled(pwm_index))
    {
        _pwm_dev[pwm_index]->TASKS_STOP = 1;
        
        while(!_pwm_dev[pwm_index]->EVENTS_STOPPED);
    }

    // transfer all pins of this module to low power mode
    for (uint8_t i = 0; i < MAX_CHANNELS; i++)
    {
        pin = _pwm_dev[pwm_index]->PSEL.OUT[i];
        if(pin != PIN_DISCONNECTED)
        {
            hi_z(pin);
            _pwm_dev[pwm_index]->PSEL.OUT[i] = PIN_DISCONNECTED;
        }
    }

    // only after all we turn off the module itself, there was the great rake run.    
    _pwm_dev[pwm_index]->ENABLE = 0; 
}

void hwPWM::_run_sequence(uint8_t pwm_index)
{    
    // run PWM
    _pwm_dev[pwm_index]->TASKS_SEQSTART[0] = 1;
}

void hwPWM::_setup(uint8_t pwm_index)
{
    // Initialize Registers
    _pwm_dev[pwm_index]->MODE            = PWM_MODE_UPDOWN_UpAndDown;
    _pwm_dev[pwm_index]->PRESCALER       = (uint32_t)_clock_div;
    _pwm_dev[pwm_index]->DECODER         = (PWM_DECODER_LOAD_Individual << PWM_DECODER_LOAD_Pos) | 
                                           (PWM_DECODER_MODE_RefreshCount << PWM_DECODER_MODE_Pos);
    _pwm_dev[pwm_index]->LOOP            = (PWM_LOOP_CNT_Disabled << PWM_LOOP_CNT_Pos);
    
    _pwm_dev[pwm_index]->SEQ[0].PTR      = (uint32_t) &_seq_0[pwm_index];
    _pwm_dev[pwm_index]->SEQ[0].CNT      = MAX_CHANNELS; // default mode is Individual --> count must be 4
    _pwm_dev[pwm_index]->SEQ[0].REFRESH  = 0;
    _pwm_dev[pwm_index]->SEQ[0].ENDDELAY = 0;
    
    _pwm_dev[pwm_index]->SEQ[1].PTR      = 0;
    _pwm_dev[pwm_index]->SEQ[1].CNT      = 0;
    _pwm_dev[pwm_index]->SEQ[1].REFRESH  = 0;
    _pwm_dev[pwm_index]->SEQ[1].ENDDELAY = 0;
}  

bool hwPWM::_is_enabled (uint8_t  pwm_index)
{
    return _pwm_dev[pwm_index]->ENABLE;
}

#ifdef _AUDIOGUDE_V3_BOARD
hwPWM pwm_agregator(128);
#endif
#ifdef _AUDIOGUDE_V2_BOARD
hwPWM pwm_agregator(128, &led_list[LED_BAT_1_PIN]);
#endif

