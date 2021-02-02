#include "include.h"
#include "input_stream.h"

char parce_data[SIZE_BUF] = {0};
bool parce_data_ready = false;
// защищенные методы->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// метод чтобы читать поток с таймаутом
int input_stream::timed_read()
{
  int c;
  _start_millis = GET_MSEC();

  do {
    c = read();
    if (c >= 0) return c;
  } while(GET_MSEC() - _start_millis < _timeout);

  return -1;     // -1 означает что таймаут истек
}

// метод, чтобы просматривать поток по таймауту
int input_stream::timed_peek()
{
  int c;
  _start_millis = GET_MSEC();
  
  do {
    c = peek();
    if (c >= 0) return c;
  } while(GET_MSEC() - _start_millis < _timeout);

  return -1;     // -1 означает что истек таймаут
}

// возвращает просмотр следующей цифры в потоке или -1, если вышло время
// отбрасывает нечисловые символы
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
        case SKIP_NONE: return -1; // код ошибки.
        case SKIP_WHITESPACE:
            switch( c ){
                case ' ':
                case '\t':
                case '\r':
                case '\n': break;
                default: return -1; // код ошибки.
            }
        case SKIP_ALL:
            break;
    }

    read();  // отбрасывает не числовые
  }
}
// защищенные методы <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<-

// публичные методы->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// устанавливает максимальное количество миллисекунд ожидания
void input_stream::set_timeout(unsigned long timeout)  
{
    _timeout = timeout;
}

 // возвращает истину если целевая строка найдена
bool  input_stream::find(char *target)
{
  return find_until(target, strlen(target), NULL, 0);
}

// читает данные из потока, пока не будет найдена целевая строка заданной длины
// труЪ если строка найдена, ложЪ если вышел таймаут
bool input_stream::find(char *target, size_t length)
{
    return find_until(target, length, NULL, 0);
}

// Тоже что и find но поиск завершается если найдена строка терминатора
bool  input_stream::find_until(char *target, char *terminator)
{
    return find_until(target, strlen(target), terminator, strlen(terminator));
}

// читает данные из потока, пока не будет найдена целевая строка заданной длины
// поиск прекращается, если найдена строка терминатора
// возвращает истину, если целевая строка найдена, ложь, если прекращено или истекло время ожидания
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

// возвращает первое действительное (long) integer значение из текущей позиции.
// lookahead определяет, как parse_int выглядит в потоке.
// См. look_ahead_mode_e энам вверху фаила.
// Lookahead завершается первым символом, который не является допустимой частью целого числа.
// Как только начинается прасинг, 'ignore' будет пропущен в потоке.
long input_stream::parse_int(look_ahead_mode_e lookahead, char ignore)
{
    bool is_negative = false;
    long value = 0;
    int c;
  
    c = peek_next_digit(lookahead, false);
    // ингнор не числовых символов
    if(c < 0)
      return 0; // возвращаемся по таймауту
  
    do{
      if(c == ignore)
        ; // игнорируем этот символ
      else if(c == '-')
        is_negative = true;
      else if(c >= '0' && c <= '9')        // это символ?
        value = value * 10 + c - '0';
      read();  // расходуем символ, который получили при просмотре (peek)
      c = timed_peek();
    }
    while( (c >= '0' && c <= '9') || c == ignore );
  
    if(is_negative)
      value = -value;
    return value;
}

