#include "api.h"

// ��������� ������ �� �����
app_fsm_states_e i2c_response_handler(interpreter_sts * ptrIntrprtr)
{
    uint32_t i {0};
    app_fsm_states_e result {ST_NA};

    while(i2c_main.get_avail()) // loop through all but the last
    {
        i2c_command[i++] = i2c_main.get_one(); // receive byte as a character
        
        if(i > switch_string::MAX_STRING_LEN)
        {break;}
    }
  
    SWITCH(i2c_command)
    {
        CASE("Init"):
            result = ST_INIT;
            break;
        CASE("Mute"):
            result = ST_MUTE;
            break;
        CASE("Speak"):
            result = ST_SPEAK;
            break;
        DEFAULT:
            result = ST_NA;
            break;
    }
    
    if(ptrIntrprtr != nullptr)
    {
        if(i2c_command[0] == '@')
        {
            // ��������� ������� ���������� ����� ������
            ptrIntrprtr->audioIOStatus.in  = (relay_sts)i2c_command[1];
            ptrIntrprtr->audioIOStatus.out = (analogOutput_sts)i2c_command[2];
        }
        else
        if(i2c_command[0] == '#')
        {
            //��������� ������� ��������� ������� ������ ��������
            ptrIntrprtr->rcvChannel.ch      = i2c_command[1];
            ptrIntrprtr->rcvChannel.adr     = i2c_command[2];
            ptrIntrprtr->trnChannel.ch      = i2c_command[3];
            ptrIntrprtr->trnChannel.baseAdr = i2c_command[4];
        }
        else
        if(i2c_command[0] == '*')
        {
            //��������� ������� ��������� VU-����� ��� �������
        }
    }
    
    memset(i2c_command, '\0', switch_string::MAX_STRING_LEN);
    return result;
}

