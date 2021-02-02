#ifndef _INPUT_STREAM_H
#define _INPUT_STREAM_H

#include "include.h"
#include "print_f.h"
#include "gps_point.h"
#include <cstring>  // for parcing

// Это перечисление предоставляет варианты просмотра для parseInt(), parseFloat()
// Методы, описанные здесь, используются до тех пор, пока не будет найден первый действительный символ
// или не случиться таймаут из-за отсутствия ввода.
enum look_ahead_mode_e
{
    SKIP_ALL,       // Все недопустимые символы игнорируются.
    SKIP_NONE,      // Ничего не пропускается, и поток не затрагивается, если только первый ожидающий символ не является допустимым.
    SKIP_WHITESPACE // Пропускаются только табуляции, пробелы, переводы строк и возврат каретки.
};

#define NO_IGNORE_CHAR  '\x01' // символ не найден в допустимом числовом поле ASCII
#define GET_MSEC() sys_tmr.get_mseconds()   // подставляем название системного таймера который используется в проекте

typedef struct  
{
    const char *str;  // строка, которую вы ищете
    size_t len;       // ее длина
    size_t index;     // индекс для поисковой процедуры.
} multi_target_t;



class input_stream : public print_f
{
    protected:
      unsigned long _timeout;                                                           // количество миллисекунд ожидания следующего символа перед прерыванием чтения по времени
      unsigned long _start_millis;                                                      // используется для отсчета таймаута
                int timed_read();                                                       // читает поток по таймуту
                int timed_peek();                                                       // просматривает поток по таймауту
                int peek_next_digit(look_ahead_mode_e lookahead, bool detectDecimal);   // возвращает следующую цифру из потока или -1 в случае если истек таймаут
  
    public:
      virtual uint32_t available() = 0;  // должны быть определены в классе, наследующем input_stream
      virtual     char read()      = 0;  // должны быть определены в классе, наследующем input_stream
      virtual     char peek()      = 0;  // должны быть определены в классе, наследующем input_stream
  
      input_stream() { _timeout = 5U; } // максимум пять мс на чтение или нахождение символа
  
    // далее идет описание методов парсинга из потока.
  
             void set_timeout(unsigned long timeout);  // устанавливает максимальное время для ожидания потоковых данных, по умолчанию 1 секунда
    unsigned long get_timeout(void) { return _timeout; }
    
             bool find(char *target);                                     // читает данные из потока, пока не будет найдена нужная строка
             bool find(uint8_t *target) { return find ((char *)target); } // возвращает истину, если нужная строка найдена, ложь, если истекло время ожидания (см. set_timeout)                                                                              
  
             bool find(char *target, size_t length);                      // читает данные из потока, пока не будет найдена целевая строка заданной длины
             bool find(uint8_t *target, size_t length) { return find ((char *)target, length); } // возвращает истину, если целевая строка найдена, ложь, если истекло время ожидания
  
             bool find(char target) { return find (&target, 1); }
  
             bool find_until(char *target, char *terminator);   // тоже что и find() но поиск заканчивается, если найдена строка терминатора
             bool find_until(uint8_t *target, char *terminator) { return find_until((char *)target, terminator); }
  
             bool find_until(char *target, size_t targetLen, char *terminate, size_t termLen);   // как указано выше, но поиск заканчивается, если найдена завершающая строка
             bool find_until(uint8_t *target, size_t targetLen, char *terminate, size_t termLen) {return find_until((char *)target, targetLen, terminate, termLen); }
  
             // возвращает первое действительное (long) integer значение из текущей позиции.
             // lookahead определяет, как parse_int выглядит в потоке.
             // См. look_ahead_mode_e энам вверху фаила.
             // Lookahead завершается первым символом, который не является допустимой частью целого числа.
             // Как только начинается прасинг, 'ignore' будет пропущен в потоке.
             long parse_int(look_ahead_mode_e lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR);
  
            float parse_float(look_ahead_mode_e lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR);          // float версия parse_int
 
           size_t read_bytes( char *buffer, size_t length);                                                   // читает символы из потока в буффер
           size_t read_bytes( uint8_t *buffer, size_t length) { return read_bytes((char *)buffer, length); }  // завершается, если нужная длина символов была прочитана или истекло время ожидания (см. set_timeout)
                                                                                                              // возвращает количество символов, помещенных в буфер (0 means no valid data found)
 
           size_t read_bytes_until( char terminator, char *buffer, size_t length); // Тоже что read_bytes только с символом заверщения
           size_t read_bytes_until( char terminator, uint8_t *buffer, size_t length) { return read_bytes_until(terminator, (char *)buffer, length); }  // завершается, если длина символов была прочитана, истекло время ожидания или если обнаружен символ-терминатор
                                                                                                                                                        // возвращает количество символов, помещенных в буфер (0 означает что небыло нормальных данных)
        gps_point parce_gps( char* input );     // парсинг GPS 
           // функции для работы с типом String добавляются туть
           string read_string();
           string read_string_until(char terminator);
  
    protected:
             long parse_int(char ignore) { return parse_int(SKIP_ALL, ignore); }
            float parse_float(char ignore) { return parse_float(SKIP_ALL, ignore); }
            // Эти перегрузки существуют для совместимости с любым классом, который произвел
            // и использовал parse_float /  parse_int с пользовательским символом игнорирования. 
            // Чтобы хранить бубличный API simple, эти перегрузки считаются защищинными.

            // Это позволяет вам искать произвольное количество строк.
            // Возвращает индекс цели, которая была найдена первой, или -1, если истекло время ожидания.
            int find_multi(multi_target_t *targets, int t_count);
                   

};

extern char parce_data[SIZE_BUF];
extern bool parce_data_ready;

#undef NO_IGNORE_CHAR
#endif
