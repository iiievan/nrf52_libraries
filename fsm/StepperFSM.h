#ifndef _STEPPER_FSM_H
#define _STEPPER_FSM_H

#include <intrinsics.h>
#include <stddef.h>
#include "nrf.h"
#include "led_driver.h"

class led_driver;       // led_driver forward declaration for control_func_t typedef compile

#define TIME_DELTA (5)   // processing interval of machines.

typedef enum
{
    FSM_LED = 0,    // fsm for leds
    FSM_RADIO ,     // fsm for radio unite
    FSM_USB,        // fsm to work with USB
    FSM_BT,         // fsm to work with Bluethooth
    FSM_I2C         // fsm to work with I2C
} fsm_interface_t; 

typedef enum
{
    FSM_NOINIT                          = 0x00,     // fsm not initialised
    LED_FSM_HELLO                       = 0x01,     // at system start                   
    LED_FSM_CHARGING                    = 0x02,     // charging in progress 
    LED_FSM_USB_CONNECTED               = 0x03,     // USB is connected
    LED_FSM_SATELLITE_SEARCH            = 0x04,     // GPS satellite search
    LED_FSM_SATELLITE_CONNECT           = 0x05,     // GPS satellite is connect
    LED_FSM_KB_TOGGLE                   = 0x06,     // pressed any keyboard button
    LED_FSM_TRACK_PAUSED                = 0x07,     // track paused 
    LED_FSM_GPS_MATCH                   = 0x08,     // аудиогид в зоне действия gps точки.
    LED_FSM_GPS_LOG_ENABLED             = 0x09,     // активирован режим трекинга GPS
    LED_FSM_MARK_GPS_POSITION           = 0x0A,     // отметить в логе GPS текущее положение в режиме трекинга
} fsmEventID_t; 

typedef enum 
{
    FSM_NA,               // начальный статус автомата при инициализации системы, остается таким если его нет в списке автоматов.
    FSM_NONE,             // автомат либо не имеет шагов либо не выполняется
    FSM_RUN,              // автомат работает и выполняет шаги
    FSM_RELEASE,          // автомат только что закончил работу
    FSM_DELAYED_START     // отложенный старт автомата, старт будет в момент следующий проверки статуса автомата.
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
         uint16_t   count;        // how many times
         uint16_t   interval;     // with what interval in ms
    action_type_t   action_type;  // what to do
       void const   *param;       // passed parameter (depends on action_type)
} const fsm_step_t;

typedef bool (*control_func_t)(led_driver *led);

class StepperFSM
{
public:    
                            StepperFSM(const fsm_interface_t iface, fsmEventID_t id, fsm_step_t fsm_prog[]) : _prog_ptr(fsm_prog),_iface(iface), _id(id) {}        
    
        fsm_interface_t     get_interface(void) const { return _iface; }
           fsmEventID_t     get_id(void)        const { return _id; }
           fsm_status_t     get_status(void)          { return _status;}
                   void     handle(bool trigger);
                   bool     control_iface_action(void const *param);

                    int     stage    {-1};   // текущий шаг автомата.
                    int     count    {0};    // сколько раз его осталось повторить.
                    int     interval {0};    // с каким интервалом.

private:

     fsm_step_t * const    _prog_ptr;           // указатель на программу автомата.
  const fsm_interface_t    _iface;              // интерфейс на который воздействует автомат.
  const    fsmEventID_t    _id;                 // идентификатор автомата.
           fsm_status_t    _status {FSM_NA};    // текущий статус автомата.       
}; 

extern StepperFSM mchn_hello;
extern StepperFSM mchn_charging;
extern StepperFSM mchn_usb_connected;

extern StepperFSM * const fsm_list[];

#endif ///_STEPPER_FSM_H