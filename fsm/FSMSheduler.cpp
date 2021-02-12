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
            _QUEUE->push(fsm);
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
    int  queue_index = -1;

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
StepperFSM& FSMsheduler::getListIndex(StepperFSM *fsm)
{
    for(auto i : _fsm_list)
    {
        if(i->ID == fsm->ID)
            break;
    }

    return *i;
} 

// true - the machine we want is on the queue, false - fault place in the list
// function directly starts or kills the machine in the queue.
bool FSMsheduler::fsmPlacement(StepperFSM *fsm, eFSMTrigger fsm_action)
{
    bool func_result = false;
    StepperFSM *pFSM = getListIndex(fsm); // find fsm in list

    // don't push fsm in queue if necessary machines is execute right now
    if (fsm_action == FSM_KILL ||
        fsm->ID == LED_FSM_MARK_GPS_POSITION ||
        fsm->ID == LED_FSM_KB_TOGGLE ||  
        (0 > fsm_in_queue(LED_FSM_MARK_GPS_POSITION) &&
         0 > fsm_in_queue(LED_FSM_KB_TOGGLE)))
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
                // remove fsm from queue, it is no longer рфтвдув
                _QUEUE.erase(pFSM);

                // if fsm is active - finish him. Machine erased from _ACTIVE_FSM next in handle() method execution.
                for (auto it = _ACTIVE_FSM.begin(); it != _ACTIVE_FSM.end(); it++) 
                {
                    if(it->ID == fsm->ID)
                    {
                        // turn fsm to initial state
                        it->ID = FSM_NOINIT;
                        it->count    =  0;
                        it->interval =  0;
                        it->stage    = -1;
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
    for(auto i : _fsm_list)
    {
        if(i->status == FSM_DELAYED_START && fsmInQueue[i] < 0)
            fsmPlacement(i, FSM_START);
    }
}

eFSMStatus FSMsheduler::getStatus(StepperFSM *fsm)
{
    eFSMStatus result = FSM_NA;

    for(auto i : _fsm_list)
    {
        if(i->ID == fsm->ID )
            result = i->status;
    }

    return result;
}

void FSMsheduler::kill_all_active_fsm(void)
{
    for(auto i : _fsm_list)
    {
        if((i->status == FSM_RUN || fsmInQueue(i) >= 0) &&
           i->ID != LED_FSM_MARK_GPS_POSITION &&
           i->ID != LED_FSM_KB_TOGGLE)
        {
            fsmPlacement(i, FSM_KILL);
        }            
    }
}

// на случай если необходима экстренная обработка автоматов
bool FSMsheduler::extra_fsm_handler(void)
{
    return false;
}

// шедулер крутится в основном цикле с периодом обработки TIME_DELTA
void FSMsheduler::handle(void)
{
    static uint64_t execute_interval_tmr = 0;
    
    int list_index;
    fsmQData_t  *p_fsm;
    fsmQData_t  *p_active_fsm;

    delayed_start_handler();    // вначале обрабатываем статусы всех автоматов.

    if((_ms_timer.get_ms() - execute_interval_tmr) > TIME_DELTA || 
        true == extra_fsm_handler())
    {
        execute_interval_tmr = _ms_timer.get_ms();
        // инициализация автоматов (при появлении новых команд)
        if (_TOTAL_FSM_FIFO.get_avail() > 0)
        {        
            // поиск свободного места в списке активных автоматов
            for (list_index = 0; list_index < FSM_ACTIVE_MAX; list_index++)
            {
                p_active_fsm = _ACTIVE_FSM_FIFO.read_item(list_index);
    
                if (p_active_fsm->fsm_id == FSM_NOINIT)
                {
                    int j;
    
                    p_fsm = _TOTAL_FSM_FIFO.read_head(); 
    
                    // добавить автомат можно только в том случае, если он уже не выполняется
                    for (j = 0; j < FSM_ACTIVE_MAX; j++)
                    {
                        p_active_fsm = _ACTIVE_FSM_FIFO.read_item(j);
    
                        if (p_fsm->fsm_id == p_active_fsm->fsm_id)
                        {
                            break;
                        }
                    }
    
                    if (j >= FSM_ACTIVE_MAX)
                    {
                        bool cmd_exec = false;
                        
                        if (list_index < FSM_ACTIVE_MAX)
                        {
                            cmd_exec = true;
                        }
    
                        if (true == cmd_exec)
                        {
                            _TOTAL_FSM_FIFO.extract(); //просто выбрасываем очередной автомат из списка, на него уже указывает p_fsm
                            
                            p_active_fsm = _ACTIVE_FSM_FIFO.read_item(list_index);
    
                            // поместить в список активных автоматов
                            p_active_fsm->fsm_id = p_fsm->fsm_id;
    
                            // поиск и инициализация нужного автомата
                            for (j = 0; j < _list_size; j++)
                            {
                                if (_fsm_list[j]->get_id() == p_fsm->fsm_id)
                                {
                                    if (_fsm_list[j]->get_status() == FSM_NA || 
                                        _fsm_list[j]->get_status() == FSM_NONE)
                                    {
                                        _fsm_list[j]->handle(true);  // выполняем автомат.
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
    
        int j;
        // деинициализируем автоматы, закончившие свою работу
        for (j = 0; j < _list_size; j++)
        {    
            _fsm_list[j]->handle(false);  // актуализируем информацию по автомату, заряжаем его на выполнение
          
            if (_fsm_list[j]->get_status() == FSM_RELEASE)
            {
                // завершение работы автомата
                int k;
                for (k = 0; k < FSM_ACTIVE_MAX; k++)
                {
                    p_active_fsm = _ACTIVE_FSM_FIFO.read_item(k);
    
                    // удалить выполненный автомат из списка
                    if (p_active_fsm->fsm_id == _fsm_list[j]->get_id())
                    {
                        p_active_fsm->fsm_id = FSM_NOINIT;
                        break;
                    }
                }
            }
        }
    }
}

FSMsheduler leds_task_sheduler(fsm_list, sys_timer);



