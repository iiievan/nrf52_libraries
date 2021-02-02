#include "app_fsm.h"

app_fsm_states_e app_fsm_current_state {ST_INIT};
uint8_t transition_cmd {CMD_NA};

TFT  WinstarWF35;

#ifdef TRANSMITTER_CH1
interpreter_sts   left_interpreter(CHANNEL_3,CHANNEL_1, FLOOR, OUTPUT_1);
interpreter_sts   right_interpreter(CHANNEL_3,CHANNEL_1, FLOOR, OUTPUT_1);
#else
interpreter_sts   left_interpreter;
interpreter_sts   right_interpreter;
#endif //TRANSMITTER_CH1
const uint16_t radioChannelsList[CH_LIST_MAX] =
{
  0x0000,
  0x3505,
  0x4507,
  0x3404
};

// хардкод, потому что не скоро еще будет больше каналов.
const audioIO_t analogInOutList[2] = 
{
  {.in = FLOOR, .out = OUTPUT_1},
  {.in = COMMON, .out = OUTPUT_2},
}; 

uint8_t sig_to_cmd_list[APP_FSM_SIG_NUM] =
{
    CMD_NA,
	CMD_INIT,
#ifdef MAIN_CPU
    CMD_SPEAK_RADIO,
    CMD_SPEAK_ANALOG,
#else
	CMD_SPEAK,
#endif	//	MAIN_CPU
	
    CMD_MUTE,

#ifdef MAIN_CPU
    CMD_LEFT_GRN,
    CMD_LEFT_PHT,
    CMD_RIGHT_GRN,
    CMD_RIGHT_PHT,
#endif	//	MAIN_CPU
	
    CMD_POWER_DOWN,
    CMD_WAKE_UP
};

