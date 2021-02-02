#include "include.h"
#include "i2c.h"

static volatile uint32_t* pincfg_reg(uint32_t pin)
{
  	NRF_GPIO_Type * port = nrf_gpio_pin_port_decode(&pin);

  	return &port->PIN_CNF[pin];
}

i2c::i2c() 
{
    // конструктор по умолчанию пустой, но он нужен
    // потому что сюда заходит каждый раз при создании объекта при наследовании
}

i2c::i2c(uint32_t sda_pin, uint32_t scl_pin, uint8_t i2c_num) 
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
#if defined(NRF52)
           _TWIM = NRF_TWIM0;
           _TWIS = NRF_TWIS0;
           _IRQn = SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn;
#else
           _TWI = NRF_TWI0;
#endif
            break;
        case 1:
#if defined(NRF52)
           _TWIM = NRF_TWIM1;
           _TWIS = NRF_TWIS1;
           _IRQn = SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn;
#else
           _TWI = NRF_TWI1;
#endif
            break;
        default:
#if defined(NRF52)
           _TWIM = NULL;
           _TWIS = NULL;
#else
           _TWI = NULL;
#endif
            break;
    }

    _bus_busy = false;

 }	

#if defined(NRF52)
 // this initialization for master mode twi
void i2c::init_master(uint32_t freq)
{
    _is_master = true;

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

    _TWIM->PSEL.SCL = _clck_pin;
    _TWIM->PSEL.SDA = _sda_pin;  
    nrf_drv_common_irq_enable(_IRQn,TWI_INT_PRIORITY);

    enable();    
}

// this initialization for slave mode twi
void i2c::init_slave(uint32_t address)
{
    _is_master = false; // если задаем адрес, то это уже не мастер а слейв.

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

    set_address(address);

    _TWIS->CONFIG = TWIS_CONFIG_ADDRESS0_Msk;   // слушаем адрес 0
    _TWIS->PSEL.SCL = _clck_pin;
    _TWIS->PSEL.SDA = _sda_pin;
    
    _TWIS->ORC = 0xff;
    
    _TWIS->INTENSET = TWIS_INTEN_STOPPED_Msk | TWIS_INTEN_ERROR_Msk | TWIS_INTEN_WRITE_Msk | TWIS_INTEN_READ_Msk;

    nrf_drv_common_irq_enable(_IRQn,TWI_INT_PRIORITY);

    enable();
}

#else

