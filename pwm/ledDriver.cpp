#include "ledDriver.h"
#include "board.h"

#ifdef _AUDIOGUDE_V2_BOARD
uint32_t led_2_port_list[LEDS_NUM] = 
{
    LED_SYS_RED_PIN,    // P0.07 LED_SYS_RED 
    LED_SYS_GREEN_PIN,  // P0.05 LED_SYS_GREEN
    LED_BL_BTN_PIN,     // P0.26 LED_BL_BTN 
    LED_BTN_PR_PIN,     // P0.11 LED_BTN_PR  
    LED_KB_PIN,         // P0.25 LED_KB
    LED_BAT_1_PIN,      // P0.08 LED_BAT_1 
    LED_BAT_2_PIN,      // P0.27 LED_BAT_2
    LED_BAT_3_PIN       // P0.06 LED_BAT_3 
}; 

ledDriver    red_led     ( led_2_port_list[LED_SYS_RED],   sys_timer, pwm_agregator, LED_SHORT_BLINK_MS );
ledDriver    green_led   ( led_2_port_list[LED_SYS_GREEN], sys_timer, pwm_agregator, LED_SHORT_BLINK_MS );
ledDriver    bl_btn_led  ( led_2_port_list[LED_BL_BTN],    sys_timer, pwm_agregator, LED_FAST_BLINK_MS );
ledDriver    btn_pr_led  ( led_2_port_list[LED_BTN_PR],    sys_timer, pwm_agregator, LED_FAST_BLINK_MS );
ledDriver    kb_led      ( led_2_port_list[LED_KB],        sys_timer, pwm_agregator, LED_FAST_BLINK_MS );
ledDriver    bat_led_1   ( led_2_port_list[LED_BAT_1_PIN], sys_timer, pwm_agregator, LED_FAST_BLINK_MS );
ledDriver    bat_led_2   ( led_2_port_list[LED_BAT_2_PIN], sys_timer, pwm_agregator, LED_FAST_BLINK_MS );
ledDriver    bat_led_3   ( led_2_port_list[LED_BAT_3_PIN], sys_timer, pwm_agregator, LED_FAST_BLINK_MS );


ledDriver* led_list[LEDS_NUM] =
{ 
    &red_led,
    &green_led,
    &bl_btn_led,
    &btn_pr_led,
    &kb_led,
    &bat_led_1,    
    &bat_led_2,    
    &bat_led_3
};
#endif //_AUDIOGUDE_V2_BOARD

#ifdef _AUDIOGUDE_V3_BOARD
uint32_t led_2_port_list[LEDS_NUM] = 
{
    LED_SYS_GREEN_PIN,  // P0.07 LED_SYS_GREEN 
    LED_BL_BTN_PIN,     // P0.26 LED_BL_BTN 
    LED_BTN_PR_PIN,     // P0.11 LED_BTN_PR  
    LED_KB_PIN,         // P0.25 LED_KB
    LED_BAT_1_PIN,      // P0.08 LED_BAT_1 
    LED_BAT_2_PIN,      // P0.06 LED_BAT_2
    LED_BAT_3_PIN,      // P0.04 LED_BAT_3 
    LED_BAT_4_PIN,      // P0.27 LED_BAT_4
    LED_BAT_5_PIN       // P0.05 LED_BAT_5 
};


ledDriver    green_led   ( led_2_port_list[LED_SYS_GREEN], sys_timer, pwm_agregator, LED_SHORT_BLINK_MS );
ledDriver    bl_btn_led  ( led_2_port_list[LED_BL_BTN],    sys_timer, pwm_agregator, LED_FAST_BLINK_MS  );
ledDriver    btn_pr_led  ( led_2_port_list[LED_BTN_PR],    sys_timer, pwm_agregator, LED_FAST_BLINK_MS  );
ledDriver    kb_led      ( led_2_port_list[LED_KB],        sys_timer, pwm_agregator, LED_FAST_BLINK_MS  );
ledDriver    charge_led_1( led_2_port_list[LED_BAT_1],     sys_timer, pwm_agregator, LED_FAST_BLINK_MS  );
ledDriver    charge_led_2( led_2_port_list[LED_BAT_2],     sys_timer, pwm_agregator, LED_FAST_BLINK_MS  );
ledDriver    charge_led_3( led_2_port_list[LED_BAT_3],     sys_timer, pwm_agregator, LED_FAST_BLINK_MS  );
ledDriver    charge_led_4( led_2_port_list[LED_BAT_4],     sys_timer, pwm_agregator, LED_FAST_BLINK_MS  );
ledDriver    charge_led_5( led_2_port_list[LED_BAT_5],     sys_timer, pwm_agregator, LED_FAST_BLINK_MS  );
 
