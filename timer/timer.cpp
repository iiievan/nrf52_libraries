#include "Timer.h"
#include "led_driver.h"

Timer::Timer(uint8_t tmr_num)
{
    switch(tmr_num)
    {        
        case 0:
            _TIMER = NRF_TIMER0;
            _IRQn = TIMER0_IRQn;
            break;
        case 1:
            _TIMER = NRF_TIMER1;
            _IRQn = TIMER1_IRQn;
            break;
        case 2:
            _TIMER = NRF_TIMER2;
            _IRQn = TIMER2_IRQn;
            break;
        case 3:
            _TIMER = NRF_TIMER3;
            _IRQn = TIMER3_IRQn;
            break;
        case 4:
            _TIMER = NRF_TIMER4;
            _IRQn = TIMER4_IRQn;
            break;
        default:
             _TIMER = nullptr;
            break;
    }
}

void    Timer::init(uint32_t presc, uint32_t compare_val, bool circulary)
{
    _TIMER->MODE = TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos;
    _TIMER->BITMODE = TIMER_BITMODE_BITMODE_24Bit << TIMER_BITMODE_BITMODE_Pos;

    _TIMER->PRESCALER = presc << TIMER_PRESCALER_PRESCALER_Pos;
    setCaptureCompare(0, compare_val, circulary);

    resume();
}

 // cc_num:0..5, priority 0..7
void Timer::setIRQ(uint8_t cc_num, uint8_t priority)  
{ 
    switch(cc_num)
    {
        case 0:
            _TIMER->INTENSET |= TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
            break;
        case 1:
            _TIMER->INTENSET |= TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos;
            break;
        case 2:
            _TIMER->INTENSET |= TIMER_INTENSET_COMPARE2_Enabled << TIMER_INTENSET_COMPARE2_Pos;
            break;
        case 3:
            _TIMER->INTENSET |= TIMER_INTENSET_COMPARE3_Enabled << TIMER_INTENSET_COMPARE3_Pos;
            break;
        case 4:
            _TIMER->INTENSET |= TIMER_INTENSET_COMPARE4_Enabled << TIMER_INTENSET_COMPARE4_Pos;
            break;
        case 5:
            _TIMER->INTENSET |= TIMER_INTENSET_COMPARE5_Enabled << TIMER_INTENSET_COMPARE5_Pos;
            break;
        default:
            break;
    }

    NVIC_SetPriority(_IRQn, priority);
    NVIC_ClearPendingIRQ(_IRQn);
    NVIC_EnableIRQ(_IRQn);
}

void Timer::setCaptureCompare(uint8_t cc_num, uint8_t value, bool circulary)  
{ 
    switch(cc_num)
    {
        case 0:
            _TIMER->CC[0] = value;
            break;
        case 1:
            _TIMER->CC[1] = value;
            break;
        case 2:
            _TIMER->CC[2] = value;
            break;
        case 3:
            _TIMER->CC[3] = value;
            break;
        case 4:
            _TIMER->CC[4] = value;
            break;
        case 5:
            _TIMER->CC[5] = value;
            break;
        default:
            break;
    }

    if(circulary)
    {
        switch(cc_num)
        {
            case 0:
                 _TIMER->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;
                break;
            case 1:
                 _TIMER->SHORTS = TIMER_SHORTS_COMPARE1_CLEAR_Enabled << TIMER_SHORTS_COMPARE1_CLEAR_Pos;
                break;
            case 2:
                 _TIMER->SHORTS = TIMER_SHORTS_COMPARE2_CLEAR_Enabled << TIMER_SHORTS_COMPARE2_CLEAR_Pos;
                break;
            case 3:
                 _TIMER->SHORTS = TIMER_SHORTS_COMPARE3_CLEAR_Enabled << TIMER_SHORTS_COMPARE3_CLEAR_Pos;
                break;
            case 4:
                 _TIMER->SHORTS = TIMER_SHORTS_COMPARE4_CLEAR_Enabled << TIMER_SHORTS_COMPARE4_CLEAR_Pos;
                break;
            case 5:
                 _TIMER->SHORTS = TIMER_SHORTS_COMPARE5_CLEAR_Enabled << TIMER_SHORTS_COMPARE5_CLEAR_Pos;
                break;
            default:
                break;
        }      
    }
   
}

void   Timer::increment(uint32_t dT)
{
    __disable_interrupt();

    _time += dT;

    __enable_interrupt();  
}

uint64_t   Timer::get_ms(void) const
{
    uint64_t res;
    
    __disable_interrupt();
    res = _time;
    __enable_interrupt();
    
    return res; 
}

uint64_t   Timer::get_us(void)
{
    uint64_t res;

    __disable_interrupt();

    _TIMER->TASKS_CAPTURE[0] = 0;
    _TIMER->TASKS_CAPTURE[0] = 1;

    res = (uint64_t)_TIMER->CC[0];

    __enable_interrupt();

    res += _time * 1000;

    return res;  
}

void   Timer::pause()
{
    _TIMER->TASKS_STOP = 1;
    _TIMER->TASKS_SHUTDOWN = 1;

    _is_paused = true;
}

void   Timer::resume()
{
    if(_is_paused)
    {
        _TIMER->TASKS_START = 1;
        _is_paused = false;
    }
}

void   Timer::onIRQ()
{
    _TIMER->EVENTS_COMPARE[0] = 0;

    if (_on_irq_callback)
    {
        _on_irq_callback(1);
    }
}

void sys_timer_callback(uint32_t value)
{
    static uint8_t activeLeds = 0;
    
    sys_timer.increment(value);
    
    activeLeds = led_drivers_handle();
    
    UNUSED(activeLeds);
}

Timer sys_timer(0);

extern "C" void TIMER0_IRQHandler(){ sys_timer.onIRQ(); }
extern "C" void TIMER1_IRQHandler(){ return; }
extern "C" void TIMER2_IRQHandler(){ return; }
extern "C" void TIMER3_IRQHandler(){ return; }
extern "C" void TIMER4_IRQHandler(){ return; }