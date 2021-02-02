#ifndef _GUI_H
#define _GUI_H

struct guiUnite;
#include "include.h"

enum class EUINTEGER : unsigned int
{
  ZERO,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  COLON,
  EUINTEGER_NUM
};

enum class EALPHABET : unsigned int
{
  A,
  R,
  U,
  E,
  N,
  IN,
  OUT,
  ALPHABET_NUM
};


struct guiUnite
{
    // this is perimetral dimensions of gui object
   int   x;
   int   y;
   int   width;    // wigth of picture object in pixels
   int   height;   // hight of picture object in pixels
   TFT  *display;

         guiUnite(int xpos, int ypos, int w, int h, TFT *disp)
         : x(xpos), y(ypos), width(w), height(h), display(disp)
         {  calculateBorders(); }

    void calculateBorders(void);

    void onState(void)                                                                      { return; }
    void offState(void)                                                                     { return; }
    void displayValue(int value)                                                            { return; }
    void fillRectangle(uint32_t color);
    void fillRectangle(int16_t xPos, int16_t yPos, uint16_t w, uint16_t h, uint32_t color);
    void drawVLine(int x, int y, int h, uint32_t color)                                     { fillRectangle(x, y, 1, h, color); }
    void drawHLine(int x, int y, int w, uint32_t color)                                     { fillRectangle(x, y, w, 1, color); }
    void drawCircle(int x1, int y1, int radius, uint32_t color);
    void drawCircleByAngle(int x1, int y1, uint32_t radius, double angle, const uint32_t * background);
    void drawCircleByAngle(int x1, int y1, uint32_t radius, double angle, uint32_t color);
    void rotateCircleByAngle(int x1, int y1, uint32_t radius, double angle, unsigned int width, uint32_t color );
};



class RSSIBar : public guiUnite
{
public:
                 RSSIBar(unsigned int x, unsigned int y, TFT *disp) 
                 : guiUnite(x,y,18,17,disp),_rssi_delta(RSSI_100 - RSSI_0),_rssi_zero(RSSI_0){} // magic numbers are set by the designer.

            void init() { displayValue(RSSI_NO_SIGNAL); } // initialization of the reception level meter doing by the minimum signal level
            void displayValue(int rssi);
private:
           uint8_t   _current_bar    {0};
           uint8_t   _last_bar_value {5};
         const int   _rssi_delta;
         const int   _rssi_zero;
};



class batteryLevel : public guiUnite
{
public:
                 batteryLevel(unsigned int x, unsigned int y, TFT *disp) 
                 : guiUnite(x,y,29,17,disp){} // magic numbers are set by the designer.

            void init();
            void displayValue(int value);
};



class speakTimer : public guiUnite
{
public:
                    speakTimer(unsigned int x, unsigned int y, TFT *disp);

            void 	reset_right();
            void    reset_left() { reset_right(); _last_angle = _current_angle = 180.0; }
			
            void    poll(uint32_t dT = 1);
			void 	continueCount();
            void    setLeftHold()        { _left_hold = true; _holdCount(); }
            void    setRightHold()       { _right_hold = true; _holdCount(); }
			bool 	getLeftHold() const  {	 return _left_hold; }
            bool    getRightHold() const {   return _right_hold; }

private:
            void    _holdCount();
            
    unsigned int  	radius;
    unsigned int  	minutes;
    unsigned int  	seconds;

          double    _last_angle    {0.0};
          double    _current_angle;
            // time holders
			bool  	_left_hold     { false };
            bool    _right_hold    { false };
            bool    _time_is_hold  { false };
			
   const uint8_t   *_integerList[static_cast<unsigned int>(EUINTEGER::EUINTEGER_NUM)];  // massive of pointers on font integers + colon symbol
};




#define LABEL_LENGTH_MAX (3) // maximum char lenght of label
class LanguageLabel : public guiUnite
{
public:
                    LanguageLabel(unsigned int x, unsigned int y, TFT *disp, const char *label, bool dir = true); 

            void    setLabel(const char * lbl);

     		void    onState(void);
     		void    offState(void);
            void    displayValue(int value = 0);

            bool    getVisibility(void) const { return _isVisible; }   

private:
            char    _label[LABEL_LENGTH_MAX];
            bool    _isVisible { false };
   const    bool    _dir;   // translate direction
            
