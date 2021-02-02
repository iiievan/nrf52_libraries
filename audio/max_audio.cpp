#include "include.h"
#include "max_audio.h"

const uint8_t volume_val_high[10] =  {0x3F, 0x12, 0x11, 0x10, 0x0E, 0x0C, 0x0A, 0x08, 0x06, 0x02};  //mute, -12, -10, -8,  -5,  -3,  -1, +1, +3, +5
//const u8 volume_val_mid[10] = {0x3F, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0D, 0x0B, 0x0A, 0x09};  //mute, -14, -12, -10, -8,  -6,  -4, -2, -1, 0
//const u8 volume_val_low[10] = {0x3F, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0D, 0x0C};  //mute, -18, -16, -14, -12, -10, -8, -6, -4, -3

// таблица регулировки тональности в dB
const uint8_t tone_table[DBI_DISCRETE_STEPS][6] =
{
    {0x7F, 0x64, 0x3F, 0xA6, 0x06, 0xAD}, //+12dB: K:0x7F64 K2:0x3FA6 C2:0x06AD
    {0x71, 0x8A, 0x3F, 0xA3, 0x06, 0xCC}, //+11dB: K:0x718A K2:0x3FA3 C2:0x06CC
    {0x65, 0x31, 0x3F, 0xA0, 0x06, 0xE9}, //+10dB: K:0x6531 K2:0x3FA0 C2:0x06E9
    {0x5A, 0x30, 0x3F, 0x9D, 0x07, 0x02}, //+ 9dB: K:0x5A30 K2:0x3F9D C2:0x0702
    {0x50, 0x61, 0x3F, 0x9B, 0x07, 0x17}, //+ 8dB: K:0x5061 K2:0x3F9B C2:0x0717
    {0x47, 0xA3, 0x3F, 0x99, 0x07, 0x25}, //+ 7dB: K:0x47A3 K2:0x3F99 C2:0x0725
    {0x3F, 0x9D, 0x3F, 0x98, 0x07, 0x2A}, //+ 6dB: K:0x3F9D K2:0x3F98 C2:0x072A
    {0x38, 0xE7, 0x3F, 0x99, 0x07, 0x23}, //+ 5dB: K:0x38E7 K2:0x3F99 C2:0x0723
    {0x32, 0xB7, 0x3F, 0x9C, 0x07, 0x0A}, //+ 4dB: K:0x32B7 K2:0x3F9C C2:0x070A
    {0x2D, 0x33, 0x3F, 0xA2, 0x06, 0xD6}, //+ 3dB: K:0x2D33 K2:0x3FA2 C2:0x06D6
    {0x28, 0x49, 0x3F, 0xAC, 0x06, 0x72}, //+ 2dB: K:0x2849 K2:0x3FAC C2:0x0672
    {0x23, 0xE7, 0x3F, 0xBF, 0x05, 0xA9}, //+ 1dB: K:0x23E7 K2:0x3FBF C2:0x05A9
    {0x20, 0x00, 0x40, 0x00, 0x00, 0x00}, //+ 0dB: K:0x2000 K2:0x4000 C2:0x0000
    {0x1C, 0x85, 0x3F, 0xB3, 0x06, 0x2B}, //- 1dB: K:0x1C85 K2:0x3FB3 C2:0x062B
    {0x19, 0x6B, 0x3F, 0x8A, 0x07, 0xA7}, //- 2dB: K:0x196B K2:0x3F8A C2:0x07A7
    {0x16, 0xA7, 0x3F, 0x62, 0x08, 0xD7}, //- 3dB: K:0x16A7 K2:0x3F62 C2:0x08D7
    {0x14, 0x30, 0x3F, 0x3A, 0x09, 0xEA}, //- 4dB: K:0x1430 K2:0x3F3A C2:0x09EA
    {0x11, 0xFE, 0x3F, 0x0E, 0x0A, 0xF2}, //- 5dB: K:0x11FE K2:0x3F0E C2:0x0AF2
    {0x10, 0x09, 0x3E, 0xDF, 0x0B, 0xF6}, //- 6dB: K:0x1009 K2:0x3EDF C2:0x0BF6
    {0x0E, 0x4B, 0x3E, 0xAB, 0x0C, 0xFB}, //- 7dB: K:0x0E4B K2:0x3EAB C2:0x0CFB
    {0x0C, 0xBD, 0x3E, 0x72, 0x0E, 0x05}, //- 8dB: K:0x0CBD K2:0x3E72 C2:0x0E05
    {0x0B, 0x5A, 0x3E, 0x32, 0x0F, 0x14}, //- 9dB: K:0x0B5A K2:0x3E32 C2:0x0F14
    {0x0A, 0xE1, 0x3D, 0xEC, 0x10, 0x2C}, //-10dB: K:0x0AE1 K2:0x3DEC C2:0x102C
    {0x09, 0x04, 0x3D, 0x9D, 0x11, 0x4D}, //-11dB: K:0x0904 K2:0x3D9D C2:0x114D
    {0x08, 0x09, 0x3D, 0x46, 0x12, 0x78}, //-12dB: K:0x0809 K2:0x3D46 C2:0x1278 
};

