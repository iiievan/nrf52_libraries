#ifndef _PUSH_BUTTONS_H
#define _PUSH_BUTTONS_H
#include "include.h"

//#define MATRIX_KEYBOARD

#ifdef MATRIX_KEYBOARD
    #define KEYPAD_ROWS         (6)
    #define KEYPAD_COLS         (3)
    #define LIST_MAX            (KEYPAD_ROWS * KEYPAD_COLS)
#else
	#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
		   #define BTNS_NUM            (4)
	#else 
		   #define BTNS_NUM            (1)	// нулевой массив должен содержать один символ
	#endif
    
    #define LIST_MAX            (BTNS_NUM)
#endif  //MATRIX_KEYBOARD
        
#define make_keymap(x)      ((char*)x)
#define OPEN                (false)
#define CLOSED              (true)

typedef enum
{   
    TOUT_SHORT,                     // короткое нажатие на кнопку
#define SHORT_HOLD_TOUT     (500)   
    TOUT_NORMAL,                    // нормальное нажатие на кнопку
#define NORMAL_HOLD_TOUT    (1000) 
    TOUT_LONG,                      // долгое нажатие на кнопку
#define LONG_HOLD_TOUT      (2000)  
    HOLD_TOUT_NUM
} hold_time_e;

#define DEBOUNCE_TIME       (20)    // время на антидребезг кнопки в миллисекнудах
#define KEY_KOMBO_TOUT      (3000)  // время на ввод следующего символа при вводе комбинации символа.
#define KEY_COMBO_LENGTH    (3)     // длина комбинации нажатия клавиш
#define NO_KEY              '\0'

typedef enum
{    
          NA = -1,
         IDLE = 0, 
      PRESSED = 1, 
   HOLD_SHORT = 2,
  HOLD_NORMAL = 3,
    HOLD_LONG = 4,
     RELEASED = 5 
} button_state_e;

class Button 
{
public:
    char           symbol {NO_KEY};
    int16_t        number {NA};
    button_state_e state;
    bool           state_changed {false};
    
    Button(){}
    
    Button(char user_key_char)
    {
        symbol   =  user_key_char;
        number =  NA;
        state  =  IDLE;
        state_changed = false;
    }
private:
};

class pushButtons : public Button 
{
public:

#ifdef MATRIX_KEYBOARD
                 //инициализация для матричной клавиатуры.
                 pushButtons(char *user_keymap, uint8_t *row, uint8_t *col, uint8_t num_rows, uint8_t num_cols,  void (*event_listener)(char, pushButtons *) = nullptr);
#else
                 //инициализация просто для набора кнопок
                 pushButtons(char *user_keymap, uint8_t *btns, uint8_t btns_num, void (*event_listener)(char, pushButtons *) = nullptr);
#endif // MATRIX_KEYBOARD    

          void   go_power_down();      //переводит модуль в энергосберегающее состояние.

       uint8_t   bit_map[LIST_MAX];  // результат обработки клавиатуры складывается сюда.
        Button   key_list[LIST_MAX];   // массив клавиш и их состояний.          

          char   get_button();
          bool   get_buttons();
          void   set_debounce_tout(uint32_t);
       int32_t   find_in_list(char key_char);
       int32_t   find_in_list(int32_t key_code);

button_state_e   get_state();

          char   wait_for_key();
          void   set_key_combination(uint8_t combo_len, char key);
          char*  waiting_key_combo();
          void   reset_combination();

private:
          char   *_p_keymap;

#ifdef MATRIX_KEYBOARD
       uint8_t   *_p_row_pins;
       uint8_t   *_p_column_pins;
       uint8_t    _rows_num;
       uint8_t    _cols_num;
#else
       uint8_t   *_p_btns_pins;
       uint8_t    _btns_num;
#endif // MATRIX_KEYBOARD

    const bool   _OPEN;
    const bool   _CLOSED;

      uint64_t   _hold_tmr[HOLD_TOUT_NUM];
      uint32_t   _hold_tout[HOLD_TOUT_NUM]{SHORT_HOLD_TOUT, NORMAL_HOLD_TOUT, LONG_HOLD_TOUT};
      uint32_t   _debounce_tout{DEBOUNCE_TIME};

          char   _combination[KEY_COMBO_LENGTH] {0};
      uint64_t   _key_combo_tmr{0};
      uint32_t   _combination_cntr{0};
const uint32_t   _combo_tout;

          bool   _single_key{false};
  
          void   _scan_keys();
          bool   _update_list();
          void   _next_key_state(int8_t idx, bool Button);
          void   _transition_to(int8_t idx, button_state_e next_state);
          void   (*_keypad_event_listener)(char, pushButtons *);
};

extern         void     keypad_event(char key, pushButtons *set_of_btns);   // обработчик по изменению кнопок, без антидребезга
extern         void     keypad_handler_dbnc(pushButtons *);    // обработчик клавиатуры с антидребезгом


#ifdef MATRIX_KEYBOARD
    extern         char     keypad_symbols[KEYPAD_ROWS][KEYPAD_COLS];
    extern      uint8_t     row_pins[KEYPAD_ROWS];
    extern      uint8_t     col_pins[KEYPAD_COLS];
    extern  pushButtons     custom_keypad;
#else
    extern         char     keypad_symbols[BTNS_NUM];
    extern      uint8_t     btn_pins[BTNS_NUM];
    extern  pushButtons     buttons_set;
#endif

#endif  //_PUSH_BUTTONS_H