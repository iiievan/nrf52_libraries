#ifndef __AUDIOGUIDE_V2_BOARD_H
#define __AUDIOGUIDE_V2_BOARD_H

//forward declaration for board
class ledDriver;

#include "utils.h"

#define PORT_0                  (0)
#define PORT_1                  BIT(5)

#ifndef PIN_DISCONNECTED
#define PIN_DISCONNECTED        (0xFFFFFFFFUL)    // Define that pin is disconnected from hardware
#endif

#define I2S_MCK_PIN             (PORT_0 | 18)  // P0.18 MAX_MCLK
#define I2S_LRCK_PIN            (PORT_0 | 20)  // P0.20 I2S_LRCLK
#define I2S_SCK_PIN             (PORT_0 | 17)  // P0.17 I2S_CLK
#define I2S_SDIN_PIN            (PORT_0 | 22)  // P0. I2S_SDIN
#define I2S_SDOUT_PIN           (PORT_0 | 19)  // P0. I2S_SDOUT
        
#define I2C_CLCK_PIN            (PORT_0 | 16)  // P0.16
#define I2C_SDA_PIN             (PORT_0 | 15)  // P0.15
        
#define RF_MODE_PIN             (PORT_1 | 6)   // P0.06
//#define RF_SWANT_PIN          (PORT_XX | x)  // pulled up to +3.0V
#define RF_RX_EN_PIN            (PORT_0 | 9)   // P0.09
#define RF_TX_EN_PIN            (PORT_0 | 10)  // P0.10
#define RF_PDET_PIN             (PORT_0 | 2)   // P0.02                                     // AIN0

#define MAIN_MEAS_PIN           (PORT_0 | 28)  // P0.28 MAIN_MEAS_PIN                       // AIN4
#define VBAT_MEAS_PIN           (PORT_0 | 29)  // P0.29 VBAT_MEAS                           // AIN5  
#define CHRG_EN_PIN             (PORT_0 | 3)   // P0.03 CHPRG/PWKEY
#define RF_POWER_ENABLE         (PORT_1 | 14)  // P1.14 3V0_RF_EN
#define MODULE_PWR              (PORT_1 | 8)   // P1.08 GSM and GPS power enable
#define JACK_5_PIN              (PORT_0 | 30)  // P0.30                                     // AIN6
#define JACK_6_PIN              (PORT_0 | 31)  // P0.31                                     // AIN7
#define SYS_3V0_PIN             (PORT_1 | 7)   // P1.07

#define BUZZER                  (PORT_0 | 4)   // P0.04 BUZZER
#define VIBRO                   (PORT_1 | 12)  // P1.12 VIBRO

#define GPS_RX                  (PORT_0 | 12)  // P0.12 for NRF this is TX
#define GPS_TX                  (PORT_1 | 9)   // P1.09 for NRF this is RX
#define GPS_BAUDRATE            UART_BAUDRATE_BAUDRATE_Baud9600    // GPS BAUDRATE 9600
#define GSM_UART_RX             (PORT_0 | 13)  // P0.13
#define GSM_UART_TX             (PORT_0 | 14)  // P0.14

// matrix keypad definitions
#define BTN_ROW_1               (PORT_1 | 11)   // P1.11
#define BTN_ROW_2               (PORT_1 | 4)    // P1.04
#define BTN_ROW_3               (PORT_1 | 3)    // P1.03
#define BTN_ROW_4               (PORT_1 | 2)    // P1.02
#define BTN_ROW_5               (PORT_1 | 1)    // P1.01
#define BTN_ROW_6               (PORT_1 | 13)   // P1.13
                                                    
#define BTN_COL_1               (PORT_1 | 15)   // P1.15
#define BTN_COL_2               (PORT_1 | 10)   // P1.10
#define BTN_COL_3               (PORT_1 | 5)    // P1.05

// leds
#define THREE_PIN_CHARGE_BAR

#define LED_SYS_RED_PIN         (PORT_0 | 7)   // P0.07 LED_SYS_RED 
#define LED_SYS_GREEN_PIN       (PORT_0 | 5)   // P0.05 LED_SYS_GREEN 
#define LED_BL_BTN_PIN          (PORT_0 | 26)  // P0.26 LED_BL_BTN 
#define LED_BTN_PR_PIN          (PORT_0 | 11)  // P0.11 LED_BTN_PR  
#define LED_KB_PIN              (PORT_0 | 25)  // P0.25 LED_KB
#define LED_BAT_1_PIN           (PORT_0 | 8)   // P0.08 LED_BAT_1 
#define LED_BAT_2_PIN           (PORT_0 | 27)  // P0.27 LED_BAT_2 
#define LED_BAT_3_PIN           (PORT_0 | 6)   // P0.06 LED_BAT_3

enum 
{
    LED_SYS_RED = 0, 
    LED_SYS_GREEN ,
    LED_BL_BTN, 
    LED_BTN_PR,   
    LED_KB,
    LED_BAT_1,
    LED_BAT_2,
    LED_BAT_3,
    LEDS_NUM
};

enum 
{
    CHARGE_LED_1,
    CHARGE_LED_2,
    CHARGE_LED_3,
    CHARGE_LED_4,
    CHARGE_LED_5,
    CHARGE_LED_NUM,
    SHTDWN  = -1 
};

// LED_BAT_1..3 are included in the spice module due to lack of pins
// and managed separately in set_chrg_bar
// LED_BAT_2 is needed to indicate the critical discharge of the battery by blinking, therefore the charge_bar driver is installed for it.

extern ledDriver red_led;     
extern ledDriver green_led;   
extern ledDriver bl_btn_led; 
extern ledDriver btn_pr_led;  
extern ledDriver kb_led;
extern ledDriver bat_led_1; 
extern ledDriver bat_led_2;  // control first led in sequence
extern ledDriver bat_led_3;

extern ledDriver* led_list[];
extern uint32_t led_2_port_list[];

#endif //__AUDIOGUIDE_V2_BOARD_H