//начальная инициализация регистров в максе
#ifdef MAX_9867
const uint8_t MAX_9867_INIT_REG[][3] = {
#ifdef TRANSMITTER 
// len   | register | data 
  {0x02,    0x04,     0x00},    // Interrupt Enable
  {0x02,    0x05,     0x10},    // System Clock
  {0x02,    0x06,     0x80},    // Audio Clock High
  {0x02,    0x07,     0x00},    // Audio Clock Low 
  {0x02,    0x08,     0x10},    // Interface 1a
  {0x02,    0x09,     0x00},    // Interface 1b // if MP3 here must be 0x80(DMONO)
  {0x02,    0x0A,     0x50},    // Codec Filters: AVFILT.0 , AVFILT.2
  {0x02,    0x0B,     0x00},    // DAC Gain/Sidetone
  {0x02,    0x0C,     0x00},    // DAC Level
  {0x02,    0x0D,     0x33},    // ADC Level 0дБ
  {0x02,    0x0E,     0x00},    // Left Line input level
  {0x02,    0x0F,     0x00},    // Right Line input level
  {0x02,    0x10,     0x00},    // Left Volume Control
  {0x02,    0x11,     0x00},    // Right Volume Control
  {0x02,    0x12,     0x20},    // Left Mic Gain : 0x20
  {0x02,    0x13,     0x00},    // Right Mic Gain
  {0x02,    0x14,     0x40},    // Input : MXINL.0
  {0x02,    0x15,     0x00},    // Microphone
  {0x02,    0x16,     0x00},    // Mode: headphone mode
  {0x02,    0x17,     0x82},    // System shutdown: right left mic enable
#endif //TRANSMITTER

#ifdef RECEIVER 
// len   | register | data
  {0x02,    0x04,     0x00},    // Interrupt Enable
  {0x02,    0x05,     0x10},    // System Clock
  {0x02,    0x06,     0x80},    // Audio Clock High
  {0x02,    0x07,     0x00},    // Audio Clock Low   
  {0x02,    0x08,     0x10},    // Interface 1a
  {0x02,    0x09,     0x00},    // Interface 1b // if MP3 here must be 0x80(DMONO)
  {0x02,    0x0A,     0x00},    // Codec Filters  
  {0x02,    0x0B,     0x00},    // DAC Gain/Sidetone
  {0x02,    0x0C,     0x00},    // DAC Level
  {0x02,    0x0D,     0x33},    // ADC Level 0dB 
  {0x02,    0x0E,     0x00},    // Left Line input level
  {0x02,    0x0F,     0x00},    // Right Line input level
  {0x02,    0x10,     0x0A},    // Left Volume Control : 0x0A
  {0x02,    0x11,     0x00},    // Right Volume Control
  {0x02,    0x12,     0x00},    // Left Mic Gain  
  {0x02,    0x13,     0x00},    // Right Mic Gain  
  {0x02,    0x14,     0x00},    // Input
  {0x02,    0x15,     0x00},    // Microphone
  {0x02,    0x16,     0x01},    // Mode: headphone mode  
  {0x02,    0x17,     0x88},    // System shutdown: left dac enable
#else
  0
#endif  // RECEIVER
};
#endif // MAX_9867

