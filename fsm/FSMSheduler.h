#ifndef _FSM_SHEDULER_H
#define _FSM_SHEDULER_H

#include <vector>
#include <queue>
#include "utils.h"
#include "StepperFSM.h"
#include "timer.h"


#define FSM_QUEUE_MAX        (16UL)          // the total number of machines in the list
#define FSM_ACTIVE_MAX      (2 + 1)         // the number of simultaneously operating machines at the moment

typedef enum 
{
    FSM_START = 0, 
    FSM_KILL
} eFSMTrigger;

#ifndef countof
    #define countof(a)  (sizeof(a) / sizeof(*(a)))
#endif

// essentially a stripped-down machine card that provides its interface and id
typedef struct _fsm_iface_link_t_
{
  _fsm_iface_link_t_() : iface(FSM_LED),fsm_id(FSM_NOINIT){}
  
      eFSMInterface     iface;
            eFSM_id     fsm_id;
} fsmQData_t;

typedef struct
{
           eFSMInterface    fsm_iface;  
                 eFSM_id    fsm_id;     
              StepperFSM   *fsm;        
              eFSMStatus   *fsm_sts;    
} fsm_list_t;

class FSMsheduler
{
public:    
                             FSMsheduler(StepperFSM **list, Timer &rTmr)
                             : _fsm_list(list), _ms_timer(rTmr) 
                             {                                 
                                 _ACTIVE_FSM.reserve(FSM_ACTIVE_MAX);                                                              
                             } 

                    bool     push(StepperFSM &fsm);                                 // try to add fsm to the vector list. Catch exception if unsuccess and return false
                     int     fsmInQueue(StepperFSM *fsm);                           // checking if the machine is added to the queue. return index of machine
              StepperFSM*    getListIndex(StepperFSM *fsm);                         // find the machine into fsm list.
                    bool     place(StepperFSM *fsm, eFSMTrigger fsm_action); // command to execute the machine. true - the required machine is in the list, false - it is not in the list

              eFSMStatus     getStatus(StepperFSM *fsm);                            // updating the machine status
                    void     killAllactive(void);                                   // kills all currently active machines
 
                    bool     extra_fsm_handler(void);                               // in case emergency processing of fsm needed (faster than TIME_DELTA)
                    void     delayedStart(void);                                    // delayed start processing
                    void     shedule(void);                                         // the scheduler spins in the main cycle.

private:  
                   Timer   &_ms_timer; 
 std::vector<StepperFSM*>   _ACTIVE_FSM;   // currently active machines
  std::deque<StepperFSM*>   _QUEUE;        // queue of all machines 
              StepperFSM  **_fsm_list;      
};

extern FSMsheduler leds_task_sheduler; 

#endif //_FSM_SHEDULER_H