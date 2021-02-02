#ifndef _TFT_H
#define _TFT_H

// backward declaration
union CRGB;
struct pins3SPI_t;

#include "include.h"

#define ILI9488

#define HIGTH_PIXELS                          (480)
#define WIDTH_PIXELS                          (320)

#ifdef ILI9488
  // система команд для ILI9488
  #define TFT_NOP		                      (0x00)
  #define TFT_MEM_WRITE		                  (0x2C)
  #define TFT_PAGE_ADR_SET                    (0x2B)
  #define TFT_COL_ADR_SET                     (0x2A)
  #define POS_GAMMA_CTRL                      (0xE0)
  #define NEG_GAMMA_CTRL                      (0xE1)
  #define IFACE_MODE_CTRL                     (0xB0)
  #define FRAME_RATE_MODE_CTRL                (0xB1)
  #define DISP_INVERSION_CTRL                 (0xB4)
  #define DISP_INVERSION_ON                   (0x21)
  #define POWER_CTRL_1                        (0xC0)
  #define POWER_CTRL_2                        (0xC1)
  #define VCOM_CTRL                           (0xC5)
  #define DISP_FUNCTION_CTRL                  (0xB6)
  #define MEM_ACC_CTRL                        (0x36)
  #define IFACE_PIXEL_FORMAT                  (0x3A)
  #define HS_LANES_CTRL                       (0xBE)
  #define SET_IMAGE_CTRL                      (0xE9)
  #define AJUST_CTRL                          (0xF7)
  #define SLEEP_OUT                           (0x11)
  #define DISPLAY_ON                          (0x29)
#endif              
              
#define  CRED                                 (0xFF0000)
#define  CGREEN                               (0x00FF00)
#define  CBLUE                                (0x0000FF)
                          
// цвета по дизайну                         
#define  CSKYBLUE                             (0x009FDD)
#define  CGRAY                                (0x686868)
#define  CROYALRED                            (0xF13E49)
#define  CYELLOW                              (0xF5EB57)
#define  CDEEPGREEN                           (0x0A6613)
#define  CGRASSGREEN                          (0x7CAF41)
#define  CBLACK                               (0x000000)
#define  CWHITE                               (0xFFFFFF)

enum class EBackgroundMask : uint32_t
{
    MASK_0,
    MASK_1,
    MASK_2,
    MASK_3,
    MASK_4,
    MASK_5,
    BACKGROUND_MASK_NUM
};

#define LETTER_SIZE     (18)
#define ARROW_SIZE      (19)
#define PICTOGRAM_W     (26)
#define PICTOGRAM_H     (36)
#define DIGIT_H 	    (27)
#define DIGIT_W 	    (20)
           
#define LCD_CMD         (0)
#define LCD_DATA        (1) 

union CRGB
{
   struct 
   {
        union 
        { 
            uint8_t   b; 
            uint8_t   blue;
        };
        union 
        {
            uint8_t   g; 
            uint8_t   green; 
        };
        union 
        {
            uint8_t   r; 
            uint8_t   red; 
        };  
        union 
        {
            uint8_t   a; 
            uint8_t   alpha; 
        };  
   };
   union 
   {
       uint32_t   raw; 
        uint8_t   bgra[4]; 
   };
   
   CRGB(uint32_t rgb = CBLACK): raw(rgb){}
};

class TFT
{
public:
                TFT(uint32_t hight = HIGTH_PIXELS, uint32_t width = WIDTH_PIXELS) : _Hight(hight),_Width(width) {};
           void initController(spim &rSPI);

           TFT& writeCmd(char cmd);
           void transferImage(int x, int y, int16_t w, int16_t h, const uint8_t * symbol, const uint32_t * background);
           void transferColor(CRGB &rColor, unsigned int num);
           void transferData(const char *data, unsigned int len);
		   void switchDoubleBuffer() { _transferBuffer.switch_frames();}
		   
	   uint32_t getHight() const { return _Hight;}
	   uint32_t getWidth() const { return _Width;}
     
           void drawPixel(int x, int y, uint32_t color);
           void fillWithColor(uint32_t color);
           void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);

private:
       uint32_t _get_pixel_from_background(const uint8_t pix, const uint32_t *background);
 const uint32_t _Hight; 
 const uint32_t _Width;

#ifdef ILI9488
private:
    frame_buffer<uint32_t, 27UL> _transferBuffer;
protected:
           spim  *_pSPI {nullptr};

 		uint8_t   _NOP   {TFT_NOP};
        uint8_t   _MC	 {TFT_COL_ADR_SET};
        uint8_t   _MP	 {TFT_PAGE_ADR_SET};
        uint8_t   _MW	 {TFT_MEM_WRITE};     // Memory Write command
        uint8_t   _SC	 {TFT_COL_ADR_SET};   // Start Column command
        uint8_t   _EC	 {TFT_COL_ADR_SET};   // End column command
        uint8_t   _SP	 {TFT_PAGE_ADR_SET};  // Start Page command
        uint8_t   _EP	 {TFT_PAGE_ADR_SET};  // End Page command
#endif  //ILI9488
};

extern           TFT  WinstarWF35;


extern const  uint8_t zipper[][22];
extern const  uint8_t letter_A[][LETTER_SIZE];
extern const  uint8_t letter_R[][LETTER_SIZE];
extern const  uint8_t letter_U[][LETTER_SIZE];
extern const  uint8_t letter_E[][LETTER_SIZE];
extern const  uint8_t letter_N[][LETTER_SIZE];

extern const  uint8_t colon[][9];
extern const  uint8_t digit_0[][DIGIT_W];
extern const  uint8_t digit_1[][DIGIT_W];
extern const  uint8_t digit_2[][DIGIT_W];
extern const  uint8_t digit_3[][DIGIT_W];
extern const  uint8_t digit_4[][DIGIT_W];
extern const  uint8_t digit_5[][DIGIT_W];
extern const  uint8_t digit_6[][DIGIT_W];
extern const  uint8_t digit_7[][DIGIT_W];
extern const  uint8_t digit_8[][DIGIT_W];
extern const  uint8_t digit_9[][DIGIT_W];
  
extern const  uint8_t ArrowOUT[][ARROW_SIZE];
extern const  uint8_t ArrowIN[][ARROW_SIZE];
extern const  uint8_t PhantomPict[][PICTOGRAM_W];
extern const  uint8_t RadioPict[][PICTOGRAM_W];
extern const  uint8_t AnalogPict[][PICTOGRAM_W];

extern const  uint8_t black_dot_3pix[][5];

extern const uint32_t interpreterSpeakBackground[];
extern const uint32_t interpreterMuteBackground[];
extern const uint32_t pictBackground[];
extern const uint32_t clockBackground[];

#endif  //_TFT_H