// важно понимать что это конечный автомат, для которого главное находится в каком нибудь состоянии
// и только в последнюю очередь переклчюаться на исполняющую функцию.
// по этому при посылке SW_SIG_NA он остается в состоянии котором и был до этого и не выполняет ничего. Если нужно чтобы выполнял -
// запихай туда callback вместо NULL
app_fsm_transition_t fsm_table[APP_FSM_STATES_NUM][APP_FSM_SIG_NUM] = 
{
#ifdef MAIN_CPU     
    [ST_INIT][SW_SIG_NA]                    = {ST_INIT,         nullptr},          
    [ST_INIT][SW_SIG_INIT]                  = {ST_INIT,         st_hndlr_init},          // начальная стадия, инициализация всего и чтение конфигурации
    [ST_INIT][SW_SIG_SPEAK_RADIO]           = {ST_SPEAK_RADIO,  st_hndlr_speak_radio},   // переход автоматом после чтения кофигурации
    [ST_INIT][SW_SIG_SPEAK_ANALOG]          = {ST_SPEAK_ANALOG, st_hndlr_speak_analog},  // переход автоматом после чтения кофигурации
    [ST_INIT][SW_SIG_MUTE]                  = {ST_MUTE,         nullptr},
    [ST_INIT][SW_SIG_LEFT_GRN]              = {ST_SP_LEFT_GRN,  nullptr},
    [ST_INIT][SW_SIG_LEFT_PHT]              = {ST_SP_LEFT_PHT,  nullptr},
    [ST_INIT][SW_SIG_RIGHT_GRN]             = {ST_SP_RIGHT_GRN, nullptr},
    [ST_INIT][SW_SIG_RIGHT_PHT]             = {ST_SP_RIGHT_PHT, nullptr},
    [ST_INIT][SW_SIG_POWER_DOWN]            = {ST_POWER_DOWN,   nullptr},                
    [ST_INIT][SW_SIG_WAKE_UP]               = {ST_WAKE_UP,      nullptr},                

    [ST_SPEAK_RADIO][SW_SIG_NA]             = {ST_SPEAK_RADIO,  nullptr},  
    [ST_SPEAK_RADIO][SW_SIG_INIT]           = {ST_INIT,         nullptr},               
    [ST_SPEAK_RADIO][SW_SIG_SPEAK_RADIO]    = {ST_SPEAK_RADIO,  nullptr},
    [ST_SPEAK_RADIO][SW_SIG_SPEAK_ANALOG]   = {ST_SPEAK_ANALOG, st_hndlr_speak_analog},  // переход автоматом при изменении конфигурации по BT
    [ST_SPEAK_RADIO][SW_SIG_MUTE]           = {ST_MUTE,         st_hndlr_mute},          // переход автоматически после выполнения st_hndlr_speak_analog
    [ST_SPEAK_RADIO][SW_SIG_LEFT_GRN]       = {ST_SP_LEFT_GRN,  nullptr},
    [ST_SPEAK_RADIO][SW_SIG_LEFT_PHT]       = {ST_SP_LEFT_PHT,  nullptr},
    [ST_SPEAK_RADIO][SW_SIG_RIGHT_GRN]      = {ST_SP_RIGHT_GRN, nullptr},
    [ST_SPEAK_RADIO][SW_SIG_RIGHT_PHT]      = {ST_SP_RIGHT_PHT, nullptr},
    [ST_SPEAK_RADIO][SW_SIG_POWER_DOWN]     = {ST_POWER_DOWN,   st_hndlr_power_down},   // гарнитура и фантомное питание откл., или удержание кнопки 10.сек.
    [ST_SPEAK_RADIO][SW_SIG_WAKE_UP]        = {ST_WAKE_UP,      nullptr}, 
   
    [ST_SPEAK_ANALOG][SW_SIG_NA]            = {ST_SPEAK_ANALOG, nullptr}, 
    [ST_SPEAK_ANALOG][SW_SIG_INIT]          = {ST_INIT,         nullptr},
    [ST_SPEAK_ANALOG][SW_SIG_SPEAK_RADIO]   = {ST_SPEAK_RADIO,  st_hndlr_speak_radio},   // переход автоматом при изменении конфигурации по BT
    [ST_SPEAK_ANALOG][SW_SIG_SPEAK_ANALOG]  = {ST_SPEAK_ANALOG, nullptr},                
    [ST_SPEAK_ANALOG][SW_SIG_MUTE]          = {ST_MUTE,         st_hndlr_mute},          // переход автоматически после выполнения st_hndlr_speak_radio
    [ST_SPEAK_ANALOG][SW_SIG_LEFT_GRN]      = {ST_SP_LEFT_GRN,  nullptr},
    [ST_SPEAK_ANALOG][SW_SIG_LEFT_PHT]      = {ST_SP_LEFT_PHT,  nullptr},
    [ST_SPEAK_ANALOG][SW_SIG_RIGHT_GRN]     = {ST_SP_RIGHT_GRN, nullptr},
    [ST_SPEAK_ANALOG][SW_SIG_RIGHT_PHT]     = {ST_SP_RIGHT_PHT, nullptr},
    [ST_SPEAK_ANALOG][SW_SIG_POWER_DOWN]    = {ST_POWER_DOWN,   st_hndlr_power_down},    // гарнитура и фантомное питание откл., или удержание кнопки 10.сек.
    [ST_SPEAK_ANALOG][SW_SIG_WAKE_UP]       = {ST_WAKE_UP,      nullptr}, 
   
    [ST_MUTE][SW_SIG_NA]                    = {ST_MUTE,         nullptr},    
    [ST_MUTE][SW_SIG_INIT]                  = {ST_INIT,         nullptr},            
    [ST_MUTE][SW_SIG_SPEAK_RADIO]           = {ST_SPEAK_RADIO,  st_hndlr_speak_radio},   // переход автоматом при изменении конфигурации по BT
    [ST_MUTE][SW_SIG_SPEAK_ANALOG]          = {ST_SPEAK_ANALOG, st_hndlr_speak_analog},  // переход автоматом при изменении конфигурации по BT
    [ST_MUTE][SW_SIG_MUTE]                  = {ST_MUTE,         nullptr},
    [ST_MUTE][SW_SIG_LEFT_GRN]              = {ST_SP_LEFT_GRN,  st_hndlr_left_grn},      // I2C:BTN.MUTE нажата
    [ST_MUTE][SW_SIG_LEFT_PHT]              = {ST_SP_LEFT_PHT,  st_hndlr_left_pht},      // I2C:BTN.MUTE нажата
    [ST_MUTE][SW_SIG_RIGHT_GRN]             = {ST_SP_RIGHT_GRN, st_hndlr_right_grn},     // I2C:BTN.MUTE нажата
    [ST_MUTE][SW_SIG_RIGHT_PHT]             = {ST_SP_RIGHT_PHT, st_hndlr_right_pht},     // I2C:BTN.MUTE нажата
    [ST_MUTE][SW_SIG_POWER_DOWN]            = {ST_POWER_DOWN,   st_hndlr_power_down},    // гарнитура и фантомное питание откл., или удержание кнопки 10.сек.
    [ST_MUTE][SW_SIG_WAKE_UP]               = {ST_WAKE_UP,      nullptr},

    [ST_SP_LEFT_GRN][SW_SIG_NA]             = {ST_SP_LEFT_GRN,  nullptr}, 
    [ST_SP_LEFT_GRN][SW_SIG_INIT]           = {ST_INIT,         nullptr},               
    [ST_SP_LEFT_GRN][SW_SIG_SPEAK_RADIO]    = {ST_SPEAK_RADIO,  st_hndlr_speak_radio},  // переход автоматом при изменении конфигурации по BT
    [ST_SP_LEFT_GRN][SW_SIG_SPEAK_ANALOG]   = {ST_SPEAK_ANALOG, st_hndlr_speak_analog}, // переход автоматом при изменении конфигурации по BT
    [ST_SP_LEFT_GRN][SW_SIG_MUTE]           = {ST_MUTE,         st_hndlr_mute},         // I2C:BTN.MUTE нажата
    [ST_SP_LEFT_GRN][SW_SIG_LEFT_GRN]       = {ST_SP_LEFT_GRN,  nullptr},
    [ST_SP_LEFT_GRN][SW_SIG_LEFT_PHT]       = {ST_SP_LEFT_PHT,  st_hndlr_left_pht},     // SW_PHANTOM в положении ON
    [ST_SP_LEFT_GRN][SW_SIG_RIGHT_GRN]      = {ST_SP_RIGHT_GRN, st_hndlr_right_grn},    // I2C:R.BTN.SPEAK нажата
    [ST_SP_LEFT_GRN][SW_SIG_RIGHT_PHT]      = {ST_SP_RIGHT_PHT, st_hndlr_right_pht},    // I2C:R.BTN.SPEAK нажата
    [ST_SP_LEFT_GRN][SW_SIG_POWER_DOWN]     = {ST_POWER_DOWN,   st_hndlr_power_down},   // гарнитура и фантомное питание откл., или удержание кнопки 10.сек.
    [ST_SP_LEFT_GRN][SW_SIG_WAKE_UP]        = {ST_WAKE_UP,      nullptr},
 
    [ST_SP_LEFT_PHT][SW_SIG_NA]             = {ST_SP_LEFT_PHT,  nullptr}, 
    [ST_SP_LEFT_PHT][SW_SIG_INIT]           = {ST_INIT,         nullptr},              
    [ST_SP_LEFT_PHT][SW_SIG_SPEAK_RADIO]    = {ST_SPEAK_RADIO,  st_hndlr_speak_radio},  // переход автоматом при изменении конфигурации по BT
    [ST_SP_LEFT_PHT][SW_SIG_SPEAK_ANALOG]   = {ST_SPEAK_ANALOG, st_hndlr_speak_analog}, // переход автоматом при изменении конфигурации по BT
    [ST_SP_LEFT_PHT][SW_SIG_MUTE]           = {ST_MUTE,         st_hndlr_mute},         // I2C:BTN.MUTE нажата
    [ST_SP_LEFT_PHT][SW_SIG_LEFT_GRN]       = {ST_SP_LEFT_GRN,  st_hndlr_left_grn},     // SW_PHANTOM в положении OFF
    [ST_SP_LEFT_PHT][SW_SIG_LEFT_PHT]       = {ST_SP_LEFT_PHT,  nullptr},
    [ST_SP_LEFT_PHT][SW_SIG_RIGHT_GRN]      = {ST_SP_RIGHT_GRN, st_hndlr_right_grn},    // I2C:R.BTN.SPEAK нажата  
    [ST_SP_LEFT_PHT][SW_SIG_RIGHT_PHT]      = {ST_SP_RIGHT_PHT, st_hndlr_right_pht},    // I2C:R.BTN.SPEAK нажата
    [ST_SP_LEFT_PHT][SW_SIG_POWER_DOWN]     = {ST_POWER_DOWN,   st_hndlr_power_down},   // гарнитура и фантомное питание откл., или удержание кнопки 10.сек.
    [ST_SP_LEFT_PHT][SW_SIG_WAKE_UP]        = {ST_WAKE_UP,      nullptr},
 
    [ST_SP_RIGHT_GRN][SW_SIG_NA]            = {ST_SP_RIGHT_GRN, nullptr},
    [ST_SP_RIGHT_GRN][SW_SIG_INIT]          = {ST_INIT,         nullptr},                
    [ST_SP_RIGHT_GRN][SW_SIG_SPEAK_RADIO]   = {ST_SPEAK_RADIO,  st_hndlr_speak_radio},   // переход автоматом при изменении конфигурации по BT
    [ST_SP_RIGHT_GRN][SW_SIG_SPEAK_ANALOG]  = {ST_SPEAK_ANALOG, st_hndlr_speak_analog},  // переход автоматом при изменении конфигурации по BT
    [ST_SP_RIGHT_GRN][SW_SIG_MUTE]          = {ST_MUTE,         st_hndlr_mute},          // I2C:BTN.MUTE нажата
    [ST_SP_RIGHT_GRN][SW_SIG_LEFT_GRN]      = {ST_SP_LEFT_GRN,  st_hndlr_left_grn},      // I2C:L.BTN.SPEAK нажата 
    [ST_SP_RIGHT_GRN][SW_SIG_LEFT_PHT]      = {ST_SP_LEFT_PHT,  st_hndlr_left_pht},      // I2C:L.BTN.SPEAK нажата
    [ST_SP_RIGHT_GRN][SW_SIG_RIGHT_GRN]     = {ST_SP_RIGHT_GRN, nullptr},
    [ST_SP_RIGHT_GRN][SW_SIG_RIGHT_PHT]     = {ST_SP_RIGHT_PHT, st_hndlr_right_pht},     // SW_PHANTOM в положении ON
    [ST_SP_RIGHT_GRN][SW_SIG_POWER_DOWN]    = {ST_POWER_DOWN,   st_hndlr_power_down},    // гарнитура и фантомное питание откл., или удержание кнопки 10.сек.
    [ST_SP_RIGHT_GRN][SW_SIG_WAKE_UP]       = {ST_WAKE_UP,      nullptr},

    [ST_SP_RIGHT_PHT][SW_SIG_NA]            = {ST_SP_RIGHT_PHT, nullptr},  
    [ST_SP_RIGHT_PHT][SW_SIG_INIT]          = {ST_INIT,         nullptr},              
    [ST_SP_RIGHT_PHT][SW_SIG_SPEAK_RADIO]   = {ST_SPEAK_RADIO,  st_hndlr_speak_radio},   // переход автоматом при изменении конфигурации по BT
    [ST_SP_RIGHT_PHT][SW_SIG_SPEAK_ANALOG]  = {ST_SPEAK_ANALOG, st_hndlr_speak_analog},  // переход автоматом при изменении конфигурации по BT
    [ST_SP_RIGHT_PHT][SW_SIG_MUTE]          = {ST_MUTE,         st_hndlr_mute},          // I2C:BTN.MUTE нажата
    [ST_SP_RIGHT_PHT][SW_SIG_LEFT_GRN]      = {ST_SP_LEFT_GRN,  st_hndlr_left_grn},      // I2C:L.BTN.SPEAK нажата
    [ST_SP_RIGHT_PHT][SW_SIG_LEFT_PHT]      = {ST_SP_LEFT_PHT,  st_hndlr_left_pht},      // I2C:L.BTN.SPEAK нажата
    [ST_SP_RIGHT_PHT][SW_SIG_RIGHT_GRN]     = {ST_SP_RIGHT_GRN, st_hndlr_right_grn},     // SW_PHANTOM в положении OFF
    [ST_SP_RIGHT_PHT][SW_SIG_RIGHT_PHT]     = {ST_SP_RIGHT_PHT, nullptr},
    [ST_SP_RIGHT_PHT][SW_SIG_POWER_DOWN]    = {ST_POWER_DOWN,   st_hndlr_power_down},    // гарнитура и фантомное питание откл., или удержание кнопки 10.сек.
    [ST_SP_RIGHT_PHT][SW_SIG_WAKE_UP]       = {ST_WAKE_UP,      nullptr},
   
    // из состояния power_down мы можем только проснуться.
    [ST_POWER_DOWN][SW_SIG_NA]              = {ST_POWER_DOWN,   nullptr},
    [ST_POWER_DOWN][SW_SIG_INIT]            = {ST_INIT,         nullptr},                
    [ST_POWER_DOWN][SW_SIG_SPEAK_RADIO]     = {ST_SPEAK_RADIO,  nullptr},
    [ST_POWER_DOWN][SW_SIG_SPEAK_ANALOG]    = {ST_SPEAK_ANALOG, nullptr},
    [ST_POWER_DOWN][SW_SIG_MUTE]            = {ST_MUTE,         nullptr},
    [ST_POWER_DOWN][SW_SIG_LEFT_GRN]        = {ST_SP_LEFT_GRN,  nullptr},
    [ST_POWER_DOWN][SW_SIG_LEFT_PHT]        = {ST_SP_LEFT_PHT,  nullptr},
    [ST_POWER_DOWN][SW_SIG_RIGHT_GRN]       = {ST_SP_RIGHT_GRN, nullptr},
    [ST_POWER_DOWN][SW_SIG_RIGHT_PHT]       = {ST_SP_RIGHT_PHT, nullptr},      
    [ST_POWER_DOWN][SW_SIG_POWER_DOWN]      = {ST_POWER_DOWN,   nullptr},
    [ST_POWER_DOWN][SW_SIG_WAKE_UP]         = {ST_WAKE_UP,      st_hndlr_wake_up},            // нажата какая то кнопка, воткнута гарнитура, включено фантомное питание.
   
    [ST_WAKE_UP][SW_SIG_NA]                 = {ST_WAKE_UP,      nullptr},
    [ST_WAKE_UP][SW_SIG_INIT]               = {ST_INIT,         nullptr},                
    [ST_WAKE_UP][SW_SIG_SPEAK_RADIO]        = {ST_SPEAK_RADIO,  st_hndlr_speak_radio},   // переход автоматом при чтении конфигурации
    [ST_WAKE_UP][SW_SIG_SPEAK_ANALOG]       = {ST_SPEAK_ANALOG, st_hndlr_speak_analog},  // переход автоматом при чтении конфигурации
    [ST_WAKE_UP][SW_SIG_MUTE]               = {ST_MUTE,         nullptr},          
    [ST_WAKE_UP][SW_SIG_LEFT_GRN]           = {ST_SP_LEFT_GRN,  nullptr},
    [ST_WAKE_UP][SW_SIG_LEFT_PHT]           = {ST_SP_LEFT_PHT,  nullptr},
    [ST_WAKE_UP][SW_SIG_RIGHT_GRN]          = {ST_SP_RIGHT_GRN, nullptr},
    [ST_WAKE_UP][SW_SIG_RIGHT_PHT]          = {ST_SP_RIGHT_PHT, nullptr},
    [ST_WAKE_UP][SW_SIG_POWER_DOWN]         = {ST_POWER_DOWN,   nullptr},
    [ST_WAKE_UP][SW_SIG_WAKE_UP]            = {ST_WAKE_UP,      nullptr},
#else
    [ST_INIT][SW_SIG_NA]                    = {ST_INIT,         nullptr},               // начальная стадия, инициализация всего и чтение конфигурации
    [ST_INIT][SW_SIG_INIT]                  = {ST_INIT,         st_hndlr_init},
    [ST_INIT][ST_SPEAK]           			= {ST_SPEAK,        st_hndlr_speak},         
    [ST_INIT][SW_SIG_MUTE]                  = {ST_MUTE,         st_hndlr_mute},			// переход автоматом после чтения кофигурации
    [ST_INIT][SW_SIG_POWER_DOWN]            = {ST_POWER_DOWN,   nullptr},                
    [ST_INIT][SW_SIG_WAKE_UP]               = {ST_WAKE_UP,      nullptr},                

    [ST_SPEAK][SW_SIG_NA]             		= {ST_SPEAK,        nullptr},    
    [ST_SPEAK][SW_SIG_INIT]                 = {ST_INIT,         nullptr},            
    [ST_SPEAK][ST_SPEAK]    				= {ST_SPEAK,        st_hndlr_speak},        // экшен не равен нулю для возможности переключить микрофон с фантома на гарнитуру
    [ST_SPEAK][SW_SIG_MUTE]           		= {ST_MUTE,         st_hndlr_mute},         // нажата кнопка MUTE, переход автоматически после выполнения st_hndlr_speak_analog
    [ST_SPEAK][SW_SIG_POWER_DOWN]     		= {ST_POWER_DOWN,   st_hndlr_power_down},
    [ST_SPEAK][SW_SIG_WAKE_UP]        		= {ST_WAKE_UP,      nullptr},              
   
    [ST_MUTE][SW_SIG_NA]                    = {ST_MUTE,         nullptr},
    [ST_MUTE][SW_SIG_INIT]                  = {ST_INIT,         nullptr},                
    [ST_MUTE][ST_SPEAK]           			= {ST_SPEAK,        st_hndlr_speak},        // нажата кнопка Speak
    [ST_MUTE][SW_SIG_MUTE]                  = {ST_MUTE,         st_hndlr_mute},
    [ST_MUTE][SW_SIG_POWER_DOWN]            = {ST_POWER_DOWN,   st_hndlr_power_down},   // I2C: POWER_DOWN
    [ST_MUTE][SW_SIG_WAKE_UP]               = {ST_WAKE_UP,      nullptr},
   
    // из состояния power_down мы можем только проснуться.
    [ST_POWER_DOWN][SW_SIG_NA]              = {ST_POWER_DOWN,   nullptr},
    [ST_POWER_DOWN][SW_SIG_INIT]            = {ST_INIT,         nullptr},                
    [ST_POWER_DOWN][ST_SPEAK]     			= {ST_SPEAK,        nullptr},
    [ST_POWER_DOWN][SW_SIG_MUTE]            = {ST_MUTE,         nullptr},      
    [ST_POWER_DOWN][SW_SIG_POWER_DOWN]      = {ST_POWER_DOWN,   nullptr},
    [ST_POWER_DOWN][SW_SIG_WAKE_UP]         = {ST_WAKE_UP,      st_hndlr_wake_up},            // нажата какая то кнопка, I2C: WAKE_UP
   
    [ST_WAKE_UP][SW_SIG_NA]                 = {ST_WAKE_UP,      nullptr}, 
    [ST_WAKE_UP][SW_SIG_INIT]               = {ST_INIT,         nullptr},               
    [ST_WAKE_UP][ST_SPEAK]        			= {ST_SPEAK,        st_hndlr_mute},  // переход автоматом при чтении конфигурации
    [ST_WAKE_UP][SW_SIG_MUTE]               = {ST_MUTE,         nullptr},
    [ST_WAKE_UP][SW_SIG_POWER_DOWN]         = {ST_POWER_DOWN,   nullptr},
    [ST_WAKE_UP][SW_SIG_WAKE_UP]            = {ST_WAKE_UP,      nullptr},
#endif
};

