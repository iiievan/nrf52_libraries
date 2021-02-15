#include "FSMSheduler.h"

bool FSMsheduler::push(StepperFSM &fsm)
{
    bool result = true;
    static uint32_t heap_free_size  = heap_avail() - 1;
    static uint32_t max_object_size = ALLOCATION_CRITICAL_MIN;
    uint32_t object_size = 0;
    uint32_t heapAvailable = heap_avail();  

    // recalculate maximum object size
    if(heapAvailable < heap_free_size)
    {
        object_size  =  heap_free_size - heapAvailable;
    
        if(object_size > max_object_size)
        {
            max_object_size = object_size;
            
            if(max_object_size < heap_free_size)
              result = false;
        }
    
        heap_free_size = heapAvailable;
    } 
    // try allocate memory for new object
    try 
    {
        // if possibly allocate so much space, and there is no exceptions
        if(max_object_size < heap_free_size)
            _QUEUE.push_front(&fsm);
    }
    catch (std::bad_alloc) 
    {
        result = false;
    }
    
    return result;
}

// check, is fsm in queue
int FSMsheduler::fsmInQueue(StepperFSM *fsm)
{
    int  queue_index = FSM_NA;

    // find fsm with this ID
    for(int i = 0; i < _QUEUE.size(); i++)
    {
        if(_QUEUE[i]->ID == fsm->ID)
        {
            queue_index = i;
            break;            
        }
    } 

    return queue_index;
}  

// check, is fsm in queue
StepperFSM* FSMsheduler::getListIndex(StepperFSM *fsm)
{
    int i;
    
    for(i = 0 ; _fsm_list[i] != nullptr; i++)
    {
        if(_fsm_list[i]->ID == fsm->ID)
            break;
    }

    return _fsm_list[i];
} 

// true - the machine we want is on the queue, false - fault place in the list
// function directly starts or kills the machine in the queue.
bool FSMsheduler::place(StepperFSM *fsm, eFSMTrigger fsm_action)
{
    bool func_result = false;
    StepperFSM *pFSM = getListIndex(fsm); // find fsm in list

    // don't push fsm in queue if necessary machines is execute right now
    if (fsm_action == FSM_KILL ||
        fsm->ID == LED_FSM_USB_CONNECTED ||
        fsm->ID == LED_FSM_CHARGING ||  
        (0 > fsmInQueue(&mchn_usb_connected) &&
         0 > fsmInQueue(&mchn_charging)))
    {   
        if (pFSM != nullptr && _QUEUE.size() < FSM_QUEUE_MAX)
        {
            // start fsm by placing in queue
            if (fsm_action == FSM_START)
            {
                _QUEUE.push_front(pFSM);
            } 
            else            
            if (fsm_action == FSM_KILL) // остановка управляющей функции
            {
                // remove fsm from queue, it is no longer handled
                for (auto qit = _QUEUE.begin(); qit != _QUEUE.end(); qit++) 
                {
                    if((*qit)->ID == fsm->ID)
                    {
                        _QUEUE.erase(qit);
                        _QUEUE.shrink_to_fit();
                    }
                }                
                
                // if fsm is active - finish him. Machine erased from _ACTIVE_FSM next in handle() method execution.
                for (auto ait = _ACTIVE_FSM.begin(); ait != _ACTIVE_FSM.end(); ait++) 
                {
                    if((*ait)->ID == fsm->ID)
                    {
                        // turn fsm to initial state
                        (*ait)->ID = FSM_NOINIT;
                        (*ait)->count    =  0;
                        (*ait)->interval =  0;
                        (*ait)->stage    = -1;
                    }
                }
            }

            // machine in queue
            func_result = true;
        }

        // fault placing fsm
        func_result = false;
    }

    return func_result;
}

// handle machines with a delayed start, just spinning in the handle() loop.
void FSMsheduler::delayedStart(void)
{
    int i;
    
    for(i = 0 ; _fsm_list[i] != nullptr; i++)
    {
        if(_fsm_list[i]->status == FSM_DELAYED_START && fsmInQueue(_fsm_list[i]) < 0)
            place(_fsm_list[i], FSM_START);
    }
}

