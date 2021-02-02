#include "include.h"
#include "input_stream.h"

char parce_data[SIZE_BUF] = {0};
bool parce_data_ready = false;
// ���������� ������->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// ����� ����� ������ ����� � ���������
int input_stream::timed_read()
{
  int c;
  _start_millis = GET_MSEC();

  do {
    c = read();
    if (c >= 0) return c;
  } while(GET_MSEC() - _start_millis < _timeout);

  return -1;     // -1 �������� ��� ������� �����
}

// �����, ����� ������������� ����� �� ��������
int input_stream::timed_peek()
{
  int c;
  _start_millis = GET_MSEC();
  
  do {
    c = peek();
    if (c >= 0) return c;
  } while(GET_MSEC() - _start_millis < _timeout);

  return -1;     // -1 �������� ��� ����� �������
}

// ���������� �������� ��������� ����� � ������ ��� -1, ���� ����� �����
// ����������� ���������� �������
int input_stream::peek_next_digit(look_ahead_mode_e lookahead, bool detect_decimal)
{
  int c;
  while (1) {
    c = timed_peek();

    if( c < 0 ||
        c == '-' ||
        (c >= '0' && c <= '9') ||
        (detect_decimal && c == '.')) return c;

    switch( lookahead ){
        case SKIP_NONE: return -1; // ��� ������.
        case SKIP_WHITESPACE:
            switch( c ){
                case ' ':
                case '\t':
                case '\r':
                case '\n': break;
                default: return -1; // ��� ������.
            }
        case SKIP_ALL:
            break;
    }

    read();  // ����������� �� ��������
  }
}
// ���������� ������ <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-

// ��������� ������->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// ������������� ������������ ���������� ����������� ��������
void input_stream::set_timeout(unsigned long timeout)  
{
    _timeout = timeout;
}

 // ���������� ������ ���� ������� ������ �������
bool  input_stream::find(char *target)
{
  return find_until(target, strlen(target), NULL, 0);
}

// ������ ������ �� ������, ���� �� ����� ������� ������� ������ �������� �����
// ���� ���� ������ �������, ���� ���� ����� �������
bool input_stream::find(char *target, size_t length)
{
    return find_until(target, length, NULL, 0);
}

// ���� ��� � find �� ����� ����������� ���� ������� ������ �����������
bool  input_stream::find_until(char *target, char *terminator)
{
    return find_until(target, strlen(target), terminator, strlen(terminator));
}

// ������ ������ �� ������, ���� �� ����� ������� ������� ������ �������� �����
// ����� ������������, ���� ������� ������ �����������
// ���������� ������, ���� ������� ������ �������, ����, ���� ���������� ��� ������� ����� ��������
bool input_stream::find_until(char *target, size_t target_len, char *terminator, size_t term_len)
{
  if (terminator == NULL) 
  {
      multi_target_t t[1] = {{target, target_len, 0}};

      return find_multi(t, 1) == 0 ? true : false;
  } 
  else 
  {
      multi_target_t t[2] = {{target, target_len, 0}, {terminator, term_len, 0}};

      return find_multi(t, 2) == 0 ? true : false;
  }
}

// ���������� ������ �������������� (long) integer �������� �� ������� �������.
// lookahead ����������, ��� parse_int �������� � ������.
// ��. look_ahead_mode_e ���� ������ �����.
// Lookahead ����������� ������ ��������, ������� �� �������� ���������� ������ ������ �����.
// ��� ������ ���������� �������, 'ignore' ����� �������� � ������.
long input_stream::parse_int(look_ahead_mode_e lookahead, char ignore)
{
    bool is_negative = false;
    long value = 0;
    int c;
  
    c = peek_next_digit(lookahead, false);
    // ������ �� �������� ��������
    if(c < 0)
      return 0; // ������������ �� ��������
  
    do{
      if(c == ignore)
        ; // ���������� ���� ������
      else if(c == '-')
        is_negative = true;
      else if(c >= '0' && c <= '9')        // ��� ������?
        value = value * 10 + c - '0';
      read();  // ��������� ������, ������� �������� ��� ��������� (peek)
      c = timed_peek();
    }
    while( (c >= '0' && c <= '9') || c == ignore );
  
    if(is_negative)
      value = -value;
    return value;
}

// float ������ parse_int
float input_stream::parse_float(look_ahead_mode_e lookahead, char ignore)
{
    bool is_negative = false;
    bool is_fraction = false;
    long value = 0;
    int c;
    float fraction = 1.0;
  
    c = peek_next_digit(lookahead, true);
  
    // ������ �� �������� ��������
    if(c < 0)
      return 0; //  ������������ �� ��������
  
    do{
      if(c == ignore)
        ; // ignore
      else if(c == '-')
        is_negative = true;
      else if (c == '.')
        is_fraction = true;
      else if(c >= '0' && c <= '9')  {      // �����?
        value = value * 10 + c - '0';
        if(is_fraction)
           fraction *= 0.1;
      }
      read();  // ��������� ������, ������� �������� ��� ��������� (peek)
      c = timed_peek();
    }
    while( (c >= '0' && c <= '9')  || (c == '.' && !is_fraction) || c == ignore );
  
    if(is_negative)
      value = -value;
    if(is_fraction)
      return value * fraction;
    else
      return value;
}

