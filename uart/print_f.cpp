#include "include.h"
#include "print_f.h"


void print_f::print(const string &s, bool enable)
{  
    if(enable) {    
        write(s.c_str(), s.length());
    }
    else
    { return; }
}

void print_f::print(const char str[], bool enable)
{   
    if(enable) {  
        write(str);
    }
    else
    { return; }
}

void print_f::print(char c, bool enable)
{  
    if(enable) {   
        write(c);
    }
    else
    { return; }
}

void print_f::print(unsigned char c, int base, bool enable)
{
    if(enable) { 
        print((unsigned long) c, base);
    }
    else
    { return; }
}

void print_f::print(int n, int base, bool enable)
{
    if(enable) { 
        print((long)n, base);
    }
    else
    { return; }
}

void print_f::print(unsigned int n, int base, bool enable)
{
    if(enable) { 
        print((unsigned long)n, base);
    }
    else
    { return; }
}

void print_f::print(long n, int base, bool enable)
{  
    if(enable) { 
        if (base == 0) 
        {
          write(n);
        } 
        else 
        if (base == 10) 
        {
            if (n < 0) 
            {
                print('-');
                n = -n;
                _print_number(n, 10);
            }
        
            _print_number(n, 10);
        
        } 
        else 
        {
            _print_number(n, base);
        }
    }
    else
    { return; }
}

void print_f::print(unsigned long n, int base, bool enable)
{ 
    if(enable) {   
        if (base == 0) 
        {  write(n); }
        else 
        { _print_number(n, base); }
    }
    else
    { return; }
}

void print_f::print(double n, int digits, bool enable)
{
    if(enable) {
        _print_float(n, digits);
    }
    else
    { return; }
}


void print_f::println(const string &s, bool enable)
{
    if(enable) {
        print(s);
        println();
    }
    else
    { return; }
}

void print_f::println(const char c[], bool enable)
{
    if(enable) {
        print(c);
        println();
    }
    else
    { return; }
}

void print_f::println(char c, bool enable)
{
    if(enable) {
        print(c);
        println();
    }
    else
    { return; }
}

void print_f::println(unsigned char c, int base, bool enable)
{
    if(enable) {
        print(c, base);
        println();
    }
    else
    { return; }
}

void print_f::println(int num, int base, bool enable)
{
    if(enable) {
        print(num, base);
        println();
    }
    else
    { return; }
}

void print_f::println(unsigned int num, int base, bool enable)
{
    if(enable) {
        print(num, base);
        println(); 
    }
    else
    { return; }
}

void print_f::println(long num, int base, bool enable)
{
    if(enable) {
        print(num, base);
        println();
    }
    else
    { return; }    
}

void print_f::println(unsigned long num, int base, bool enable)
{
    if(enable) {
        print(num, base);
        println();
    }
    else
    { return; }    
}

void print_f::println(double num, int digits, bool enable)
{
    if(enable) {
        print(num, digits);
        println();
    }
    else
    { return; }
}

void print_f::println(bool enable)
{  
    if(enable) {  
        write("\r\n");
    }
    else
    { return; }
}

void print_f::_print_number(unsigned long n, uint8_t base)
{
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];
        
    *str = '\0';
    
    // prevent crash if called with base == 1
    if (base < 2) 
    base = 10;
    
    do 
    {
        char c = n % base;
        n /= base;
      
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);
    
    write(str);
}

void print_f::_print_float(double number, uint8_t digits) 
{         
    if (isnan(number))  print("nan");
    if (isinf(number))  print("inf");
    if (number > 4294967040.0) print ("ovf");  // constant determined empirically
    if (number <-4294967040.0) print ("ovf");  // constant determined empirically
    
    // Handle negative numbers
    if (number < 0.0)
    {
       print("-");
       number = - number;
    }
    
    // Round correctly so that print(1.999, 2) prints as "2.00"
    double rounding = 0.5;

    for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;
    
    number += rounding;
    
    // Extract the integer part of the number and print it
    unsigned long int_part = (unsigned long)number;
    double remainder = number - (double)int_part;
    print(int_part);
    
    // Print the decimal point, but only if there are digits beyond
    if (digits > 0)
    {
        print("."); 
    }
    
    // Extract digits from the remainder one at a time
    while (digits-- > 0)
    {
        remainder *= 10.0;
        unsigned int to_print = (unsigned int)(remainder);
        print(to_print);
        remainder -= to_print; 
    }
}
