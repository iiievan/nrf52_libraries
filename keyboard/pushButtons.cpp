#include "include.h"
#include "pushButtons.h"


#ifdef MATRIX_KEYBOARD
       char keypad_symbols[KEYPAD_ROWS][KEYPAD_COLS]=   {{ '1', '2', '3' },
                                                         { '4', '5', '6' },
                                                         { '7', '8', '9' },
                                                         { 'L', '0', '*' },
                                                         { 'a', 'P', 'b' },
                                                         { 'c', '+', '-' }};

    uint8_t row_pins[KEYPAD_ROWS] = {BTN_ROW_1, BTN_ROW_2, BTN_ROW_3, BTN_ROW_4, BTN_ROW_5, BTN_ROW_6};
    uint8_t col_pins[KEYPAD_COLS] = {BTN_COL_1, BTN_COL_2, BTN_COL_3};
    
pushButtons custom_keypad(make_keymap(keypad_symbols), row_pins, col_pins, sizeof(row_pins), sizeof(col_pins),keypad_event);
#else

       char keypad_symbols[BTNS_NUM]  = 
#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
	   {'F', 'C', 'S', 'M'};
#else 
	   {0};
#endif
    uint8_t btn_pins[BTNS_NUM] = 
#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
	   {BTN_FL_COM, BTN_CH1_CH2, BTN_SPEAK, BTN_MUTE};
#else 
	   {0};
#endif
	
    
pushButtons buttons_set(make_keymap(keypad_symbols), btn_pins, sizeof(btn_pins), keypad_event);
#endif