// ������ ������� �� ������ � ������
// �����������, ���� ������ ����� �������� ���� ��������� ��� ������� ����� �������� (��. set_timeout)
// ���������� ���������� ��������, ���������� � ����� (0 means no valid data found)
// ������ ������ ���� �� null terminated.
size_t input_stream::read_bytes(char *buffer, size_t length)
{
  size_t count = 0;
  while (count < length) {
    int c = timed_read();
    if (c < 0) break;
    *buffer++ = (char)c;
    count++;
  }

  return count;
}


// ���� ��� read_bytes ������ � �������� ����������
// �����������, ���� ����� �������� ���� ���������, ������� ����� �������� ��� ���� ��������� ������-����������
// ���������� ���������� ��������, ���������� � ����� (0 �������� ��� ������ ���������� ������)
size_t input_stream::read_bytes_until(char terminator, char *buffer, size_t length)
{
    size_t index = 0;
    while (index < length) {
      int c = timed_read();
      if (c < 0 || c == terminator) break;
      *buffer++ = (char)c;
      index++;
    }

    return index; // ���������� ����� ��������, �� �������� ���� ����������
}

gps_point input_stream::parce_gps(char* input)
{
    char *ptr = NULL;
    char *tst;
    gps_point parce_point;
    char collect_data[13];
    int commas = 0;
    int  index = 0;
    
    static uint8_t satellite_connect_dbnce[2]={0};
    #define SAT_CON_DBNC_NUM 1
    #define SAT_DIS_DBNC_NUM 9

    float degrees, minutes;
    
    ptr = strstr(input, "GPRMC");
      
     if (ptr == NULL)
    { 
        parce_point.reset();
        return parce_point;
    }
    
    tst = ptr;
    
    // ��������� ��� ������ �����������
    while (commas < 13)
    {
        tst++;
      
        if(*tst == ',')
        {
            commas++;
            index = 0;
        }        
        // ���� ������� ������ �� ������� ��� ������ ��������� ������ ��������
        if(++index > 12)
        break;
        
        // ��������� ����������� ����� �������
        if(commas == 12 && *tst == '*')
        break;
    }
    
    // ��������� �� ������ �������
    if( index > 12 || commas > 12)
    {   
        parce_point.reset();
        return parce_point;
    }
    
    commas = 0;
    index = 0;
    
    while (commas <= 13)
    {        
        // ������� ���������� �������
        if (*ptr == ',')
        {
            commas++;
            ptr++;
        }
        
        // ������ �� �������
        switch(commas)
        {
            case 1: // ������ ���� ��� ����� � ������� UTC
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }
              index = 0;
              
              // ������ ����
              while (*ptr != ',')
              { 
                  collect_data[index] = *ptr;
                  ptr++; index++;
              }
              
              collect_data[index] = *ptr;
              
              parce_point.time_stamp = atof(collect_data);              
              break;
            case 2: // ������ ���� - ������������� ������
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }
                          
              parce_point.validity = *ptr;
              ptr++;
              break;
            case 3: // ������ - ������
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }
              
              index = 0;
              
              // ������ ����
              while (*ptr != ',')
              { 
                    collect_data[index] = *ptr;
    
                    // ������ ��� ����� ��� �������
                    if(index == 1)
                    {
                        collect_data[2] = ';';
                        degrees = atof(collect_data);
                    }
    
                    ptr++;
                    
                    // ���� �� ���������.
                    if (index == 0 && collect_data[index] == '0')
                    index = 0;
                    else
                    index++;
              }
              
              collect_data[index] = *ptr;

              minutes = atof(&collect_data[2]);
              
              parce_point.latitiude = degrees + minutes/60.0;              
              break;
            case 4: // ��������, �����?
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }
              
              parce_point.n_s = *ptr;
              ptr++;
              break;
            case 5: // ��� �������
             if(*ptr == ',') // �� ������ ���������� ������
              { break; }
              
              index = 0;
              
              // ������ ����
              while (*ptr != ',')
              { 
                    collect_data[index] = *ptr;
                    
                    // ������ ��� ����� ��� �������
                    if(index == 1)
                    {
                        collect_data[2] = ';';
                        degrees = atof(collect_data);
                    }
    
                    ptr++;
                    
                    // ���� �� ���������.
                    if (index == 0 && collect_data[index] == '0')
                    index = 0;
                    else
                    index++;
              }
              
              collect_data[index] = *ptr;

              minutes = atof(&collect_data[2]);
              
              parce_point.longitude = degrees + minutes/60.0;
              break;
            case 6: // ��������, ���������?
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }
              
              parce_point.e_w = *ptr;
              ptr++;
              break;
            case 7: // ��������
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }
               
              index = 0;
                           
              // ������ ����
              while (*ptr != ',')
              { 
                  collect_data[index] = *ptr;
                  ptr++; index++;
              }
              
              collect_data[index] = *ptr;
              
              parce_point.speed = atof(collect_data); 
              break;
            case 8: // ����
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }
               
              index = 0;
                           
              // ������ ����
              while (*ptr != ',')
              { 
                  collect_data[index] = *ptr;
                  ptr++; index++;
              }
              
              collect_data[index] = *ptr;
              
              parce_point.course = atof(collect_data); 
              break;
            case 9: // ����              
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }
              
              index = 0;
                            
              // ������ ����
              while (*ptr != ',')
              { 
                  collect_data[index] = *ptr;
                  ptr++; index++;
              }
              
              collect_data[index] = *ptr;
              
              parce_point.date_stamp = atoi(collect_data);                
              break;
            case 10:
            case 11:
            case 12:
            case 13:
              if(*ptr == ',') // �� ������ ���������� ������
              { break; }    
              // ������ ������� ������ �� ��������� - ��� ����������� ����� � ����������.
              while (*ptr != '*')
              { ptr++; }
              
              ptr--;
              
              for ( int i = 0; i < 4; i++)
              {
                  parce_point.chksum[i] = *ptr;
                  ptr++;
              }
              commas++; // ������� �� ����� ��������
              break;              
            case 0:
              ptr++;
              break;
           default:
              break;
        }  
     }
     
     // ��������� ������, ������ ������ ������ ���� ������ - ����� �����
     if (parce_point.chksum[0] == 'A' && parce_point.validity == 'A')
     {        
         if(stState.satellite_connect == false &&
             ++satellite_connect_dbnce[0] >= SAT_CON_DBNC_NUM)
         {
                 stState.satellite_connect = true; 
                 satellite_connect_dbnce[0] = 0;
         }
     }
     else
    {   
        parce_point.reset();
        
        if(stState.satellite_connect == true &&
           ++satellite_connect_dbnce[1] >= SAT_DIS_DBNC_NUM)
        {
            stState.satellite_connect = false;
            satellite_connect_dbnce[1] = 0;
        }
    }
    
    return parce_point;
}

