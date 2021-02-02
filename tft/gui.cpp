#include "include.h"
#include "gui.h"
#include "TFT.h"

void guiUnite::calculateBorders(void) 
{  
    int end;

    // calculate object placement on the display, adjust if necessary.
    if (width < 0) 
    {
        width = -width;
        x -= width;
    }
                               
    end = x + width;
    if (x < 0)
        x = 0;

    if (end > display->getWidth())
        end = display->getWidth();

    width = end - x;

    if (height < 0) 
    {
        height = -height;
        y -= height;
    } 

    end = y + height;
    if (y < 0)
        y = 0;

    if (end > display->getHight())
        end = display->getHight();

    height = end - y;
}

void guiUnite::fillRectangle(uint32_t color) 
{   
    CRGB rgb = CRGB(color);
    display->setAddrWindow(x, y, x + width - 1, y + height - 1);
    display->writeCmd(TFT_MEM_WRITE).transferColor(rgb,width * height); 
}

void guiUnite::fillRectangle(int16_t xPos, int16_t yPos, uint16_t w, uint16_t h, uint32_t color) 
{   
    CRGB rgb = CRGB(color);
    display->setAddrWindow(xPos, yPos, xPos + w - 1, yPos + h - 1);
    display->writeCmd(TFT_MEM_WRITE).transferColor(rgb, w * h); 
}

