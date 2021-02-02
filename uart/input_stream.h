#ifndef _INPUT_STREAM_H
#define _INPUT_STREAM_H

#include "include.h"
#include "print_f.h"
#include "gps_point.h"
#include <cstring>  // for parcing

// ��� ������������ ������������� �������� ��������� ��� parseInt(), parseFloat()
// ������, ��������� �����, ������������ �� ��� ���, ���� �� ����� ������ ������ �������������� ������
// ��� �� ��������� ������� ��-�� ���������� �����.
enum look_ahead_mode_e
{
    SKIP_ALL,       // ��� ������������ ������� ������������.
    SKIP_NONE,      // ������ �� ������������, � ����� �� �������������, ���� ������ ������ ��������� ������ �� �������� ����������.
    SKIP_WHITESPACE // ������������ ������ ���������, �������, �������� ����� � ������� �������.
};

#define NO_IGNORE_CHAR  '\x01' // ������ �� ������ � ���������� �������� ���� ASCII
#define GET_MSEC() sys_tmr.get_mseconds()   // ����������� �������� ���������� ������� ������� ������������ � �������

typedef struct  
{
    const char *str;  // ������, ������� �� �����
    size_t len;       // �� �����
    size_t index;     // ������ ��� ��������� ���������.
} multi_target_t;



class input_stream : public print_f
{
    protected:
      unsigned long _timeout;                                                           // ���������� ����������� �������� ���������� ������� ����� ����������� ������ �� �������
      unsigned long _start_millis;                                                      // ������������ ��� ������� ��������
                int timed_read();                                                       // ������ ����� �� �������
                int timed_peek();                                                       // ������������� ����� �� ��������
                int peek_next_digit(look_ahead_mode_e lookahead, bool detectDecimal);   // ���������� ��������� ����� �� ������ ��� -1 � ������ ���� ����� �������
  
    public:
      virtual uint32_t available() = 0;  // ������ ���� ���������� � ������, ����������� input_stream
      virtual     char read()      = 0;  // ������ ���� ���������� � ������, ����������� input_stream
      virtual     char peek()      = 0;  // ������ ���� ���������� � ������, ����������� input_stream
  
      input_stream() { _timeout = 5U; } // �������� ���� �� �� ������ ��� ���������� �������
  
    // ����� ���� �������� ������� �������� �� ������.
  
             void set_timeout(unsigned long timeout);  // ������������� ������������ ����� ��� �������� ��������� ������, �� ��������� 1 �������
    unsigned long get_timeout(void) { return _timeout; }
    
             bool find(char *target);                                     // ������ ������ �� ������, ���� �� ����� ������� ������ ������
             bool find(uint8_t *target) { return find ((char *)target); } // ���������� ������, ���� ������ ������ �������, ����, ���� ������� ����� �������� (��. set_timeout)                                                                              
  
             bool find(char *target, size_t length);                      // ������ ������ �� ������, ���� �� ����� ������� ������� ������ �������� �����
             bool find(uint8_t *target, size_t length) { return find ((char *)target, length); } // ���������� ������, ���� ������� ������ �������, ����, ���� ������� ����� ��������
  
             bool find(char target) { return find (&target, 1); }
  
             bool find_until(char *target, char *terminator);   // ���� ��� � find() �� ����� �������������, ���� ������� ������ �����������
             bool find_until(uint8_t *target, char *terminator) { return find_until((char *)target, terminator); }
  
             bool find_until(char *target, size_t targetLen, char *terminate, size_t termLen);   // ��� ������� ����, �� ����� �������������, ���� ������� ����������� ������
             bool find_until(uint8_t *target, size_t targetLen, char *terminate, size_t termLen) {return find_until((char *)target, targetLen, terminate, termLen); }
  
             // ���������� ������ �������������� (long) integer �������� �� ������� �������.
             // lookahead ����������, ��� parse_int �������� � ������.
             // ��. look_ahead_mode_e ���� ������ �����.
             // Lookahead ����������� ������ ��������, ������� �� �������� ���������� ������ ������ �����.
             // ��� ������ ���������� �������, 'ignore' ����� �������� � ������.
             long parse_int(look_ahead_mode_e lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR);
  
            float parse_float(look_ahead_mode_e lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR);          // float ������ parse_int
 
           size_t read_bytes( char *buffer, size_t length);                                                   // ������ ������� �� ������ � ������
           size_t read_bytes( uint8_t *buffer, size_t length) { return read_bytes((char *)buffer, length); }  // �����������, ���� ������ ����� �������� ���� ��������� ��� ������� ����� �������� (��. set_timeout)
                                                                                                              // ���������� ���������� ��������, ���������� � ����� (0 means no valid data found)
 
           size_t read_bytes_until( char terminator, char *buffer, size_t length); // ���� ��� read_bytes ������ � �������� ����������
           size_t read_bytes_until( char terminator, uint8_t *buffer, size_t length) { return read_bytes_until(terminator, (char *)buffer, length); }  // �����������, ���� ����� �������� ���� ���������, ������� ����� �������� ��� ���� ��������� ������-����������
                                                                                                                                                        // ���������� ���������� ��������, ���������� � ����� (0 �������� ��� ������ ���������� ������)
        gps_point parce_gps( char* input );     // ������� GPS 
           // ������� ��� ������ � ����� String ����������� ����
           string read_string();
           string read_string_until(char terminator);
  
    protected:
             long parse_int(char ignore) { return parse_int(SKIP_ALL, ignore); }
            float parse_float(char ignore) { return parse_float(SKIP_ALL, ignore); }
            // ��� ���������� ���������� ��� ������������� � ����� �������, ������� ��������
            // � ����������� parse_float /  parse_int � ���������������� �������� �������������. 
            // ����� ������� ��������� API simple, ��� ���������� ��������� �����������.

            // ��� ��������� ��� ������ ������������ ���������� �����.
            // ���������� ������ ����, ������� ���� ������� ������, ��� -1, ���� ������� ����� ��������.
            int find_multi(multi_target_t *targets, int t_count);
                   

};

extern char parce_data[SIZE_BUF];
extern bool parce_data_ready;

#undef NO_IGNORE_CHAR
#endif