bool invoke_transition(uint8_t cmd, void * pArg)
{  
    // меняем состояние автомата, только если он свободен
    if(transition_cmd == CMD_NA)
    { 
        transition_cmd = cmd;
		app_fsm_sheduler(pArg);	// выполняем планировщик чтобы была возможность скриптованных изменений автомата
        return true;
    }
    else
    { return false; }    
}

switch_signals_e _get_signal(uint8_t cmd)
{
    uint8_t result = SW_SIG_NA;  

    // сопоставляем команду сигналу.
    for(result = SW_SIG_NA; result < APP_FSM_SIG_NUM; result++)
    {
        if(cmd == sig_to_cmd_list[result])
        { break; }           
    }

    return (switch_signals_e)result;
}


void app_fsm_sheduler(void * pArg)
{    
    app_fsm_states_e new_state;
    switch_signals_e current_signal = _get_signal(transition_cmd);

    if(transition_cmd != CMD_NA)
    {
        transition_cmd = CMD_NA;
    }   

    new_state = fsm_table[app_fsm_current_state][current_signal].new_state;
        
    transition_callback_t worker = fsm_table[app_fsm_current_state][current_signal].worker;
	
    if(app_fsm_current_state != new_state)
    	app_fsm_current_state = new_state;
		
    if (worker != nullptr)
    {  worker(pArg);  }
}

