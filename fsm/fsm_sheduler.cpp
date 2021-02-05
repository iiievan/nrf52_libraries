#include "include.h"
#include "fsm_sheduler.h"

// ���������, �������� �� ������� � �������
bool fsm_sheduler::fsm_in_fifo_added(fsm_id_t fsm_id)
{
      bool  func_result = false;
       int  list_index = 0;
    size_t  curr_fifo_avail = _TOTAL_FSM_FIFO.get_avail();

    // �������������� ��� ���
    while (_fsm_list[list_index]->get_id() != fsm_id && 
           list_index < _list_size)
    { list_index++; }

    // ��������������
    if (curr_fifo_avail < MAX_FSM_FIFO_LEN && _fsm_list[list_index]->get_id() == fsm_id)
    {
        for (list_index = 0; list_index < curr_fifo_avail; list_index++)
        {
            fsm_iface_link_t   *p_fsm_iface_link = _TOTAL_FSM_FIFO.read_item(list_index);

            if (p_fsm_iface_link->fsm_id == fsm_id)
            {
                func_result = true;
                break;
            }
        }
    }

    return func_result;
}  

// true - ������ ������� ���� � ������, false - ��� ��� � ������
// ������� ��������������� ��������� ��� ������� ������� � ������
bool fsm_sheduler::fsm_execute(fsm_id_t fsm_id, fsm_trigger_t fsm_action)
{
    bool func_result = false;
    int list_index = 0;

    // �� ��������� � ����������� ����� �������� ��� �������� ���������� ������� ������� ��� �������� ��������� ����������.
    if (fsm_action == FSM_KILL ||
        fsm_id == LED_FSM_MARK_GPS_POSITION ||
        fsm_id == LED_FSM_KB_TOGGLE ||  
        (false == fsm_in_fifo_added(LED_FSM_MARK_GPS_POSITION) &&
         false == fsm_in_fifo_added(LED_FSM_KB_TOGGLE)))
    {        
        // ���� ������� � ������
        while (_fsm_list[list_index]->get_id() != fsm_id && list_index < _list_size)
        { list_index++; }
    
        
        if (_TOTAL_FSM_FIFO.get_avail() < _TOTAL_FSM_FIFO.get_size() &&
            _fsm_list[list_index]->get_id() == fsm_id )
        {
            // ������ ����������� �������
            if (fsm_action == FSM_START)
            {
                // ����� �������� ������ �� �������� ��� ���� ����� ��������� ��� � FIFO
                fsm_iface_link_t    fsm_iface_link;
                
                fsm_iface_link.fsm_id = fsm_id;
                fsm_iface_link.iface  = _fsm_list[list_index]->get_interface();

                _TOTAL_FSM_FIFO.add(fsm_iface_link);
            } 
            else            
            if (fsm_action == FSM_KILL) // ��������� ����������� �������
            {
                //cmd_fifo_t temp_cmd_list;
                fifo<fsm_iface_link_t, MAX_FSM_FIFO_LEN> TMP_FIFO;
                    
                // ����� � �������� �� FIFO (��������� �� FIFO ��� �������, ����� ���������, �� ��������� FIFO, ����� ��������� ��� �������)
                // �� ��� ��� ������� ����� ������� ������ ���� ����� ���):
                while (_TOTAL_FSM_FIFO.get_avail() > 0)
                {
                    fsm_iface_link_t  extract_iface_link = _TOTAL_FSM_FIFO.extract();
                    
                    if (extract_iface_link.fsm_id != fsm_id)
                    {
                        TMP_FIFO.add(extract_iface_link);
                    }
                }

                while (TMP_FIFO.get_avail() > 0)
                {
                    fsm_iface_link_t  extract_iface_link = TMP_FIFO.extract();
                    _TOTAL_FSM_FIFO.add(extract_iface_link);
                }
    
                // ����� � �������� �� ������ ���������� � ������ ������, ��������� ��������
                for (list_index = 0; list_index < MAX_ACTIVE_FSM; list_index++)
                {
                    fsm_iface_link_t *p_active_fsm = _ACTIVE_FSM_FIFO.read_item(list_index);

                    if (p_active_fsm->fsm_id == fsm_id)
                    {
                        int j = 0;
                        p_active_fsm->fsm_id = FSM_NOINIT;

                        // ����� � ��������� ���������������� ��������
                        for (j = 0; j < _list_size; j++)
                        {
                            if (_fsm_list[j]->get_id() == fsm_id)
                            {
                                _fsm_list[j]->count    =  0;
                                _fsm_list[j]->interval =  0;
                                _fsm_list[j]->stage    = -1;

                                break;
                            }
                        }
                    }
                }
            }

            // ������ ������� � ������
            func_result = true;
        }
        // ������� �������� ��� � ������.
        func_result = false;
    }

    return func_result;
}

