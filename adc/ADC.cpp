#include "ADC.h"


template <auto ch_num>
ADC<ch_num>::ADC(EADCGain common_gain, EADCPull common_pull, EADCAcquisitionTime acq, EADCResolution resolution)
:_ch_list
{
    ADCChannel_t(AIN_0,     6*ADC_REF_MV/ADC_CODE_MAX * (200.0 + 100.0)/100.0,  300.0f, 0.5f),   // RF_PDET_PIN
    ADCChannel_t(AIN_4,     4*ADC_REF_MV/ADC_CODE_MAX * (200.0 + 100.0)/100.0,  300.0f, 0.1f),   // MAIN_MEAS_PIN
    ADCChannel_t(AIN_5,     4*ADC_REF_MV/ADC_CODE_MAX,                          0.0f,   1.0f),   // VBAT_MEAS_PIN
    ADCChannel_t(AIN_6,     6*ADC_REF_MV/ADC_CODE_MAX,                          500.0f, 0.3f),   // JACK_5_PIN
    ADCChannel_t(AIN_7,     6*ADC_REF_MV/ADC_CODE_MAX,                          500.0f, 0.3f),   // JACK_6_PIN
    ADCChannel_t(AIN_VDD,   6*ADC_REF_MV/ADC_CODE_MAX,                          100.0f, 0.9f)    // VDD
}
{
    _resolution = resolution;
    
    enable();

    // initiaiton of channels
    for(uint32_t i = 0; i < ch_num; i++)
        NRF_SAADC->CH[i].PSELP = (uint32_t)_ch_list[i].aInput_num; 

    // common  initialisation of all positive ADC channels, 
    // private initialisation done individually
    for(uint32_t i = 0; i < ch_num; i++)
        NRF_SAADC->CH[i].CONFIG = (acq << SAADC_CH_CONFIG_TACQ_Pos) |
                                  (SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos) | // internal 0.6V as reference
                                  (common_gain << SAADC_CH_CONFIG_GAIN_Pos) |
                                  (common_pull << SAADC_CH_CONFIG_RESP_Pos);   
    disable();
}

template <auto ch_num>
void ADC<ch_num>::init()
{
    enable();

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
void   ADC<ch_num>::configChannel(EADCChannels channel,
                                  EADCGain common_gain, 
                                  EADCPull common_pull, 
                                  EADCAcquisitionTime acq, 
                                  EADCReferenceVoltage refVoltage)
{
    uint8_t index;

    // find channel in list
    for(index = 0; index < ch_num; index++)
    {
        if(_ch_list[index].aInput_num == channel)
            break;
    }

    NRF_SAADC->CH[index].CONFIG = (acq << SAADC_CH_CONFIG_TACQ_Pos) |
                                  (refVoltage << SAADC_CH_CONFIG_REFSEL_Pos) | 
                                  (common_gain << SAADC_CH_CONFIG_GAIN_Pos) |
                                  (common_pull << SAADC_CH_CONFIG_RESP_Pos); 
}

template <auto ch_num>
void ADC<ch_num>::deinit()
{
    for (uint8_t i = 0; i < ch_num; i++)
    {
        NRF_SAADC->CH[0].PSELP = 0;
        NRF_SAADC->CH[0].CONFIG = 0;
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
    
    while (NRF_SAADC->EVENTS_END == 1);
    deinit();
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
        if(_ch_list[index].aInput_num == channel)
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
        NRF_SAADC->EVENTS_STARTED = 0;

        // scale converted data
        for(uint8_t i = 0; i < ch_num; i++)
            _ch_list[i].scaleRaw(_raw_adc_value[i]);      
    
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

extern ADC<6> adc_unite;
extern void adc_callback();
extern "C" void SAADC_IRQHandler(); 

