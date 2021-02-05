#include "nrf_hw_pwm.h"

NRF_PWM_Type* nrf_hw_pwm::_pwm_dev[] =
{
    NRF_PWM0,
    NRF_PWM1,
    NRF_PWM2,
    NRF_PWM3
};

uint16_t  nrf_hw_pwm::_seq_0[HWPWM_MODULE_NUM][MAX_CHANNELS]      = {0};
 int16_t  nrf_hw_pwm::_pin_allocation_map[LEDS_NUM][INFO_MAP_NUM] = {0};  // карта соответствия led pin chnl pwm
 int16_t  nrf_hw_pwm::_old_chrg_bar_state                         = SHTDWN;

nrf_hw_pwm::nrf_hw_pwm()
{     
    // конструктор по умолчанию пустой, но он нужен
    // потому что сюда заходит каждый раз при создании объекта led_driver
}

nrf_hw_pwm::nrf_hw_pwm(uint16_t clock_div)
{       
    // инициализируем таблицу соответствия каналов
    for (uint8_t k = 0; k < LEDS_NUM; k++)
    {
        _pin_allocation_map[k][PIN_NUM] = REMOVED;   // пин отсутствует
        _pin_allocation_map[k][CHN_NUM] = CHNL_NA;   // канала нет
        _pin_allocation_map[k][PWM_NUM] = STATE_NA;  // номер модуля PWM неизвестен
    }  
    
    // обнуляем таблицу значений PWM
    memset(_seq_0, 0, MAX_CHANNELS);
    set_clock_div(clock_div);    

    for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
    {
        set_max_value(pwm, (uint32_t)MAX_PWM_VALUE);
        _setup(pwm);
    }

    // в данной конфигурации модуля чарджбара нет.
    _chctrl_1 = REMOVED;
    _chctrl_2 = REMOVED;
    _chctrl_3 = REMOVED;
}

nrf_hw_pwm::nrf_hw_pwm(uint16_t clock_div, uint32_t pin_1, uint32_t pin_2, uint32_t pin_3)
{       
    // инициализируем таблицу соответствия каналов
    for (uint8_t k = 0; k < LEDS_NUM; k++)
    {
        _pin_allocation_map[k][PIN_NUM] = REMOVED;   // пин отсутствует
        _pin_allocation_map[k][CHN_NUM] = CHNL_NA;   // канала нет
        _pin_allocation_map[k][PWM_NUM] = STATE_NA;  // номер модуля PWM неизвестен
    }  
    
    // обнуляем таблицу значений PWM
    memset(_seq_0, 0, MAX_CHANNELS);
    set_clock_div(clock_div);    

    for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
    {
        set_max_value(pwm, (uint32_t)MAX_PWM_VALUE);
        _setup(pwm);
    }

    // Добавляем пины и светодиоды для модуля управляения чардж баром.
    add_pin(pin_1);
    add_pin(pin_2);
    add_pin(pin_3);

    _chctrl_1 = _pin_2_led(pin_1);
    _chctrl_2 = _pin_2_led(pin_2);
    _chctrl_3 = _pin_2_led(pin_3);
}

// оставлю на всякий случай на будущее, но в целом оперировать uint8_t разрядностью удобно
// при задании ШИМ.
void nrf_hw_pwm::set_max_value(uint8_t pwm_index, uint32_t value)
{
    _max_value = value;

    _pwm_dev[pwm_index]->COUNTERTOP = value;
}


// 1:2:4:8:16:32:64:128
void nrf_hw_pwm::set_clock_div(uint8_t div )
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
            // по умолчанию ставим 16МГц
            _clock_div = PWM_PRESCALER_PRESCALER_DIV_1;
    }
}