// ��������� ��������� � ���������� �������, �������� ������ � �������� �����.
void fsm_sheduler::delayed_start_handler(void)
{
    uint8_t i;

    for (i = 0; _fsm_list[i] != nullptr; i++)
    {
        if (FSM_DELAYED_START == _fsm_list[i]->get_status() && 
            fsm_in_fifo_added(_fsm_list[i]->get_id()) == false)
        {
            fsm_execute(_fsm_list[i]->get_id(), FSM_START);
        }
    }
}

fsm_status_t fsm_sheduler::fsm_sts_get(fsm_id_t func_id)
{
    fsm_status_t func_result = FSM_NA;
    uint8_t i;

    for (i = 0; _fsm_list[i]->get_id() != FSM_NOINIT; i++)
    {
        if (_fsm_list[i]->get_id() == func_id)
        {
            func_result = _fsm_list[i]->get_status();
            break;
        }
    }

    return func_result;
}

void fsm_sheduler::kill_all_active_fsm(void)
{
    uint8_t i;

    for (i = 0; _fsm_list[i]->get_id() != FSM_NOINIT; i++)
    {
        if ((FSM_RUN == _fsm_list[i]->get_status() || fsm_in_fifo_added(_fsm_list[i]->get_id()) == true) &&
            _fsm_list[i]->get_id() != LED_FSM_MARK_GPS_POSITION &&
            _fsm_list[i]->get_id() != LED_FSM_KB_TOGGLE )
        {
            fsm_execute(_fsm_list[i]->get_id(), FSM_KILL);
        }
    }

}

// �� ������ ���� ���������� ���������� ��������� ���������
bool fsm_sheduler::extra_fsm_handler(void)
{
    return false;
}

// ������� �������� � �������� ����� � �������� ��������� TIME_DELTA
void fsm_sheduler::execute_sheduler(void)
{
    static uint64_t execute_interval_tmr = 0;
    
    int list_index;
    fsm_iface_link_t  *p_fsm;
    fsm_iface_link_t  *p_active_fsm;

    delayed_start_handler();    // ������� ������������ ������� ���� ���������.

    if((sys_tmr.get_mseconds() - execute_interval_tmr) > TIME_DELTA || 
        true == extra_fsm_handler())
    {
        execute_interval_tmr = sys_tmr.get_mseconds();
        // ������������� ��������� (��� ��������� ����� ������)
        if (_TOTAL_FSM_FIFO.get_avail() > 0)
        {        
            // ����� ���������� ����� � ������ �������� ���������
            for (list_index = 0; list_index < MAX_ACTIVE_FSM; list_index++)
            {
                p_active_fsm = _ACTIVE_FSM_FIFO.read_item(list_index);
    
                if (p_active_fsm->fsm_id == FSM_NOINIT)
                {
                    int j;
    
                    p_fsm = _TOTAL_FSM_FIFO.read_head(); 
    
                    // �������� ������� ����� ������ � ��� ������, ���� �� ��� �� �����������
                    for (j = 0; j < MAX_ACTIVE_FSM; j++)
                    {
                        p_active_fsm = _ACTIVE_FSM_FIFO.read_item(j);
    
                        if (p_fsm->fsm_id == p_active_fsm->fsm_id)
                        {
                            break;
                        }
                    }
    
                    if (j >= MAX_ACTIVE_FSM)
                    {
                        bool cmd_exec = false;
                        
                        if (list_index < MAX_ACTIVE_FSM)
                        {
                            cmd_exec = true;
                        }
    
                        if (true == cmd_exec)
                        {
                            _TOTAL_FSM_FIFO.extract(); //������ ����������� ��������� ������� �� ������, �� ���� ��� ��������� p_fsm
                            
                            p_active_fsm = _ACTIVE_FSM_FIFO.read_item(list_index);
    
                            // ��������� � ������ �������� ���������
                            p_active_fsm->fsm_id = p_fsm->fsm_id;
    
                            // ����� � ������������� ������� ��������
                            for (j = 0; j < _list_size; j++)
                            {
                                if (_fsm_list[j]->get_id() == p_fsm->fsm_id)
                                {
                                    if (_fsm_list[j]->get_status() == FSM_NA || 
                                        _fsm_list[j]->get_status() == FSM_NONE)
                                    {
                                        _fsm_list[j]->processing(true);  // �������� ������� �� ����������
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
        // ���������������� ��������, ����������� ���� ������
        for (j = 0; j < _list_size; j++)
        {    
            _fsm_list[j]->processing(false);  // ������������� ���������� �� ��������, �������� ��� �� ����������
          
            if (_fsm_list[j]->get_status() == FSM_RELEASE)
            {
                // ���������� ������ ��������
                int k;
                for (k = 0; k < MAX_ACTIVE_FSM; k++)
                {
                    p_active_fsm = _ACTIVE_FSM_FIFO.read_item(k);
    
                    // ������� ����������� ������� �� ������
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

fsm_sheduler led_list_fsm_sheduler(fsm_list);



