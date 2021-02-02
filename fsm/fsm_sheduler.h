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

// �� ���� ��������� �������� ��������, ��������������� ��� ��������� � id
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

                   // ������� ���������� ���������� �� ������ ��������� ->
                   bool     fsm_in_fifo_added(fsm_id_t fsm_id);                     // ��������, �������� �� ������� � �������
                   bool     fsm_execute(fsm_id_t fsm_id, fsm_trigger_t fsm_action); // ������� �� ���������� ��������. true - ������ ������� ���� � ������, false - ��� ��� � ������
                   void     delayed_start_handler(void);                            // ��������� ����������� ������ ��������
           fsm_status_t     fsm_sts_get(fsm_id_t func_id);                          // ������������ ������� ��������
                   void     kill_all_active_fsm(void);                              // ������� ��� �������� �� ������ ������ ��������
                  // <- ������� ���������� ���������� �� ������ ���������

                   bool     extra_fsm_handler(void);                               // �� ������ ���� ���������� ���������� ��������� ���������(������� ��� TIME_DELTA)
                   void     execute_sheduler(void);                                // ������� �������� � �������� �����.

private:  

    fifo<fsm_iface_link_t, MAX_FSM_FIFO_LEN> _TOTAL_FSM_FIFO;   // ����� ������ ���� ���������
    fifo<fsm_iface_link_t, MAX_ACTIVE_FSM>   _ACTIVE_FSM_FIFO;  // ����� �������� � ������ ������ ���������    

    finite_state_machine * const    *_fsm_list;    // ��������� �� ������ �������� fsm ��� ���������.
                 const  uint32_t    _list_size;    // ������ ������ ���������         
};

extern fsm_sheduler led_list_fsm_sheduler;

#endif