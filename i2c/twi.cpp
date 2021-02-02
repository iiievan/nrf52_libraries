#include "include.h"
#include "twi.h"

twi::twi() 
{
    // конструктор по умолчанию пустой, но он нужен
    // потому что сюда заходит каждый раз при создании объекта при наследовании
}

twi::twi(uint32_t sda_pin, uint32_t scl_pin, uint8_t i2c_num) 
{       
	if(sda_pin != PIN_DISCONNECTED &&
	   scl_pin != PIN_DISCONNECTED)
	{
		_sda_pin = sda_pin;
		_clck_pin = scl_pin;
	}
	else
	{
		_sda_pin = PIN_DISCONNECTED;
		_clck_pin = PIN_DISCONNECTED;
	} 

    switch(i2c_num)
    {
        case 0:
            _TWI = NRF_TWI0;
            break;
        case 1:
            _TWI = NRF_TWI1;
            break;
        default:
            _TWI = NULL;
            break;
    }

    _bus_busy = false;
 }	

void twi::init(uint32_t freq)
{
    nrf_gpio_cfg_output(_clck_pin);
    nrf_gpio_cfg_output(_sda_pin);
    
    nrf_gpio_pin_clear(_clck_pin);
    nrf_gpio_pin_set  (_clck_pin);
    nrf_gpio_pin_clear(_clck_pin);
    
    nrf_gpio_pin_clear(_sda_pin);
    nrf_gpio_pin_set  (_sda_pin);
    nrf_gpio_pin_clear(_sda_pin);

    *pincfg_reg(_clck_pin) = SCL_PIN_INIT_CONF;
    *pincfg_reg(_sda_pin)  = SDA_PIN_INIT_CONF;  

    set_clock(freq);    

    _TWI->PSELSCL = _clck_pin;
    _TWI->PSELSDA = _sda_pin;  

    enable();    
}

// this initialization for master mode twi without interrupt
void twi::init(uint32_t address, uint32_t freq)
{
    nrf_gpio_cfg_output(_clck_pin);
    nrf_gpio_cfg_output(_sda_pin);
    
    nrf_gpio_pin_clear(_clck_pin);
    nrf_gpio_pin_set  (_clck_pin);
    nrf_gpio_pin_clear(_clck_pin);
    
    nrf_gpio_pin_clear(_sda_pin);
    nrf_gpio_pin_set  (_sda_pin);
    nrf_gpio_pin_clear(_sda_pin);

    *pincfg_reg(_clck_pin) = SCL_PIN_INIT_CONF;
    *pincfg_reg(_sda_pin)  = SDA_PIN_INIT_CONF;

    set_clock(freq);

    _TWI->PSELSCL = _clck_pin;
    _TWI->PSELSDA = _sda_pin;    
   
    set_address(address);

    enable();
}

void twi::set_clock(uint32_t freq)
{
    uint32_t result_frequency;

    disable();

	if (freq > 0)
	{
		if(freq < 200 )
			result_frequency = TWI_FREQUENCY_FREQUENCY_K100 << TWI_FREQUENCY_FREQUENCY_Pos;
		else 
		if(freq < 400)
			result_frequency = TWI_FREQUENCY_FREQUENCY_K250 << TWI_FREQUENCY_FREQUENCY_Pos;
		else
			result_frequency = TWI_FREQUENCY_FREQUENCY_K400 << TWI_FREQUENCY_FREQUENCY_Pos;
	}

    _TWI->FREQUENCY = result_frequency;

    enable();

}

void twi::set_address(uint32_t address)
{
    if(address <= 127)
    _TWI->ADDRESS = address >> 1;   // почему то надо сдвигать адрес, какая то аппаратная фигня, так и не понял.
}

void twi::enable()
{
    _TWI->ENABLE = (TWI_ENABLE_ENABLE_Enabled << TWI_ENABLE_ENABLE_Pos);
}

void twi::disable()
{
    _TWI->ENABLE = (TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos);

}

bool twi::write(uint8_t *buf, uint16_t len, bool stop_bit)
{
 	uint32_t cnt = 2000;

    _bus_busy = true;

  	_TWI->EVENTS_TXDSENT = 0;

  	for (u8 i = 0; i < len; i++)
  	{
  	  	_TWI->TXD = buf[i];

  	  	if (i == 0)
  	  		_TWI->TASKS_STARTTX = 1;

  	  	while (_TWI->EVENTS_TXDSENT == 0 && cnt)
  	  	{
  	  	  	if (cnt)
  	  	        cnt--;
  	  	}

  	  	_TWI->EVENTS_TXDSENT = 0;
  	}

  	if (stop_bit)
    	_TWI->TASKS_STOP = 1;
  
    _bus_busy = false;

  	if (cnt == 0)
    	return true;
    else
    	return false;
}

bool twi::read(uint8_t *buf, uint16_t len)
{
	uint32_t cnt = 2000;

    _bus_busy = true;
 
 	_TWI->EVENTS_RXDREADY = 0;
 	_TWI->SHORTS = TWI_SHORTS_BB_STOP_Msk;
 	_TWI->EVENTS_BB = 0;
 	_TWI->EVENTS_STOPPED = 0;
 	_TWI->TASKS_STARTRX = 1;

 	while (NRF_TWI0->EVENTS_RXDREADY == 0 && cnt)
 	{
 	  	if (cnt)
 	    	cnt--;
 	}

 	buf[0] = (uint8_t)_TWI->RXD;

 	_TWI->SHORTS = 0;
 	_TWI->EVENTS_BB = 0;
 	_TWI->TASKS_STOP = 1;
 	
    _bus_busy = false;

 	if (cnt == 0)
   		return true;
    else
   		return false;

}

bool twi::is_busy()
{
    return _bus_busy;
}