ledDriver* led_list[LEDS_NUM] =
{ 
    &green_led,
    &bl_btn_led,
    &btn_pr_led,
    &kb_led,
    &charge_led_1,
    &charge_led_2,    
    &charge_led_3,
    &charge_led_4,   
    &charge_led_5
};
#endif

ledDriver::ledDriver(uint32_t  pin_, 
                        Timer &rTmr,
                        hwPWM &rPWM,
                     uint32_t  f_time,  // msec - rise and fall time to max value 
                   ELedBright  max_val,             
                         bool  inverted)
: _rTimer(rTmr),_rPWM_module(rPWM), _max_val(max_val),inversion(inverted) 
{       
    set_fadetime(f_time);    
    _timer = _rTimer.get_ms() - _tout;    

    pin = pin_; 
    nrf_gpio_cfg_output(pin);
    
    for(int i = 0; i < LEDS_NUM; i++)
    {
        if(led_2_port_list[i] == pin)
        {
          led = i;
          break;
        }
    }

    _rPWM_module.linkDriver(this);       
}

// calculate period between increments(dec) of led brightness  and  
// step of incrementaion, so to meet fade time
void ledDriver::set_fadetime(uint32_t f_time)
{       
   volatile int nod;
  
    // calculate the greatest common factor(nod)
    if( _max_val >= f_time)
    {
          nod = ::nod<int>((int)f_time,(int)_max_val);
        _tout = (uint32_t)nod;
        _step = (uint8_t)round((double)(_max_val/(f_time/nod)));
    }
    else
    {
          nod = ::nod<int>((int)f_time,(int)_max_val);
        _tout = (uint32_t)round((double)(f_time/(_max_val/nod)));
        _step = nod;
    }
}

void ledDriver::light_up() 
{
    __disable_interrupt();
  
    _stop();    
    _rPWM_module.setDriver(this, LIGHT_UP);
    
    __enable_interrupt();
} 

// turn off the LED completely
void ledDriver::turn_off() 
{
    __disable_interrupt();
  
    _stop();
    _rPWM_module.setDriver(this, TURN_OFF); 
    
    __enable_interrupt();
}

// set the required brightness of the LED
void ledDriver::bright_set(uint32_t value) 
{   
    __disable_interrupt();

    _stop(); 
    _bright_val = value;
    _rPWM_module.setDriver(this, value);
    
    __enable_interrupt();
}

void ledDriver::run(void)
{ 
    __disable_interrupt();
  
    if (!_need_finish())
    {      
      _status = STS_RUN;
      // infinite fading cycle
      _num_of_rptions = -1;
    }
    
    __enable_interrupt();
} 

void ledDriver::run(int repetitions)
{ 
    __disable_interrupt();
    
    // don't start the driver if
    // the repetitions from previousaction have not been completed.
    if (_num_of_rptions < 0)
    {
        _num_of_rptions = repetitions;
    
        _status = STS_RUN;
    }
    
    __enable_interrupt();
}

void ledDriver::run_up(void)
{ 
    __disable_interrupt();
  
    // if no need finish prevous action
    if (!_need_finish())
    { 
        if(_bright_val < _max_val)    
            _status = STS_RUN_UP;
    }
    
    __enable_interrupt();
} 

void ledDriver::run_down(void)
{ 
    __disable_interrupt();
    
    // if no need finish prevous action
    if (!_need_finish())
    { 
        // commented out: decrease from the current brightness value
        //_bright_val = _max_val;
      if(_bright_val > 0)
        _status = STS_RUN_DOWN;
    }
    
    __enable_interrupt();
} 