void guiUnite::drawCircle(int x1, int y1, int radius, uint32_t color)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y)
    {
        display->drawPixel( x + x1,  y + y1, color);
        display->drawPixel( y + x1,  x + y1, color);
        display->drawPixel(-x + x1,  y + y1, color);
        display->drawPixel(-y + x1,  x + y1, color);
        display->drawPixel(-x + x1, -y + y1, color);
        display->drawPixel(-y + x1, -x + y1, color);
        display->drawPixel( x + x1, -y + y1, color);
        display->drawPixel( y + x1, -x + y1, color);
        y++;
        
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

// erase cicle from 0 to 360 degrees
void guiUnite::drawCircleByAngle(int x1, int y1, uint32_t radius, double angle, const uint32_t * background)
{ 
    double x,y;
    //translate from degrees to radians
    double a = angle * M_PI / 180;      
        
    x = (double)radius * cos(a);
    y = (double)radius * sin(a);    

    display->transferImage(((int)x + x1 - 2), ((int)y + y1 - 2),5,5,(const uint8_t *)&black_dot_3pix, background);
}

// cicle from 0 to 360 degrees
void guiUnite::drawCircleByAngle(int x1, int y1, uint32_t radius, double angle, uint32_t color)
{ 
    double x,y;
    //translate from degrees to radians
    double a = angle * M_PI / 180;      
        
    x = (double)radius * cos(a);
    y = (double)radius * sin(a);    

    display->drawPixel(((int)x + x1), ((int)y + y1), color);
}

// cicle from 0 to 360 degrees
void guiUnite::rotateCircleByAngle(int x1, int y1, uint32_t radius, double angle, unsigned int width, uint32_t color )
{ 
    double x,y;
    //translate from degrees to radians
    double a = angle * M_PI / 180;      
        
    x = (double)radius * cos(a);
    y = (double)radius * sin(a);
	
	for(uint8_t i = 0; i < width; i++)
	{
    	drawCircle(((int)x + x1), ((int)y + y1),8 - i, color);
	}
}


void RSSIBar::displayValue(int rssi)
{ 
    int   dy;
            
    if(rssi < _rssi_zero)
    {
        _current_bar = 0;
    }
    else
    if(rssi >= _rssi_zero && rssi < (_rssi_zero + (_rssi_delta/5)))
    {
      _current_bar = 1;
    }
    else
    if(rssi >= (_rssi_zero + (_rssi_delta/5)) && rssi < (_rssi_zero + (2*_rssi_delta/5)))
    {
        _current_bar = 2;
    }
    else
    if(rssi >=  (_rssi_zero + (2*_rssi_delta/5)) && rssi < (_rssi_zero + (3*_rssi_delta/5)))
    {
        _current_bar = 3;
    }
    else
    if(rssi >=  (_rssi_zero + (3*_rssi_delta/5)) && rssi < (_rssi_zero + (4*_rssi_delta/5)))
    {
        _current_bar = 4;
    }
    else
    if(rssi >=  (_rssi_zero + (4*_rssi_delta/5)))
    {
        _current_bar = 5;
    }
    

    if(_current_bar > _last_bar_value)
    {
        for(int i = _last_bar_value; i <= _current_bar; i++)
        {
            if(i == 0) i++;
          
            if(i == 5)
                dy = 2*i;
            else
                dy = 2*i - 1;
    
            guiUnite::fillRectangle(((guiUnite::x - 2) - (16 - i*4)), (guiUnite::y + (10 - dy)), 2, (7 + dy), CSKYBLUE);
        }         
    }
    else
    {
        for(int i = _last_bar_value; i > _current_bar; i--)
        {
            if(i == 0) break;
          
            if(i == 5)
                dy = 2*i;
            else
                dy = 2*i - 1;           
            
            guiUnite::fillRectangle(((guiUnite::x - 2) - (16 - i*4)), (guiUnite::y + (10 - dy)), 2, (7 + dy), CWHITE);
        }
    }       
    
    _last_bar_value = _current_bar;
}



void batteryLevel::init()
{
  	// draw outlines of the battery
    guiUnite::fillRectangle( guiUnite::x,       guiUnite::y,       24,  2, CWHITE);
    guiUnite::fillRectangle( guiUnite::x,       guiUnite::y,        2, 15, CWHITE);
    guiUnite::fillRectangle((guiUnite::x + 24), guiUnite::y,        2, 15, CWHITE);
    guiUnite::fillRectangle( guiUnite::x,      (guiUnite::y + 15), 26,  2, CWHITE); 
	guiUnite::fillRectangle((guiUnite::x + 26),(guiUnite::y + 4),   3,  2, CWHITE);
	guiUnite::fillRectangle((guiUnite::x + 26),(guiUnite::y + 11),  3,  2, CWHITE);
	guiUnite::fillRectangle((guiUnite::x + 27),(guiUnite::y + 6),   2,  5, CWHITE);
	
    displayValue(100);
	
	// for testing
	//displayValue(70);
	//displayValue(50);
	//displayValue(30);
	//displayValue(10);
	//displayValue(2);
	//displayValue(100);
	//displayValue(200);
}


void batteryLevel::displayValue(int value)
{
  static uint8_t lastBarValue{0};
         uint8_t currentBar{0};
		    CRGB pixel;
     
    const int startValue = 7;
    const int endValue = 100; 
    const int dVlaue = endValue - startValue;

    if(value < startValue)
    {
        currentBar = 0;
    }
    else
    if(value >= startValue && value < (startValue + (dVlaue/5)))
    {
      currentBar = 1;
    }
    else
    if(value >= (startValue + (dVlaue/5)) && value < (startValue + (2*dVlaue/5)))
    {
        currentBar = 2;
    }
    else
    if(value >=  (startValue + (2*dVlaue/5)) && value < (startValue + (3*dVlaue/5)))
    {
        currentBar = 3;
    }
    else
    if(value >=  (startValue + (3*dVlaue/5)) && value < (startValue + (4*dVlaue/5)))
    {
        currentBar = 4;
    }
    else
    if(value >=  (startValue + (4*dVlaue/5)))
    {
        currentBar = 5;
		if(value > endValue)
		  lastBarValue = 0; 	// to display charging	
    }
    
    if(currentBar > lastBarValue)
    {
	  	// show state of connected charger
	  	if(currentBar == 5 &&
		   (value > endValue))
		{			
			// draw zipper.
		  	guiUnite::display->transferImage(guiUnite::x + 2, guiUnite::y + 2, 22, 13,(const uint8_t *)zipper, clockBackground);
		}
		else
		{
			for(int i = lastBarValue; i <= currentBar; i++)
        	{
        	    if(i == 0) i++;
    	
        	    guiUnite::fillRectangle((guiUnite::x + 4*i),(guiUnite::y + 4), 2, 9, CWHITE);
        	} 
		}        
    }
    else
    {
	  	if(currentBar > 0)
	  	{
      	  for(int i = lastBarValue; i > currentBar; i--)
      	  {
      	      if(i == 0) break;          
      	      
      	      guiUnite::fillRectangle((guiUnite::x + 4*i),(guiUnite::y + 4), 2, 9, CBLACK);
      	  }
	  	}
	  	else
	  	{
	  			// the voltage is extremely low - draw red bar.
	  			guiUnite::fillRectangle((guiUnite::x + 4),(guiUnite::y + 4), 2, 9, CRED);
	  	}
    }        
    
    lastBarValue = currentBar;  
}








#define ADDITIONAL_ANGLE (6.4)
#define MINUTES_MAX      (15)
speakTimer::speakTimer(unsigned int x, unsigned int y, TFT *disp)
: guiUnite(x,y,81,81,disp), // magic numbers of width and height is the radius of the circle.
  _integerList  //  an array of pre-built font characters
  {
        (const uint8_t *)&digit_0,
        (const uint8_t *)&digit_1,
        (const uint8_t *)&digit_2,
        (const uint8_t *)&digit_3,
        (const uint8_t *)&digit_4,
        (const uint8_t *)&digit_5,
        (const uint8_t *)&digit_6,
        (const uint8_t *)&digit_7,
        (const uint8_t *)&digit_8,
        (const uint8_t *)&digit_9,
        (const uint8_t *)&colon
  } 
{ 
    radius = guiUnite::width;
} 

void speakTimer::reset_right()
{ 
    minutes = seconds = 0; 

    guiUnite::rotateCircleByAngle(guiUnite::x, guiUnite::y, radius, _current_angle + ADDITIONAL_ANGLE, 2, CBLACK);
    guiUnite::rotateCircleByAngle(guiUnite::x, guiUnite::y, radius, _last_angle + ADDITIONAL_ANGLE, 2, CBLACK);

    _last_angle = _current_angle = 0.0f;
    // erase circle
    for(float i = 0; i < 360.0f; i += 3.0f)
    {
        guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,radius,(double)i,clockBackground);
    }
}