#ifdef MAX_98089
//начальная инициализация регистров в максе для работы по радиоканалам
const uint8_t MAX_98089_MAIN_START_INIT[][3] = 
{  
    // len   | register | data
    // настройка шины I2S_1 , I2S-2 не используется
    {0x02,     0x11,    0x30},  // Clock mode: sample rate 16 KHz for filtering
    {0x02,     0x12,    0x30},  // Anyclock control for 15.625kHz LRCLK, 8Mhz PCLK
    {0x02,     0x13,    0x00},  // Anyclock control for 15.625kHz LRCLK, 8Mhz PCLK
    {0x02,     0x14,    0x10},  // DAI1 Format: slave I2S
    {0x02,     0x16,    0x43},  // I/O configuration record and playback enable
    {0x02,     0x18,    0x00},  // Filters: disable
	
    // настройка выхода OUT CH1, OUT CH2
    {0x02,     0x22,    0x88},  // Left DAC to DAI1_left chnl, right DAC to DAI1_right chnl
    {0x02,     0x28,    0x01},  // Left  Receiver OUTPUT: connect to left DAC
    {0x02,     0x29,    0x01},  // Right Receiver OUTPUT: connect to right DAC
    {0x02,     0x2A,    0x80},  // Receiver Control: enable line output 0dB
    {0x02,     0x2F,    0x00},  // DAI1 playback level
    {0x02,     0x3B,    0x15},  // Left line Volume: 0db
    {0x02,     0x3C,    0x15},  // Right line Volume: 0db
    {0x02,     0x4D,    0x0E},  // Output Enable
	
    // настройка входов Floor и Common 
    {0x02,     0x23,    0x04},  // Left ADC :left ADC to left channel DAI1
    {0x02,     0x24,    0x00},  // Right ADC: not working at start 
    {0x02,     0x33,    0x03},  // Left ADC level // Левое ацп для микрофона без фантомного питания, пока выключим
    {0x02,     0x34,    0x03},  // Right ADC level
    {0x02,     0x37,    0x03},  // INA Input Level
    {0x02,     0x38,    0x03},  // INB Input Level
    {0x02,     0x3F,    0x08},  // Microphone AGC configuration
    {0x02,     0x40,    0x03},  // Microphone AGC threshold
    {0x02,     0x47,    0xC0},  // Audio Input: INA Diff, INB Diff  
    {0x02,     0x49,    0xE0},  // Audio Input: INA Diff, INB Diff 
    {0x02,     0x4C,    0xC2},  // Input Enable 
	
    // общая настройка
    {0x02,     0x10,    0x10},  // System clock: PCLK = MCLK
    {0x02,     0x4E,    0xF0},  // Bias Control:  
//  {0x02,     0x50,    0x0F},  // DAC Power mode 
    {0x02,     0x51,    0x81},  // System shutdown
};

