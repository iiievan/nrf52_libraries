#ifndef _FSM_H
#define _FSM_H

#include "include.h"

#define TIME_DELTA 5   // интервал обработки автоматов.

typedef enum
{
    FSM_LED = 0,    // автомат для светодиодов
    FSM_RADIO ,     // автомат для радиочасти
    FSM_USB,        // автомат для работы с USB
    FSM_BT          // автомат для работы с BT
} fsm_interface_t; 

typedef enum
{
    FSM_NOINIT                          = 0x00,     // автомат не инициализирован
    LED_FSM_HELLO                       = 0x01,     // заставка при старте после перезагрузки системы                   
    LED_FSM_CHARGING                    = 0x02,     // идет зарядка 
    LED_FSM_USB_CONNECTED               = 0x03,     // подключено USB
    LED_FSM_SATELLITE_SEARCH            = 0x04,     // поиск спутника связи 
    LED_FSM_SATELLITE_CONNECT           = 0x05,     // связь со спутником установлена идет прием координат
    LED_FSM_KB_TOGGLE                   = 0x06,     // нажали на какую либо кнопку клавиатуры
    LED_FSM_TRACK_PAUSED                = 0x07,     // нажали на паузу во время проигрывания. 
    LED_FSM_GPS_MATCH                   = 0x08,     // аудиогид в зоне действия gps точки.
    LED_FSM_GPS_LOG_ENABLED             = 0x09,     // активирован режим трекинга GPS
    LED_FSM_MARK_GPS_POSITION           = 0x0A,     // отметить в логе GPS текущее положение в режиме трекинга
} fsm_id_t; 

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
         uint16_t   count;        // сколько раз
         uint16_t   interval;     // с каким интервалом в мс
    action_type_t   action_type;  // что делать
       void const   *param;       // передаваемый параметр (зависит от action_type)
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

        int  stage    {-1};   // текущий шаг автомата.
        int  count    {0};    // сколько раз его осталось повторить.
        int  interval {0};    // с каким интервалом.

private:

     fsm_step_t * const    _prog_ptr;           // указатель на программу автомата.
  const fsm_interface_t    _iface;              // интерфейс на который воздействует автомат.
  const        fsm_id_t    _id;                 // идентификатор автомата.
           fsm_status_t    _status {FSM_NA};    // текущий статус автомата.       
}; 

extern finite_state_machine mchn_hello;
extern finite_state_machine mchn_charging;
extern finite_state_machine mchn_usb_connected;

extern finite_state_machine * const fsm_list[];

#endif