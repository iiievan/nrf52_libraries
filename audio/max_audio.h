#ifndef _MAXAUDIO_DRIVER_H_
#define _MAXAUDIO_DRIVER_H_

#include "include.h"
#include "twi.h"
#include "i2s.h"
#include "frame_buffer.h"


// ��� ����� ����������� ���������� ��� ������������ ���������� �����������.
//#define MAX_9867    
#define MAX_98089

#ifdef FIND_BEACON_ALARM
  #define DEFAULT_VOLUME  0
#else
  #define DEFAULT_VOLUME  6
#endif

#ifdef MAX_9867
#define MAX_9867_INIT_LINES (sizeof(MAX_9867_INIT_REG)/sizeof(MAX_9867_INIT_REG[0]))
#define INIT_LINES  MAX_9867_INIT_LINES

#define VOLUME_VALS     (10)
#define VOLUME_REG      (0x10)
#define POWER_REG       (0x17)
#define JSNS_REG        (0x01)

#define I2C_MAX_9867_WRITE_ADDR   (0x30)
#define I2C_MAX_9867_READ_ADDR    (0x31)

extern const uint8_t MAX_9867_INIT_REG[][3];
#endif  // MAX_9867

#ifdef MAX_98089
#define MAX_98089_INIT_LINES (sizeof(MAX_98089_INIT_REG)/sizeof(MAX_98089_INIT_REG[0]))
#define INIT_LINES  MAX_98089_INIT_LINES

#define VOLUME_VALS     (10)
#define VOLUME_REG      (0x39)
#define POWER_REG       (0x51)
#define JSNS_REG        (0x02)
#define DAI1_IO_REG     (0x16)
#define DAI2_IO_REG     (0x1E)

// �������� �����������
#define BAND_1_START_REG (0x84)
#define BAND_2_START_REG (0x8E)
#define BAND_3_START_REG (0x98)
#define BAND_4_START_REG (0xA2)
#define BAND_5_START_REG (0xAC)

#define I2C_MAX_98089_WRITE_ADDR  (0x20)
#define I2C_MAX_98089_READ_ADDR   (0x21)

extern const uint8_t MAX_98089_INIT_REG[][3];
#endif //MAX_98089

typedef enum
{
  P12 = 0,
  P11,
  P10,
  P9,
  P8,
  P7,
  P6,
  P5,
  P4,
  P3,
  P2,
  P1,
  ZERO,
  M1,
  M2,
  M3,
  M4,
  M5,
  M6,
  M7,
  M8,
  M9,
  M10,
  M11,
  M12,
  DBI_DISCRETE_STEPS  
} dBi_tone_e;

class max_audio : public twi, i2s
{
public:    
                  max_audio(uint32_t sda_pin, uint32_t scl_pin);

           void   init();
           void   init_LR();
		   void   init_main();
           void   initPhantom();
           void   initGarniture();
           void   listenAnalog();   // ��������� ����� ��� ������ ���� �� ������ � ��������� ������
           void   listenRadio();    // ��������� ����� ��� ������ ���� �� ������ � �����-�������
           void   selectFloor();    // ��������� ����������� ���� �� ������ �� ������ floor
           void   selectCommon();   // ��������� ����������� ���� �� ������ �� ������ common
           void   selectOut1();     // ��������� ����������� ���� �� ������ �� ������� Out1
           void   selectOut2();     // ��������� ����������� ���� �� ������ �� ������ Out2
           void   selectAnalogInput(interpreter_sts * ptrIntrprtr);     // �������� ��� ��� ���� ���� � ����������� � ���������� �����������
           void   selectAnalogOutput(interpreter_sts * ptrIntrprtr);    // �������� ��� ��� ���� ����� � ����������� � ���������� �����������

        uint8_t   read_reg(uint8_t reg);
           void   write_reg(uint8_t reg, uint8_t val);

            int   get_volume_index();
        uint8_t   get_volume();
           void   set_volume(uint8_t indx);
           void   set_high_tone(dBi_tone_e tone);
           void   set_low_tone (dBi_tone_e tone);
           void   set_mute(bool mute);
           void   set_mic(bool on, bool filter);
           void   shutdown(void);
           bool   turn_on(void);
           
           bool   enable_dai_sdout(uint8_t addr);
           bool   disable_dai_sdout(uint8_t addr);
           bool   enable_dai_sdin(uint8_t addr);
           bool   disable_dai_sdin(uint8_t addr);

        uint8_t   get_shdn();
        uint8_t   get_status();
		    uint8_t   get_jack_sense();
           void   set_gain(uint8_t gain, bool integrated_mic);
       e_gstate   volume_up(bool is_power_down);
       e_gstate   volume_down(bool is_power_down);
           void   volume_default();

           void   is_max_reset(); 
           bool   is_twi_busy();
           
           void   free_tx_buffers();
           void   sync_receiving();
                    
           void   i2s_irq(); 
           void   soft_irq(); 

           bool   snd_rx;   // ����, ��� �������� ������ ������� � ������ ��� ���������������.
           
          using   i2s::pause;     // ����� ��� ������ � ���� �� ����� ������.
          using   i2s::i2s_paused;     // ����� ��� ������ � ���� �� ����� ������. 
          using   i2s::i2s_busy;     // ����� ��� ������ � ���� �� ����� ������. 
          using   i2s::resume;    // ����� ��� ������ � ���� �� ����� ������.
           
private:

          using   i2s::irq;       // ����� �� ���� ������� � ���� �� ����� ������.  

           int    _volume_index;
          bool    _max_reset;
};

// ��� ���������� ������ ������ ���������� ���������� �� ���� i2s � ���������� ����������, ���������
// �� ����������� �� ����, ��� ���������� ���������� ������ �� �������� ��� �����
#if defined (RECEIVER_LEFT) || defined (RECEIVER_RIGHT) || defined (TRANSMITTER_CH1)
extern  max_audio  max_audio_codec;
    
extern "C" void I2S_IRQHandler();
extern "C" void SWI0_EGU0_IRQHandler();
#endif // RECEIVER_LEFT || RECEIVER_RIGHT || TRANSMITTER_CH1


#endif // _MAXAUDIO_DRIVER_H_