//начальная инициализация регистров в максе для работы по радиоканалам
const uint8_t MAX_98089_LR_START_INIT[][3] = 
{  
    // len   | register | data
  	// настройка выхода на наушники
    {0x02,     0x20,    0x01},  // Filters 
    {0x02,     0x31,    0x00},  // DIA2 Playback Level
    {0x02,     0x39,    0x1A},  // Left Headphone Volume
    {0x02,     0x3A,    0x1A},  // Right Headphone Volume
    {0x02,     0x4D,    0xC3},  // Output Enable  

  	// настройка микрофонов  
    {0x02,     0x11,    0x30},  // Clock mode: sample rate 16 KHz for filtering
    {0x02,     0x12,    0x30},  // Anyclock control for 15.625KHz LRCLK, 8Mhz PCLK
    {0x02,     0x13,    0x00},  // Anyclock control for 15.625KHz LRCLK, 8MHz PCLK
    {0x02,     0x14,    0x10},  // DAI1 Format: Slave I2S
    {0x02,     0x37,    0x03},  // INA Input Level: 0dB
    {0x02,     0x3F,    0x0B},  // Microphone AGC configuration
    {0x02,     0x40,    0xF3},  // Microphone AGC threshold
    {0x02,     0x47,    0x80},  // Audio Input: INA Diff 
	
 	// настройка эквалайзера
    //{0x02,     0x49,    0x02},  // Level control: EQ2 - enable
    //{0x02,     0x86,    0xC0},  // Band 1 K1:h 
    //{0x02,     0x87,    0x01},  // Band 1 K1:l
    //{0x02,     0x8A,    0x00},  // Band 1 C1:h
    //{0x02,     0x8B,    0x06},  // Band 1 C1:l
    //{0x02,     0x90,    0xC0},  // Band 2 K1:h 
    //{0x02,     0x91,    0x01},  // Band 2 K1:l
    //{0x02,     0x94,    0x00},  // Band 2 C1:h
    //{0x02,     0x95,    0x06},  // Band 2 C1:l
    //{0x02,     0x9A,    0x40},  // Band 3 K1:h 
    //{0x02,     0x9B,    0x00},  // Band 3 K1:l
    //{0x02,     0x9E,    0x00},  // Band 3 C1:h
    //{0x02,     0x9F,    0x00},  // Band 3 C1:l
    //{0x02,     0xA4,    0x40},  // Band 4 K1:h 
    //{0x02,     0xA5,    0x00},  // Band 4 K1:l
    //{0x02,     0xA8,    0x00},  // Band 4 C1:h
    //{0x02,     0xA9,    0x00},  // Band 4 C1:l
    //{0x02,     0xAE,    0x40},  // Band 5 K1:h 
    //{0x02,     0xAF,    0x00},  // Band 5 K1:l
    //{0x02,     0xB2,    0x00},  // Band 5 C1:h
    //{0x02,     0xB3,    0x00},  // Band 5 C1:l
    
  	// общая настройка
    {0x02,     0x10,    0x10},  // System clock: PCLK = MCLK
    {0x02,     0x0F,    0x02},  // Interrupt enable: jdet irq
    {0x02,     0x4B,    0x81},  // Jack Detection: deb 50ms
    {0x02,     0x4E,    0xF0},  // Bias Control:
    {0x02,     0x51,    0x81},  // System shutdown
};


#endif //MAX_98089

max_audio::max_audio(uint32_t sda_pin, uint32_t scl_pin)
: twi(sda_pin, scl_pin),
  i2s(MCLK_PIN, LRCLK_PIN, BCLK_PIN, SDIN_PIN ,SDOUT_PIN)
{
    snd_rx = false;
    _volume_index = 0;
}

void max_audio::init()
{  
#ifdef MAX_9867    
    twi::init(I2C_MAX_9867_WRITE_ADDR, 400);
#else
    twi::init(I2C_MAX_98089_WRITE_ADDR, 400);
#endif

    i2s::init(); 
    
#ifndef TRANSMITTER_CH1
    i2s::pause();  // запускаем шину при приеме первого пакета аудио для синхронизации с приемником.
#endif
}


void max_audio::init_LR()
{ 
    i2s::pause();

    for (uint8_t i = 0; i <  countof(MAX_98089_LR_START_INIT); i++)
    {
        _max_reset = twi::write((uint8_t*)&MAX_98089_LR_START_INIT[i][1], MAX_98089_LR_START_INIT[i][0], true);
    }

    i2s::resume();
}

void max_audio::init_main()
{ 
  	i2s::pause();
	
    for (uint8_t i = 0; i < countof(MAX_98089_MAIN_START_INIT); i++)
    {
        _max_reset = twi::write((uint8_t*)&MAX_98089_MAIN_START_INIT[i][1], MAX_98089_MAIN_START_INIT[i][0], true);
    }
	
	i2s::resume();
}

