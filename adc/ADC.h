#ifndef __ADC_H
#define __ADC_H

#include <intrinsics.h>
#include <stddef.h>
#include "nrf.h"
#include "Timer.h"

#define AIN_CH_MAX         (8)
#define ADC_REF_MV         (600.0)
#define ADC_CODE_MAX       (4096.0)
#define ADC_INT_PRIORITY   (7)
#define ADC_MEAS_INTERVAL  (300)            // in milliseconds


typedef enum
{
    AIN_NC = 0,
    AIN_0,
    AIN_1,
    AIN_2,
    AIN_3,
    AIN_4,
    AIN_5,
    AIN_6,
    AIN_7,
    AIN_VDD,
    AIN_VDDHDIV5    
} EADCInputs;


typedef enum
{
    VIN_ADC_VALUE   = AIN_4,
    VBAT_ADC_VALUE  = AIN_5,
    PDET_ADC_VALUE  = AIN_0,
    JACK5_ADC_VALUE = AIN_6,
    JACK6_ADC_VALUE = AIN_7,
    INNER_VDD       = AIN_VDD  
}EADCChannels;
#define ADC_CHANNELS_NUM  (6) // 1..8

typedef enum
{
    RES_8B = 0,
    RES_10B,
    RES_12B,
    RES_14B,  
} EADCResolution;

struct ADCChannel_t
{
EADCChannels     channel_num;
 const float     mVolts_c;               // millivolts translation coefficient
 const float     filt_threshold;         // filter applying threshold 
 const float     exponent_c;             // exponential approximation coefficient
       float     scaled_value  {0.0f};   // raw adc value after applying mVolts_ñ
       float     filt_value    {0.0f};   // result filtered value  
 
                 ADCChannel_t(EADCChannels channel,
                                     float mV_c  =  6 * ADC_REF_MV/ADC_CODE_MAX, 
                                     float f_th  = 300.0f, 
                                     float exp_c = 0.5f)
                 : channel_num(channel), mVolts_c(mV_c), filt_threshold(f_th), exponent_c(exp_c)
                 { }
 
 ADCChannel_t&   scaleRaw(int16_t raw) 
                 { 
                     scaled_value = mVolts_c * (float)raw;
                     return *this;  
                 }
 
        float    filterData() 
                 { 
                     float temp = scaled_value - filt_value;
     
                     if (temp < 0)
                         temp *= -1.0;
                     if (temp > filt_threshold)
                         filt_value = scaled_value;
                     else  
                         filt_value = filt_value * exponent_c + scaled_value * (1.0 - exponent_c);
     
                     return filt_value;
                 }
};  

typedef enum
{
    ACQ_3us = 0,
    ACQ_5us,
    ACQ_10us,
    ACQ_15us,
    ACQ_20us,
    ACQ_40us    
} EADCAcquisitionTime;

typedef enum
{
    INTERNAL = 0,
    VDD1DIV4 
} EADCReferenceVoltage;

typedef enum
{
    GAIN_1DIV6 = 0,
    GAIN_1DIV5,
    GAIN_1DIV4,
    GAIN_1DIV3,
    GAIN_1DIV2,
    GAIN_1,
    GAIN_2,
    GAIN_4
} EADCGain;

typedef enum
{
    BYPASS,
    PULLDOWN,
    PULLUP,
    VDD1_2
} EADCPull;

// configuration preferences of adc channel
struct ADCConfig_t
{
                EADCGain    gain;
                EADCPull    pull;
     EADCAcquisitionTime    acq_us      {ACQ_20us};
    EADCReferenceVoltage    reference   {INTERNAL};

                            ADCConfig_t(EADCGain gain,
                                        EADCPull pull = BYPASS,
                             EADCAcquisitionTime acq = ACQ_20us,
                            EADCReferenceVoltage reference = INTERNAL)
                            : gain(gain), pull(pull), acq_us(acq), reference(reference) 
                            { }
}; 


template <auto ch_num = AIN_CH_MAX>
class ADC
{
public:
                     ADC(EADCResolution resolution = RES_12B);

              void   init();
              void   deinit();
              void   enable()  { NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Enabled;  } 
              void   disable() { NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Disabled; }
              bool   isBusy()  { return (bool)NRF_SAADC->EVENTS_STARTED; }
              
              void   measure();
             float   get(EADCChannels channel);             

              void   onIRQ();
              void   setConvertionEND_IRQ(uint8_t priority);   // priority:0..7
              void   setCallback(void(*function)(void)) { _on_irq_callback = function; }
            
private:
      ADCChannel_t   _ch_list[ch_num];
       ADCConfig_t   _config_list[ch_num];

           int16_t   _raw_adc_value[ch_num];
    EADCResolution   _resolution;

         IRQn_Type   _IRQn;         // irq module
              void (*_on_irq_callback)(void) { nullptr };   // callback on request event user function

          uint64_t  _time {0}; // the timer itself
              bool  _is_paused { true };
};

extern ADC<ADC_CHANNELS_NUM> adc_unite;
extern void adc_callback();
extern "C" void SAADC_IRQHandler();

#include "ADC.cpp" // because this is template of class



#endif // __ADC_H

