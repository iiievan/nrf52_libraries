#ifndef _FSM_SHEDULER_H
#define _FSM_SHEDULER_H

#include "StepperFSM.h"
#include "fifo.h"
#include "timer.h"
#include <vector>

#define FSM_LIST_MAX        (16UL)          // the total number of machines in the list
#define FSM_ACTIVE_MAX      (2 + 1)         // the number of simultaneously operating machines at the moment

typedef enum 
{
    FSM_START = 0, 
    FSM_KILL
} fsm_trigger_t;

#ifndef countof
    #define countof(a)  (sizeof(a) / sizeof(*(a)))
#endif

// essentially a stripped-down machine card that provides its interface and id
typedef struct _fsm_iface_link_t_
{
  _fsm_iface_link_t_() : iface(FSM_LED),fsm_id(FSM_NOINIT){}
  
    fsm_interface_t     iface;
       fsmEventID_t     fsm_id;
} fsmQData_t;

typedef struct
{
         fsm_interface_t    fsm_iface;  //can_iface_t
            fsmEventID_t    fsm_id;     //can_ctl_func_id_t
              StepperFSM   *fsm;        //state_machine_func_t
            fsm_status_t   *fsm_sts;    //state_machine_status_t
} fsm_list_t;

class FSMsheduler
{
public:    
                            FSMsheduler(StepperFSM * const *list ,  Timer &rTmr)
                            : _fsm_list(list),_list_size(countof(list)),_ms_timer(rTmr) 
                            {} 

                   // automatic control functions from the program logic ->
                   bool     fsm_in_fifo_added(fsmEventID_t fsm_id);                     // checking if the machine is added to the queue
                   bool     fsm_execute(fsmEventID_t fsm_id, fsm_trigger_t fsm_action); // command to execute the machine. true - the required machine is in the list, false - it is not in the list
                   void     delayed_start_handler(void);                                // delayed start processing
           fsm_status_t     fsm_sts_get(fsmEventID_t func_id);                          // updating the machine status
                   void     kill_all_active_fsm(void);                                  // kills all currently active machines
                  // <- automatic control functions from the program logic

                   bool     extra_fsm_handler(void);                                    // in case emergency processing of fsm needed (faster than TIME_DELTA)
                   void     handle(void);                                               // the scheduler spins in the main cycle.

private:  
                  Timer    &_ms_timer; 
    fifo<fsmQData_t, FSM_LIST_MAX> _TOTAL_FSM_FIFO;   // buffer of all machines in general
    fifo<fsmQData_t, FSM_ACTIVE_MAX>   _ACTIVE_FSM_FIFO;  // buffer of currently active machines    

      StepperFSM * const   *_fsm_list;    // a pointer to a list of fsm objects to process.
         const  uint32_t    _list_size;   // machine list size         
};

extern FSMsheduler leds_machines;

#endif //_FSM_SHEDULER_H