void   max_audio::initPhantom()
{
    uint8_t phantomSettings[][3] =
    {    
        {0x02,     0x15,    0x40},  // DAI1 Clock: for phantom
        {0x02,     0x18,    0x50},  // Filters : for debug with sinwave or phantom
        {0x02,     0x23,    0x04},  // Left ADC: for phantom
        {0x02,     0x24,    0x00},  // Right ADC: for phantom
        {0x02,     0x34,    0x03},  // Right ADC level: for phantom
        {0x02,     0x36,    0x20},  // MIC2 input level: for debug with sinwave or phantom
        {0x02,     0x4C,    0x8A},  // Input Enable: for phantom
    };

    i2s::pause();
  
    for (uint8_t i = 0; i < countof(phantomSettings); i++)
    {
        _max_reset = twi::write((uint8_t*)&phantomSettings[i][1], phantomSettings[i][0], true);
    }
  
    i2s::resume();

}

void   max_audio::initGarniture()
{
    uint8_t garnitureSettings[][3] =
    {
        {0x02,     0x15,    0x40},  // DAI1 Clock: for garniture
        {0x02,     0x18,    0x50},  // Filters : for garniture
        {0x02,     0x23,    0x40},  // Left ADC: for garniture
        {0x02,     0x24,    0x04},  // Right ADC: for garniture     
        {0x02,     0x33,    0x03},  // Left ADC level: for garniture
        {0x02,     0x36,    0x20},  // MIC2 input level: for garniture		 
        {0x02,     0x4C,    0x8A},  // Input Enable: for garniture
    };

    i2s::pause();
  
    for (uint8_t i = 0; i < countof(garnitureSettings); i++)
    {
        _max_reset = twi::write((uint8_t*)&garnitureSettings[i][1], garnitureSettings[i][0], true);
    }
  
    i2s::resume();
}

void   max_audio::listenAnalog()
{
    uint8_t listenAnalogSettings[][3] =
    {
        {0x02,     0x19,    0x00},  // Clock mode: 
        {0x02,     0x1A,    0x00},  // Anyclock control 
        {0x02,     0x1B,    0x00},  // Anyclock control f
        {0x02,     0x1C,    0x00},  // DAI2 Format: 
        {0x02,     0x1D,    0x00},  // DAI2 Clock: 
        {0x02,     0x1E,    0x00},  // I/O configuration
		{0x02,     0x22,    0x84},  // DAC
        {0x02,     0x16,    0x43},  // I/O configuration: record and playback enable
    };

    i2s::pause();
  
    for (uint8_t i = 0; i < countof(listenAnalogSettings); i++)
    {
        _max_reset = twi::write((uint8_t*)&listenAnalogSettings[i][1], listenAnalogSettings[i][0], true);
    }
  
    i2s::resume();
}

void   max_audio::listenRadio()
{
    uint8_t listenRadioSettings[][3] =
    {
        {0x02,     0x19,    0x30},  // Clock mode: sample rate 16 KHz for filtering
        {0x02,     0x1A,    0x30},  // Anyclock control for 15.625kHz LRCLK, 8Mhz PCLK
        {0x02,     0x1B,    0x00},  // Anyclock control for 15.625kHz LRCLK, 8Mhz PCLK
        {0x02,     0x1C,    0x90},  // DAI2 Format: Master I2S
        {0x02,     0x1D,    0x07},  // DAI2 Clock: BCLK = PCLK/16 = 500КГц
        {0x02,     0x1E,    0x81},  // I/O configuration
        {0x02,     0x22,    0x21},  // DAC
        {0x02,     0x16,    0x42},  // I/O configuration: playback enable
    };

    i2s::pause();
  
    for (uint8_t i = 0; i < countof(listenRadioSettings); i++)
    {
        _max_reset = twi::write((uint8_t*)&listenRadioSettings[i][1], listenRadioSettings[i][0], true);
    }
  
    i2s::resume();
}

// переводит центральный макс на работу со входом floor
void   max_audio::selectFloor()
{
    uint8_t reg = read_reg(0x23);

    // назначает левому АЦП вход INA
    reg |=  0x04;
    reg &= ~0x01;

    write_reg(0x23, reg);
}