void speakTimer::poll(uint32_t dT)
{
    unsigned int ones, tenths, temp;
    const double angleDelta = 360.0/(((double)MINUTES_MAX)*60.0);

	if(!_time_is_hold)
	{
    	seconds += dT;
		
		if(seconds > 59)
    	{
    	    seconds = 0;
    	    minutes++;
    	}
		
    	if(minutes == MINUTES_MAX)
    	{
		  	// reset timer and erase circle
    	    reset_right();
		}
		    
		_current_angle += angleDelta;

    	temp =  minutes;
		ones = temp % 10;
    	guiUnite::display->transferImage(133, 225,DIGIT_W,DIGIT_H,_integerList[ones],pictBackground);
    	guiUnite::display->transferImage(156, 225,      9,DIGIT_H,_integerList[static_cast<unsigned int>(EUINTEGER::COLON)],pictBackground); 
		
    	temp /= 10;
    	tenths = temp % 10;
    	guiUnite::display->transferImage(111, 225,DIGIT_W,DIGIT_H,_integerList[tenths],pictBackground);
		
    	temp =  seconds;
		ones = temp % 10;
    	guiUnite::display->transferImage(190, 225,DIGIT_W,DIGIT_H,_integerList[ones],pictBackground);
		
    	temp /= 10;
    	tenths = temp % 10;
    	guiUnite::display->transferImage(168, 225,DIGIT_W,DIGIT_H,_integerList[tenths],pictBackground);

		guiUnite::rotateCircleByAngle(guiUnite::x, guiUnite::y, radius, _last_angle + ADDITIONAL_ANGLE, 2, CBLACK);
        guiUnite::rotateCircleByAngle(guiUnite::x, guiUnite::y, radius, _current_angle + ADDITIONAL_ANGLE, 2, CSKYBLUE); 

		// fill sector of circle equals one last second
		for(double i = _last_angle; i <= _current_angle; i += 0.1)
		{
			guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,radius,	  (double)i,	clockBackground[static_cast<unsigned int>(EBackgroundMask::MASK_5)]);
			guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,(radius - 1),(double)i,	clockBackground[static_cast<unsigned int>(EBackgroundMask::MASK_3)]);
			guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,(radius + 1),(double)i,	clockBackground[static_cast<unsigned int>(EBackgroundMask::MASK_2)]);
			guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,radius,	  (double)i,	clockBackground[static_cast<unsigned int>(EBackgroundMask::MASK_5)]);
		}
      
		
		_last_angle = _current_angle;
	}    
}