int8_t nrf_hw_pwm::add_pin(uint32_t pin)
{
    volatile      int        ch = CHNL_NA;
    volatile  int16_t       led = _pin_2_led(pin);
               int8_t pwm_index = STATE_NA;

    if(led != REMOVED)
    { return ALRDY_IS; } 

    // find free slot which is not connected
    for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
    {
        for(int i = 0; i < MAX_CHANNELS; i++)
        {
            if ( _pwm_dev[pwm]->PSEL.OUT[i] & PWM_PSEL_OUT_CONNECT_Msk )
            {
                ch = i;
                pwm_index = pwm;   // далее работаем с этим модулем PWM
                break;
            }
        }
            
        if(ch >= 0)
        { break; }        
     }    
    
    // не удалось выделить канал
    if(ch < 0)
    { return ch; } 

    // если все ок, добавляем канал в карту вместе с пином и номером PWM модуля.
    for (uint8_t i = 0; i < LEDS_NUM; i++)
    {
        if (led_2_port_list[i] == pin) 
        {
            _pin_allocation_map[i][PIN_NUM] = (uint8_t)pin;
            _pin_allocation_map[i][CHN_NUM] = (uint8_t)ch;
            _pin_allocation_map[i][PWM_NUM] = (uint8_t)pwm_index;
            break;
        }
    }
    
    nrf_gpio_cfg_output(pin);
    led = _pin_2_led(pin);
    
    // Must disable before changing PSEL
    if (_is_enabled(pwm_index))
    {
        _pwm_dev[pwm_index]->ENABLE = 0;
        _pwm_dev[pwm_index]->PSEL.OUT[ch] = pin;
        _pwm_dev[pwm_index]->ENABLE = 1;
    }
    else
    {
        _pwm_dev[pwm_index]->PSEL.OUT[ch] = pin;
    }
    
    //обнуляем канал
    write_chnl(led, 0);
    
    return STATE_OK;
}

int8_t nrf_hw_pwm::remove_pin(uint8_t led)
{
    int8_t pwm_index = STATE_NA;
  
    // неправильный светодиод
    if (led >= LEDS_NUM)
    { return REMOVED; }

    volatile int ch = (int)_led_2_channel(led);

    // неверный канал
    if (ch < 0)
    return (int16_t)ch; 

    pwm_index = _pin_allocation_map[led][PWM_NUM];

    bool const en = _is_enabled(pwm_index);

    // Must disable before changing PSEL
    if (en) _pwm_dev[pwm_index]->ENABLE = 0;
    
    _pwm_dev[pwm_index]->PSEL.OUT[ch] = PIN_DISCONNECTED;
    
    _seq_0[pwm_index][ch] = 0;
    
    if (en) _pwm_dev[pwm_index]->ENABLE = 1;
    
    return REMOVED;
}

int16_t nrf_hw_pwm::_led_2_channel(uint8_t led)
{
    // нет такого светодиода
    if(led >= LEDS_NUM)
    { return  REMOVED; }

    if ( _pin_allocation_map[led][CHN_NUM] != CHNL_NA)
    {  return _pin_allocation_map[led][CHN_NUM]; } 
    else
    {  
        // нет такого канала
        return CHNL_NA; 
    }    
}

int16_t nrf_hw_pwm::_pin_2_led(uint32_t pin)
{
    for(uint8_t led = 0; led < LEDS_NUM; led++)
    {
        // такой пин уже есть, выходим из функции
        if(_pin_allocation_map[led][PIN_NUM] == pin)
        { return led; }
    }

    // нет такого пина
    return REMOVED;  
}

bool nrf_hw_pwm::_is_enabled (uint8_t  pwm_index)
{
  return _pwm_dev[pwm_index]->ENABLE;
}

void nrf_hw_pwm::start(uint8_t  pwm_index)
{
    _pwm_dev[pwm_index]->ENABLE  = (PWM_ENABLE_ENABLE_Enabled << PWM_ENABLE_ENABLE_Pos);
}

void nrf_hw_pwm::stop(uint8_t  pwm_index)
{ 
    // переводим все ножки этого модуля в режим низкого энергопотребления
    for (uint8_t i = 0; i < LEDS_NUM; i++)
    {
        if (_pin_allocation_map[i][PWM_NUM] == pwm_index) 
        {          
            nrf_gpio_cfg(led_2_port_list[i],
                             NRF_GPIO_PIN_DIR_INPUT,
                             NRF_GPIO_PIN_INPUT_DISCONNECT,
                             NRF_GPIO_PIN_NOPULL,
                             NRF_GPIO_PIN_S0S1,
                             NRF_GPIO_PIN_NOSENSE);
        }
    }
    
    // останавливаем только если модуль был активирован, потому что
    // иначе просто зависнет на while, поскольку TASKS_STOP не работает
    // если модуль не активен.
    if(_is_enabled(pwm_index))
    {
        _pwm_dev[pwm_index]->TASKS_STOP = 1;
        
        while(!_pwm_dev[pwm_index]->EVENTS_STOPPED);
    }
            
    for(uint8_t i = 0; i < MAX_CHANNELS; i++)
    {
        if(_pwm_dev[pwm_index]->PSEL.OUT[i] != PIN_DISCONNECTED)
        { _pwm_dev[pwm_index]->PSEL.OUT[i] = PIN_DISCONNECTED; }     
    }
    
    // только после всего выключаем сам модуль, такие вот грабли.    
    _pwm_dev[pwm_index]->ENABLE = 0;
}

