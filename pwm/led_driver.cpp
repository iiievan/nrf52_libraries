#include "led_driver.h"
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

// должен быть создан до того как будут использован в производных классах ниже.
// иначе порушится вся карта пинов и каналов. Т.к. каждый led_driver является производным
// при вызове своего конструктора он сначала вызовет конструктор по умолчанию hw_pwm() - который бессмысленен чуть менее чем полностью)
led_driver    charge_bar  ( led_2_port_list[LED_BAT_1],
                            led_2_port_list[LED_BAT_2],
                            led_2_port_list[LED_BAT_3], 128, &sys_timer);  

led_driver    red_led     ( led_2_port_list[LED_SYS_RED],   &sys_timer, MAX_PWM_VALUE, LED_SHORT_BLINK_MS );
led_driver    green_led   ( led_2_port_list[LED_SYS_GREEN], &sys_timer, MAX_PWM_VALUE, LED_SHORT_BLINK_MS );
led_driver    bl_btn_led  ( led_2_port_list[LED_BL_BTN],    &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    btn_pr_led  ( led_2_port_list[LED_BTN_PR],    &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    kb_led      ( led_2_port_list[LED_KB],        &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );


led_driver* led_list[LEDS_NUM] =
{ 
    &red_led,
    &green_led,
    &bl_btn_led,
    &btn_pr_led,
    &kb_led,
    &charge_bar,    // по сути это LED_BAT_1..3 входят в модуль чардж бара.
    NULL,    
    NULL
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


led_driver    green_led   ( led_2_port_list[LED_SYS_GREEN], &sys_timer, MAX_PWM_VALUE, LED_SHORT_BLINK_MS );
led_driver    bl_btn_led  ( led_2_port_list[LED_BL_BTN],    &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    btn_pr_led  ( led_2_port_list[LED_BTN_PR],    &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    kb_led      ( led_2_port_list[LED_KB],        &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    charge_led_1( led_2_port_list[LED_BAT_1],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    charge_led_2( led_2_port_list[LED_BAT_2],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    charge_led_3( led_2_port_list[LED_BAT_3],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    charge_led_4( led_2_port_list[LED_BAT_4],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
led_driver    charge_led_5( led_2_port_list[LED_BAT_5],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );

led_driver* led_list[LEDS_NUM] =
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

led_driver::led_driver(uint32_t pin, Timer *pTmr, uint16_t max_val,  uint32_t f_time)
: pTimer(pTmr)
{
    if (max_val <= LED_BRIGHT_100)
    _max_val  = max_val;
    else
    _max_val = LED_BRIGHT_100;
    
    _fade_time = f_time;
    
    set_fadetime(f_time);
    
    _timer    = pTimer->get_ms() - _tout;
    
    // добавляем пин, если еще не добавлен.
    add_pin(pin);

    _led = get_led_num(pin);

    _bright_val      = 0;
    _fade_dir = true;
    _run      = false;
    _run_up   = false;
    _run_down = false;
    
    _num_of_rptions = -1;
}

led_driver::led_driver(uint32_t pin_1, 
                       uint32_t pin_2, 
                       uint32_t pin_3, 
                       uint16_t clock_div, 
                       Timer *pTmr,  
                       uint16_t max_val,  
                       uint32_t f_time) 
: nrf_hw_pwm(clock_div, pin_1, pin_2, pin_3),pTimer(pTmr) 
{
    if (max_val <= LED_BRIGHT_100)
    _max_val  = max_val;
    else
    _max_val = LED_BRIGHT_100;
    
    _fade_time = f_time;
    
    set_fadetime(f_time);
    
    _timer    = pTimer->get_ms() - _tout;
    
    _led = get_led_num(pin_2);       // пин 2 является управляющим сам по себе одним светодиодом - первым

    _bright_val      = 0;
    _fade_dir = true;
    _run      = false;
    _run_up   = false;
    _run_down = false;
    
    _num_of_rptions = -1; 

    set_chrg_bar(SHTDWN);
}

void led_driver::go_power_down(void)
{  
    for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
    { nrf_hw_pwm::stop(pwm); }
}

// функция рассичтывает период между инкрементацией свечения светодиода и  
// шаг инкрементации, так чтобы уложиться во период времени за который 
// свечение светодиода поднимется(или опустится) на заданную величину.
void led_driver::set_fadetime(uint32_t f_time)
{       
   volatile int nod;
  
    // рассчитываем наибольший общий делитель
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

void led_driver::light_up() 
{
    __disable_interrupt();
  
    _stop();    
    write_chnl(_led, LIGHT_UP);
    
    __enable_interrupt();
} 

// погасить светодиод полностью
void led_driver::turn_off() 
{
    __disable_interrupt();
  
    _stop();
    write_chnl(_led, TURN_OFF); 
    
    __enable_interrupt();
}

// установить нужную яркость светодиода
void led_driver::bright_set(uint32_t value) 
{   
    __disable_interrupt();

    _stop(); 
    _bright_val = value;
    write_chnl(_led, value);
    
    __enable_interrupt();
}

void led_driver::run(void)
{ 
    __disable_interrupt();
  
    if (!_need_finish())
    {      
      _run = true;
      // запускаем на бесконечное количество вспышек
      _num_of_rptions = -1;
    }
    
    __enable_interrupt();
} 

void led_driver::run(int repetitions)
{ 
    __disable_interrupt();
    
    // не запускаем драйвер если не 
    // отработаны повторы с предыдущей команды запуска.
    if (_num_of_rptions < 0)
    {
        _num_of_rptions = repetitions;
    
        _run = true;
    }
    
    __enable_interrupt();
}

void led_driver::run_up(void)
{ 
    __disable_interrupt();
  
    // если не требуется завершения предыдущей команды
    if (!_need_finish())
    { 
        if(_bright_val < _max_val)    
        _run_up = true;
    }
    
    __enable_interrupt();
} 

void led_driver::run_down(void)
{ 
    __disable_interrupt();
    
    // если не требуется завершения предыдущей команды
    if (!_need_finish())
    { 
        // Закомментил: уменьшаем с текущего значения яркости
        //_bright_val = _max_val;
      if(_bright_val > 0)
        _run_down = true;
    }
    
    __enable_interrupt();
} 

void led_driver::_stop(void)   
{  
    _num_of_rptions = -1;

    _run        = false;
    _run_up     = false;
    _run_down   = false;

    _timer   = pTimer->get_ms() - _tout;

    _bright_val     = 0;
    _fade_dir = true;
    
}

bool led_driver::handle(void) 
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

// размещается в прерывании.
bool led_driver::_fade(void)   
{   
    bool result = false;

    if(_run)
    {
        result = true;

        if (pTimer->get_ms() - _timer > (uint64_t)_tout)
        {
             if(_fade_dir)
             {
                 _bright_val += (int)_step;
                 if(_bright_val < (int)_max_val )
                 { write_chnl(_led,_bright_val); }
                 else
                 { 
                     _bright_val = (int)_max_val;
                     write_chnl(_led,_bright_val);
                     _fade_dir = !_fade_dir;
                 }
             }
             else
             { 
                 _bright_val -= (int)_step;
                 if(_bright_val > 0 )
                 { write_chnl(_led,_bright_val); }
                 else
                 { 
                     _bright_val = 0;
                     write_chnl(_led,_bright_val);
                     _fade_dir = !_fade_dir;
  
                     if(--_num_of_rptions == 0)
                     {   
                        _stop();
  
                        return result;
                     }
                 }
             }
             
             _timer = pTimer->get_ms();
        }
    }

    return result;
}  

// размещается в прерывании.
bool led_driver::_fade_up(void)   
{   
    bool result = false;

    if(_run_up)
    {
        result = true;

        if (pTimer->get_ms() - _timer > (uint64_t)_tout)
        {
            _bright_val += (int)_step;

            if(_bright_val < (int)_max_val )
            { write_chnl(_led,_bright_val); }
            else
            { 
                _bright_val = (int)_max_val;
                write_chnl(_led,_bright_val);

                _run_up = false;
            }

            if(_run_up == false)
            { _timer   = pTimer->get_ms() - (uint64_t)_tout; }
            else
            { _timer   = pTimer->get_ms(); }            
        }
    }

    return result;
} 

// размещается в прерывании.
bool led_driver::_fade_down(void)   
{   
    bool result = false;

    if(_run_down)
    {
        result = true;

        if (pTimer->get_ms() - _timer > (uint64_t)_tout)
        {
            _bright_val -= (int)_step;

            if(_bright_val > 0 )
            { write_chnl(_led,_bright_val); }
            else
            { 
                _bright_val = 0;

                write_chnl(_led,_bright_val); 

                _run_down = false;
            }
             
            if(_run_down == false)
            { _timer   = pTimer->get_ms() - (uint64_t)_tout; }
            else
            { _timer   = pTimer->get_ms(); } 
        }
    }

    return result;
} 

bool led_driver::_need_finish(void)
{
    if ( _num_of_rptions > 1)
    { 
        // драйвер запущен на несколько повторений или
        // на бесконечное количество делаем это последним
        _num_of_rptions = 1;
        return true;
    } 
    else
    if ( _run_up || _run_down )
    {   
        // даем завершиться восходящему или нисходящему градиенту
        return true; 
    }
    else
    if (_run &&( _num_of_rptions < 0))
    {
        // выключаем только по отдельному запуску turn_off() в цикле если запущен
        // на бесконечный повтор
        //turn_off();
        return true;
    }
    else
    { 
        return false;
    }  
}

uint8_t led_drivers_handle(void)
{
    bool busy = false;
    uint8_t  result = 0;
    
   //обработка драйверов светодиодов
   for ( uint32_t i = 0; i < LEDS_NUM; i++)
   { 
      if(led_list[i] != NULL)
      { busy = led_list[i]->handle(); } 
       
      // защелкиваем защелку       
      if(busy)
      { 
          busy = false;
          result++;
      }
   }

   // флажок нужен для того чтобы показать 
   // сколько светодиодов сейчас обрабатываеться
   return result;
}

