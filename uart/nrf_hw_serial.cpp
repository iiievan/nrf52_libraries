#include "include.h"
#include "nrf_hw_serial.h"

nrf_hw_serial::nrf_hw_serial(uint32_t _transmit_pin, uint32_t _receive_pin)
{
    _rx_timer                  =  0;
    _tx_timer                  =  0;
    _amount_rx_bytes           =  0;
    _tx_busy                   = false; 

    nrf_gpio_pin_set(_transmit_pin);
    nrf_gpio_cfg_output(_transmit_pin);  //  for NRF this is TX 
    NRF_UARTE0->PSEL.TXD = _transmit_pin;   
    
    nrf_gpio_cfg_input(_receive_pin, NRF_GPIO_PIN_NOPULL);   // For for NRF this is RX
    NRF_UARTE0->PSEL.RXD = _receive_pin;
  
    NRF_UARTE0->PSEL.RTS = PIN_DISCONNECTED;
    NRF_UARTE0->PSEL.CTS = PIN_DISCONNECTED;
    
    update_rx_timer();
    update_tx_timer();
 }

int8_t nrf_hw_serial::init(uint32_t baudrate, uint32_t _pwr_en_pin)
{    
    NRF_UARTE0->CONFIG  = 0; 

    // config power enable output for uart communication module if presented.
    if (_pwr_en_pin != PIN_DISCONNECTED)
    {
        nrf_gpio_cfg_output(_pwr_en_pin);
        nrf_gpio_pin_clear(_pwr_en_pin);
        
        // включаем сам модуль.
        nrf_gpio_pin_set(_pwr_en_pin);
    }

    NRF_UARTE0->CONFIG  = (UARTE_CONFIG_HWFC_Disabled << UARTE_CONFIG_HWFC_Pos);

    switch (baudrate) {
        case 1200:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud1200;
            break;
        case 2400:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud2400;
            break;
        case 4800:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud4800;
            break;
        case 9600:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud9600;
            break;
        case 14400:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud14400;
            break;
        case 19200:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud19200;
            break;
        case 28800:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud28800;
            break;
        case 38400:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud38400;
            break;
        case 57600:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud57600;
            break;
        case 76800:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud76800;
            break;
        case 115200:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud115200;
            break;
        case 230400:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud230400;
            break;
        case 250000:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud250000;
            break;
        case 460800:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud460800;
            break;
        case 921600:
            NRF_UARTE0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud921600;
            break;
        default:
            return UART_NOBAUD;
    }
    
    NRF_UARTE0->ENABLE = UARTE_ENABLE_ENABLE_Enabled;
    
    NRF_UARTE0->TXD.PTR = (uint32_t)_tx_chunk;
    NRF_UARTE0->TXD.MAXCNT = tx_data.get_avail();
    NRF_UARTE0->EVENTS_ENDTX  = 0;
    NRF_UARTE0->TASKS_STARTTX = 0;
    
    NRF_UARTE0->RXD.MAXCNT = RX_CHUNK_SIZE;
    NRF_UARTE0->RXD.PTR = (uint32_t)_rx_chunk;
    NRF_UARTE0->INTENCLR = 0xFFFFFFFF;
    NRF_UARTE0->INTEN = (UARTE_INTEN_RXDRDY_Enabled << UARTE_INTEN_RXDRDY_Pos) | 
                        (UARTE_INTEN_TXDRDY_Enabled << UARTE_INTEN_RXDRDY_Pos) | 
                        (UARTE_INTEN_CTS_Disabled   << UARTE_INTEN_CTS_Pos) | 
                        (UARTE_INTEN_ENDRX_Enabled  << UARTE_INTEN_ENDRX_Pos);
    
    NRF_UARTE0->INTENSET = (UARTE_INTENSET_ENDRX_Enabled  << UARTE_INTENSET_ENDRX_Pos) |
                           (UARTE_INTENSET_ENDTX_Enabled  << UARTE_INTENSET_ENDTX_Pos) |
                           (UARTE_INTENSET_TXDRDY_Enabled << UARTE_INTENSET_TXDRDY_Pos);
    
    //NRF_UARTE0->SHORTS = UARTE_SHORTS_ENDRX_STARTRX_Enabled << UARTE_SHORTS_ENDRX_STARTRX_Pos;
    
    NRF_UARTE0->EVENTS_RXSTARTED = 0;
    NRF_UARTE0->TASKS_STARTRX = 1;
    while(NRF_UARTE0->EVENTS_RXSTARTED == 0);
    NRF_UARTE0->EVENTS_RXSTARTED = 0;
    NRF_UARTE0->EVENTS_RXDRDY = 0;
    NRF_UARTE0->ERRORSRC = BIT(2) | BIT(3);
    NRF_UARTE0->TASKS_STARTRX = 1;
              
    NVIC_SetPriority(UARTE0_UART0_IRQn, UART0_INT_PRIORITY);
    NVIC_ClearPendingIRQ(UARTE0_UART0_IRQn);
    NVIC_EnableIRQ(UARTE0_UART0_IRQn);
        
    println("UART0 started...");

    return UART_OK;
}