// переводит центральный макс на работу со входом common    
void   max_audio::selectCommon()
{
    uint8_t reg = read_reg(0x23);

    // назначает левому АЦП вход INB
    reg &= ~0x04;
    reg |=  0x01;   

    write_reg(0x23, reg);
}

// переводит центральный макс на работу со выходом Out1   
void   max_audio::selectOut1()
{
    uint8_t reg = read_reg(0x4D);

    // включаем левый ЦАП, выключаем правый ЦАП
    reg &= ~0x01;
    reg |=  0x02;

    write_reg(0x4D, reg);

    // левый ресивер выводим из mute
    reg = read_reg(0x3B);
    reg &= ~0x80;
    write_reg(0x3B, reg);

    // правый глушим
    reg = read_reg(0x3C);
    reg |= 0x80;
    write_reg(0x3C, reg);
}

// переводит центральный макс на работу со входом Out2     
void   max_audio::selectOut2()
{
    uint8_t reg = read_reg(0x4D);

    // включаем правый ЦАП, выключаем левый ЦАП
    reg |=  0x01;
    reg &= ~0x02;       

    write_reg(0x4D, reg);

    // левый глушим
    reg = read_reg(0x3B);
    reg |= 0x80;
    write_reg(0x3B, reg);

    // правый выводим из mute
    reg = read_reg(0x3C);
    reg &= ~0x80;
    write_reg(0x3C, reg);

} 

void max_audio::selectAnalogInput(interpreter_sts * ptrIntrprtr)
{
    switch(ptrIntrprtr->audioIOStatus.in)
    {
        case FLOOR:
            selectFloor();
            break;
        case COMMON:
            selectCommon();
            break;
        case INPUT_NA:
        default:
            break;
    }
}

void max_audio::selectAnalogOutput(interpreter_sts * ptrIntrprtr)
{
    switch(ptrIntrprtr->audioIOStatus.out)
    {
        case OUTPUT_1:
            selectOut1();
            break;
        case OUTPUT_2:
            selectOut2();
            break;
        case OUTPUT_NA:
        default:
            break;
    }
}

uint8_t max_audio::read_reg(uint8_t reg)
{
    uint8_t res;
    
    _max_reset = twi::write(&reg, 1, false);
    
    _max_reset = twi::read(&res, 1);
    
    return res;
}

void max_audio::write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2];

    buf[0] = reg;
    buf[1] = val;
    
    _max_reset =  twi::write((uint8_t*)&buf, 2, true);
 }

int max_audio::get_volume_index()
{
    return _volume_index;
}

uint8_t max_audio::get_volume()
{
    uint8_t res;
    uint8_t const *volume_val = volume_val_high;
  
    res  = read_reg(VOLUME_REG);
    _volume_index = 0;

    for (u8 i = 0; i < VOLUME_VALS - 1; i++)
    {
        if (res <= volume_val[i] && res > volume_val[i + 1])
        {
            _volume_index = i;

            break;
        }
    }

    if (res >= volume_val[0])
        _volume_index = 0;

    if (res <= volume_val[VOLUME_VALS - 1])
        _volume_index = VOLUME_VALS - 1;
    
    return res;
}

void max_audio::set_volume(uint8_t indx)
{
#ifdef MAX_98089
  // понимает значения только от 0 до 31(0x1F)
  uint8_t vol = indx/8; // 255/8 = 1F;

  write_reg(0x39, vol);
  write_reg(0x3A, vol);
#else
  uint8_t const* volume_val = volume_val_high;

  _volume_index = indx;
  
  write_reg(VOLUME_REG, volume_val[indx]);
#endif
}

void   max_audio::set_high_tone(dBi_tone_e tone)
{
    // перезаписываем только К, К2 и C2
    uint8_t x[6] = {0,1,4,5,8,9};

    for(uint8_t i = 0; i < 6; i++)
    { write_reg(BAND_3_START_REG + x[i], tone_table[tone][i]); }

    for(uint8_t i = 0; i < 6; i++)
    { write_reg(BAND_4_START_REG + x[i], tone_table[tone][i]); }

    for(uint8_t i = 0; i < 6; i++)
    { write_reg(BAND_5_START_REG + x[i], tone_table[tone][i]); }
}

