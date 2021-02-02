#ifndef _FSM_SHEDULER_H
#define _FSM_SHEDULER_H

#include "include.h"
#include "fsm.h"
#include "fifo.h"

typedef enum 
{
    FSM_START = 0, 
    FSM_KILL
} fsm_trigger_t;

#ifndef countof
    #define countof(a)  (sizeof(a) / sizeof(*(a)))
#endif

// по сути урезанная карточка автомата, предоставляющая его интрефейс и id
typedef struct _fsm_iface_link_t_
{
  _fsm_iface_link_t_() : iface(FSM_LED),fsm_id(FSM_NOINIT){}
  
    fsm_interface_t     iface;
           fsm_id_t     fsm_id;
} fsm_iface_link_t;

typedef struct
{
         fsm_interface_t    fsm_iface;  //can_iface_t
                fsm_id_t    fsm_id;     //can_ctl_func_id_t
    finite_state_machine   *fsm;        //state_machine_func_t
            fsm_status_t   *fsm_sts;    //state_machine_status_t
} fsm_list_t;

class fsm_sheduler
{
public:    
                            fsm_sheduler(finite_state_machine * const *list): _fsm_list(list),_list_size(countof(list)) {} 

                   // функции управления автоматами из логики программы ->
                   bool     fsm_in_fifo_added(fsm_id_t fsm_id);                     // проверка, добавлен ли автомат в очередь
                   bool     fsm_execute(fsm_id_t fsm_id, fsm_trigger_t fsm_action); // команда на исполнение автомата. true - нужный автомат есть в списке, false - его нет в списке
                   void     delayed_start_handler(void);                            // обработка отложенного старта автомата
           fsm_status_t     fsm_sts_get(fsm_id_t func_id);                          // актуализация статуса автомата
                   void     kill_all_active_fsm(void);                              // убивает все активные на данный момент автоматы
                  // <- функции управления автоматами из логики программы

                   bool     extra_fsm_handler(void);                               // на случай если необходима экстренная обработка автоматов(быстрее чем TIME_DELTA)
                   void     execute_sheduler(void);                                // шедулер крутится в основном цикле.

private:  

    fifo<fsm_iface_link_t, MAX_FSM_FIFO_LEN> _TOTAL_FSM_FIFO;   // буфер вообще всех автоматов
    fifo<fsm_iface_link_t, MAX_ACTIVE_FSM>   _ACTIVE_FSM_FIFO;  // буфер активных в данный момент автоматов    

    finite_state_machine * const    *_fsm_list;    // указатель на список объектов fsm для обработки.
                 const  uint32_t    _list_size;    // размер списка автоматов         
};

extern fsm_sheduler led_list_fsm_sheduler;

#endif