void st_hndlr_init(void * pArg)
{  
    uint32_t i = 0;
    radioCh_t radioCh_ini;
    
#if defined (TRANSMITTER_CH1)
      radioCh_ini.raw = radioChannelsList[CHANNEL_1];
#elif defined (TRANSMITTER_CH2)
      radioCh_ini.raw = radioChannelsList[CHANNEL_2];
#endif
#if	defined (RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
      radioCh_ini.raw = radioChannelsList[CHANNEL_3];
#endif
		
	init_gpio(); 
    
    if (NRF_WDT->RUNSTATUS)
      reset();
    
    init_clock();
#if !defined(MAIN_CPU)
	init_wdt();
#endif 
    read_cfg();
    check_bootloader(); 
    seed_random(0);	
	
    // обнуляем статусы до инициализации i2c, иначе он войдет
    // войдет в прерывание еще на этапе инициализации и снова их обнулит
    // сразу после инициализации шины.
    st_state.speakEnvironment = ENVIRONMENT_NA;
    st_state.MicrophoneType   = MICROPHONE_NA;

#if defined(RECEIVER_LEFT)
        i2c_main.init_slave(RL_SLAVE_ADDR);    
#elif defined(RECEIVER_RIGHT)
        i2c_main.init_slave(RR_SLAVE_ADDR);
#elif defined(TRANSMITTER_CH1)
        i2c_main.init_slave(TCH1_SLAVE_ADDR);
#elif defined(TRANSMITTER_CH2)
       i2c_main.init_slave(TCH2_SLAVE_ADDR);
#endif
	   
// главный контроллер сам управляет режимом приема и передачи
#if !defined(MAIN_CPU)
     i2c_main.on_receive(i2c_main_receive_event);
     i2c_main.on_request(i2c_main_request_event);
#endif 

#if defined(MAIN_CPU)	
    i2c_main.init_master(400);	
	delay_ms(500);	// ждем когда загрузятся все остальные.
	
	// и сбрасываем их.
	i2c_main.start_transmission(RL_SLAVE_ADDR);
    i2c_main.write("Reset", 5);
    i2c_main.end_transmission();
	
	i2c_main.start_transmission(RR_SLAVE_ADDR);
    i2c_main.write("Reset", 5);
    i2c_main.end_transmission();
	
	i2c_main.start_transmission(TCH1_SLAVE_ADDR);
    i2c_main.write("Reset", 5);
    i2c_main.end_transmission();
	
	delay_ms(100);
	
    WinstarWF35.initController(threeLineSPI);
    WinstarWF35.fillWithColor(CBLACK);
    leftVUMeter.displayValue(255);
	rightVUMeter.displayValue(255);
    leftInputLabel.offState();
	leftOutputLabel.offState();
	rightInputLabel.offState();
	rightOutputLabel.offState();	
    
	interpreterTimer.setLeftHold();
	interpreterTimer.reset_left();

	rssi_bar.init();
	rssi_bar.displayValue(-59);
	
	batteryBar.init();
	
#endif 	   
         
#ifdef TRANSMITTER_CH2  // второй передатчик не управляет никаким максом, просто слушает шину i2s
    i2s_input_stream.init();
#endif  // TRANSMITTER_CH2
#if	defined (RECEIVER_LEFT) || 	defined (RECEIVER_RIGHT) || defined (TRANSMITTER_CH1)	
	max_audio_codec.init();
#if defined (RECEIVER_LEFT) ||  defined (RECEIVER_RIGHT)
	max_audio_codec.init_LR();
#endif
#endif
	
    radio_unit.init_default();  // by default we are proprietary 
	
    /*****настройка для передатчика и приемника для отладки*****/
#ifndef MAIN_CPU
    init_config_default(radioCh_ini);
#endif
#if	defined (RECEIVER_LEFT) || defined(RECEIVER_RIGHT)	
	radio_unit.set_address();       //обновляем адрес для аудио данных
#endif
    
    /*****настройка для передатчика и приемника для отладки*****/
#ifndef MAIN_CPU           
    soft_interrupt_init();     
    adc_unit.meas_radio();	
#endif
    //сбросим счетчик на поиск передатчика
    st_state.transmitter_search_ms = FREE_AUDIO_BUFF_TIMEOUT_MS; 
	
    UNUSED(i);
    UNUSED(radioCh_ini);
    
    st_config.firm = 0x2A;
	
#ifndef MAIN_CPU
    // никуда не переключаемся пока не поступит команды переключиться от MAIN_CPU
	// это нужно для синхронизации.	
	invoke_transition(CMD_NA);	
#endif	
}

