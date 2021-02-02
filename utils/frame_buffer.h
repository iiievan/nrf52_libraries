#ifndef _FRAME_BUFER_H_
#define _FRAME_BUFER_H_

#include "include.h"

struct i2s_sample_t 
{
  union {
    struct {
      union {
        int16_t r;
        int16_t right_chnl;
      };
      union {
        int16_t l;
        int16_t left_chnl;
      };
    };
    
    uint32_t stereo;
  };
};

template <typename T, size_t buf_size = 16UL >
class frame_buffer
{
public:    
                    frame_buffer()
                    :_complete_frame(buf[0]),_empty_frame(buf[1]) 
                    {     
                       _buf_size = buf_size;    
                       clear();
                    } 
        
             void   clear() 			{ memset(buf, 0, sizeof(buf));}						// reset whole buffer
	         void   clear_empty() 		{ memset((uint8_t*)_empty_frame, 0, _buf_size);}	// reset only empty_frame
	         void   clear_complete() 	{ memset((uint8_t*)_complete_frame, 0, _buf_size);}	// reset only complete frame
	       size_t   get_size() 			{ return _buf_size; }

               T*   get_complete_frame(void)    { return _complete_frame; }       // return pointer on complete frame
               T*   get_empty_frame(void)       { return _empty_frame; }          // return pointer on empty frames

        // in case of stereo sound buffer
        uint32_t* get_left_chnl(i2s_sample_t* frame)        { return (uint32_t*)frame; } // returns pointer on left channel
        uint32_t* get_right_chnl(i2s_sample_t* frame)                                    // returns pointer on right channel      
        {   
            int16_t *ptr_uint16 = (int16_t*)frame;           

            return (uint32_t*)(++ptr_uint16); 
        } 

    // меняет указатели на буферы местами
    // теперь тот, что был на заполенения  - на отправку
    // а то что был на отправку - заполняется.
    // возвращает укзатель на буфер для проигрывания(тоесть заполненный буффер).
    T* switch_frames() {
        if (_complete_frame == buf[0])
        {
            _empty_frame = buf[0];
            _complete_frame = buf[1];
        }
        else
        {
            _empty_frame = buf[1];
            _complete_frame = buf[0];
        }
        
        return _complete_frame;
    }

    void call_filling_irq(void)     { NRF_EGU0->TASKS_TRIGGER[0] = 1; }  // вызываем софтварное прерывание для очередного заполнения буфера

    void fill_frame_with_sin(int16_t amplitude , uint32_t period) {

        const  float pi = 3.14159265359;
               float angle = 0.0;
        static float phase = 0.0; 
        
        uint16_t sin_value;
      
        // заполняем буффер синусойдой
        for (uint32_t i = 0; i < buf_size; i++)
        {       
            sin_value = (int16_t)((float)amplitude * sin (angle + phase)) ;
            _empty_frame[i].right_chnl = sin_value;
            _empty_frame[i].l = _empty_frame[i].r;
                       
            angle += (float)(2 * pi) / period;

            if (i == (buf_size - 1))
            { phase += angle;}
        }
    }
    
    frame_buffer &operator=(frame_buffer &right)
    {
        T *  ptr;
        
        if(&right != this)
        {
            // заполняем текущий пустой кадр уэтого буффера, готовым(заполненным) кадром
            // буфера у которого мы берем данные.
            ptr = right.get_complete_frame();
            
            for(uint32_t i = 0; i < _buf_size; i++)
            {
                _empty_frame[i] = ptr[i];
            }      
        }
        
        return *this;   // для возможности сцепки
    }


    void upsample(i2s_sample_t *out_buf, uint16_t len)
    {
        // len must be higher than buf_size
        if(len <= _buf_size)
        { return; }

    }

    void downsample(i2s_sample_t *out_buf, uint16_t len)
    {
        // len must be lower than buf_size
        if(len >= _buf_size)
        { return; }

        float downstep = (float)_buf_size/(float)len;
        float curr_step = 0;
        float k;
        uint16_t i,n;
          
        for (i = 0; i < len; curr_step += downstep, i++)
        {
            n = (uint16_t)curr_step;
            k = curr_step - (float)n;
            n *= 2;
            
            //*out_buf++ = (int16_t)(in[n] + k*(in[n + 2] - in[n]));
            //правый
            n++;
            //*out_buf++ = (int16_t)(in[n] + k*(in[n + 2] - in[n]));
        }
        
        UNUSED(k);

    }

protected:
                    //буфер двойной, в тот момент пока один заполняется, второй отправляет данные.     
                T   buf[2][buf_size] {0}; //    буфер собственной персоной

private:
               T*   _complete_frame;  // указатель на текущий отправляемый кадр
               T*   _empty_frame;     // указатель на следующий кадр, для заполнения его перед отправкой.
          size_t    _buf_size;
};  

#endif // _FRAME_BUFER_H_

