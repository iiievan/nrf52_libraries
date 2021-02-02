#ifndef __BOOT_TOOLS_H
#define __BOOT_TOOLS_H

//логический список светодиодов
#define RED_LED                 0
#define GREEN_LED               1
#define BAT_1_LED               2
#define BAT_2_LED               3
#define BAT_3_LED               4
#define BAT_4_LED               5
#define BAT_5_LED               6
#define BTN_LED                 7
#define LED_NUM                 8

#ifdef NRF52840_XXAA

#define PORT_0  0
#define PORT_1  BIT(5)

//номера пинов МК
#define LED_RED_PIN             (PORT_0 | 19)
#define LED_GREEN_PIN           (PORT_0 | 18)
#define BAT_LED_1_PIN           (PORT_0 | 26)   
#define BAT_LED_2_PIN           (PORT_0 | 4)
#define BAT_LED_3_PIN           (PORT_0 | 6)
//#define BAT_LED_4_PIN           (PORT_0 | 21)
//#define BAT_LED_5_PIN           (PORT_0 | 21)
#define BAT_LED_BTN_PIN         (PORT_0 | 7)

#define RF_MODE_PIN             (PORT_1 | 6)
//#define RF_SWANT_PIN            (PORT_0 | 21)
#define RF_RX_EN_PIN            (PORT_0 | 9)
#define RF_TX_EN_PIN            (PORT_0 | 10)
#define RF_PDET_PIN             (PORT_0 | 2)

#define CHRG_EN_PIN             (PORT_0 | 3)

//#define BUTTON_UP_PIN           (PORT_0 | 21)
//#define BUTTON_DOWN_PIN         (PORT_0 | 21)

#define RF_POWER_ENABLE         (PORT_1 | 14)

#endif

#ifdef NRF52832_XXAA

//номера пинов МК
#define LED_RED_PIN             21
#define LED_GREEN_PIN           20
#define BAT_LED_1_PIN           13   
#define BAT_LED_2_PIN           14
#define BAT_LED_3_PIN           15
#define BAT_LED_4_PIN           16
#define BAT_LED_5_PIN           17
#define BAT_LED_BTN_PIN         12

#define RF_MODE_PIN             22
#define RF_SWANT_PIN            25
#define RF_RX_EN_PIN            23
#define RF_TX_EN_PIN            24
#define RF_PDET_PIN             28

#define CHRG_EN_PIN             4

#define BUTTON_UP_PIN           26
#define BUTTON_DOWN_PIN         31

#define RF_POWER_ENABLE         27

#endif


typedef enum {
  CHRG_MAX_CURRENT,
  CHRG_MEDIUM_CURRENT,
  CHRG_MIN_CURRENT,
}ECHRG_TYPE;

#define LED_R_ON        nrf_gpio_cfg_input(LED_RED_PIN, NRF_GPIO_PIN_PULLUP)
#define LED_R_OFF       nrf_gpio_cfg_input(LED_RED_PIN, NRF_GPIO_PIN_PULLDOWN)
#define LED_G_ON        nrf_gpio_cfg_input(LED_GREEN_PIN, NRF_GPIO_PIN_PULLUP)
#define LED_G_OFF       nrf_gpio_cfg_input(LED_GREEN_PIN, NRF_GPIO_PIN_PULLDOWN)

extern void Delay100us(u32 Dly);
extern void Delay10us(u32 Dly);
extern void Delay1us(u32 Dly);

extern void RF_OFF();
extern void RF_RX();

extern u16 CRC16( const u8 *pBuf, u32 uiLength );
extern void InitGPIO(void);
extern void clock_initialization();
extern void nrf_drv_common_irq_enable(IRQn_Type IRQn, uint8_t priority);
extern void Reset();

#endif