void nrf_hw_serial::deinit(void)
{                                            
    NRF_UARTE0->INTEN = (UARTE_INTEN_RXDRDY_Disabled << UARTE_INTEN_RXDRDY_Pos) | 
                        (UARTE_INTEN_TXDRDY_Disabled << UARTE_INTEN_RXDRDY_Pos) | 
                        (UARTE_INTEN_CTS_Disabled   << UARTE_INTEN_CTS_Pos) | 
                        (UARTE_INTEN_ENDRX_Disabled  << UARTE_INTEN_ENDRX_Pos);
    
    NRF_UARTE0->INTENSET = (UARTE_INTENSET_ENDRX_Disabled  << UARTE_INTENSET_ENDRX_Pos) |
                           (UARTE_INTENSET_ENDTX_Disabled  << UARTE_INTENSET_ENDTX_Pos) |
                           (UARTE_INTENSET_TXDRDY_Disabled << UARTE_INTENSET_TXDRDY_Pos);
    
    NRF_UARTE0->SHORTS = UARTE_SHORTS_ENDRX_STARTRX_Disabled;
    NRF_UARTE0->TASKS_STOPRX = 1UL;
    NRF_UARTE0->EVENTS_TXSTOPPED = 0UL;
    NRF_UARTE0->TASKS_STOPTX = 1UL;
    while (!NRF_UARTE0->EVENTS_TXSTOPPED)
    {} 
    
    NRF_UARTE0->PSEL.TXD = PIN_DISCONNECTED;
    NRF_UARTE0->PSEL.RXD = PIN_DISCONNECTED;
  
    NVIC_DisableIRQ(UARTE0_UART0_IRQn);
    NRF_UARTE0->ENABLE = UARTE_ENABLE_ENABLE_Disabled;
}



uint32_t nrf_hw_serial::available(void)
{
    return rx_data.get_avail();
}

char nrf_hw_serial::peek(void)
{
    return rx_data.peek_one();
}

char nrf_hw_serial::read(void)
{
    return rx_data.get_one();
}

uint32_t nrf_hw_serial::available_for_write(void)
{
    return rx_data.get_free();
}

void nrf_hw_serial::write_buf(const char *data, size_t len)
{   
    uint32_t wait_counter = 40000;
    uint32_t added;
  
    if(_amount_rx_bytes > RX_CHUNK_SIZE*2) { _amount_rx_bytes = 0; }
    // задержка в случае если идет прием.
    while(_amount_rx_bytes && (wait_counter-- > 1));
    
    if(wait_counter <= 1 && _amount_rx_bytes)
    { _amount_rx_bytes = 0; }

    static char missed[TX_CHUNK_SIZE] = {0};
    
    if(data != NULL)
    { 
       __disable_interrupt();  
       
       added = tx_data.add((char *)data, len);
       
       // если буффер переполнен начинаем передачу немедленно
       if (added < len)
       {
           // сохраняем данные не уместившиеся в буфер
           memcpy(missed, data + added, len);
           
           _tx_busy = true;       
           _start_tx();
           
           __enable_interrupt();
           //ждем когда данные отправятся
           while(_tx_busy);           
           __disable_interrupt();
           
           // отправляем оставшиеся данные
           tx_data.add(missed, (len - added));
           __enable_interrupt();
       }   
         
       _tx_busy = true;
       _start_tx();
       
       __enable_interrupt();
       
       //ждем когда данные отправятся
       while(_tx_busy);
    }
}

void nrf_hw_serial::write_one(char c)
{
    if(_amount_rx_bytes > RX_CHUNK_SIZE*2) { _amount_rx_bytes = 0; }
    // задержка в случае если идет прием.
    while(_amount_rx_bytes);    

    tx_data.add_one(c);
}

bool nrf_hw_serial::write(ring_buffer *ringbuf)
{     
    char c;
  
    if(ringbuf->is_empty())
    { return false; } 
    
    while(!ringbuf->is_empty())
    {
       c = ringbuf->get_one();
       tx_data.add_one(c);
    }
    
    write_buf(NULL,0);
    
    return true;
}