// float версия parse_int
float input_stream::parse_float(look_ahead_mode_e lookahead, char ignore)
{
    bool is_negative = false;
    bool is_fraction = false;
    long value = 0;
    int c;
    float fraction = 1.0;
  
    c = peek_next_digit(lookahead, true);
  
    // ингнор не числовых символов
    if(c < 0)
      return 0; //  возвращаемся по таймауту
  
    do{
      if(c == ignore)
        ; // ignore
      else if(c == '-')
        is_negative = true;
      else if (c == '.')
        is_fraction = true;
      else if(c >= '0' && c <= '9')  {      // число?
        value = value * 10 + c - '0';
        if(is_fraction)
           fraction *= 0.1;
      }
      read();  // расходуем символ, который получили при просмотре (peek)
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

// читает символы из потока в буффер
// завершается, если нужная длина символов была прочитана или истекло время ожидания (см. set_timeout)
// возвращает количество символов, помещенных в буфер (0 means no valid data found)
// буффер должен быть не null terminated.
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


// Тоже что read_bytes только с символом завершения
// завершается, если длина символов была прочитана, истекло время ожидания или если обнаружен символ-терминатор
// возвращает количество символов, помещенных в буфер (0 означает что небыло нормальных данных)
size_t input_stream::read_bytes_until(char terminator, char *buffer, size_t length)
{
    size_t index = 0;
    while (index < length) {
      int c = timed_read();
      if (c < 0 || c == terminator) break;
      *buffer++ = (char)c;
      index++;
    }

    return index; // возвращает число символов, не содержит нуль терминатор
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
    
    // проверяем что строка полноценная
    while (commas < 13)
    {
        tst++;
      
        if(*tst == ',')
        {
            commas++;
            index = 0;
        }        
        // если символы прошли но запятой нет значит сообщение пришло негодное
        if(++index > 12)
        break;
        
        // сообщение полноценное можно парсить
        if(commas == 12 && *tst == '*')
        break;
    }
    
    // сообщение не годное выходим
    if( index > 12 || commas > 12)
    {   
        parce_point.reset();
        return parce_point;
    }
    
    commas = 0;
    index = 0;
    
    while (commas <= 13)
    {        
        // считаем количество запятых
        if (*ptr == ',')
        {
            commas++;
            ptr++;
        }
        
        // парсим по запятым
        switch(commas)
        {
            case 1: // первое поле это время в формате UTC
              if(*ptr == ',') // на случай отсутствия данных
              { break; }
              index = 0;
              
              // парсим поле
              while (*ptr != ',')
              { 
                  collect_data[index] = *ptr;
                  ptr++; index++;
              }
              
              collect_data[index] = *ptr;
              
              parce_point.time_stamp = atof(collect_data);              
              break;
            case 2: // второе поле - достоверность данных
              if(*ptr == ',') // на случай отсутствия данных
              { break; }
                          
              parce_point.validity = *ptr;
              ptr++;
              break;
            case 3: // третье - широта
              if(*ptr == ',') // на случай отсутствия данных
              { break; }
              
              index = 0;
              
              // парсим поле
              while (*ptr != ',')
              { 
                    collect_data[index] = *ptr;
    
                    // первые два числа это градусы
                    if(index == 1)
                    {
                        collect_data[2] = ';';
                        degrees = atof(collect_data);
                    }
    
                    ptr++;
                    
                    // ноль не учитываем.
                    if (index == 0 && collect_data[index] == '0')
                    index = 0;
                    else
                    index++;
              }
              
              collect_data[index] = *ptr;

              minutes = atof(&collect_data[2]);
              
              parce_point.latitiude = degrees + minutes/60.0;              
              break;
            case 4: // северная, южная?
              if(*ptr == ',') // на случай отсутствия данных
              { break; }
              
              parce_point.n_s = *ptr;
              ptr++;
              break;
            case 5: // это долгота
             if(*ptr == ',') // на случай отсутствия данных
              { break; }
              
              index = 0;
              
              // парсим поле
              while (*ptr != ',')
              { 
                    collect_data[index] = *ptr;
                    
                    // первые два числа это градусы
                    if(index == 1)
                    {
                        collect_data[2] = ';';
                        degrees = atof(collect_data);
                    }
    
                    ptr++;
                    
                    // ноль не учитываем.
                    if (index == 0 && collect_data[index] == '0')
                    index = 0;
                    else
                    index++;
              }
              
              collect_data[index] = *ptr;

              minutes = atof(&collect_data[2]);
              
              parce_point.longitude = degrees + minutes/60.0;
              break;
            case 6: // западная, восточная?
              if(*ptr == ',') // на случай отсутствия данных
              { break; }
              
              parce_point.e_w = *ptr;
              ptr++;
              break;
            case 7: // скорость
              if(*ptr == ',') // на случай отсутствия данных
              { break; }
               
              index = 0;
                           
              // парсим поле
              while (*ptr != ',')
              { 
                  collect_data[index] = *ptr;
                  ptr++; index++;
              }
              
              collect_data[index] = *ptr;
              
              parce_point.speed = atof(collect_data); 
              break;
            case 8: // курс
              if(*ptr == ',') // на случай отсутствия данных
              { break; }
               
              index = 0;
                           
              // парсим поле
              while (*ptr != ',')
              { 
                  collect_data[index] = *ptr;
                  ptr++; index++;
              }
              
              collect_data[index] = *ptr;
              
              parce_point.course = atof(collect_data); 
              break;
            case 9: // дата              
              if(*ptr == ',') // на случай отсутствия данных
              { break; }
              
              index = 0;
                            
              // парсим поле
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
              if(*ptr == ',') // на случай отсутствия данных
              { break; }    
              // просто листаем данные до звездочки - это контрольная сумма с валидацией.
              while (*ptr != '*')
              { ptr++; }
              
              ptr--;
              
              for ( int i = 0; i < 4; i++)
              {
                  parce_point.chksum[i] = *ptr;
                  ptr++;
              }
              commas++; // выходим из цикла парсинга
              break;              
            case 0:
              ptr++;
              break;
           default:
              break;
        }  
     }
     
     // валидация верная, значит данные пришли тоже верные - можно брать
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

// публичные методы-<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int input_stream::find_multi(multi_target_t *targets, int t_count) 
{
    // любая целевая строка нулевой длины автоматически совпадает и сделает
    // срачь в остальной части алгоритма.
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
            // в простом случае, если получилось совпадение разбираемся с этим первым делом.
            if (c == t->str[t->index]) 
            {
              if (++t->index == t->len)
                return t - targets;
              else
                continue;
            }
      
            // если нет, то нам нужно вернуться назад и посмотреть, что можно еще поделать
            // вниз по течению (то есть «1112» не соответствует первой позиции в «11112»
            // но он будет соответствовать второй позиции, поэтому мы не можем просто сбросить текущий
            // индекс в 0 когда найдем несоостветствие.
            if (t->index == 0)
              continue;
      
            int orig_index = t->index;
      
            do {
                --t->index;
                // сначала проверьте, работает ли текущий символ с новым текущим индексом
                if (c != t->str[t->index])
                  continue;
        
                // если это единственный символ, то у нас все хорошо, больше нечего проверять
                if (t->index == 0) 
                {
                    t->index++;
                    break;
                }
        
                // в противном случае нам нужно проверить оставшуюся найденную строку
                int diff = orig_index - t->index;
                size_t i;
      
                for (i = 0; i < t->index; ++i)
                {
                    if (t->str[i] != t->str[i + diff])
                    break;
                }
        
                // если мы успешно прошли предыдущий цикл, то наш текущий
                // индекс - хороший.
                if (i == t->index) 
                {
                    t->index++;
                    break;
                }
        
                // в противном случае мы просто попробуем следующий индекс
            } while (t->index);
        }
    }
    
    // до сюда не должны доходить
    //return -1;
}