void speakTimer::continueCount() 
{  
    unsigned int ones, tenths, temp;

    if(_time_is_hold)
    {
        temp =  minutes;
        ones = temp % 10;
        guiUnite::display->transferImage(133, 225,DIGIT_W,DIGIT_H,_integerList[ones],pictBackground);
        guiUnite::display->transferImage(156, 225,      9,DIGIT_H,_integerList[static_cast<unsigned int>(EUINTEGER::COLON)],pictBackground); 
        
        temp /= 10;
        tenths = temp % 10;
        guiUnite::display->transferImage(111, 225,DIGIT_W,DIGIT_H,_integerList[tenths],pictBackground);
        
        temp =  seconds;
        ones = temp % 10;
        guiUnite::display->transferImage(190, 225,DIGIT_W,DIGIT_H,_integerList[ones],pictBackground);
        
        temp /= 10;
        tenths = temp % 10;
        guiUnite::display->transferImage(168, 225,DIGIT_W,DIGIT_H,_integerList[tenths],pictBackground);

        guiUnite::rotateCircleByAngle(guiUnite::x, guiUnite::y, radius, _current_angle + ADDITIONAL_ANGLE, 2, CSKYBLUE);

        // fill sector of circle equals one last second
        for(double i = (double)_last_angle; i <= (double)_current_angle; i += 0.1)
        {
            guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,radius,   (double)i,    clockBackground[static_cast<unsigned int>(EBackgroundMask::MASK_5)]);
            guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,(radius - 1),(double)i, clockBackground[static_cast<unsigned int>(EBackgroundMask::MASK_3)]);
            guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,(radius + 1),(double)i, clockBackground[static_cast<unsigned int>(EBackgroundMask::MASK_2)]);
            guiUnite::drawCircleByAngle(guiUnite::x,guiUnite::y,radius,   (double)i,    clockBackground[static_cast<unsigned int>(EBackgroundMask::MASK_5)]);
        }  
    
        _time_is_hold = false;
        _left_hold = false;
        _right_hold = false;
    } 
}

void speakTimer::_holdCount()     
{ 
    unsigned int ones, tenths, temp;

    if (!_time_is_hold)
    {
        _time_is_hold = true;
    
        temp =  minutes;
        ones = temp % 10;
        guiUnite::display->transferImage(133, 225,DIGIT_W,DIGIT_H,_integerList[ones],interpreterMuteBackground);
        guiUnite::display->transferImage(156, 225,      9,DIGIT_H,_integerList[static_cast<unsigned int>(EUINTEGER::COLON)],interpreterMuteBackground); 
        
        temp /= 10;
        tenths = temp % 10;
        guiUnite::display->transferImage(111, 225,DIGIT_W,DIGIT_H,_integerList[tenths],interpreterMuteBackground);
        
        temp =  seconds;
        ones = temp % 10;
        guiUnite::display->transferImage(190, 225,DIGIT_W,DIGIT_H,_integerList[ones],interpreterMuteBackground);
        
        temp /= 10;
        tenths = temp % 10;
        guiUnite::display->transferImage(168, 225,DIGIT_W,DIGIT_H,_integerList[tenths],interpreterMuteBackground);
    
        guiUnite::rotateCircleByAngle(guiUnite::x, guiUnite::y, radius, _current_angle + ADDITIONAL_ANGLE, 2, CGRAY);
    }  
}










LanguageLabel::LanguageLabel(unsigned int x, unsigned int y, TFT *disp, const char *label, bool dir)
:   guiUnite(x,y,130,51,disp), _dir(dir),
    _alphabetList  // an array of pre-built font characters
    {
          (const uint8_t *)&letter_A,
          (const uint8_t *)&letter_R,
          (const uint8_t *)&letter_U,
          (const uint8_t *)&letter_E,
          (const uint8_t *)&letter_N,
          (const uint8_t *)&ArrowIN,
          (const uint8_t *)&ArrowOUT          
    },
    _currentBackground((uint32_t *)interpreterSpeakBackground) 
{ 
    setLabel(label);
} 

void   LanguageLabel::setLabel(const char *lbl)
{
    for(int i = 0; i < (LABEL_LENGTH_MAX + 1); i++)
    {
        _label[i] = lbl[i];

        if(_label[i] == '\0')
            break;
    }
}