void st_hndlr_speak_radio(void * pArg)
{
    st_state.speakEnvironment = RADIO_ENVIRONMENT;
	transferMediaPict.displayValue((const uint8_t *)RadioPict);  

#ifdef MAIN_CPU
	if(st_state.MicrophoneType != PHANTOM_MIC)
	{
		// если это не фантом то выключаем все преобразователи 
	  	// иначе ничего не трогаем
		minus_15V_off();
		delay_ms(150);
		plus_15V_off();
	}
#endif	
	
    invoke_transition(CMD_MUTE);    // переходим полюбому в mute после выполнения кода
}

void st_hndlr_speak_analog(void * pArg)
{
    st_state.speakEnvironment = ANALOG_ENVIRONMENT;
	
    transferMediaPict.displayValue((const uint8_t *)AnalogPict);

#ifdef MAIN_CPU
	if(st_state.MicrophoneType != PHANTOM_MIC)
	{
		plus_15V_on(); 
    	delay_ms(40);
    	minus_15V_on();
    	delay_ms(200);
	}
#endif
	
    invoke_transition(CMD_MUTE);    // переходим полюбому в mute после выполнения кода
}

void st_hndlr_speak(void * pArg)
{	  
#if defined(RECEIVER_LEFT)|| defined(RECEIVER_RIGHT)
    static uint8_t old_mic_type {MICROPHONE_NA};

    nrf_gpio_pin_clear(LED_SPEAK);
	nrf_gpio_pin_clear(LED_CH1_CH2);
	nrf_gpio_pin_clear(LED_MUTE);
    
    nrf_gpio_pin_set(LED_SPEAK);
	
    max_audio_codec.enable_dai_sdout(DAI1_IO_REG);
#endif

#if defined(RECEIVER_LEFT)|| defined(RECEIVER_RIGHT)
	// настраиваем кодек для работы с микрофоном с фантомным питанием
	// или гарнитурой.
    if(old_mic_type != st_state.MicrophoneType)
    {
    	switch(st_state.MicrophoneType)
    	{
            case PHANTOM_MIC:
                max_audio_codec.initPhantom();
            break;
            
            case GARNITURE_MIC:              
                max_audio_codec.initGarniture();                
            break;
			
			default:
			case MICROPHONE_NA:
			break;
    	}  
		
        old_mic_type = st_state.MicrophoneType;
     }
#endif
}