   const uint8_t   *_alphabetList[static_cast<unsigned int>(EALPHABET::ALPHABET_NUM)];  // massive of pointers on a font alphabet
         uint32_t  *_currentBackground;
};



class functionalPictogram : public guiUnite
{
public:
                    functionalPictogram(unsigned int x,
                                        unsigned int y,
									         TFT *disp,
                                   const uint8_t *pict = nullptr,
                                        unsigned int w = PICTOGRAM_W,
                                        unsigned int h = PICTOGRAM_H)
                    : guiUnite(x,y,w,h,disp),_currentBackground((uint32_t *)pictBackground)
                    {   setPict(pict); } 

            void    setPict(const uint8_t *pict) { _pPict = pict; } 

            void    onState(void)
                    { guiUnite::display->transferImage(guiUnite::x,guiUnite::y,guiUnite::width,guiUnite::height,(const uint8_t *)_pPict, _currentBackground); }

            void    offState(void)
                    { guiUnite::fillRectangle(CBLACK); }

            void    displayValue(const uint8_t *pict = nullptr, unsigned int w = PICTOGRAM_W, unsigned int h = PICTOGRAM_H)
                    {
                        // recalculate the possibility of placing the pictogram on the display
                        guiUnite::width = w;
                        guiUnite::height = h;
                        guiUnite::calculateBorders();

                        setPict(pict);
                        onState();
                    }

            bool    getVisibility(void) const { return _isVisible; }   

private:
   const  uint8_t  *_pPict;            
         uint32_t  *_currentBackground;            
             bool   _isVisible { false };
};




#define VU_LENGTH                             (120)
#define VU_GAP                                (3)
#define ITEMS_NUM                             (12)
template <size_t items_number = ITEMS_NUM>
class VUMeter : public guiUnite
{
public:
                    VUMeter(unsigned int x,
                            unsigned int y,
                                 TFT *disp,
                            unsigned int w = 10,
                            unsigned int h = VU_LENGTH)
                    : guiUnite(x,y,w,h,disp),_itemsNumber(items_number), _itemsGap(VU_GAP)
                    {
                        // inititalization of UV-meter pallete values
                        for( unsigned int k = 0; k < _itemsNumber; k++)
                        {
                            if(k < (unsigned int)((float)_itemsNumber/9.0f))
                                _VUpalette[k] = CROYALRED;
                            else
                            if(k < (unsigned int)((2.0f*(float)_itemsNumber)/9.0f))
                                _VUpalette[k] = CYELLOW;
                            else
                            if(k < (unsigned int)((4.0f*(float)_itemsNumber)/9.0f))
                                _VUpalette[k] = CGRASSGREEN;
                            else
                                _VUpalette[k] = CDEEPGREEN;
                        }

                        _itemLength = ((guiUnite::height/_itemsNumber) - _itemsGap);
                    }

            void    displayValue(uint32_t value)
                    {
                        if(_lastValue != value)
                        {
                            for(int i = 0, y = 0; i < _itemsNumber; i += 1, y += (guiUnite::height/_itemsNumber))
							  guiUnite::fillRectangle(guiUnite::x, guiUnite::y + y,guiUnite::width,_itemLength, _VUpalette[i]);  

                            _lastValue = value;
                        }
                    }

        uint32_t    getLastValue() { return _lastValue; } 

private:
   const uint8_t    _itemsNumber;
   const uint8_t    _itemsGap;
         uint8_t    _itemLength;   
        uint32_t    _VUpalette[items_number];
        uint32_t    _lastValue { 0 };            

};


extern             RSSIBar    rssi_bar;
extern        batteryLevel    batteryBar;
extern          speakTimer    interpreterTimer;
extern functionalPictogram    phantomPict;
extern functionalPictogram    transferMediaPict;
extern       VUMeter<16UL>    leftVUMeter;
extern       VUMeter<16UL>    rightVUMeter;

extern       LanguageLabel    leftInputLabel;
extern       LanguageLabel    leftOutputLabel;
extern       LanguageLabel    rightInputLabel;
extern       LanguageLabel    rightOutputLabel;


#endif //_GUI_H