#ifdef MATRIX_KEYBOARD
// Allows custom keymap, pin configuration, and keypad sizes.
pushButtons::pushButtons(char *user_keymap, uint8_t *row, uint8_t *col, uint8_t num_rows, uint8_t num_cols, void (*event_listener)(char, pushButtons *))
:_combo_tout(KEY_KOMBO_TOUT),_OPEN(false),_CLOSED(true)
{
    _p_row_pins = row;
    _p_column_pins = col;
    _rows_num = num_rows;
    _cols_num = num_cols;
    _p_keymap = user_keymap;

    for (uint8_t i = 0 ; i < _rows_num; i++)
    {
        nrf_gpio_cfg_sense_input(_p_row_pins[i], NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
    }
    
    for (uint8_t j = 0 ; j < _cols_num; j++)
    {
        nrf_gpio_cfg_output(_p_column_pins[j]);
    } 
    
    for(uint8_t y = 0; y < _rows_num; y++)
    {
        for(uint8_t x = 0; x < _cols_num; x++)
        bit_map[y*_cols_num + x] = 0;
    }
        
    _keypad_event_listener  = event_listener;
}
#else
//инициализация просто для набора кнопок
pushButtons::pushButtons(char *user_keymap, uint8_t *btns, uint8_t btns_num, void (*event_listener)(char, pushButtons *))
:_combo_tout(KEY_KOMBO_TOUT),_OPEN(true),_CLOSED(false)
{
    _p_btns_pins = btns;
    _btns_num = btns_num;
    _p_keymap = user_keymap;

    for (uint8_t i = 0 ; i < _btns_num; i++)
    {
        nrf_gpio_cfg_sense_input(_p_btns_pins[i], NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    }    
    
    for(uint8_t y = 0; y < _btns_num; y++)
    {
        bit_map[y] = 0;
    }
    
    set_debounce_tout(DEBOUNCE_TIME);
    
    _keypad_event_listener  = event_listener;
}
#endif //MATRIX_KEYBOARD

void pushButtons::go_power_down() 
{
    // настраиваем прерывание GPIOTE для скорейшего выхода контроллера из сна.
    nrf_drv_common_irq_enable(GPIOTE_IRQn, GPIO_INT_PRIORITY);
    NRF_GPIOTE->EVENTS_PORT = 0;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_PORT_Msk;

#ifdef MATRIX_KEYBOARD
    // все строки подтягиваем к плюсу питания
    for (uint8_t i = 0 ; i < _rows_num; i++)
    {
        nrf_gpio_cfg_sense_input(_p_row_pins[i], NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
    }
    
    // а колонки к минусу
    for (uint8_t j = 0 ; j < _cols_num; j++)
    {
        nrf_gpio_cfg_input(_p_column_pins[j],NRF_GPIO_PIN_PULLDOWN);
    }     
    // тогда при нажатии на кнопку будет формироваться прерывание и контроллер выйдет из сна.
#else
    // для набора кнопок ничего не требуется они и так настроены нормально изначально: 
    // на вход, подтяг к верху, чувствительность к логическому 0.
#endif  //MATRIX_KEYBOARD
}

// Возвращает только одну нажатую клавишу из листа нажатых, она лежит в элементе[0].
char pushButtons::get_button() 
{
	_single_key = true;

	if (get_buttons() && 
        key_list[0].state_changed && 
        (key_list[0].state == PRESSED))
	{ return key_list[0].symbol; }
	
	_single_key = false;

	return NO_KEY;
}

// обновляем список нажатых клавиш.
bool pushButtons::get_buttons() 
{
    static uint64_t dbnc_tmr = 0;

	 bool key_activity = false;
  
	if ((sys_tmr.get_mseconds() - dbnc_tmr) > _debounce_tout)
    {
        dbnc_tmr = sys_tmr.get_mseconds();

	 	_scan_keys();
	 	key_activity = _update_list();
	 }
  
	 return key_activity;
}

// Минимальный антидребезг 1мс.
void pushButtons::set_debounce_tout(uint32_t debounce) 
{
	debounce < 1 ? _debounce_tout = 1 : _debounce_tout = debounce;
}

// Сканирует клавиатуру.
void pushButtons::_scan_keys() 
{
#ifdef MATRIX_KEYBOARD
    // настраиваем входы строк на чувствительность к высокому уровню
    for(uint8_t i = 0; i < _rows_num; i++)
    { nrf_gpio_cfg_sense_input(_p_row_pins[i], NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH); }    
 
    // подаем поочередно на колонки импульс выского уровня и считываем его.
    for(uint8_t x = 0; x < _cols_num; x++)
    { 
       nrf_gpio_cfg_output(_p_column_pins[x]);
       nrf_gpio_pin_set(_p_column_pins[x]);

       for (uint8_t y = 0; y < _rows_num; y++)
       {         
          if (nrf_gpio_pin_read(_p_row_pins[y]) == _CLOSED)
          { bit_map[y*_cols_num + x] = 1; }
          else
          { bit_map[y*_cols_num + x] = 0; }          
       }
       
       nrf_gpio_pin_clear(_p_column_pins[x]);
    } 
#else
    for (uint8_t y = 0; y < _btns_num; y++)
    {         
       if (nrf_gpio_pin_read(_p_btns_pins[y]) == _CLOSED)
       { bit_map[y] = 1; }
       else
       { bit_map[y] = 0; }          
    }

#endif // MATRIX_KEYBOARD
}

// Обновляет лист нажатых клавиш. 
// возвращает true, если нажата хоть одна из клавиш.
bool pushButtons::_update_list() 
{
    bool any_activity = false;
    
    // Delete any IDLE keys
	for (uint8_t i = 0; i < LIST_MAX; i++) 
    {
		if (key_list[i].state == IDLE) 
        {
			key_list[i].symbol = NO_KEY;
			key_list[i].number = NA;
			key_list[i].state_changed = false;
		}
	}

#ifdef MATRIX_KEYBOARD 
    for (uint8_t y = 0; y < _rows_num; y++)
    {
        for (uint8_t x = 0; x < _cols_num; x++)
        {
            bool button = bit_map[y*_cols_num + x];
            int32_t key_code = y*_cols_num + x; 
            char key_char = _p_keymap[key_code];
            int32_t idx = find_in_list(key_char);
            
			// Клавиша уже есть в списке, пусть переходит в следующее состояние.
			if (idx > -1)	
            {
				  _next_key_state(idx, button);
			}

			// Клавиша не в списке, добавляем ее.
			if ((idx == -1) && button) 
            {
				for (int8_t i = 0; i < LIST_MAX; i++) 
                {
                    // Если есть пустой слот добавляем в него, иначе выкидываем.
					if (key_list[i].symbol == NO_KEY) 
                    {		
                        
						key_list[i].symbol = key_char;
						key_list[i].number = key_code;
						key_list[i].state = IDLE;		// Начальное состояние клавиши, которая не в списке - IDLE.
						_next_key_state (i, button);
						break;	
					}
				}
			}  
        }
    }
#else
    for (uint8_t y = 0; y < _btns_num; y++)
    {
           bool button; 
        int32_t key_code = y; 
           char key_char = _p_keymap[key_code];
        int32_t idx      = find_in_list(key_char);
		
		if(bit_map[y])
		{ button = _CLOSED; }
		else
		{ button = _OPEN; }		  
		
        // Клавиша уже есть в списке, пусть переходит в следующее состояние.
        if (idx > -1)   
        {
            _next_key_state(idx, button);
        }

        // Клавиша не в списке, добавляем ее.
        if ((idx == -1) && 
			(button == _CLOSED)) 
        {
            for (uint8_t i = 0; i < LIST_MAX; i++) 
            {
                // Если есть пустой слот добавляем в него, иначе выкидываем.
                if (key_list[i].symbol == NO_KEY) 
                {       
                    
                    key_list[i].symbol = key_char;
                    key_list[i].number = key_code;
                    key_list[i].state = IDLE;       // Начальное состояние клавиши, которая не в списке - IDLE.
                    _next_key_state (i, button);
                    break;  
                }
            }
        }  
    }
#endif //MATRIX_KEYBOARD
    
	// если изменения в клавишах есть, сообщаем об этом.
	for (uint8_t i = 0; i < LIST_MAX; i++) 
    {
		if (key_list[i].state_changed) 
          any_activity = true;
	}

	return any_activity;
}


// Эта функция хоть и конечный автомат, тем не менее применима для антидребезга.
void pushButtons::_next_key_state(int8_t idx, bool button)
{
	key_list[idx].state_changed = false;

	switch (key_list[idx].state) 
    {
	    case IDLE:
	   	    if (button == _CLOSED) 
            {
	   	        _transition_to (idx, PRESSED);
                            
                for (uint8_t tmr = TOUT_SHORT; tmr < HOLD_TOUT_NUM; tmr++)
	   	         _hold_tmr[tmr] = sys_tmr.get_mseconds();            
            }		
	   	    break;

	    case PRESSED:
	   	    if ((sys_tmr.get_mseconds() - _hold_tmr[TOUT_SHORT]) > _hold_tout[TOUT_SHORT])	// Ждем события TOUT_SHORT...
	   	    {  
                _transition_to (idx, HOLD_SHORT);
            }
	   	    else 
            if (button == _OPEN)				// или нажатие было кратковременным - RELEASED.
                _transition_to (idx, RELEASED);
	   	    break;

        case HOLD_SHORT:
            if ((sys_tmr.get_mseconds() - _hold_tmr[TOUT_NORMAL]) > _hold_tout[TOUT_NORMAL])  // Ждем события TOUT_NORMAL...
                _transition_to (idx, HOLD_NORMAL);
            else 
            if (button == _OPEN)             // или нажатие было кратковременным - RELEASED.
                _transition_to (idx, RELEASED);
            break;

        case HOLD_NORMAL:
            if ((sys_tmr.get_mseconds() - _hold_tmr[TOUT_LONG]) > _hold_tout[TOUT_LONG])  // Ждем события TOUT_LONG...
                _transition_to (idx, HOLD_LONG);
            else 
            if (button == _OPEN)             // или нажатие было кратковременным - RELEASED.
                _transition_to(idx, RELEASED);
            break;

	      case HOLD_LONG:
	      	if (button == _OPEN)
              _transition_to(idx, RELEASED);
	      	break;

	      case RELEASED:
	      	_transition_to(idx, IDLE);
	      	break;
	}
}

void pushButtons::_transition_to(int8_t idx, button_state_e next_state) 
{
	key_list[idx].state = next_state;
	key_list[idx].state_changed = true;
   
	// функционал нужен для применения функции get_button();
	// вызывающей каллбэк _keypad_event_listener
	if (_single_key)  
    {
	  	if((_keypad_event_listener != nullptr) && 
           (idx == 0))  
        { _keypad_event_listener(key_list[0].symbol, this); }
	}
	else 
    {
	  	if(_keypad_event_listener != nullptr)  
        { _keypad_event_listener(key_list[idx].symbol, this); }
	}
}

// Search by character for a key in the list of active keys.
// Returns -1 if not found or the index into the list of active keys.
int32_t pushButtons::find_in_list (char key_char) 
{
	for (int8_t i = 0; i < LIST_MAX; i++) 
    {
	  	if (key_list[i].symbol == key_char) 
        {
	  	  	return i;
	  	}
	}
       
	return -1;
}

// Search by code for a key in the list of active keys.
// Returns -1 if not found or the index into the list of active keys.
int32_t pushButtons::find_in_list (int32_t key_code) 
{
	for (int8_t i = 0; i < LIST_MAX; i++) 
    {
		if (key_list[i].number == key_code) 
        {
			return i;
		}
	}
    
	return -1;
}

button_state_e pushButtons::get_state() 
{
	return key_list[0].state;
}

char pushButtons::wait_for_key() 
{
	char wait_key = NO_KEY;

	while((wait_key = get_button()) == NO_KEY );	// Block everything while waiting for a keypress.

	return wait_key;
}

void pushButtons::set_key_combination(uint8_t combo_len, char key) 
{ 
     if(_combination_cntr > combo_len) // combo is finished?
     {
        _combination_cntr = 0;
        reset_combination();
     } 

    _combination[_combination_cntr++] = key;  
    
    _key_combo_tmr = sys_tmr.get_mseconds() + _combo_tout;    // клавиша введена вовремя, пролонгируем таймер на ожидание следующей   
}

char* pushButtons::waiting_key_combo() 
{
    volatile int delta;
    char* ptr = nullptr;
    
    if(_key_combo_tmr > 0)
    {
        delta = _key_combo_tmr - sys_tmr.get_mseconds();
        
        if (delta < 0)
        {
            _key_combo_tmr = 0;
            ptr = &_combination[0];
        }
    }

    return ptr;
}

void pushButtons::reset_combination()
{  
    memset(_combination, NO_KEY, KEY_COMBO_LENGTH);
    _combination_cntr = 0;
}

 // обработчик клавиатуры с антидребезгом
void keypad_handler_dbnc(pushButtons *set_of_btns)
{  
        char  key_symbol;
        char* ptr_combo = nullptr;
         int  key_combination = 0;
    uint16_t  mp3_point;
    
    interpreter_sts *pIntprtr{nullptr};
#if defined(RECEIVER_LEFT)
    pIntprtr = &left_interpreter;
#elif defined(RECEIVER_RIGHT)
    pIntprtr = &right_interpreter;
#endif
     
    // Важно понимать что из-за особенности матричной клавиатуры, чухнуть он может
    // две нажатые клавиши только в разных рядах и колонках.Т.е. всего три нажатые клавиши.
    // Заполняет массив клавиш key_list[ ] 10-ю активными в данный момент клавишами.
    // возвращает истину если есть хоть одна активная клавиша.
    if (set_of_btns->get_buttons())
    {
        for (uint8_t i = 0; i < LIST_MAX; i++)   // сканируем весь список клавиш.
        {
            if (set_of_btns->key_list[i].state_changed)   // ищем только те клавиши, которые поменяли свое состояние.
            {
                key_symbol = set_of_btns->key_list[i].symbol;
                
                switch (set_of_btns->key_list[i].state) 
                {  
                    case PRESSED:
                        switch(key_symbol)
                        {                       
                            case 'F': 
                               if(st_state.speakEnvironment == RADIO_ENVIRONMENT) 
                               {
                                    int index {-1};
                                 
                                    // смотрим какой сейчас канал и выбираем следующий
                                    for(int i = 0; i < CH_LIST_MAX; i++)
                                    {
                                        if(pIntprtr->rcvChannel.raw == radioChannelsList[i])
                                        {
                                            index = i;
                                            break;
                                        }
                                    }
                                    
                                    if(index >= 0)
                                    {
                                        if(index == (CH_LIST_MAX - 1))
                                            index = 0; // конец списка? переходим в начало.
                                        else
                                            index++;
                                        
                                        pIntprtr->rcvChannel.raw = radioChannelsList[index];
                                    }
                                    else
                                      pIntprtr->rcvChannel.raw = radioChannelsList[CHANNEL_NA];                                      
                               }
                               
                               if(st_state.speakEnvironment == ANALOG_ENVIRONMENT) 
                               {
                                    if(pIntprtr->audioIOStatus.in == analogInOutList[1].in)
                                        pIntprtr->audioIOStatus.in = analogInOutList[0].in;
                                    else
                                        pIntprtr->audioIOStatus.in = analogInOutList[1].in; 
                               }
							  break;
                            case 'C':
                               if(st_state.speakEnvironment == RADIO_ENVIRONMENT) 
                               {
                                    int index {-1};
                                 
                                    // смотрим какой сейчас канал и выбираем следующий
                                    for(int i = 0; i < CH_LIST_MAX; i++)
                                    {
                                        if(pIntprtr->trnChannel.raw == radioChannelsList[i])
                                        {
                                            index = i;
                                            break;
                                        }
                                    }
                                    
                                    if(index >= 0)
                                    {
                                        if(index == (CH_LIST_MAX - 1))
                                            index = 0; // конец списка? переходим в начало.
                                        else
                                            index++;
                                        
                                        pIntprtr->trnChannel.raw = radioChannelsList[index];
                                    }
                                    else
                                      pIntprtr->trnChannel.raw = radioChannelsList[CHANNEL_NA];                                      
                               }
                               
                               if(st_state.speakEnvironment == ANALOG_ENVIRONMENT) 
                               {
                                    if(pIntprtr->audioIOStatus.out == analogInOutList[1].out)
                                        pIntprtr->audioIOStatus.out = analogInOutList[0].out;
                                    else
                                        pIntprtr->audioIOStatus.out = analogInOutList[1].out; 
                               }
							  break;
                            case 'S':
							#ifndef MAIN_CPU
							  	invoke_transition(CMD_SPEAK);
							#endif // MAIN_CPU
							  break;
                            case 'M':
							  invoke_transition(CMD_MUTE);
							  break; 
                            default:
                              break;
                        }
						
						switch(key_symbol)
                        {                       
                            case 'F': 
                            case 'C':
                            case 'S':
                            case 'M':
                                //set_of_btns->set_key_combination(KEY_COMBO_LENGTH, key_symbol);                          
                                break;                             
                            default:
                                break;
                        }
                    break;
                    case HOLD_SHORT:                                                                  
                    break;
                    case HOLD_NORMAL:
                    break;
                    case HOLD_LONG:                      
                        switch(key_symbol)
                        {                       
                            case 'F':
							    break; 
                            case 'C':
							    break; 
                            case 'S':
							#ifndef MAIN_CPU
							  		invoke_transition(CMD_SPEAK);
							#endif // MAIN_CPU								
							    break; 
                            case 'M':
							  	invoke_transition(CMD_MUTE);
                                break;
                            default:
                                break;
                        }
                        break;
                    case RELEASED:
					    switch(key_symbol)
                        {                       
                            case 'F': 
							  //nrf_gpio_pin_clear(LED_FL_COM);
							  break;
                            case 'C':
							  //nrf_gpio_pin_clear(LED_CH1_CH2);
							  break;
                            case 'S':
							  //nrf_gpio_pin_clear(LED_SPEAK);
							  break;
                            case 'M':
							  //nrf_gpio_pin_clear(LED_MUTE);
							  break;                             
                            default:
                              break;
                        }
                        break;                      
                    case IDLE:
                        break;
                    default:
                        break;
                }
            } 
        }
    }
    
	// обработка нажатия комбинации клавиш.  ->
    ptr_combo = set_of_btns->waiting_key_combo();

    if(ptr_combo != nullptr)
    {
        key_combination = atoi(ptr_combo);
        
        if (key_combination <= 3)
        {
           mp3_point = key_combination;
        }
        //else 
        //{
//
        //}
        
        set_of_btns->reset_combination();
    }
	
	UNUSED(mp3_point);
	
	//  <- обработка нажатия комбинации клавиш.
}

// Callback возывается каждый раз при нажатии любой клавиши при работе методов
// обрабатывается вперед, все что в keypad_handler_dbnc() обрабатывается в последнюю очередь.
// надо понимать что эта штука без дебоунса
void keypad_event(char key, pushButtons* set_of_btns)
{
   switch (set_of_btns->get_state())
   {
    case PRESSED:
        switch(key)
        {                       
            case 'F':
			   break;
            case 'C':
			   break;
            case 'S':
			   break;
            case 'M':
			   break;
             default:
                break;
		} 
        break;
    case HOLD_SHORT:
        break;
    case HOLD_NORMAL:
        break;
    case HOLD_LONG:
        break;
    case RELEASED:      
        break;
    case IDLE:
	   break;
      default:
        break;
	}
 }