void   max_audio::set_low_tone (dBi_tone_e tone)
{
    // перезаписываем только К, К2 и C2
    uint8_t x[6] = {0,1,4,5,8,9};

    for(uint8_t i = 0; i < 6; i++)
    { write_reg(BAND_1_START_REG + x[i], tone_table[tone][i]); }

    for(uint8_t i = 0; i < 6; i++)
    { write_reg(BAND_2_START_REG + x[i], tone_table[tone][i]); }
}

void max_audio::set_mute(bool mute)
{
#ifdef MAX_9867
    if (mute)
        write_reg(0x0C, BIT(6));
    else
        write_reg(0x0C, 0x00);
#else
    if (mute)
        write_reg(0x4D, 0x00);
    else
        write_reg(0x4D, 0x0F);
    return;
#endif  // MAX_9867
}

// disabling i2s sdout
// return true if bit was changed
bool max_audio::disable_dai_sdout(uint8_t addr)
{
    uint8_t reg = read_reg(addr);
       bool result {false};

    if(reg & 0x02)
    {
       reg &= ~0x02;
       write_reg(addr, reg);
       result = true;
    }
    
    return result;
}

// enabling i2s sdout
// return true if bit was changed
bool max_audio::enable_dai_sdout(uint8_t addr)
{
    uint8_t reg = read_reg(addr);
       bool result {false};
    
    if(!(reg & 0x02))
    {
       reg |= 0x02;
       write_reg(addr, reg);
       result = true;
    }

    return result;
}

// disabling i2s sdin
//return true if bit was changed
bool max_audio::disable_dai_sdin(uint8_t addr)
{
    uint8_t reg = read_reg(addr);
       bool result {false};

    if(reg & 0x01)
    {
       reg &= ~0x01;
       write_reg(addr, reg);
       result = true;
    }
    
    return result;
}

// enabling i2s sdin
// return true if bit was changed
bool max_audio::enable_dai_sdin(uint8_t addr)
{
    uint8_t reg = read_reg(addr);
       bool result {false};

    if(!(reg & 0x01))
    {
       reg |= 0x01;
       write_reg(addr, reg);
       result = true;
    }
    
    return result;
}

void max_audio::set_mic(bool on, bool filter)
{
#ifdef MAX_9867
    if (on)
    {
        write_reg(0x17, 0x80);
        write_reg(0x12, 0x00);
        write_reg(0x13, 0x20);
        write_reg(0x14, 0x10);
        write_reg(0x17, 0x83);
        write_reg(0x0A, 0x50);
    }
    else
    {
        write_reg(0x17, 0x80);
        write_reg(0x12, 0x20);
        write_reg(0x13, 0x00);
        write_reg(0x14, 0x40);
        write_reg(0x17, 0x82);

        if (filter)
            write_reg(0x0A, 0x20);
         else
            write_reg(0x0A, 0x50);
    }
#else
    return;
#endif  // MAX_9867
}

void max_audio::shutdown()
{    
    uint8_t reg = read_reg(POWER_REG);

    reg &= ~0x80;

    write_reg(POWER_REG, reg);
}

// return true if bit was changed
bool max_audio::turn_on()
{
    uint8_t reg = read_reg(POWER_REG);
       bool result {false};
       
   if(!(reg & 0x80))
   {
       reg |= 0x80;
       write_reg(POWER_REG, reg);
       result = true;
    }

    return result;
}

uint8_t max_audio::get_shdn()
{
    return ((read_reg(POWER_REG) & 0x80) >> 7);
}

uint8_t max_audio::get_status()
{
    return read_reg(0x00);
}

uint8_t max_audio::get_jack_sense()
{
  	return read_reg(JSNS_REG);
}

void max_audio::set_gain(uint8_t gain, bool integrated_mic)
{
  
#ifdef MAX_9867
    if (integrated_mic)
        write_reg(0x13, gain);
    else
        write_reg(0x12, gain);
#endif  // MAX_9867
}

