#ifndef _API_H
#define _API_H

// forward declaration
union radioCh_t;
struct interpreter_sts;

#include "include.h"

typedef enum
{
    ENVIRONMENT_NA,
	RADIO_ENVIRONMENT,
	ANALOG_ENVIRONMENT
} speak_env_sts;

typedef enum
{
	MICROPHONE_NA,
	PHANTOM_MIC,
	GARNITURE_MIC
} microphoneType_e;

typedef enum
{
  INPUT_NA,
  FLOOR,    // relay input 1
  COMMON    // relay input 2 
} relay_sts;

typedef enum
{
  OUTPUT_NA,
  OUTPUT_1,
  OUTPUT_2  
} analogOutput_sts;

union radioCh_t
{
   struct 
   {
        union 
        { 
            uint8_t   adr; 
            uint8_t   baseAdr;
        };

        union 
        {
            uint8_t   ch; 
            uint8_t   channel; 
        };	 	 
   };
   uint16_t   raw;
};

typedef union 
{
   struct 
   {
        union 
        { 
                     uint8_t   output;
            analogOutput_sts   out; 
        };
        union 
        {
              uint8_t   input;
            relay_sts   in;  
        }; 	 
   };
   uint16_t   raw;
} audioIO_t;

enum 
{
    CHANNEL_NA  =  0,   
    CHANNEL_1,      
    CHANNEL_2,     
    CHANNEL_3,
    CH_LIST_MAX  
};
extern  const uint16_t   radioChannelsList[];

struct interpreter_sts
{
    radioCh_t rcvChannel;
    radioCh_t trnChannel;
    audioIO_t audioIOStatus;
        
    interpreter_sts(uint8_t rCh = CHANNEL_3, uint8_t tCh = CHANNEL_1, uint8_t in = COMMON, uint8_t out = OUTPUT_2)
    {
        rcvChannel.raw = radioChannelsList[rCh];
        trnChannel.raw = radioChannelsList[tCh];
        audioIOStatus.in = (relay_sts)in;
        audioIOStatus.out = (analogOutput_sts)out;
    }
    
    bool operator ==(const interpreter_sts &right) const
    {
        // сравниваем только передатчики и аналоговые входы выходы
        // приемники сами мен€ют свой канал без отправки по i2c
        return (trnChannel.raw == right.trnChannel.raw &&
                audioIOStatus.raw == right.audioIOStatus.raw);
    }
    
    bool operator !=(const interpreter_sts &right) const
    {
        // сравниваем только передатчики и аналоговые входы выходы
        // приемники сами мен€ют свой канал без отправки по i2c
        return (trnChannel.raw != right.trnChannel.raw ||
                audioIOStatus.raw != right.audioIOStatus.raw);
    }
    
    interpreter_sts& operator =(const interpreter_sts &right)
    {
        if(&right != this)
        {
             rcvChannel.raw    = right.rcvChannel.raw ;
             trnChannel.raw    = right.trnChannel.raw ;
             audioIOStatus.raw = right.audioIOStatus.raw;
        }

        return *this;
    }
};

extern  interpreter_sts   left_interpreter;
extern  interpreter_sts   right_interpreter;
extern  const  uint16_t   radioChannelsList[];
extern  const audioIO_t   analogInOutList[];

extern app_fsm_states_e i2c_response_handler(interpreter_sts * ptrIntrprtr);
extern void application_poll(void);
extern void i2c_main_receive_event(int);
extern void i2c_main_request_event();

#endif //_API_H