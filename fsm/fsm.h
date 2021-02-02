#ifndef _FSM_H
#define _FSM_H

#include "include.h"

#define TIME_DELTA 5   // �������� ��������� ���������.

typedef enum
{
    FSM_LED = 0,    // ������� ��� �����������
    FSM_RADIO ,     // ������� ��� ����������
    FSM_USB,        // ������� ��� ������ � USB
    FSM_BT          // ������� ��� ������ � BT
} fsm_interface_t; 

typedef enum
{
    FSM_NOINIT                          = 0x00,     // ������� �� ���������������
    LED_FSM_HELLO                       = 0x01,     // �������� ��� ������ ����� ������������ �������                   
    LED_FSM_CHARGING                    = 0x02,     // ���� ������� 
    LED_FSM_USB_CONNECTED               = 0x03,     // ���������� USB
    LED_FSM_SATELLITE_SEARCH            = 0x04,     // ����� �������� ����� 
    LED_FSM_SATELLITE_CONNECT           = 0x05,     // ����� �� ��������� ����������� ���� ����� ���������
    LED_FSM_KB_TOGGLE                   = 0x06,     // ������ �� ����� ���� ������ ����������
    LED_FSM_TRACK_PAUSED                = 0x07,     // ������ �� ����� �� ����� ������������. 
    LED_FSM_GPS_MATCH                   = 0x08,     // �������� � ���� �������� gps �����.
    LED_FSM_GPS_LOG_ENABLED             = 0x09,     // ����������� ����� �������� GPS
    LED_FSM_MARK_GPS_POSITION           = 0x0A,     // �������� � ���� GPS ������� ��������� � ������ ��������
} fsm_id_t; 

typedef enum 
{
    FSM_NA,               // ��������� ������ �������� ��� ������������� �������, �������� ����� ���� ��� ��� � ������ ���������.
    FSM_NONE,             // ������� ���� �� ����� ����� ���� �� �����������
    FSM_RUN,              // ������� �������� � ��������� ����
    FSM_RELEASE,          // ������� ������ ��� �������� ������
    FSM_DELAYED_START     // ���������� ����� ��������, ����� ����� � ������ ��������� �������� ������� ��������.
} fsm_status_t;

typedef enum
{
    MOD_LED_RED         =  0, 
    MOD_LED_GREEN       =  1, 
    MOD_LED_BL_BTN      =  2, 
    MOD_LED_BTN_PR      =  3, 
    MOD_LED_KB          =  4, 
    MOD_LED_CHARGE_BAR  =  5,
    OBJECT             = 254,
    NO_TO_DO           = 255
} action_type_t;

typedef struct
{
         uint16_t   count;        // ������� ���
         uint16_t   interval;     // � ����� ���������� � ��
    action_type_t   action_type;  // ��� ������
       void const   *param;       // ������������ �������� (������� �� action_type)
} const fsm_step_t;

class led_driver;       // led_driver forward declaration for control_func_t typedef compile
typedef bool (*control_func_t)(led_driver *led);

class finite_state_machine
{
public:    
                        finite_state_machine(const fsm_interface_t iface, fsm_id_t id, fsm_step_t fsm_prog[]) : _prog_ptr(fsm_prog),_iface(iface), _id(id) {}        

        fsm_interface_t get_interface(void) const { return _iface; }
               fsm_id_t get_id(void)        const { return _id; }
           fsm_status_t get_status(void)          { return _status;}
                   void processing(bool trigger);
                   bool control_iface_action(void const *param);

        int  stage    {-1};   // ������� ��� ��������.
        int  count    {0};    // ������� ��� ��� �������� ���������.
        int  interval {0};    // � ����� ����������.

private:

     fsm_step_t * const    _prog_ptr;           // ��������� �� ��������� ��������.
  const fsm_interface_t    _iface;              // ��������� �� ������� ������������ �������.
  const        fsm_id_t    _id;                 // ������������� ��������.
           fsm_status_t    _status {FSM_NA};    // ������� ������ ��������.       
}; 

extern finite_state_machine mchn_hello;
extern finite_state_machine mchn_charging;
extern finite_state_machine mchn_usb_connected;

extern finite_state_machine * const fsm_list[];

#endif