e_gstate max_audio::volume_up(bool is_power_down)
{
    e_gstate res = FAIL;

    if (is_power_down)
      return res;

    if (get_shdn())
    {
        get_volume();

        if (_volume_index < VOLUME_VALS - 1)
        {
            _volume_index++;

            set_volume((uint8_t)_volume_index);

            res = OK;
        }
    }
    
    return res;
}

e_gstate max_audio::volume_down(bool is_power_down)
{
    e_gstate res = FAIL;

    if (is_power_down)
      return res;
      
    if (get_shdn())
    {
        get_volume();

        if (_volume_index > 0)
        {
            _volume_index--;
            set_volume((uint8_t) _volume_index);

            res = OK;
        }
    }
    
    return res;
}

void max_audio::volume_default()
{
    _volume_index = DEFAULT_VOLUME;

     set_volume((uint8_t) _volume_index);
}

void max_audio::is_max_reset()
{  
#if defined (RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
    if(i2s::i2s_busy == false)
    {
        //nrf_gpio_pin_set(DBG_PIN_3);
        i2s::pause();
    }
    
    for(uint16_t j = 0; j < 1024; j++)
    {
      if(bv32_codec.sound_decode_ready)
      { 
            i2s::resume();
            //nrf_gpio_pin_clear(DBG_PIN_3);
            break;
      }
    }
#endif
    
    if (_max_reset)
    {        
        //выключаем аудио
        this->shutdown();
        delay_ms(10);

        nrf_gpio_pin_clear(MAX_ENABLE);

        twi::disable();

        //включаем аудио
        delay_ms(50);
        twi::init();

        nrf_gpio_pin_set(MAX_ENABLE);
        
        delay_ms(10);
        this->init();
    
        _max_reset = false;        
    }
}

bool max_audio::is_twi_busy()
{
    return twi::is_busy();
}

void max_audio::free_tx_buffers()
{
    i2s::output_frame.clear();
}

void max_audio::sync_receiving()
{
  /*
    static int cnt[2] = {0,0};
    
  __disable_interrupt();
  
  if (_sub_frame_cnt >= RECEIVER_SUB_FRAME_MAX - 2) 
  {
      cnt[0]++;
  }
  else
  {
      cnt[1]++;
      _sub_frame_cnt = RECEIVER_SUB_FRAME_MAX - 2;
  }
  
  __enable_interrupt();
*/
  return;
}

void max_audio::i2s_irq()
{
    i2s::irq();
}

void max_audio::soft_irq()
{  
#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT)
    //i2s::output_frame.fill_frame_with_sin(16000, 35);
    #ifdef RX_INTERVALS_DEBUG
        //nrf_gpio_pin_set(DBG_PIN_3);
    #endif
    bv32_codec.decode_handler(radio_unit.radio_encoded_snd_rx, &output_frame);
    
    #ifdef RX_INTERVALS_DEBUG
        //nrf_gpio_pin_clear(DBG_PIN_3);
    #endif
#endif
#if defined(TRANSMITTER_CH1)
	#ifdef TX_INTERVALS_DEBUG
        nrf_gpio_pin_set(DBG_PIN_3);
    #endif
    // кодируем приянтые по i2s данные
	bv32_codec.record_handler(&input_frame, radio_unit.radio_encoded_snd_tx);
	
	#ifdef TX_INTERVALS_DEBUG
        nrf_gpio_pin_clear(DBG_PIN_3);
    #endif
#endif    
}

#if defined(RECEIVER_LEFT) || defined(RECEIVER_RIGHT) || defined(TRANSMITTER_CH1)
max_audio max_audio_codec(I2C_MAX_SDA, I2C_MAX_SCL);

void I2S_IRQHandler(void)
{
    max_audio_codec.i2s_irq();  // обработка прерывания шины I2S, тут же вызывается и софтварное прерывание, для заполнения буфера кадров.
}

void SWI0_EGU0_IRQHandler()
{
    NRF_EGU0->EVENTS_TRIGGERED[0] = 0;

    max_audio_codec.soft_irq(); // заполняем очередной кадр в потоке.
}
#endif // RECEIVER_LEFT || RECEIVER_RIGHT || TRANSMITTER_CH1





