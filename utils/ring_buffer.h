#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include "include.h"

template <size_t buf_size = 16>
class ring_buffer
{
public:    
                     ring_buffer() : _size(buf_size) { reset(); }

                char get_tail() 
                {
                    volatile char result = -1; 
                
                    result = *curr_data();
                
                    pop();
                
                    return result;
                }
 
                size_t add(char* data, size_t len)
                {
                      __disable_interrupt();
                      
                      uint32_t i;                      
                  
                      for (i = 0; i < len; i++) 
                      {
                          if (is_full()) {  break;  }
                  
                          push(data[i]);
                      }
                  
                      __enable_interrupt();
                  
                      return i;
                }

                size_t get(char* data, size_t len)
                {
                      __disable_interrupt();

                      volatile uint32_t bytes_avail = get_avail();
                      
                      if (len > bytes_avail) { len = bytes_avail; }
                  
                      if (len > 0) 
                      {       
                          for (int idx = 0; idx < len; idx++ ) 
                          { data[idx] = get_tail(); }
                      }
                  
                      __enable_interrupt();
                  
                      return len;                  
                }

                char add_one(char& c)
                {
                    __disable_interrupt();
                
                    char result = -1;
                
                    // если буфер полный, то выплевываем один символ
                    if (is_full()) { result = get_tail(); }

                    push(c); 
                
                    __enable_interrupt();  
                
                    return result;
                }

                char get_one()
                {
                      __disable_interrupt();

                      char result = -1;

                      if (!is_empty()) { result = get_tail(); }

                      __enable_interrupt();

                      return result;
                }

                char peek_one() // Look what is putted in buffer, without take element
                {
                      __disable_interrupt();

                      char result = *curr_data();
                  
                      __enable_interrupt();
                      
                      return result;                  
                }                           

    inline      size_t get_avail() const { return _avail; }                 // Return available data in ringbuffer 
    inline      size_t get_free()  const { return (_size - _avail); }       // Return available space in ringbuffer     
    inline      size_t get_size()  const { return _size; }                  // Return size of ringbuffer  
    inline        bool is_empty()  const { return  _tail == _head; }        // Test if the ringbuffer is empty.
    inline        bool is_full()   const { return  0 == get_free(); }       // Test if the ringbuffer is full.
    inline        void reset()           { _head = _tail = _avail = 0; }    // reset(but not clear) data in buffer
    inline        void reset_to_zero()              
                  { 
                    // reset to zero data in buffer
                    _head = _tail = _avail = 0;
                    memset(_queue, 0, sizeof(_queue)); 
                  }    
    inline        void set_head(size_t value) { _head = _avail = value; }    // this method uses in dma buffer fill.

    inline const char* curr_data() const { return &(_queue[_tail]); }
    inline       char* curr_data()       { return &(_queue[_tail]); }

    // выбрасывает элемент из буфера
    inline        void pop()
                  {
                      if (get_avail() == 0) return;
                      if (get_avail() == 1) reset();
                      else
                      {
                         _tail = (_tail + 1) % buf_size;
                         _avail--;
                      }
                  }

    // добавляет элемент в буфер
    inline        void push(char& data)
                  {
                      _queue[_head] = data;
                      _head = (_head + 1) % buf_size;
                      
                      // двигаем хвост с потерей данных если буфер полный
                      // при этом количество доступных элементов остается равным buf_size
                      if (is_full())
                      { _tail = (_tail + 1) % buf_size; }
                      else
                      { _avail++; }
                  }
				  
	inline        bool push_for_dma()
                  {
                      _head = (_head + 1) % buf_size;
                      
                      // двигаем хвост с потерей данных если буфер полный
                      // при этом количество доступных элементов остается равным buf_size
                      if (is_full())
                      { return false; }
                      else
                      { 
						_avail++; 
						return true;						
					  }
                  }

    char* get_buf_pointer(void) { return _queue; }  

private:
                  char _queue[buf_size] {0};  // ring buffer itself    
    const       size_t _size;                 // buffer size
                size_t _avail;                // available elements in buffer
                size_t _head;               
                size_t _tail;              
};

#endif