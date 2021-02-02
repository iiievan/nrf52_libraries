#ifndef _PRINTF_H
#define _PRINTF_H

#include "include.h"
#include <string>

using namespace std;

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef  BIN 
#undef  BIN
#endif
#define BIN 2

class print_f
{
public:
    print_f() : _write_error(0) {}

             int get_write_error() { return _write_error; }
            void clear_write_error() { set_write_error(0); }

    virtual void write(char) = 0;
            void write(const char *str) 
            {
                if (str == NULL) 
                return;

                volatile uint32_t len = strlen(str);

                write(str, len);
            }

    virtual void write(const char *, size_t) = 0;

// default to zero, meaning "a single write may block"
// should be overriden by subclasses with buffering
virtual uint32_t available_for_write(void) { return 0; } 
            
            void print(const string &,              bool enable = true);                
            void print(const char[],                bool enable = true);
            void print(char,                        bool enable = true);
            void print(unsigned char, int = DEC,    bool enable = true);
            void print(int, int = DEC,              bool enable = true);
            void print(unsigned int, int = DEC,     bool enable = true);
            void print(long, int = DEC,             bool enable = true);
            void print(unsigned long, int = DEC,    bool enable = true);
            void print(double, int = 2,             bool enable = true);

            void println(const string &,            bool enable = true);
            void println(const char[],              bool enable = true);
            void println(char,                      bool enable = true);
            void println(unsigned char, int = DEC,  bool enable = true);
            void println(int, int = DEC,            bool enable = true);
            void println(unsigned int, int = DEC,   bool enable = true);
            void println(long, int = DEC,           bool enable = true);
            void println(unsigned long, int = DEC,  bool enable = true);
            void println(double, int = 2,           bool enable = true);
            void println(                           bool enable = true);

    virtual void flush() { /* Empty implementation for backward compatibility */ }

protected:
            void set_write_error(int err = 1) { _write_error = err; }
private:
             int _write_error;
            void _print_number(unsigned long, uint8_t);
            void _print_float(double, uint8_t);
};

#endif