void application_poll()
{
    static uint64_t req_timer {0};
    static  uint8_t phantom_sw_dbnc {0}; 
    static  uint8_t environment_sw_dbnc {0};
    
#if defined (MAIN_CPU)      
    app_fsm_states_e response{ST_NA};
    static app_fsm_states_e RL_last_state{ST_NA};
    static interpreter_sts  leftOld_sts;
    static interpreter_sts  rightOld_sts;
    static app_fsm_states_e RR_last_state{ST_NA};
    static app_fsm_states_e TCH1_last_state{ST_NA};
    static         uint64_t tch1_service_tmr {0}; 
#define TCH1_START_TOUT (50)      
    static app_fsm_states_e TCH2_last_state{ST_NA};
    
    static bool mic_changed {false};
    static bool env_left_changed {false};
    static bool env_right_changed {false};
    static bool env_tch1_changed {false};

char writeData[7] {'\0'};  // ��������� slave'��
static interpreter_sts *pCurrentIntrptr{nullptr};
    
    if(tch1_service_tmr == 0)
    { 
       // ������ �� ��������     
       tch1_service_tmr = sys_tmr.get_mseconds(); 
    }    
  
    if (sys_tmr.get_mseconds() - req_timer > MAIN_I2C_REQ_TOUT)
    {
            req_timer = sys_tmr.get_mseconds();
    
         // ��������� ����� ����� �������� ������ ��������
         if(!nrf_gpio_pin_read(SW_ENVIRMNT) &&
             RADIO_ENVIRONMENT != st_state.speakEnvironment) 
         {
             if((environment_sw_dbnc++) > 5)
             {
                 environment_sw_dbnc = 0;
                // ����� �������� �����, ������� ������ ��� � slave-���
                // ������ ���������, �� ������ ������ ������� � ��� ����� ����� ������� ������ SPEAK
                invoke_transition(CMD_SPEAK_RADIO);
                env_left_changed  = true;
                env_right_changed = true;
                env_tch1_changed  = true;
            }               
         }
             
         if(nrf_gpio_pin_read(SW_ENVIRMNT) && 
            ANALOG_ENVIRONMENT != st_state.speakEnvironment) 
         {
             if((environment_sw_dbnc++) > 5)
             {
                 environment_sw_dbnc = 0;
                // ����� �������� �����, ������� ������ ��� � slave-���
                // ������ ���������, �� ������ ������ ������� � ��� ����� ����� ������� ������ SPEAK
                invoke_transition(CMD_SPEAK_ANALOG);
                env_left_changed  = true;
                env_right_changed = true;
                env_tch1_changed  = true;
             }               
         }
    
         // ��������� ���������� �� ��������� ������� +48V
         if(nrf_gpio_pin_read(SW_PHANTOM) && 
            st_state.MicrophoneType != PHANTOM_MIC) 
         {
             if((phantom_sw_dbnc++) > 5)
             {
                st_state.MicrophoneType = PHANTOM_MIC;
                
				phantomPict.onState();
                
                phantom_sw_dbnc = 0;
                
                //�������� ���������������
                if(st_state.speakEnvironment == ANALOG_ENVIRONMENT)
                {
                    // �� ������� ��������������� +15 � -15 �������� �����������.
                    phantom_48V_on();
                    delay_ms(200); 
                }
                else
                {
                    plus_15V_on(); 
                    delay_ms(40);
                    minus_15V_on();
                    delay_ms(200);
                    phantom_48V_on();
                    delay_ms(200);  
                }               
                
                // ������������ � ��������� �� ������ ��������� ����� ��� ������ slave
                mic_changed = true;
             }
         }
         
         // ���� ��������� ����������� +48V
         if(!nrf_gpio_pin_read(SW_PHANTOM) && 
            st_state.MicrophoneType != GARNITURE_MIC) 
         {
             if((phantom_sw_dbnc++) > 5)
             {
                st_state.MicrophoneType = GARNITURE_MIC;
                
				phantomPict.offState();
                
                phantom_sw_dbnc = 0;

                if(st_state.speakEnvironment == ANALOG_ENVIRONMENT)
                {
                    // �� ������� ��������������� +15 � -15 �������� �����������.
                    phantom_48V_off();
                    delay_ms(1500);
                }
                else
                {
                    //�������� ���������������          
                    phantom_48V_off();
                    delay_ms(1500);
                    minus_15V_off();
                    delay_ms(150);
                    plus_15V_off();
                }
                
                // ������������ � ������� �� ��������� ��������� ����� ��� ������ slave
                mic_changed = true;
             }   
         }
          
        // �.1. ���������� ����� ��������
        i2c_main.request_from(RL_SLAVE_ADDR, 9);        
        response = i2c_response_handler(nullptr);     // ������������ �����
    
         switch(response)
         { 
             case ST_INIT:
               
                i2c_main.start_transmission(RL_SLAVE_ADDR);
                i2c_main.write("Mute", 4);
                i2c_main.end_transmission();
                
                // ����� ��������� ������ ���� ��������������� � �������    
                env_left_changed = true;
                // � ������������� ������� � MUTE, ��������� � ��������� ��������� �� ������ �� �������.
                invoke_transition(CMD_MUTE);
                
                delay_ms(1);
         
                 break;
             case ST_SPEAK: 
                 // ��������� ������� ������ ������� ������ ��������
                 i2c_main.start_transmission(RL_SLAVE_ADDR);
                 i2c_main.write("ioSts", 5);                  // ������ ��������� ���������� � ��������� ������� ������ ��������
                 i2c_main.end_transmission();
                 
                 i2c_main.request_from(RL_SLAVE_ADDR, 9);     // ��������� �����
                 i2c_response_handler(&left_interpreter);     // ��������� ���������� ��� ������ �����������

                 if(mic_changed ||
                    (app_fsm_current_state != ST_SP_LEFT_GRN &&
                     app_fsm_current_state != ST_SP_LEFT_PHT))
                 {      
                    // ���� �� ����� ���� ��������� MUTE, � ������� ������
                    if(RL_last_state == ST_MUTE &&
                       (RR_last_state == ST_SPEAK ||
                        RR_last_state == ST_MUTE))
                    {       
                        // ������ ������
                        i2c_main.start_transmission(RR_SLAVE_ADDR);
                        i2c_main.write("Mute", 4);
                        i2c_main.end_transmission();
						
						//reset interpreter counter if changed interpreter person
						if(interpreterTimer.getRightHold() || 
						   pCurrentIntrptr == &right_interpreter)
							interpreterTimer.reset_left();
						
					  	interpreterTimer.continueCount();
                        pCurrentIntrptr = &left_interpreter;
                        // ����� �� ����� ����������� � ��������� ����� �������� �� �������� �����������
                        delay_ms(1);
                    }					
                    
                     // � ����� ������ - �� ������
                    switch(st_state.MicrophoneType)
                    {
                        case PHANTOM_MIC:
                            invoke_transition(CMD_LEFT_PHT);
                            break;
                        case GARNITURE_MIC:
                            invoke_transition(CMD_LEFT_GRN);
                            break;
                        default:                      
                          break;
                    }
					
					if(!leftInputLabel.getVisibility())
						leftInputLabel.onState();
					if(!leftOutputLabel.getVisibility())
						leftOutputLabel.onState();
					if(rightInputLabel.getVisibility())
						rightInputLabel.offState();
					if(rightOutputLabel.getVisibility())
						rightOutputLabel.offState();
                    
                    mic_changed = false;
                 }
                 
                 break;
             case ST_MUTE:
                 // ������� � ��� ����� ��������� ������� ����� ����������� ������
                 // ��� ������ ������� ���������
			   	if(RL_last_state == ST_SPEAK && 
				   RR_last_state == ST_MUTE)
				{
				  	interpreterTimer.setLeftHold();
				}
                 break;
             default:
                 break;
         }
        
        // �� ����� ������ ��������������� ������ NA
        if(ST_NA != response)
        {
            if(env_left_changed)
            {
                //��������� � ����� ��������� ����� ��������
                i2c_main.start_transmission(RL_SLAVE_ADDR);                    
                if(st_state.speakEnvironment == RADIO_ENVIRONMENT)
                    i2c_main.write("Radio", 5);
                if(st_state.speakEnvironment == ANALOG_ENVIRONMENT)
                    i2c_main.write("Analog", 6);                    
                i2c_main.end_transmission();
                
                env_left_changed = false;
            }
            
            RL_last_state = response;
        }           
    
        // �.2.���������� ������ ��������
        i2c_main.request_from(RR_SLAVE_ADDR, 9);    
        response = i2c_response_handler(nullptr);    // ������������ �����
     
         switch(response)
         { 
             case ST_INIT:                  
                i2c_main.start_transmission(RR_SLAVE_ADDR);
                i2c_main.write("Mute", 4);
                i2c_main.end_transmission();
                
                // ����� ��������� ������ ���� ��������������� � �������    
                env_right_changed = true;
                // � ������������� ������� � MUTE, ��������� � ��������� ��������� �� ������ �� �������.
                invoke_transition(CMD_MUTE);
                
                delay_ms(1);
                 break;
             case ST_SPEAK:
                 // ��������� ������� ������ ������� ������ ��������
                 i2c_main.start_transmission(RR_SLAVE_ADDR);
                 i2c_main.write("ioSts", 5);                  // ������ ��������� ���������� � ��������� ������� ������ ��������
                 i2c_main.end_transmission();
                 
                 i2c_main.request_from(RR_SLAVE_ADDR, 9);     // ��������� �����
                 i2c_response_handler(&right_interpreter);    // ��������� ���������� ��� ������� �����������
                 
                 if(mic_changed ||
                    (app_fsm_current_state != ST_SP_RIGHT_GRN &&
                     app_fsm_current_state != ST_SP_RIGHT_PHT))
                 {
                     // ���� �� ����� ���� ��������� MUTE, � ������� ����� ��� ��� �������
                     // ����� �������� ���������
                    if(RR_last_state == ST_MUTE &&
                       (RL_last_state == ST_SPEAK ||
                        RL_last_state == ST_MUTE))
                    {       
                        // ������ ����� � ������ ��� �������� ��������� mute,
                        // ��������� �� �� ���������.
                        i2c_main.start_transmission(RL_SLAVE_ADDR);
                        i2c_main.write("MuteCL", 6);
                        i2c_main.end_transmission();
						
						//reset interpreter counter if changed interpreter person
						if(interpreterTimer.getLeftHold() ||
						   pCurrentIntrptr == &left_interpreter)
							interpreterTimer.reset_right();
						
					  	interpreterTimer.continueCount();
                        pCurrentIntrptr = &right_interpreter;
                        // ����� �� ����� ����������� � ��������� ����� �������� �� �������� �����������
                        delay_ms(1);
                    }		

                                        
                     // � ����� ������ - �� ������
                    switch(st_state.MicrophoneType)
                    {
                        case PHANTOM_MIC:
                            invoke_transition(CMD_RIGHT_PHT);
                            break;
                        case GARNITURE_MIC:
                            invoke_transition(CMD_RIGHT_GRN);
                            break;
                        default:                      
                          break;
                    }
					
					if(leftInputLabel.getVisibility())
						leftInputLabel.offState();
					if(leftOutputLabel.getVisibility())
						leftOutputLabel.offState();
					if(!rightInputLabel.getVisibility())
						rightInputLabel.onState();
					if(!rightOutputLabel.getVisibility())
						rightOutputLabel.onState();
                    
                    mic_changed = false;
                 }
                 break;
             case ST_MUTE:
                // ���� � ����� � ������ �������� � �����, �� ����
                // ������ ���� ������ ������ ����.
                if(RL_last_state == ST_MUTE)
                {
                    pCurrentIntrptr = nullptr;
                    invoke_transition(CMD_MUTE);
                }
				
				if(RR_last_state == ST_SPEAK &&
				   RL_last_state == ST_MUTE)
				{
				  	interpreterTimer.setRightHold();
				}
                break;
             default:
                 break;
         }
        
        // �� ����� ������ ��������������� ������ NA
        if(ST_NA != response)
        {
            if(env_right_changed)
            {
                // � ����� ������ ��������� � ����� ��������� ����� ��������
                i2c_main.start_transmission(RR_SLAVE_ADDR);                    
                if(st_state.speakEnvironment == RADIO_ENVIRONMENT)
                    i2c_main.write("Radio", 5);
                if(st_state.speakEnvironment == ANALOG_ENVIRONMENT)
                    i2c_main.write("Analog", 6);                    
                i2c_main.end_transmission();
                
                env_right_changed = false;
            }
            
            RR_last_state = response;
        }
        
        // �.3.���������� ���������� ������� ������
        i2c_main.request_from(TCH1_SLAVE_ADDR, 9);    
        response = i2c_response_handler(nullptr);    // ������������ �����

        switch(response)
        { 
            case ST_INIT:
                // ����� ��������� ������ ���� ��������������� � �������
                env_tch1_changed = true;
                break;
            case ST_SPEAK:                  
            case  ST_MUTE:
                // ������� ����������, �������� ��������.
                if(leftOld_sts != left_interpreter || 
                   rightOld_sts != right_interpreter)
                {
                    if(pCurrentIntrptr != nullptr)
                    {
                        switch(st_state.speakEnvironment)
                        {
                            case RADIO_ENVIRONMENT:
                                writeData[0] = '#';
                                writeData[1] = (char)pCurrentIntrptr->trnChannel.ch;
                                writeData[2] = (char)pCurrentIntrptr->trnChannel.adr;
                                writeData[3] = (char)st_config.transmitter_id;
                                break;
                            case ANALOG_ENVIRONMENT:
                                writeData[0] = '@';
                                writeData[1] = (char)left_interpreter.audioIOStatus.in;
                                writeData[2] = (char)left_interpreter.audioIOStatus.out;
                                writeData[3] = (char)right_interpreter.audioIOStatus.in;
                                writeData[4] = (char)right_interpreter.audioIOStatus.out;    
                                break;
                            default:
                                break;
                        }
    
                        i2c_main.start_transmission(TCH1_SLAVE_ADDR);
                        i2c_main.write(writeData, 7);
                        i2c_main.end_transmission();
                    }

                    leftOld_sts = left_interpreter;
                    rightOld_sts = right_interpreter;
                }
                break;
            default:
                break;
        }
        
           // �� ����� ������ ��������������� ������ NA
        if(ST_NA != response)
        {
            if(env_tch1_changed && 
               sys_tmr.get_mseconds() - tch1_service_tmr > TCH1_START_TOUT)
            {
                // � ����� ������ ��������� � ����� ��������� ����� ��������
                i2c_main.start_transmission(TCH1_SLAVE_ADDR);                    
                if(st_state.speakEnvironment == RADIO_ENVIRONMENT)
                    i2c_main.write("Radio", 5);
                if(st_state.speakEnvironment == ANALOG_ENVIRONMENT)
                    i2c_main.write("Analog", 6);                    
                i2c_main.end_transmission();
                
                env_tch1_changed = false;
            }
            
            TCH1_last_state = response;     
        }
    }
   
    UNUSED(TCH1_last_state);
    UNUSED(TCH2_last_state);   
#endif  //MAIN_CPU
    UNUSED(req_timer);
    UNUSED(phantom_sw_dbnc);
    UNUSED(environment_sw_dbnc);   
}