void nrf_hw_pwm::_setup(uint8_t pwm_index)
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

void nrf_hw_pwm::_run_sequence(uint8_t pwm_index)
{    
    // запускаем PWM
    _pwm_dev[pwm_index]->TASKS_SEQSTART[0] = 1;
}

inline int8_t nrf_hw_pwm::write_chnl(uint8_t led, uint32_t value, bool inverted)
{
    uint8_t pwm_index = STATE_NA;
  
    // неправильный светодиод
    if (led >= LEDS_NUM)
    { return REMOVED; }

    volatile int ch = (int)_led_2_channel(led);

    // неверный канал
    if (ch < 0)
    return (int16_t)ch;

    pwm_index = _pin_allocation_map[led][PWM_NUM];

    _seq_0[pwm_index][ch] = value | (inverted ? 0 : 1UL << 15);

    // Start PWM if not already
    if (!_is_enabled(pwm_index))  
    { start(pwm_index); }
    
    _run_sequence(pwm_index);    
    
    return STATE_OK;
}

inline int8_t nrf_hw_pwm::write_pin(uint32_t pin, uint32_t value, bool inverted)
{
    volatile int16_t led = _pin_2_led(pin); 
    
    if(led < ALRDY_IS)
    { return REMOVED; }  
    
    write_chnl(led, value, inverted);
    
    return STATE_OK;
}


int nrf_hw_pwm::read_pin(uint32_t pin)
{
    volatile int16_t led = _pin_2_led(pin); 
    
    if(led < ALRDY_IS)
    { return REMOVED; }
        
    return read_chnl(led);
}

int nrf_hw_pwm::read_chnl(uint8_t led)
{
    int8_t pwm_index = STATE_NA;
    
    // неправильный светодиод
    if (led >= LEDS_NUM)
    { return REMOVED; }

    volatile int ch = (int)_led_2_channel(led);

    // неверный канал
    if (ch < 0)
    return (int16_t)ch;

    pwm_index = _pin_allocation_map[led][PWM_NUM];

    return (_seq_0[pwm_index][ch] & 0x7FFF);
}

int nrf_hw_pwm::get_channel(uint32_t pin)
{
    volatile int16_t led = _pin_2_led(pin); 
    
    if(led < ALRDY_IS)
    { return REMOVED; }  
    
    return _pin_allocation_map[led][CHN_NUM];
}

int nrf_hw_pwm::get_pwm_num(uint32_t pin)
{
    volatile int16_t led = _pin_2_led(pin); 
    
    if(led < ALRDY_IS)
    { return REMOVED; }  
    
    return _pin_allocation_map[led][PWM_NUM];
}

int nrf_hw_pwm::get_led_num(uint32_t pin)
{
    volatile int16_t led = _pin_2_led(pin); 
    
    if(led < ALRDY_IS)
    { return REMOVED; }  
    
    return led;
}

#ifdef THREE_PIN_CHARGE_BAR
void nrf_hw_pwm::set_chrg_bar(int16_t led_num)
{
    // не управляем ни чем если пины удалены.
    if (_chctrl_1 == REMOVED ||
        _chctrl_2 == REMOVED || 
        _chctrl_3 == REMOVED)
    { return; }

    // чтобы не моргало.
    if (_old_chrg_bar_state != led_num)
    {
        switch(led_num)
        {
            case CHARGE_LED_1:
                write_chnl(_chctrl_2, 220, true);
                break;
    
            case CHARGE_LED_2:
                write_chnl(_chctrl_2, 220, true);
                write_chnl(_chctrl_1, 220, true);
                break;
    
            case CHARGE_LED_3:
                write_chnl(_chctrl_2, 220, true);
                write_chnl(_chctrl_1, 220, true);
                write_chnl(_chctrl_3,        32);
                break;
    
            case CHARGE_LED_4:
                write_chnl(_chctrl_2, 220, true);
                write_chnl(_chctrl_1,   0, true);
                write_chnl(_chctrl_3,        32);
                break;
    
            case CHARGE_LED_5:
                write_chnl(_chctrl_2, 32);
                write_chnl(_chctrl_1, 32);
                write_chnl(_chctrl_3, 45);
                break;
                
            case SHTDWN:
            default:
                write_chnl(_chctrl_2, 0);
                write_chnl(_chctrl_1, 0);
                write_chnl(_chctrl_3, 0);
                break;
        }
    
        _old_chrg_bar_state = led_num;

    }
}
#endif // THREE_PIN_CHARGE_BAR




