#include "include.h"
#include "fsm.h"

void finite_state_machine::processing(bool trigger)
{
      fsm_status_t result = FSM_RUN;
    control_func_t cf;
              bool cf_result;
        led_driver *led = led_list[_prog_ptr[this->stage].action_type];

    if (trigger == true)
    {
        if (this->stage == -1)       // STATE_NONE
        {
            this->count = _prog_ptr[0].count;
            if (this->count == 0)
            {
                _status = FSM_NONE;
                return;
            }
            this->stage    = 0;
            this->interval = 0;             
        }
        
        _status = result;
        return;                     
    } 
    else
    {
        if (this->stage == -1)
        {
            _status = FSM_NONE;
            return;     
        }
    }

    do
    {
        if (this->interval == 0)
        {
            this->interval = (_prog_ptr[this->stage].interval + (TIME_DELTA - 1)) / TIME_DELTA;         //����� ��������� - ���� ����� ���� ��������� � �����������-������������
                                                                                                                 //���������� � ������� ������� ������ TICK_COUNT_INTERVAL
            if (this->interval == 0)
            {
                this->interval = 1;                                                 
            }

            switch (_prog_ptr[this->stage].action_type)
            {
                case OBJECT:                                                      // ���� �������� � �������� ��������   
                    control_iface_action(led);               
                    break;

                case NO_TO_DO:                                                    // ���� ������ �� ������ - ������ �������� ����� � �������
                    break;

                default:                                                          // ���� ������� �-��� ���������� ��������(�����������)
                    cf = (control_func_t)(_prog_ptr[this->stage].param);          // �������� ������� ���������� �� �������
                    cf_result = cf(led);
                    // ���� � ����� ����� ��������� ����������� �� ���������
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
            if (this->interval == 0)                                                // ���� �������� ��������� ��� ������� �������� �������� - �������� ���������� �������
            {
                this->count--;
                if (this->count == 0)
                {
                    this->stage++;
                    this->count = _prog_ptr[this->stage].count;
                    if (this->count == 0)                                          // �������� ��������� ��������� ��������
                    {
                        this->stage = -1;
                        result = FSM_RELEASE;
                        break;                                                      // ��������� � Do {} While();
                    }
                }
            }
        }
    } while (this->interval == 0);

    _status = result;
}

bool finite_state_machine::control_iface_action(void const *param)
{
    bool result = false;
    // ���������� ��������� � ����������� �����������.
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
// ������� mchn_hello: ����������� ������������, ��������.
//-------------------------------------------------------------------------------------------------

static bool func_blink_kb_1_time(led_driver *led)
{
    static bool toggle = true;

    if(toggle)
        led->light_up();
    else
        led->turn_off();

    toggle = !toggle;

    return false;
}

static bool hello_end(led_driver *led)
{
    led->turn_off();

    return false;
}

static const fsm_step_t hello_prog[] =
{
    {  1,   500, MOD_LED_KB, (void const*)func_blink_kb_1_time },    
    {  1,   300, NO_TO_DO,   NULL   },
    {  1,   5,   MOD_LED_KB, (void const*)hello_end },

    {0}
};

finite_state_machine mchn_hello(FSM_LED, LED_FSM_HELLO, hello_prog);
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
// ������� mchn_charging: ����������� ��� ���������� �� �������.
//-------------------------------------------------------------------------------------------------
static bool func_blink_kb_2_times(led_driver *led)
{
    static bool toggle = true;

    if(toggle)
        led->light_up();
    else
        led->turn_off();

    toggle = !toggle;

    return false;
}

static bool charging_end(led_driver *led)
{
    led->turn_off();

    return false;
}

static const fsm_step_t charging_prog[] =
{
    {  2,   500, MOD_LED_KB, (void const*)func_blink_kb_2_times },    
    {  1,   800, NO_TO_DO,   NULL   },
    {  1,   5, NO_TO_DO,     (void const*)charging_end },

    {0}
};

finite_state_machine mchn_charging(FSM_LED, LED_FSM_CHARGING, charging_prog);
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
// ������� mchn_usb_connected: ����������� ��� ���������� USB
//-------------------------------------------------------------------------------------------------
static bool func_blink_kb_3_times(led_driver *led)
{
    static bool toggle = true;

    if(toggle)
        led->light_up();
    else
        led->turn_off();

    toggle = !toggle;

    return false;
}

static bool usb_end(led_driver *led)
{
    led->turn_off();

    return false;
}

static const fsm_step_t usb_prog[] =
{
    {  3,   500, MOD_LED_KB, (void const*)func_blink_kb_3_times },    
    {  1,   800, NO_TO_DO,   NULL   },
    {  1,   5,   MOD_LED_KB, (void const*)usb_end }, 

    {0}
};

finite_state_machine mchn_usb_connected(FSM_LED, LED_FSM_USB_CONNECTED, usb_prog);
//-------------------------------------------------------------------------------------------------

finite_state_machine * const fsm_list[4] = 
{ 
    &mchn_hello,
    &mchn_charging,
    &mchn_usb_connected,
    nullptr                    // ����� ����� �������� ������
};