void ledDriver::_stop(void)   
{  
    _num_of_rptions = -1;

    _status = STS_RUN_DOWN;

    _timer   = _rTimer.get_ms() - _tout;

    _bright_val = 0;
    _fade_dir   = true;    
}

bool ledDriver::handle(void) 
{  
     bool result = false;

    if(_fade())
        result = true;
    if(_fade_up())
        result = true;
    if(_fade_down())
        result = true;

    return result;
}

bool ledDriver::_fade(void)   
{   
    bool result = false;

    if(_status == STS_RUN)
    {
        result = true;

        if (_rTimer.get_ms() - _timer > (uint64_t)_tout)
        {
             _timer = _rTimer.get_ms();
             
             if(_fade_dir)
             {
                 _bright_val += (int)_step;
                 if(_bright_val < (int)_max_val )
                 { _rPWM_module.setDriver(this,_bright_val); }
                 else
                 { 
                     _bright_val = (int)_max_val;
                     _rPWM_module.setDriver(this,_bright_val);
                     _fade_dir = !_fade_dir;
                 }
             }
             else
             { 
                 _bright_val -= (int)_step;
                 if(_bright_val > 0 )
                 { _rPWM_module.setDriver(this,_bright_val); }
                 else
                 { 
                     _bright_val = 0;
                     _rPWM_module.setDriver(this,_bright_val);
                     _fade_dir = !_fade_dir;
  
                     if(--_num_of_rptions == 0)
                     {   
                        _stop();
  
                        return result;
                     }
                 }
             } 
        }
    }

    return result;
}  

bool ledDriver::_fade_up(void)   
{   
    bool result = false;

    if(_status == STS_RUN_UP)
    {
        result = true;

        if (_rTimer.get_ms() - _timer > (uint64_t)_tout)
        {
            _bright_val += (int)_step;

            if(_bright_val < (int)_max_val )
            { _rPWM_module.setDriver(this,_bright_val); }
            else
            { 
                _bright_val = (int)_max_val;
                _rPWM_module.setDriver(this,_bright_val);

                _status = STS_FINISHED;
            }

            if(_status == STS_FINISHED)
            { _timer   = _rTimer.get_ms() - (uint64_t)_tout; }
            else
            { _timer   = _rTimer.get_ms(); }            
        }
    }

    return result;
} 

bool ledDriver::_fade_down(void)   
{   
    bool result = false;

    if(_status == STS_RUN_DOWN)
    {
        result = true;

        if (_rTimer.get_ms() - _timer > (uint64_t)_tout)
        {
            _bright_val -= (int)_step;

            if(_bright_val > 0 )
            { _rPWM_module.setDriver(this,_bright_val); }
            else
            { 
                _bright_val = 0;

                _rPWM_module.setDriver(this,_bright_val); 

                _status = STS_FINISHED;
            }
             
            if(_status == STS_FINISHED)
            { _timer   = _rTimer.get_ms() - (uint64_t)_tout; }
            else
            { _timer   = _rTimer.get_ms(); } 
        }
    }

    return result;
} 

bool ledDriver::_need_finish(void)
{
    if ( _num_of_rptions > 1)
    { 
        // make this repetiotion last
        _num_of_rptions = 1;
        return true;
    } 
    else
    if (_status == STS_RUN_UP || _status == STS_RUN_DOWN)
    {   
        // let ascending or descending gradient complete
        return true; 
    }
    else
    if (_status == STS_RUN && 
        ( _num_of_rptions < 0))
        return true;
    else
        return false;

}

uint8_t led_drivers_handle(void)
{
    bool busy = false;
    uint8_t  result = 0;
#ifdef _AUDIOGUDE_V3_BOARD
    const uint32_t leds_number = LEDS_NUM;
#endif
#ifdef _AUDIOGUDE_V2_BOARD
    const uint32_t leds_number = LED_BAT_1;
#endif
    
   // handle led drivers
   for (uint32_t i = 0; i < leds_number; i++)
   { 
      if(led_list[i] != NULL)
      { busy = led_list[i]->handle(); } 
       
      // snap the latch       
      if(busy)
      { 
          busy = false;
          result++;
      }
   }

   // return how many LEDs are handled right now 
   return result;
}

