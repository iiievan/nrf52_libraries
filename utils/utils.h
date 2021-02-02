#ifndef _UTILS_H
#define _UTILS_H

#include "nrf.h"
#include "nrf_gpio.h"

#ifdef _cplusplus
extern "C" {
#endif
  
#define MY_RAND_MAX        (32767)
#define MY_RAND_MIN        (-32768)
  
#define M_PI 			   (3.141592653589f)
  
#define ASSERT(expr)                                                          \
if (expr)                                                                     \
{                                                                             \
}                                                                             \
else                                                                          \
{                                                                             \
    while (1);                                                                \
}

#define countof(a)              (sizeof(a) / sizeof(*(a)))

#define hi_z(pin)															\
nrf_gpio_cfg(pin,															\
             NRF_GPIO_PIN_DIR_INPUT,										\
             NRF_GPIO_PIN_INPUT_DISCONNECT,									\
             NRF_GPIO_PIN_NOPULL,											\
             NRF_GPIO_PIN_S0S1,												\
             NRF_GPIO_PIN_NOSENSE);											\

               
#ifdef __cplusplus
#define UNUSED(x)  (x = x)
#else
#define UNUSED(x)  ((void)(x))
#endif  //__cplusplus
               
#define BIT(bit)           (1UL   <<     (bit))
#define SETBIT(val, bit)   ((val) |=  BIT(bit))
#define CLRBIT(val, bit)   ((val) &= ~BIT(bit))
#define XORBIT(val, bit)   ((val) ^=  BIT(bit))
#define TSTBIT(val, bit)   ((val)  &  BIT(bit))
               
extern  int random(void); // RAND_MAX assumed to be 32767
extern  int rnd_max(int max);
extern void seed_random(unsigned int seed);
extern uint16_t crc16_fill(const uint8_t *pBuf, uint32_t uiLength, uint16_t fill);
extern uint16_t crc16(const uint8_t *pBuf, uint32_t uiLength);
extern volatile uint32_t* pincfg_reg(uint32_t pin);

#ifdef _cplusplus
}
#endif

#endif // _UTILS_H