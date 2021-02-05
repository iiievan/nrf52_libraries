#ifndef _FIFO_H
#define _FIFO_H

#include "include.h"

#define MAX_FSM_FIFO_LEN    (16UL)          // the total number of machines in the list
#define MAX_ACTIVE_FSM      (2 + 1)         // the number of simultaneously operating machines at the moment

template <typename T, size_t fifo_size = 16>
class fifo
{
public:
                    fifo() : _size(fifo_size) { reset(); }

inline    size_t    get_avail() const { return _avail; }                 // Return available data in FIFO 
inline    size_t    get_free()  const { return (_size - _avail); }       // Return available space in FIFO     
inline    size_t    get_size()  const { return _size; }                  // Return size of FIFO 
inline      bool    is_empty()  const { return  _tail == _head; }        // Test if the FIFO is empty.
inline      bool    is_full()   const { return  0 == get_free(); }       // Test if the FIFO is full.
            void    reset()           { _head = _tail = _avail = 0;}     // reset(but not clear) data in buffer

            // add new element in queue
            void add(T value) 
            { 
                _queue[(_head++) & (_size - 1)] = value;

                if (!is_full()) { _avail++; }
            }

            T extract()    
            { 
               T result;

                if (get_avail() > 0)
                { _avail--;  }
                else
                { return result;}

                return _queue[(_tail++) & (_size - 1)];
            }

            T* read_head()    { return &_queue[(_tail) & (_size - 1)]; }

            T* read_item(size_t item)  
            {
                if (item <= get_size()) 
                {
                    return &_queue[(_tail + item) & (_size - 1)];
                }
                else
                { return NULL;}
            }
   
            // overwrite existing element in queue
            void write_item(size_t item, T value) 
            {                
                if (item > get_size()) { return; }

                _queue[(_tail + item) & (_size - 1)] = value;
            }

private:
                     T _queue[fifo_size];  // FIFO buffer itself    
    const       size_t _size;              // buffer size
                size_t _avail {0};         // available elements in buffer
                size_t _head  {0};               
                size_t _tail  {0}; 
};


#endif