string input_stream::read_string()
{
  string ret;

  int c = timed_read();
  while (c >= 0)
  {
    ret += (char)c;
    c = timed_read();
  }

  return ret;
}

string input_stream::read_string_until(char terminator)
{
  string ret;

  int c = timed_read();
  while (c >= 0 && c != terminator)
  {
    ret += (char)c;
    c = timed_read();
  }

  return ret;
}

// ��������� ������-<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int input_stream::find_multi(multi_target_t *targets, int t_count) 
{
    // ����� ������� ������ ������� ����� ������������� ��������� � �������
    // ����� � ��������� ����� ���������.
    for (multi_target_t *t = targets; t < (targets + t_count); ++t) 
    {
      if (t->len <= 0)
        return t - targets;
    }
  
    while (1) 
    {
        int c = timed_read();
        if (c < 0)
          return -1;
    
        for (multi_target_t *t = targets; t < (targets + t_count); ++t) 
        {
            // � ������� ������, ���� ���������� ���������� ����������� � ���� ������ �����.
            if (c == t->str[t->index]) 
            {
              if (++t->index == t->len)
                return t - targets;
              else
                continue;
            }
      
            // ���� ���, �� ��� ����� ��������� ����� � ����������, ��� ����� ��� ��������
            // ���� �� ������� (�� ���� �1112� �� ������������� ������ ������� � �11112�
            // �� �� ����� ��������������� ������ �������, ������� �� �� ����� ������ �������� �������
            // ������ � 0 ����� ������ ���������������.
            if (t->index == 0)
              continue;
      
            int orig_index = t->index;
      
            do {
                --t->index;
                // ������� ���������, �������� �� ������� ������ � ����� ������� ��������
                if (c != t->str[t->index])
                  continue;
        
                // ���� ��� ������������ ������, �� � ��� ��� ������, ������ ������ ���������
                if (t->index == 0) 
                {
                    t->index++;
                    break;
                }
        
                // � ��������� ������ ��� ����� ��������� ���������� ��������� ������
                int diff = orig_index - t->index;
                size_t i;
      
                for (i = 0; i < t->index; ++i)
                {
                    if (t->str[i] != t->str[i + diff])
                    break;
                }
        
                // ���� �� ������� ������ ���������� ����, �� ��� �������
                // ������ - �������.
                if (i == t->index) 
                {
                    t->index++;
                    break;
                }
        
                // � ��������� ������ �� ������ ��������� ��������� ������
            } while (t->index);
        }
    }
    
    // �� ���� �� ������ ��������
    //return -1;
}