void nrf_hw_serial::write(const char *data, size_t len)
{
    // проверка того что буфер лежит в нужном интервале памяти.
    // проверка переполнения буфера отправки, в случае если это происходит
    // отправляем кусками.
    if (!((uint32_t)data & RAM_MASK)) 
    {
        size_t pos = 0;
        
        while (pos < len) 
        {
            char tmp[TX_CHUNK_SIZE];
            size_t off = len - pos;
            off = (off > TX_CHUNK_SIZE) ? TX_CHUNK_SIZE : off;
            memcpy(tmp, data + pos, off);
            write_buf(tmp, off);
            pos += off;
        }
    }
    else 
    {
        write_buf(data, len);
    }
}

void nrf_hw_serial::write(char c)
{
    write_one(c);
}

// need to be placed in TIMER0_IRQHandler if  RX used
bool nrf_hw_serial::check_rx(void)
{ 
    // обрабатываем таймер только если в приеме есть байты а прерывание
    // об окончании еще не сгенерировано
    if (sys_tmr.get_mseconds() - _rx_timer > UART_RX_TIMEOUT_MS &&
        _amount_rx_bytes > 0)
    { 
        update_rx_timer();
        
        rx_data.add(_rx_chunk, _amount_rx_bytes);
        memset(_rx_chunk,-1,sizeof(_rx_chunk));

        parce_data_ready = true;
        
        /*Вызываем прерывание окончание приема*/
        NRF_UARTE0->TASKS_STOPRX = 1;
        
        return true; 
    }
    else
    { return false; }
}

// need to be placed in TIMER0_IRQHandler if TX used
bool nrf_hw_serial::poll_tx(void)
{
    // обрабатываем таймер только если что отправлять
    if ( !_tx_busy && 
         sys_tmr.get_mseconds() - _tx_timer > UART_TX_TIMEOUT_MS &&
        !tx_data.is_empty() )
    {         
        update_tx_timer();        
        _start_tx();
        
        return true; 
    }
    else
    { return false; }

}

void nrf_hw_serial::_start_tx()
{
    volatile uint32_t avail_to_tx = 0;
   
    // если буфер переполнен заполняем кусок на отправку полностью.
    if (tx_data.is_full())
    {
        avail_to_tx = TX_CHUNK_SIZE;
    }
    else
    {  
        avail_to_tx = tx_data.get_avail();

        if ( avail_to_tx > TX_CHUNK_SIZE)
        { avail_to_tx = TX_CHUNK_SIZE; }       
    }

    tx_data.get(_tx_chunk, avail_to_tx);

    //NRF_UARTE0->EVENTS_ENDTX = 0;
    NRF_UARTE0->TXD.PTR = (uint32_t)_tx_chunk;
    NRF_UARTE0->TXD.MAXCNT = avail_to_tx;
    
    /* начинаем отправку */
    NRF_UARTE0->TASKS_STARTTX = 1;
 }

void nrf_hw_serial::update_rx_timer(void)
{
    _rx_timer = sys_tmr.get_mseconds();
}

void nrf_hw_serial::update_tx_timer(void)
{
    _tx_timer = sys_tmr.get_mseconds();
}

void nrf_hw_serial::rx_irq(void)
{
    if (NRF_UARTE0->EVENTS_RXDRDY)
    {
        // запускаем таймаут на опрос буфера при приеме последнего байта
        update_rx_timer();
        // и увеличиваем количество принятых байт
        // можно было бы использовать для этих целей NRF_UARTE0->RXD.AMOUNT,
        // но он не инкрементируется в прерывании EVENTS_RXDRDY, видимо баг, не стал долго разбираться.
        _amount_rx_bytes++;     
        
        NRF_UARTE0->EVENTS_RXDRDY = 0;
    }
            
    if (NRF_UARTE0->EVENTS_ENDRX)
    { 
        _amount_rx_bytes = 0;
        
        NRF_UARTE0->RXD.MAXCNT = RX_CHUNK_SIZE;
        NRF_UARTE0->RXD.PTR = (uint32_t)_rx_chunk;    
        NRF_UARTE0->EVENTS_ENDRX  = 0;
        NRF_UARTE0->TASKS_STARTRX = 1;        
    }
}

void nrf_hw_serial::tx_irq(void)
{  
    if (NRF_UARTE0->EVENTS_TXDRDY)
    {       
       NRF_UARTE0->EVENTS_TXDRDY = 0;
    } 
    
    if (NRF_UARTE0->EVENTS_ENDTX)
    { 
        // снимаем флаг принудительной передачи, если она была только после опорожнения
        // буффера передачи
        if (_tx_busy && tx_data.is_empty())
        { _tx_busy = false; }
        
        NRF_UARTE0->EVENTS_ENDTX = 0;
    }  
}

nrf_hw_serial uarte_0(UART0_TX_PIN, UART0_RX_PIN);