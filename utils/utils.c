#include "utils.h"

static unsigned long int _next = 1;

void seed_random(unsigned int seed)
{
  if (seed == 0)
  {
    uint32_t v[4];
    
    for (uint8_t i = 0; i < 4; i++)
    {
      NRF_RNG->EVENTS_VALRDY = 0;
      NRF_RNG->TASKS_START = 1;
      while (NRF_RNG->EVENTS_VALRDY == 0);
      v[i] = NRF_RNG->VALUE;
    }
    
    NRF_RNG->TASKS_STOP = 1;
    
    _next = (v[0] << 24) | (v[1] << 16) | (v[2] << 8) | v[3];
  }
  else
    _next = seed;
}

int random(void) // RAND_MAX assumed to be 32767
{
  _next = _next * 1103515245 + 12345;
  return (unsigned int)(_next/65536) % 32768;
}

int rnd_max(int max)
{
  return (max*random()) / 32767;
}

uint16_t crc16_fill( const uint8_t *pBuf, uint32_t uiLength, uint16_t fill )
{
    register uint8_t Lo, Hi, ucSym;
 
    if (!uiLength){
        return 1;
    }
   
    Lo = fill & 0xFF;
    Hi = (fill & 0xFF00) >> 8;
 
    do {
        ucSym = *(pBuf++);
        ucSym ^= Hi;
          
        Hi = ( ucSym & 0x02 ) ? (Lo - 0x80) : Lo;
          
        if ( ucSym & 0x01 )
            Hi ^= 0xC0;
          
        Lo = ucSym;
        Lo >>= 1;
        Lo ^= ucSym;
        Lo >>= 1;
        ucSym ^= Lo;
          
        if ( ucSym & 0x08 )
            --ucSym;
          
        if ( ucSym & 0x40 )
            --ucSym;
          
        ucSym &= 0x01;
  
        if ( ucSym )
            Lo ^= 0xC0;
  
        Hi ^= ucSym;
    } while ( --uiLength );
  
    return (uint16_t)((((uint16_t)Hi)<<8) | Lo);
}

uint16_t crc16( const uint8_t *pBuf, uint32_t uiLength )
{
    return crc16_fill(pBuf, uiLength, 0xFFFF);
}

volatile uint32_t* pincfg_reg(uint32_t pin)
{
  	NRF_GPIO_Type * port = nrf_gpio_pin_port_decode(&pin);

  	return &port->PIN_CNF[pin];
}