void i2c_main_receive_event(int len)
{
    uint32_t i = 0;
    stateArgument_t outputParameter;

#if defined (RECEIVER_LEFT)
    interpreter_sts * ptrIntrprtr = &left_interpreter;
#elif defined (RECEIVER_RIGHT)
    interpreter_sts * ptrIntrprtr = &right_interpreter;
#elif defined (TRANSMITTER_CH1)
    interpreter_sts * ptrIntrprtr = nullptr;
#endif 
    
    while(i2c_main.get_avail()) // loop through all but the last
    {
        i2c_command[i++] = i2c_main.get_one(); // receive byte as a character
        
        if(i > switch_string::MAX_STRING_LEN)
        {break;}
    }
    
#ifndef MAIN_CPU   
    //we must receive
    SWITCH(i2c_command)
    {
        CASE("Mute"):           
            invoke_transition(CMD_MUTE);
        break;
#ifdef RECEIVER_LEFT
       CASE("MuteCL"):  
            // ������ ������� � mute � �������� ��������� mute
            strcpy(outputParameter.string,"CL");         
            invoke_transition(CMD_MUTE,(void *)&outputParameter);
        break;
#endif
        CASE("Reset"):          
            reset(); //27.11.2020 hard_reset(); - �� ���� ������ �������� ����������, 
                    // TCH1 ������������ ���� �������� �� ��� ������� SYSTEM_OFF ������ �� ����������
                    //  �� ������ ������ �� while(1), ����� ����������� � ��� ������� �� �������.�� ����� ������ reset.
        break; 
#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
        CASE("Grn_on"): 
            st_state.MicrophoneType = GARNITURE_MIC;
            if(app_fsm_current_state == ST_SPEAK)
               invoke_transition(CMD_SPEAK);
        break;
        CASE("Ph_on"):
            st_state.MicrophoneType = PHANTOM_MIC;
            if(app_fsm_current_state == ST_SPEAK)
                invoke_transition(CMD_SPEAK);
        break;
#endif 
        CASE("Analog"):
            st_state.speakEnvironment = ANALOG_ENVIRONMENT;
#ifdef TRANSMITTER_CH1
            // ���� ����� ��� �������� �� ����� �� I2C, �� �� ���������
            max_audio_codec.init_main();

            // ����������� ����� ������ � ������������ � ���������� ������������
            max_audio_codec.selectAnalogInput(&left_interpreter);
            max_audio_codec.selectAnalogOutput(&left_interpreter);
            max_audio_codec.selectAnalogInput(&right_interpreter);
            max_audio_codec.selectAnalogOutput(&right_interpreter);

           // �������� ����������� �����, ������ ���� �� �������� 
            max_audio_codec.turn_on(); 
            // ����������� ����������� TCH1 � INIT, ����� ����� ��� ����� ����������� ����� ��������.
            invoke_transition(CMD_SPEAK); 
#elif defined (RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
            max_audio_codec.listenAnalog();              
#endif  // TRANSMITTER_CH1
        break;
        CASE("Radio"):
            st_state.speakEnvironment = RADIO_ENVIRONMENT;
#ifdef TRANSMITTER_CH1
            // ��������� ����� ����������
            max_audio_codec.shutdown();
            // ����������� ����������� TCH1 � INIT, ����� ����� ��� ����� ����������� ����� ��������.
            invoke_transition(CMD_SPEAK);
#elif defined (RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
            max_audio_codec.listenRadio();
#endif  // TRANSMITTER_CH1
        break;
        CASE("ioSts"):
          i2c_main.reqData = true;
        break;
        
        default:
          break;
    }

    switch(i2c_command[0])
    {
        case '@':
            // �� ������ ������ ������������� ��� ��� TCH1
            if(ptrIntrprtr == nullptr)
            {
                if(left_interpreter.audioIOStatus.in != i2c_command[1])
                {
                    left_interpreter.audioIOStatus.in = (relay_sts)i2c_command[1];

                    max_audio_codec.selectAnalogInput(&left_interpreter);

                }

                if(left_interpreter.audioIOStatus.out != i2c_command[2])
                {
                    left_interpreter.audioIOStatus.out = (analogOutput_sts)i2c_command[2];

                    max_audio_codec.selectAnalogOutput(&left_interpreter);
                }

                if(right_interpreter.audioIOStatus.in != i2c_command[3])
                {
                    right_interpreter.audioIOStatus.in = (relay_sts)i2c_command[3];

                    max_audio_codec.selectAnalogInput(&right_interpreter);

                }

                if(right_interpreter.audioIOStatus.out != i2c_command[4])
                {
                    right_interpreter.audioIOStatus.out = (analogOutput_sts)i2c_command[4];

                    max_audio_codec.selectAnalogOutput(&right_interpreter);
                }
            }

            break;
        case '#':
                if(st_config.channel_num != (uint8_t)i2c_command[1] ||
                   st_config.base_adr != (uint8_t)i2c_command[2])
                {
                    // �������� � ����� �� ���������� 
                    if(ptrIntrprtr != nullptr)
                    {
                        //��������� ������� ��������� ������� ������ ��������
                        ptrIntrprtr->rcvChannel.ch      = i2c_command[1];
                        ptrIntrprtr->rcvChannel.adr     = i2c_command[2];
                        st_config.channel_num = (uint8_t)i2c_command[1];
                        st_config.base_adr = (uint8_t)i2c_command[2];
                    }
                    else    // ��� ������������
                    {
                        st_config.channel_num = (uint8_t)i2c_command[1];
                        st_config.base_adr = (uint8_t)i2c_command[2];
                        st_config.transmitter_id = (uint8_t)i2c_command[3];
                    }
    
                    set_channels();
                    save_cfg();
                    radio_unit.set_address();
                }


            break;
        default:
            break;
    }

    memset(i2c_command, '\0', switch_string::MAX_STRING_LEN); // �������� ���������� 
#endif  //MAIN_CPU  
    
    UNUSED(outputParameter);
}