void  LanguageLabel::onState(void)
{
    guiUnite::fillRectangle(guiUnite::x,guiUnite::y,guiUnite::width, guiUnite::height, CSKYBLUE);

    if(!_isVisible)
        _isVisible = true;

    _currentBackground = (uint32_t *)interpreterSpeakBackground;

    if(_dir)
    {
        guiUnite::display->transferImage(guiUnite::x + 18,guiUnite::y + 15,ARROW_SIZE,ARROW_SIZE, _alphabetList[static_cast<unsigned int>(EALPHABET::IN)],_currentBackground);
    }
    else
    {
        guiUnite::display->transferImage(guiUnite::x + 18,guiUnite::y + 15,ARROW_SIZE,ARROW_SIZE, _alphabetList[static_cast<unsigned int>(EALPHABET::OUT)],_currentBackground);
    }

    displayValue();
}

void  LanguageLabel::offState(void)
{
	
	guiUnite::fillRectangle(guiUnite::x, guiUnite::y, guiUnite::width, 2, CGRAY);
    guiUnite::fillRectangle(guiUnite::x, guiUnite::y, 2, guiUnite::height, CGRAY);
    guiUnite::fillRectangle(guiUnite::x, guiUnite::y + guiUnite::height - 2, guiUnite::width, 2, CGRAY);
    guiUnite::fillRectangle(guiUnite::x + guiUnite::width - 2, guiUnite::y, 2, guiUnite::height, CGRAY);
	guiUnite::fillRectangle(guiUnite::x + 2, guiUnite::y + 2, guiUnite::width - 4, guiUnite::height - 4, CBLACK);

    if(_isVisible)
        _isVisible = false;

    _currentBackground = (uint32_t *)interpreterMuteBackground;

    if(_dir)
    {
        guiUnite::display->transferImage(guiUnite::x + 18,guiUnite::y + 15,ARROW_SIZE,ARROW_SIZE, _alphabetList[static_cast<unsigned int>(EALPHABET::IN)],_currentBackground);
    }
    else
    {
        guiUnite::display->transferImage(guiUnite::x + 18,guiUnite::y + 15,ARROW_SIZE,ARROW_SIZE, _alphabetList[static_cast<unsigned int>(EALPHABET::OUT)],_currentBackground);
    }

    displayValue();
}

void  LanguageLabel::displayValue(int value)
{
      uint8_t clearance {44};
    EALPHABET letter;

    for(char c : _label)
    {
        switch(c)
        {
            case 'A':
            case 'a':
                letter = EALPHABET::A;
                break;
            case 'R':
            case 'r':
                letter = EALPHABET::R;
                break;
            case 'U':
            case 'u':
                letter = EALPHABET::U;
                break;
            case 'E':
            case 'e':
                letter = EALPHABET::E;
                break;
            case 'N':
            case 'n':
                letter = EALPHABET::N;
                break;
            case '\0':
            default:
                break;
        }

        if(c == '\0')
            break;
	
        guiUnite::display->transferImage(guiUnite::x + clearance,guiUnite::y + 15,LETTER_SIZE,LETTER_SIZE, _alphabetList[static_cast<unsigned int>(letter)],_currentBackground);
		
		clearance += 16;
    }
}

            RSSIBar     rssi_bar(38, 14, &WinstarWF35);
       batteryLevel     batteryBar(272,16, &WinstarWF35);
         speakTimer     interpreterTimer(160,240, &WinstarWF35);
functionalPictogram     phantomPict(147, 425, &WinstarWF35, (const uint8_t *)PhantomPict);
functionalPictogram     transferMediaPict(147, 17, &WinstarWF35, (const uint8_t *)RadioPict);
      VUMeter<16UL>     leftVUMeter(5,360, &WinstarWF35);
      VUMeter<16UL>     rightVUMeter(305,360, &WinstarWF35);

      LanguageLabel     leftInputLabel(20,70,&WinstarWF35,"RU", true);
      LanguageLabel     leftOutputLabel(20,360,&WinstarWF35,"EN", false);
      LanguageLabel     rightInputLabel(170, 70,&WinstarWF35,"RU", true);
      LanguageLabel     rightOutputLabel(170, 360,&WinstarWF35,"EN", false);

