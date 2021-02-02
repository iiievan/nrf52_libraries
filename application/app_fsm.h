#ifndef _APP_FSM_H
#define _APP_FSM_H
  
// !!!specific forward declaration of enum!!!
enum app_fsm_states_e : int;

#include "include.h"

enum app_fsm_states_e : int
{
    ST_NA = 0,
    ST_INIT,

#ifdef MAIN_CPU
    ST_SPEAK_RADIO,
    ST_SPEAK_ANALOG,
#else
    ST_SPEAK,
#endif // MAIN_CPU

    ST_MUTE,

#ifdef MAIN_CPU
    ST_SP_LEFT_GRN,
    ST_SP_LEFT_PHT,
    ST_SP_RIGHT_GRN,
    ST_SP_RIGHT_PHT,
#endif // MAIN_CPU
    
    ST_POWER_DOWN,
    ST_WAKE_UP,
    APP_FSM_STATES_NUM, 
#ifdef MAIN_CPU  
    ST_SPEAK //чтобы компилятор не ругался
#endif // MAIN_CPU
};

typedef enum 
{
#define CMD_NA           (0xA9)
    SW_SIG_NA = 0,       // сигнал - ничего не делать.
#define CMD_INIT         (0xAA)
    SW_SIG_INIT,         // сигнал - инициализации

#ifdef MAIN_CPU
#define CMD_SPEAK_RADIO   (0xAB)
    SW_SIG_SPEAK_RADIO,
#define CMD_SPEAK_ANALOG  (0xAC)
    SW_SIG_SPEAK_ANALOG,
#else
#define CMD_SPEAK         (0xCC)
    SW_SIG_SPEAK,
#endif // MAIN_CPU

#define CMD_MUTE          (0xAD)
    SW_SIG_MUTE,

#ifdef MAIN_CPU
#define CMD_LEFT_GRN      (0xBA)
    SW_SIG_LEFT_GRN,
#define CMD_LEFT_PHT      (0xBB)
    SW_SIG_LEFT_PHT,
#define CMD_RIGHT_GRN     (0xBC)
    SW_SIG_RIGHT_GRN,
#define CMD_RIGHT_PHT     (0xBD)
    SW_SIG_RIGHT_PHT,
#endif  // MAIN_CPU

#define CMD_POWER_DOWN    (0xAE)
    SW_SIG_POWER_DOWN,
#define CMD_WAKE_UP       (0xAF)
    SW_SIG_WAKE_UP,
    APP_FSM_SIG_NUM 
}switch_signals_e;

extern          uint8_t sig_to_cmd_list[];   		// список сопоставления сигналов командам
extern          uint8_t transition_cmd;      		// запрос на переход
extern app_fsm_states_e app_fsm_current_state;      // текущее состояние автомата приложения

typedef struct 
{
    switch_signals_e   wish;
                 int   value;
}inner_state_cmnd_t;

typedef void (*transition_callback_t)(void * pArg);

typedef struct 
{
         app_fsm_states_e new_state;
    transition_callback_t worker;
}app_fsm_transition_t;

// аргумент для передачи
typedef struct 
{
         char string[2];
     uint32_t delay;
}stateArgument_t;

extern stateArgument_t argMute;

extern             bool invoke_transition(uint8_t cmd, void * pArg = nullptr);
extern             void app_fsm_sheduler(void * pArg = nullptr);
       switch_signals_e _get_signal(uint8_t cmd);
	


void st_hndlr_init(void * pArg);
void st_hndlr_speak_radio(void * pArg);
void st_hndlr_speak_analog(void * pArg);
void st_hndlr_speak(void * pArg);
void st_hndlr_mute(void * pArg);
void st_hndlr_left_grn(void * pArg);
void st_hndlr_left_pht(void * pArg);
void st_hndlr_right_grn(void * pArg);
void st_hndlr_right_pht(void * pArg);
void st_hndlr_power_down(void * pArg);
void st_hndlr_wake_up(void * pArg);

#endif //_APP_FSM_H