void i2c_main_request_event()
{  
#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT) || defined(TRANSMITTER_CH1)
    char response[switch_string::MAX_STRING_LEN] {0};
    
    // if we need answer on dataRequest
    if (i2c_main.reqData)
    {
          if(st_state.speakEnvironment == RADIO_ENVIRONMENT)
          {
                // �������� � ����� �� ���������
                response[0] = '#';
#if defined(RECEIVER_LEFT)
                response[1] = left_interpreter.rcvChannel.ch;
                response[2] = left_interpreter.rcvChannel.adr;
                response[3] = left_interpreter.trnChannel.ch;
                response[4] = left_interpreter.trnChannel.adr;
        
#elif defined(RECEIVER_RIGHT)
                response[1] = right_interpreter.rcvChannel.ch;
                response[2] = right_interpreter.rcvChannel.adr;
                response[3] = right_interpreter.trnChannel.ch;
                response[4] = right_interpreter.trnChannel.adr;
#endif 
                // ���������� ��������� ������� ������ ��������
                i2c_main.write(response, 5);
                memset(response,'\0',sizeof(response));
          }
          else
          if (st_state.speakEnvironment == ANALOG_ENVIRONMENT)
          {
                response[0] = '@';
#if defined(RECEIVER_LEFT)
                response[1] = (relay_sts)left_interpreter.audioIOStatus.in;
                response[2] = (analogOutput_sts)left_interpreter.audioIOStatus.out;
#elif defined(RECEIVER_RIGHT) 
                response[1] = (relay_sts)right_interpreter.audioIOStatus.in;
                response[2] = (analogOutput_sts)right_interpreter.audioIOStatus.out;
#endif
                // ���������� ��������� ������� ������ ��������
                i2c_main.write(response, 3);
                memset(response,'\0',sizeof(response));
          }
          
          i2c_main.reqData = false;
    }
    else
    {   
        // else answer about current state
        switch(app_fsm_current_state)
        {
            case ST_INIT:
            strcpy(response, "Init");
            break;
            
            case ST_SPEAK:
            strcpy(response, "Speak");
            break;
            
            case ST_MUTE:
            strcpy(response, "Mute");
            break;
            
            case ST_POWER_DOWN:
            case ST_WAKE_UP:
            case ST_NA:
            default:
            strcpy(response, "Busy");
            break;
        }   
        i2c_main.write(response, switch_string::MAX_STRING_LEN);
    }
#else
    return;
#endif  // RECEIVER_LEFT || RECEIVER_RIGHT 
}


