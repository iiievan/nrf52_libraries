#ifndef _STEPPER_FSM_H
#define _STEPPER_FSM_H

#include <intrinsics.h>
#include <stddef.h>
#include "nrf.h"
#include "ledDriver.h"

class ledDriver;       // ledDriver forward declaration for control_func_t typedef compile

#define TIME_DELTA (5)   // processing interval of machines.

typedef enum
{
    FSM_LED = 0,    // fsm for leds
    FSM_RADIO ,     // fsm for radio unite
    FSM_USB,        // fsm to work with USB
    FSM_BT,         // fsm to work with Bluethooth
    FSM_I2C         // fsm to work with I2C
} eFSMInterface; 

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
} eFSM_id; 

typedef enum 
{
    FSM_NA   = -1,               // начальный статус автомата при инициализации системы, остается таким если его нет в списке автоматов.
    FSM_NONE = 0,             // автомат либо не имеет шагов либо не выполняется
    FSM_RUN,              // автомат работает и выполняет шаги
    FSM_WAIT,             // pending the continuation of work
    FSM_RELEASE,          // автомат только что закончил работу
    FSM_DELAYED_START     // отложенный старт автомата, старт будет в момент следующий проверки статуса автомата.
} eFSMStatus;

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
} actionType_t;

typedef struct
{
         uint16_t   count;        // how many times
         uint16_t   interval;     // with what interval in ms
    actionType_t   action_type;   // what to do
       void const   *param;       // passed parameter (depends on action_type)
} const FSMStep_t;

typedef bool (*control_func_t)(void * pArg);

class StepperFSM
{
public:   
                eFSM_id     ID;
             eFSMStatus     status  {FSM_NA}; // current fsm status
                    int     stage    {-1};    // current step.
                    int     count    {0};     // how many times is left to repeat
                    int     interval {0};     // at what interval.

                            StepperFSM(const eFSMInterface iface, eFSM_id _id, FSMStep_t fsm_prog[]) 
                            : ID(_id), _iface(iface),_prog_ptr(fsm_prog)  {}        
    
          eFSMInterface     get_interface(void) const { return _iface; }
          eFSMInterface     setInterface(ledDriver *driver);

                   void     spin(bool trigger);
                   bool     control_iface_action(void const *param);

private:

      FSMStep_t * const    _prog_ptr;  // pointer on fsm programm.
    const eFSMInterface    _iface;     // interface which fsm interaction     
}; 

extern StepperFSM  mchn_hello;
extern StepperFSM  mchn_charging;
extern StepperFSM  mchn_usb_connected;

extern StepperFSM *fsm_list[];

#endif ///_STEPPER_FSM_H