#include "include.h"
#include "twims.h"

twims::twims(uint32_t sda_pin, uint32_t scl_pin, uint8_t i2c_num) 
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

           _TWIM = NRF_TWIM0;
           _TWIS = NRF_TWIS0;
           _IRQn = SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn;
            break;
        case 1:
           _TWIM = NRF_TWIM1;
           _TWIS = NRF_TWIS1;
           _IRQn = SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn;
            break;
        default:
           _TWIM = NULL;
           _TWIS = NULL;
            break;
    }

    _bus_busy = false;
 }	

// this initialization for master mode twi
void twims::init_master(uint32_t freq)
{
    _is_master = true;

    //nrf_gpio_cfg_output(_clck_pin);
    //nrf_gpio_cfg_output(_sda_pin);
    //
    //nrf_gpio_pin_clear(_clck_pin);
    //nrf_gpio_pin_set  (_clck_pin);
    //nrf_gpio_pin_clear(_clck_pin);
    //
    //nrf_gpio_pin_clear(_sda_pin);
    //nrf_gpio_pin_set  (_sda_pin);
    //nrf_gpio_pin_clear(_sda_pin);

    *pincfg_reg(_clck_pin) = SCL_PIN_INIT_CONF;
    *pincfg_reg(_sda_pin)  = SDA_PIN_INIT_CONF;  

    set_clock(freq); 

    _TWIM->PSEL.SCL = _clck_pin;
    _TWIM->PSEL.SDA = _sda_pin;  
    nrf_drv_common_irq_enable(_IRQn,TWI_INT_PRIORITY);

    enable();    
}

// this initialization for slave mode twi
void twims::init_slave(uint32_t address)
{
    _is_master = false; // если задаем адрес, то это уже не мастер а слейв.

    //nrf_gpio_cfg_output(_clck_pin);
    //nrf_gpio_cfg_output(_sda_pin);
    //
    //nrf_gpio_pin_clear(_clck_pin);
    //nrf_gpio_pin_set  (_clck_pin);
    //nrf_gpio_pin_clear(_clck_pin);
    //
    //nrf_gpio_pin_clear(_sda_pin);
    //nrf_gpio_pin_set  (_sda_pin);
    //nrf_gpio_pin_clear(_sda_pin);

    *pincfg_reg(_clck_pin) = SCL_PIN_INIT_CONF;
    *pincfg_reg(_sda_pin)  = SDA_PIN_INIT_CONF;

    set_address(address);
    
    _TWIS->PSEL.SCL = _clck_pin;
    _TWIS->PSEL.SDA = _sda_pin;
    
    _TWIS->ORC = 0xff;
    
    _TWIS->INTENSET = TWIS_INTEN_STOPPED_Msk | TWIS_INTEN_ERROR_Msk | TWIS_INTEN_WRITE_Msk | TWIS_INTEN_READ_Msk;

    nrf_drv_common_irq_enable(_IRQn,TWI_INT_PRIORITY);

    enable();
}

void twims::set_clock(uint32_t freq)
{
    uint32_t result_frequency;

  	if (_is_master) // задавать частоту шины может только мастер.
  	{
        disable();

		if (freq > 0)
		{
			if(freq < 200 )
				result_frequency = TWIM_FREQUENCY_FREQUENCY_K100 << TWIM_FREQUENCY_FREQUENCY_Pos;
			else 
			if(freq < 400)
				result_frequency = TWIM_FREQUENCY_FREQUENCY_K250 << TWIM_FREQUENCY_FREQUENCY_Pos;
			else
				result_frequency = TWIM_FREQUENCY_FREQUENCY_K400 << TWIM_FREQUENCY_FREQUENCY_Pos;
		}

        _TWIM->FREQUENCY = result_frequency;

        enable();
  	}
}

void twims::set_address(uint32_t address)
{
    if(address <= 127)
    _TWIS->ADDRESS[0] = address;
    
    _TWIS->CONFIG = TWIS_CONFIG_ADDRESS0_Msk;   // слушаем адрес 0
}

void twims::enable()
{
  if(_is_master)
    _TWIM->ENABLE = (TWIM_ENABLE_ENABLE_Enabled << TWIM_ENABLE_ENABLE_Pos);
  else
    _TWIS->ENABLE = (TWIS_ENABLE_ENABLE_Enabled << TWIS_ENABLE_ENABLE_Pos);
}

void twims::disable()
{
    _TWIM->ENABLE = (TWIM_ENABLE_ENABLE_Disabled << TWIM_ENABLE_ENABLE_Pos);
}

uint8_t twims::request_from(uint8_t address, size_t len, bool stop_bit)
{
  	uint32_t waitTmr {32000};
  
    if(len == 0) { return 0; }

    uint32_t bytes_read = 0;
    
    _rx_buffer.reset_to_zero();
    
    _TWIM->ADDRESS = address;
    
    _TWIM->TASKS_RESUME = 0x1UL;
    _TWIM->RXD.PTR = (uint32_t)_rx_buffer.get_buf_pointer();
    _TWIM->RXD.MAXCNT = len;
    _TWIM->TASKS_STARTRX = 0x1UL;
    
    while(!_TWIM->EVENTS_RXSTARTED && !_TWIM->EVENTS_ERROR);
        _TWIM->EVENTS_RXSTARTED = 0x0UL;
    
    while(!_TWIM->EVENTS_LASTRX && 
		  !_TWIM->EVENTS_ERROR && 
		  (waitTmr--) > 0);
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
    
    bytes_read = _TWIM->RXD.AMOUNT;
    _rx_buffer.set_head(bytes_read);
    
    return bytes_read;
}

uint8_t twims::request_from(uint8_t address, size_t len)
{
    return request_from(address, len, true);
}

void twims::start_transmission(uint8_t address)
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
uint8_t twims::end_transmission(bool stop_bit)
{
    _bus_busy = false ;

    // Start twims transmission
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

uint8_t twims::end_transmission()
{
    return end_transmission(true);
}

size_t twims::write(char data_char)
{
    // No writing, without begun transmission or a full buffer
    if ( !_bus_busy || _tx_buffer.is_full() )
    {
          return 0 ;
    }
    
    _tx_buffer.add_one(data_char) ;
    
    return 1 ;
}

size_t twims::write(const char *data, size_t len)
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

void twims::on_irq(void)
{
    static bool receiving = false;
    uint32_t error;
    uint32_t rx_amount;

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
            rx_amount = _TWIS->RXD.AMOUNT;
            
            _rx_buffer.set_head(rx_amount);
            
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

bool twims::is_busy()
{
    return _bus_busy;
}

twims i2c_main(I2C_MAIN_SDA, I2C_MAIN_SCL, TWIMS_MODULE_NUM);

#if   TWIMS_MODULE_NUM == 0
void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void) { i2c_main.on_irq(); }
#elif TWIMS_MODULE_NUM == 1
void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler(void) { i2c_main.on_irq(); }
#endif