void st_hndlr_mute(void * pArg)
{
#ifdef RECEIVER_LEFT	
	stateArgument_t const * inputParameter;
	inputParameter = (stateArgument_t*)pArg;
	
	SWITCH(inputParameter->string)
	{
	  	CASE("CL"):
		  // переключаемся в mute и не зажигаем светодиод
		  nrf_gpio_pin_clear(LED_MUTE);
		  break;
		default:
		  // переключаемся в mute и обозначаем это.
		  nrf_gpio_pin_clear(LED_MUTE);
		  nrf_gpio_pin_set(LED_MUTE);
		  break;		
	}
#endif 

#ifdef MAIN_CPU
	if(leftInputLabel.getVisibility())
		leftInputLabel.offState();
	if(leftOutputLabel.getVisibility())
		leftOutputLabel.offState();
	if(rightInputLabel.getVisibility())
		rightInputLabel.offState();
	if(rightOutputLabel.getVisibility())
		rightOutputLabel.offState();
#endif
	
#if defined(RECEIVER_LEFT)|| defined(RECEIVER_RIGHT)
    nrf_gpio_pin_clear(LED_SPEAK);
    nrf_gpio_pin_clear(LED_CH1_CH2);
    nrf_gpio_pin_clear(LED_FL_COM);

    max_audio_codec.disable_dai_sdout(DAI1_IO_REG);   // просто выключяем выход у шины i2s
#endif  
}

