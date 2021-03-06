#include "StepperFSM.h"

void StepperFSM::spin(bool trigger)
{
      eFSMStatus result = FSM_RUN;
    control_func_t cf;
              bool cf_result;
        ledDriver *led = led_list[_prog_ptr[this->stage].action_type];

    if (trigger == true)
    {
        if (this->stage == -1)       // STATE_NONE
        {
            this->count = _prog_ptr[0].count;
            if (this->count == 0)
            {
                status = FSM_NONE;
                return;
            }
            this->stage    = 0;
            this->interval = 0;             
        }
        
        status = result;
        return;                     
    } 
    else
    {
        if (this->stage == -1)
        {
            status = FSM_NONE;
            return;     
        }
    }

    do
    {
        if (this->interval == 0)
        {
            this->interval = (_prog_ptr[this->stage].interval + (TIME_DELTA - 1)) / TIME_DELTA;  // before the action - so that you can fix it in the handler-modifier
                                                                                                 // rounding up is a multiple of TICK_COUNT_INTERVAL
            if (this->interval == 0)
            {
                this->interval = 1;                                                 
            }

            switch (_prog_ptr[this->stage].action_type)
            {
                case OBJECT:                                                      // or we work with the object directly  
                    control_iface_action(led);               
                    break;

                case NO_TO_DO:                                                    // or do nothing - just rewind time and attempts
                    break;

                default:                                                          // or call the object (interface) control function
                    cf = (control_func_t)(_prog_ptr[this->stage].param);          // the parameter is considered a pointer to the function
                    cf_result = cf(led);
                    // if in the end you need to manage the interface then manage
                    if (cf_result == true)                                    
                    {
                        control_iface_action(led);
                    }
                    break;
            }
        } 
        else
        {
            this->interval--;
            if (this->interval == 0)                                                // if the interval is unrolled or the machine has corrected the value - check the number of attempts
            {
                this->count--;
                if (this->count == 0)
                {
                    this->stage++;
                    this->count = _prog_ptr[this->stage].count;
                    if (this->count == 0)                                          // checking the end of the machine program
                    {
                        this->stage = -1;
                        result = FSM_RELEASE;
                        break;                                                      
                    }
                }
            }
        }
    } while (this->interval == 0);

    status = result;
}

bool StepperFSM::control_iface_action(void const *param)
{
    bool result = false;
    
    // define the interface and control action.
    switch(_iface)
    {
        case FSM_LED :
            // run led - ���� ��������.
            result = true;
        break;
        case FSM_RADIO :
            result = true;
        break;
        case FSM_USB :
            result = true;
            break;
        case FSM_BT :
            result = true;
        break;
        default:
            result = false;
        break; 
    }
  
    return result;
}


//-------------------------------------------------------------------------------------------------
// Machine mchn_hello: helloworld with leds.
//-------------------------------------------------------------------------------------------------

static bool func_blink_kb_1_time(ledDriver *led)
{
    static bool toggle = true;

    if(toggle)
        led->light_up();
    else
        led->turn_off();

    toggle = !toggle;

    return false;
}

static bool hello_end(ledDriver *led)
{
    led->turn_off();

    return false;
}

static const FSMStep_t hello_prog[] =
{
    {  1,   500, MOD_LED_KB, (void const*)func_blink_kb_1_time },    
    {  1,   300, NO_TO_DO,   NULL   },
    {  1,   5,   MOD_LED_KB, (void const*)hello_end },

    {0}
};

StepperFSM mchn_hello(FSM_LED, LED_FSM_HELLO, hello_prog);
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Machine mchn_charging: designate that devise is on charge.
//-------------------------------------------------------------------------------------------------
static bool func_blink_kb_2_times(ledDriver *led)
{
    static bool toggle = true;

    if(toggle)
        led->light_up();
    else
        led->turn_off();

    toggle = !toggle;

    return false;
}

static bool charging_end(ledDriver *led)
{
    led->turn_off();

    return false;
}

static const FSMStep_t charging_prog[] =
{
    {  2,   500, MOD_LED_KB, (void const*)func_blink_kb_2_times },    
    {  1,   800, NO_TO_DO,   NULL   },
    {  1,     5, NO_TO_DO,     (void const*)charging_end },

    {0}
};

StepperFSM mchn_charging(FSM_LED, LED_FSM_CHARGING, charging_prog);
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
// Machine mchn_usb_connected: designate that USB is connected
//-------------------------------------------------------------------------------------------------
static bool func_blink_kb_3_times(ledDriver *led)
{
    static bool toggle = true;

    if(toggle)
        led->light_up();
    else
        led->turn_off();

    toggle = !toggle;

    return false;
}

static bool usb_end(ledDriver *led)
{
    led->turn_off();

    return false;
}

static const FSMStep_t usb_prog[] =
{
    {  3,   500, MOD_LED_KB, (void const*)func_blink_kb_3_times },    
    {  1,   800, NO_TO_DO,   NULL   },
    {  1,   5,   MOD_LED_KB, (void const*)usb_end }, 

    {0}
};

StepperFSM mchn_usb_connected(FSM_LED, LED_FSM_USB_CONNECTED, usb_prog);
//-------------------------------------------------------------------------------------------------

StepperFSM *  fsm_list[4] = 
{ 
    &mchn_hello,
    &mchn_charging,
    &mchn_usb_connected,
    nullptr               // needed for poll list purpose
};

