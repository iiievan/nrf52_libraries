#ifndef _NRF_HW_SERIAL_H
#define _NRF_HW_SERIAL_H

#include "include.h"
#include "input_stream.h"
#include "ring_buffer.h"

#define UART_RX_TIMEOUT_MS     (5U)
#define UART_TX_TIMEOUT_MS     (1U)
#define RX_CHUNK_SIZE          (256U)
#define TX_CHUNK_SIZE          (256U)
#define RAM_MASK               (0x20000000)


#define UART0_RX_PIN           (PORT_1 | 9)   // P1.09 
#define UART0_TX_PIN           (PORT_0 | 12)  // P0.12 

#ifndef PIN_DISCONNECTED
#define PIN_DISCONNECTED       (0xFFFFFFFFUL)    // Define that pin is disconnected from hardware
#endif

#define UART0_INT_PRIORITY     (7)

enum {
    UART_OK         =  0,   /**< everything in order */
    UART_NODEV      = -1,   /**< invalid UART device given */
    UART_NOBAUD     = -2,   /**< given baudrate is not applicable */
    UART_INTERR     = -3,   /**< all other internal errors */
    UART_NOMODE     = -4    /**< given mode is not applicable */
};

class nrf_hw_serial : public input_stream
{
public:
                     nrf_hw_serial(uint32_t _transmit_pin, uint32_t _receive_pin);
              int8_t init(uint32_t baudrate, uint32_t _pwr_en_pin = PIN_DISCONNECTED);
              void   deinit(void);
  
    virtual uint32_t available(void);
    virtual     char peek(void);
    virtual     char read(void);
    virtual uint32_t available_for_write(void); 
    
                void write_buf(const char *data, size_t len);
                void write_one(char c);
                bool write(ring_buffer *ringbuf);

    virtual     void write(char); 
    virtual     void write(const char *data, size_t len);  

                bool check_rx(void);                // need to be placed in TIMER0_IRQHandler if RX used
                bool poll_tx(void);                 // need to be placed in TIMER0_IRQHandler if TX used 
                void update_rx_timer(void);         
                void update_tx_timer(void);         
                void rx_irq(void);                  // need to be placed in UARTE0_UART0_IRQHandler if RX used
                void tx_irq(void);                  // need to be placed in UARTE0_UART0_IRQHandler if TX used
      
         ring_buffer rx_data;                       // накопительный буффер , принятых данных после прерывания
         ring_buffer tx_data;                       // накопительный буффер данных на отправку
     
private:
                char _rx_chunk[RX_CHUNK_SIZE]{0};   // кусок данных, принятых  по DMA
                char _tx_chunk[TX_CHUNK_SIZE]{0};   // кусок данных на отправку по DMA   
                void _start_tx();
                bool _tx_busy;
                
            uint32_t _amount_rx_bytes;              // количество принятых на данный момент байт по DMA
            uint64_t _rx_timer;                     // таймер на опрос буфера если он заполнен не до конца.
            uint64_t _tx_timer;                     // таймер на опрос накопительного буффера отправки для отправки.
      
            uint32_t _transmit_pin;                 // ножка TX
            uint32_t _receive_pin;                  // ножка RX
            uint32_t _pwr_en_pin;                   // включает внешний модули если с которым будет идти обмен по UART
                     
};

extern nrf_hw_serial uarte_0;
#endif