void st_hndlr_left_grn(void * pArg)
{
    // даем команду левому приемнику переключиться на гарнитуру.
    i2c_main.start_transmission(RL_SLAVE_ADDR);
    i2c_main.write("Grn_on", 6);
    i2c_main.end_transmission();
	
    return;
}

void st_hndlr_left_pht(void * pArg)
{
    // даем команду левонму приемнику переключиться на фантомный микрофон.
    i2c_main.start_transmission(RL_SLAVE_ADDR);
    i2c_main.write("Ph_on", 5);
    i2c_main.end_transmission();

    return;
}

void st_hndlr_right_grn(void * pArg)
{
    // даем команду правому приемнику переключиться на гарнитуру.
    i2c_main.start_transmission(RR_SLAVE_ADDR);
    i2c_main.write("Grn_on", 6);
    i2c_main.end_transmission();
    return;
}

void st_hndlr_right_pht(void * pArg)
{
    // даем команду правому приемнику переключиться на фантомный микрофон.
    i2c_main.start_transmission(RR_SLAVE_ADDR);
    i2c_main.write("Ph_on", 5);
    i2c_main.end_transmission();
    return;
}

void st_hndlr_power_down(void * pArg)
{
  	return;
}

void st_hndlr_wake_up(void * pArg)
{
  	return;
}








