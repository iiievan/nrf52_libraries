#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include "nrf.h"
#include "nrf_gpio.h"

#ifdef _cplusplus
extern "C" {
#endif

 #define ALLOCATION_CRITICAL_MIN     ((uint32_t)0x100)
#define HEAP_BEGIN                  ((uint32_t)0x2003BFE0)
#define HEAP_SIZE                   ((uint32_t)0x2000)
#define HEAP_COLOR                  ((int)0x55)
#define STACK_BEGIN                 (HEAP_BEGIN + HEAP_SIZE)
#define STACK_SIZE                  ((uint32_t)0x2000)
#define STACK_COLOR                 ((int)0xAA)

  
#define MY_RAND_MAX     (32767)
#define MY_RAND_MIN     (-32768)
  
#define M_PI 			(3.141592653589f)
  
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
               

#define WATCHDOGRESET (NRF_WDT->RR[0] = 0x6E524635)
               
extern  int random(void); // RAND_MAX assumed to be 32767
extern  int rnd_max(int max);
extern void seed_random(unsigned int seed);
extern uint16_t crc16_fill(const uint8_t *pBuf, uint32_t uiLength, uint16_t fill);
extern uint16_t crc16(const uint8_t *pBuf, uint32_t uiLength);
extern volatile uint32_t* pincfg_reg(uint32_t pin);
void* memFill(void *s, int c, size_t len);
extern void colorUp_stack_heap();
extern uint32_t stack_avail();
extern uint32_t heap_avail();
extern long GetBiggestMalloc();
extern long GetBiggestNew();

#ifdef _cplusplus
}
#endif

#endif // _UTILS_H