eFSMStatus FSMsheduler::getStatus(StepperFSM *fsm)
{
    eFSMStatus result = FSM_NA;
    int i;
    
    for(i = 0 ; _fsm_list[i] != nullptr; i++)
    {
        if(_fsm_list[i]->ID == fsm->ID )
            result = _fsm_list[i]->status;
    }

    return result;
}

void FSMsheduler::killAllactive(void)
{
    int i;
    
    for(i = 0 ; _fsm_list[i] != nullptr; i++)
    {
        if((_fsm_list[i]->status == FSM_RUN || fsmInQueue(_fsm_list[i]) >= 0) &&
           _fsm_list[i]->ID != LED_FSM_CHARGING &&
           _fsm_list[i]->ID != LED_FSM_USB_CONNECTED)
        {
            place(_fsm_list[i], FSM_KILL);
        }            
    }
}

// на случай если необходима экстренная обработка автоматов
bool FSMsheduler::extra_fsm_handler(void)
{
    return false;
}

// шедулер крутится в основном цикле с периодом обработки TIME_DELTA
void FSMsheduler::shedule(void)
{
    static uint64_t execute_interval_tmr = 0;    

    StepperFSM * inQueue;
    std::vector<StepperFSM *>::iterator duplicateFSM;

    delayedStart();    // first delayed fsm.

    if((_ms_timer.get_ms() - execute_interval_tmr) > TIME_DELTA || 
        true == extra_fsm_handler())
    {
        execute_interval_tmr = _ms_timer.get_ms();

        // process machines that are in the queue
        if (!_QUEUE.empty())
        {        
            // looking for free slot among active fsm
            for (auto activeFSM = _ACTIVE_FSM.begin(); activeFSM != _ACTIVE_FSM.end(); activeFSM++) 
            {                   
                if ((*activeFSM)->ID == FSM_NOINIT &&
                    _ACTIVE_FSM.size() < FSM_ACTIVE_MAX)
                {
                    inQueue = _QUEUE.back();                   
    
                    // avoid fsm duplicating in QUEUE and in _ACTIVE_FSM
                    for (duplicateFSM = _ACTIVE_FSM.begin(); duplicateFSM != _ACTIVE_FSM.end(); duplicateFSM++)
                    {                        
                        if((*duplicateFSM)->ID == inQueue->ID)
                            break;
                    }

                    // the machine is not in the list of active, add it
                    if(duplicateFSM == _ACTIVE_FSM.end())    
                    {                        
                        // space is available
                        if (activeFSM != _ACTIVE_FSM.end())
                        {                             
                            _ACTIVE_FSM.push_back(inQueue);                            
                            _QUEUE.pop_back(); //just throw out current machine from queue, now he is on the list of active

                            // find now active fsm in list of fsm
                            for(int j = 0 ; _fsm_list[j] != nullptr; j++)
                            {
                                if (_fsm_list[j]->ID == inQueue->ID)
                                {
                                    if (_fsm_list[j]->status == FSM_NA || 
                                        _fsm_list[j]->status == FSM_NONE)
                                    {                                        
                                        _fsm_list[j]->spin(true);     // process fsm
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }    

        // deinitialize fsm's that have finished their work       
        for(int k = 0 ; _fsm_list[k] != nullptr; k++)
        {    
            _fsm_list[k]->spin(false);  // most of the time is spent here
          
            if (_fsm_list[k]->status == FSM_RELEASE)
            {
                // finish fsm
                for (auto m : _ACTIVE_FSM)
                {  
                    if (m->ID == _fsm_list[k]->ID)
                    {
                        m->ID = FSM_NOINIT;
                        break;
                    }
                }
            }
        }
    }
}

FSMsheduler leds_task_sheduler(fsm_list, sys_timer);
