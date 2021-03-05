#include "ADC.h"

template <auto ch_num>
ADC<ch_num>::ADC(EADCResolution resolution)
:_resolution(resolution),
_ch_list
{
    ADCChannel_t(VIN_ADC_VALUE,     6*ADC_REF_MV/ADC_CODE_MAX * (200.0 + 100.0)/100.0,  300.0f, 0.5f),   // MAIN_MEAS_PIN
    ADCChannel_t(VBAT_ADC_VALUE,    4*ADC_REF_MV/ADC_CODE_MAX * (200.0 + 100.0)/100.0,  300.0f, 0.1f),   // VBAT_MEAS_PIN
    ADCChannel_t(PDET_ADC_VALUE,    4*ADC_REF_MV/ADC_CODE_MAX,                          0.0f,   1.0f),   // RF_PDET_PIN
    ADCChannel_t(JACK5_ADC_VALUE,   6*ADC_REF_MV/ADC_CODE_MAX,                          500.0f, 0.3f),   // JACK_5_PIN
    ADCChannel_t(JACK6_ADC_VALUE,   6*ADC_REF_MV/ADC_CODE_MAX,                          500.0f, 0.3f),   // JACK_6_PIN
    ADCChannel_t(INNER_VDD,         6*ADC_REF_MV/ADC_CODE_MAX,                          100.0f, 0.9f)    // INNER VDD
},
_config_list
{
    ADCConfig_t(GAIN_1DIV6, BYPASS,   ACQ_20us, INTERNAL), // MAIN_MEAS_PIN
    ADCConfig_t(GAIN_1DIV4, BYPASS,   ACQ_20us, INTERNAL), // VBAT_MEAS_PIN
    ADCConfig_t(GAIN_1DIV4, PULLDOWN, ACQ_20us, INTERNAL), // RF_PDET_PIN
    ADCConfig_t(GAIN_1DIV6, PULLUP,   ACQ_20us, INTERNAL), // JACK_5_PIN
    ADCConfig_t(GAIN_1DIV6, PULLUP,   ACQ_20us, INTERNAL), // JACK_6_PIN
    ADCConfig_t(GAIN_1DIV6, BYPASS,   ACQ_20us, INTERNAL)  // VDD
}
{ }

template <auto ch_num>
void ADC<ch_num>::init()
{
    enable();

    for(uint8_t i = 0; i < ch_num; i++)
        NRF_SAADC->CH[i].PSELP = (uint32_t)_ch_list[i].channel_num; 

    for(uint8_t i = 0; i < ch_num; i++)
        NRF_SAADC->CH[i].CONFIG = (_config_list[i].acq_us << SAADC_CH_CONFIG_TACQ_Pos) |
                                  (_config_list[i].reference << SAADC_CH_CONFIG_REFSEL_Pos) | 
                                  (_config_list[i].gain << SAADC_CH_CONFIG_GAIN_Pos) |
                                  (_config_list[i].pull << SAADC_CH_CONFIG_RESP_Pos); 

    NRF_SAADC->RESULT.PTR = (uint32_t)&_raw_adc_value[0];
    NRF_SAADC->RESULT.MAXCNT = ch_num;
    NRF_SAADC->RESOLUTION = (_resolution << SAADC_RESOLUTION_VAL_Pos);

    // start ADC calibration
    NRF_SAADC->EVENTS_CALIBRATEDONE = 0;
    NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;

    while (NRF_SAADC->EVENTS_CALIBRATEDONE == 0); 
    sys_timer.delay_us(80);

    setConvertionEND_IRQ(ADC_INT_PRIORITY);
}

template <auto ch_num>
void ADC<ch_num>::deinit()
{
    for (uint8_t i = 0; i < ch_num; i++)
    {
        NRF_SAADC->CH[i].PSELP = 0;
        NRF_SAADC->CH[i].CONFIG = 0;
    }

    NRF_SAADC->TASKS_STOP = 1;

    NRF_SAADC->INTEN    = (SAADC_INTEN_END_Disabled << SAADC_INTEN_END_Pos);
    NRF_SAADC->INTENCLR = (SAADC_INTENCLR_END_Disabled << SAADC_INTENCLR_END_Pos);
    disable();
}

template <auto ch_num>
void ADC<ch_num>::measure()
{
    init();    
    
    NRF_SAADC->EVENTS_STARTED = 0;
    NRF_SAADC->TASKS_START = 1;
    while (NRF_SAADC->EVENTS_STARTED == 0);

    //make 1 sample of all channels
    NRF_SAADC->TASKS_SAMPLE = 1; 
}

template <auto ch_num>
float   ADC<ch_num>::get(EADCChannels channel)
{
    uint8_t index;
      float result = 0.0f;

    // wait until conversation finished if needed
    while(isBusy());

    // find channel in list
    for(index = 0; index < ch_num; index++)
    {
        // filter scaled data in iterrupt here to avoid time waste in irq.
        if(_ch_list[index].channel_num == channel)
            result = _ch_list[index].filterData();
    }    
    
    return result;
}

template <auto ch_num>
void   ADC<ch_num>::onIRQ()
{
    if (NRF_SAADC->EVENTS_END)
    {
        NRF_SAADC->EVENTS_END = 0x0UL;
        NRF_SAADC->EVENTS_STARTED = 0x0UL;

        // scale converted data
        for(uint8_t i = 0; i < ch_num; i++)
            _ch_list[i].scaleRaw(_raw_adc_value[i]); 
        
        deinit();
    
        if (_on_irq_callback)
            _on_irq_callback();
    }
}

template <auto ch_num>
void   ADC<ch_num>::setConvertionEND_IRQ(uint8_t priority)
{
    NRF_SAADC->INTENCLR = 0xFFFFFFFF;
    NRF_SAADC->INTEN    = (SAADC_INTEN_END_Enabled << SAADC_INTEN_END_Pos);    
    NRF_SAADC->INTENSET = (SAADC_INTENSET_END_Enabled << SAADC_INTENSET_END_Disabled);

    NRF_SAADC->EVENTS_STARTED = 0;
    NRF_SAADC->EVENTS_END = 0;

    NVIC_SetPriority(SAADC_IRQn, priority);
    NVIC_ClearPendingIRQ(SAADC_IRQn);
    NVIC_EnableIRQ(SAADC_IRQn);
} 