void i2c::init(uint32_t freq)
{
    _is_master = true;

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
void i2c::init(uint32_t address, uint32_t freq)
{
    _is_master = false; // если задаем адрес, то это уже не мастер а слейв.

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
   
    set_address();

    enable();
}
#endif // NRF52

void i2c::set_clock(uint32_t freq)
{
    uint32_t result_frequency;

  	if (_is_master) // задавать частоту шины может только мастер.
  	{
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
#if defined(NRF52)
        _TWIM->FREQUENCY = result_frequency;
#else
        _TWI->FREQUENCY = result_frequency;
#endif
        enable();
  	}
}

void i2c::set_address(uint32_t address)
{
    if(address <= 127)
#if defined(NRF52)
    _TWIS->ADDRESS[0] = address;
#else
    _TWI->ADDRESS = address >> 1;   // почему то надо сдвигать адрес, какая то аппаратная фигня, так и не понял.
#endif
}

void i2c::enable()
{
#if defined(NRF52)
    _TWIM->ENABLE = (TWIM_ENABLE_ENABLE_Enabled << TWIM_ENABLE_ENABLE_Pos);
#else
    _TWI->ENABLE = (TWI_ENABLE_ENABLE_Enabled << TWI_ENABLE_ENABLE_Pos);
#endif
}

void i2c::disable()
{
#if defined(NRF52)
        _TWIM->ENABLE = (TWIM_ENABLE_ENABLE_Disabled << TWIM_ENABLE_ENABLE_Pos);
#else
        _TWI->ENABLE = (TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos);
#endif
}

#if defined(NRF52)
uint8_t i2c::request_from(uint8_t address, size_t len, bool stop_bit)
{
    if(len == 0) { return 0; }

    size_t bytes_read = 0;
    _rx_buffer.reset_to_zero();
    
    _TWIM->ADDRESS = address;
    
    _TWIM->TASKS_RESUME = 0x1UL;
    _TWIM->RXD.PTR = (uint32_t)_rx_buffer.get_buf_pointer();
    _TWIM->RXD.MAXCNT = len;
    _TWIM->TASKS_STARTRX = 0x1UL;
    
    while(!_TWIM->EVENTS_RXSTARTED && !_TWIM->EVENTS_ERROR);
        _TWIM->EVENTS_RXSTARTED = 0x0UL;
    
    while(!_TWIM->EVENTS_LASTRX && !_TWIM->EVENTS_ERROR);
        _TWIM->EVENTS_LASTRX = 0x0UL;
    
    if (stop_bit || _TWIM->EVENTS_ERROR)
    {
        _TWIM->TASKS_STOP = 0x1UL;

        while(!_TWIM->EVENTS_STOPPED);
            _TWIM->EVENTS_STOPPED = 0x0UL;
    }
    else
    {
        _TWIM->TASKS_SUSPEND = 0x1UL;

        while(!_TWIM->EVENTS_SUSPENDED);
            _TWIM->EVENTS_SUSPENDED = 0x0UL;
    }
    
    if (_TWIM->EVENTS_ERROR) { _TWIM->EVENTS_ERROR = 0x0UL; }
    
    //bytes_read = _rx_buffer._iHead = _TWIM->RXD.AMOUNT;
    bytes_read = _rx_buffer.get_avail();
    
    return bytes_read;
}

uint8_t i2c::request_from(uint8_t address, size_t len)
{
    return request_from(address, len, true);
}

void i2c::start_transmission(uint8_t address)
{
      // save address of target and clear buffer
    _tx_address = address;
    _tx_buffer.reset_to_zero();
    
    _bus_busy = true;
}

// Errors:
//  0 : Success
//  1 : Data too long
//  2 : NACK on transmit of address
//  3 : NACK on transmit of data
//  4 : Other error
uint8_t i2c::end_transmission(bool stop_bit)
{
    _bus_busy = false ;

    // Start I2C transmission
    _TWIM->ADDRESS = _tx_address;
    
    _TWIM->TASKS_RESUME = 0x1UL;
    
    _TWIM->TXD.PTR = (uint32_t)_tx_buffer.get_buf_pointer();
    _TWIM->TXD.MAXCNT = _tx_buffer.get_avail();
    
    _TWIM->TASKS_STARTTX = 0x1UL;
    
    while(!_TWIM->EVENTS_TXSTARTED && !_TWIM->EVENTS_ERROR);
        _TWIM->EVENTS_TXSTARTED = 0x0UL;
    
    if (_tx_buffer.get_avail()) 
    {
        while(!_TWIM->EVENTS_LASTTX && !_TWIM->EVENTS_ERROR);
    }

    _TWIM->EVENTS_LASTTX = 0x0UL;
    
    if (stop_bit || _TWIM->EVENTS_ERROR)
    {
      _TWIM->TASKS_STOP = 0x1UL;

      while(!_TWIM->EVENTS_STOPPED);
      _TWIM->EVENTS_STOPPED = 0x0UL;
    }
    else
    {
        _TWIM->TASKS_SUSPEND = 0x1UL;

        while(!_TWIM->EVENTS_SUSPENDED);
            _TWIM->EVENTS_SUSPENDED = 0x0UL;
    }
    
    if (_TWIM->EVENTS_ERROR)
    {
        _TWIM->EVENTS_ERROR = 0x0UL;
      
        uint32_t error = _TWIM->ERRORSRC;
      
        _TWIM->ERRORSRC = error;
      
        if (error == TWIM_ERRORSRC_ANACK_Msk)
        {
            return 2;
        }
        else if (error == TWIM_ERRORSRC_DNACK_Msk)
        {
            return 3;
        }
        else
        {
            return 4;
        }
    }
    
    return 0;
}

uint8_t i2c::end_transmission()
{
    return end_transmission(true);
}

size_t i2c::write(char data_char)
{
    // No writing, without begun transmission or a full buffer
    if ( !_bus_busy || _tx_buffer.is_full() )
    {
          return 0 ;
    }
    
    _tx_buffer.add_one(&data_char) ;
    
    return 1 ;
}

size_t i2c::write(const uint8_t *data, size_t len)
{
    //Try to store all data
    for(size_t i = 0; i < len; ++i)
    {
      //Return the number of data stored, when the buffer is full (if write return 0)
      if(!write(data[i]))
          return i;
    }
    
    //All data stored
    return len;
}

void i2c::on_irq(void)
{
    static bool receiving = false;
    uint32_t error;

    if (_TWIS->EVENTS_WRITE)
    {
        _TWIS->EVENTS_WRITE = 0x0UL;
        
        receiving = true;
        
        _rx_buffer.reset_to_zero();
        
        _TWIS->RXD.PTR = (uint32_t)_rx_buffer.get_buf_pointer();
        _TWIS->RXD.MAXCNT = _rx_buffer.get_size();
        
        _TWIS->TASKS_PREPARERX = 0x1UL;
    }
    
    if (_TWIS->EVENTS_READ)
    {
        _TWIS->EVENTS_READ = 0x0UL;
        
        receiving = false;
        _bus_busy = true;
        
        _tx_buffer.reset_to_zero();
        
        if (on_request_callback)
        {
            on_request_callback();
        }
        
        _bus_busy = false;
        
        _TWIS->TXD.PTR = (uint32_t)_tx_buffer.get_buf_pointer();
        _TWIS->TXD.MAXCNT = _tx_buffer.get_avail();
        
        _TWIS->TASKS_PREPARETX = 0x1UL;
    }
    
    if (_TWIS->EVENTS_STOPPED)
    {
        _TWIS->EVENTS_STOPPED = 0x0UL;
        
        if (receiving)
        {
            int rx_amount = _TWIS->RXD.AMOUNT;
            
            _rx_buffer._iHead = rx_amount;
            
            if (on_receive_callback)
            {
                on_receive_callback(rx_amount);
            }
        }
    }
    
    if (_TWIS->EVENTS_ERROR)
    {
        _TWIS->EVENTS_ERROR = 0x0UL;
        
        error = _TWIS->ERRORSRC;

        _TWIS->ERRORSRC = error;
        
        _TWIS->TASKS_STOP = 0x1UL;
    }
}

#else
bool i2c::write(uint8_t *buf, uint16_t len, bool stop_bit)
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

bool i2c::read(uint8_t *buf, uint16_t len)
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
#endif // NRF52

bool i2c::is_busy()
{
    return _bus_busy;
}
