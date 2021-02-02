#include "include.h"
#include "TFT.h"

void TFT::initController(spim &rSPI)
{
    const char settings[15]   = {0x00, 0x04, 0x06, 0x00, 0x0F, 0x0A, 0x38, 0x9B, 0x49, 0x09, 0x06, 0x0B, 0x1D, 0x1E, 0x0F};
    const char settings_2[15] = {0x00, 0x21, 0x22, 0x04, 0x09, 0x06, 0x36, 0x46, 0x47, 0x05, 0x10, 0x0F, 0x39, 0x3B, 0x0F};
    const char settings_3[15] = {0x80, 0xA0, 0x02, 0x17, 0x15, 0x41, 0x00, 0x12, 0x80, 0x02, 0x48, 0x66, 0x00, 0x04, 0x00};
    const char settings_4[4] = {0xA9, 0x51, 0x2C, 0x82};

    _pSPI = &rSPI;
    _pSPI->init(8000);

	_pSPI->reset_active();
    delay_ms(6);
	_pSPI->reset_clear();
    delay_ms(30);
	_pSPI->reset_active();
    delay_ms(600);
	
	writeCmd(POS_GAMMA_CTRL).transferData(settings,sizeof(settings));
    
    //Negative Gamma Control
	writeCmd(NEG_GAMMA_CTRL).transferData(settings_2,sizeof(settings_2));   
   
	writeCmd(IFACE_MODE_CTRL        ).transferData(&settings_3[0], 1);
	writeCmd(FRAME_RATE_MODE_CTRL	).transferData(&settings_3[1], 1);
	writeCmd(DISP_INVERSION_CTRL 	).transferData(&settings_3[2], 1);
	writeCmd(POWER_CTRL_1			).transferData(&settings_3[3], 2);
	writeCmd(POWER_CTRL_2			).transferData(&settings_3[5], 1);
	writeCmd(VCOM_CTRL				).transferData(&settings_3[6], 3);
	writeCmd(DISP_FUNCTION_CTRL		).transferData(&settings_3[9], 1);
	writeCmd(MEM_ACC_CTRL			).transferData(&settings_3[10],1);
	writeCmd(IFACE_PIXEL_FORMAT		).transferData(&settings_3[11],1);
	writeCmd(HS_LANES_CTRL			).transferData(&settings_3[12],2);
	writeCmd(SET_IMAGE_CTRL			).transferData(&settings_3[14],1); 
    
	writeCmd(AJUST_CTRL).transferData(settings_4,sizeof(settings_4));//Adjust Control 3

    writeCmd(DISP_INVERSION_ON);      //Display Inversion ON for WF35U(IPS,320x480)    
    writeCmd(SLEEP_OUT);              //Sleep Out
    delay_ms(1);
    writeCmd(DISPLAY_ON);             //Display ON
}

TFT& TFT::writeCmd(char cmd)
{
      unsigned int 	lenght = 8;    
           uint8_t 	paddedBit = 7;
		   uint8_t *pPadded = (uint8_t*)_transferBuffer.get_empty_frame();;   //nine-bit padded buffer 

    _pSPI->select();

    for (*pPadded = 0; lenght; lenght--)
    {   
        if(lenght == 1) 
        {
            // last 8 byte is cmd that we need.
            *pPadded++ |= (LCD_CMD << paddedBit) | (cmd >> (8 - paddedBit));
            *pPadded = cmd << paddedBit;
        } 
        else
        {
            // firstly, we write 7 byte by nop cmd.
            *pPadded++ |= (LCD_CMD << paddedBit) | (TFT_NOP >> (8 - paddedBit));
            *pPadded = TFT_NOP << paddedBit;
        } 
		
		if (--paddedBit == 0xFF)
        {
            paddedBit = 7;
            *(++pPadded) = 0;
        }
    }    

    // wait when prevous dispatch ends, if it need
    // because you cannot switch frames during transmission
     while(_pSPI->getStartEvent()){};
    // switching frames and send complete frame
    _pSPI->isrTransfer((char*)_transferBuffer.switch_frames(), 9);   
    // prepare empty frame for prevous filling with arranged bytes.
    _transferBuffer.clear_empty();

    _pSPI->deselect();

    return *this;   
}

void TFT::transferImage(int x, int y, int16_t w, int16_t h, const uint8_t * symbol, const uint32_t * background)
{     
        CRGB pixel   = CRGB(_get_pixel_from_background(symbol[0], background));
const unsigned int   actuallyByteLength = (unsigned int)(((float)_transferBuffer.get_size() * 8.0f)/9.0f);
      unsigned int   byteToBeSend = (unsigned int)(ceil((((float)(w  * h * 3)) * 9.0f)/8.0f));
      unsigned int   remainder = (w  * h * 3) % 8;
      unsigned int   length;          //must be always multiplycity by 8

      unsigned int   sendSize = _transferBuffer.get_size();        //must be  always multiplycity by 9
           uint8_t   paddedBit;            
           uint8_t  *pPadded;   //nine-bit padded buffer
           uint8_t  *pBuf = &pixel.bgra[2];
		   uint8_t 	i = 0, j = 0;      

    setAddrWindow(x, y, x + w - 1, y + h - 1); 
	
	writeCmd(_MW);	
	
    _pSPI->select();

    while(byteToBeSend)
    {
        pPadded = (uint8_t*)_transferBuffer.get_empty_frame();
        paddedBit = 7;		
        
        if(byteToBeSend > 9)
        {   
            if(byteToBeSend < _transferBuffer.get_size())
            {
                // splitting up the buffer
                length = 8; 
                sendSize = 9;
            }
            else
               length = actuallyByteLength;
            
            byteToBeSend -= sendSize;
        }
        else
        {
            length = remainder;            
            byteToBeSend = 0;
            sendSize = 9;
        }   
        
        // sending the main data value.
        for (*pPadded = 0; length; length--)
        {             
           *pPadded++ |= (LCD_DATA << paddedBit) | (*pBuf >> (8 - paddedBit));
           *pPadded = *pBuf << paddedBit;

            // bypass the alpha channel
            if(pBuf-- == &pixel.bgra[0])
            {			
				//and draw next pixel 
			  	if(j++ == w - 1 )
				{ 
				  	i++; 
				  	j = 0; 
				}	
				
                pixel.raw = _get_pixel_from_background(symbol[i*w + j], background); 
                pBuf = &pixel.bgra[2];
            }

            if (--paddedBit == 0xFF)
            {
                paddedBit = 7;
                *(++pPadded) = 0;
            }
        }       
        
        // comlete buffer last bytes with NOP command if it need
        while(paddedBit != 7)
        {
            //write 7 byte by nop cmd.
           *pPadded++ |= (LCD_CMD << paddedBit) | (TFT_NOP >> (8 - paddedBit));
           *pPadded = TFT_NOP << paddedBit;
            
            if (--paddedBit == 0xFF)
            {
                paddedBit = 7;
                *(++pPadded) = 0;
            }
        }
		
        // wait when prevous dispatch ends, if it need
        // because you cannot switch frames during transmission
        while(_pSPI->getStartEvent()){};
        // switching frames and send complete frame
        _pSPI->isrTransfer((char*)_transferBuffer.switch_frames(),sendSize);   
        // prepare empty frame for prevous filling with arranged bytes.
        _transferBuffer.clear_empty();  
    }

    _pSPI->deselect();    
}

void TFT::transferColor(CRGB &rColor, unsigned int pixNum)
{
const unsigned int  actuallyByteLength = (unsigned int)(((float)_transferBuffer.get_size() * 8.0f)/9.0f);
      unsigned int 	byteToBeSend = (unsigned int)(ceil(((float)(pixNum * 3) * 9.0f)/8.0f));
      unsigned int 	remainder = (pixNum * 3) % 8;
      unsigned int 	length;          //must be always multiplycity by 8
	  unsigned int 	sendSize = _transferBuffer.get_size();		 //must be also always multiplycity by 8
           uint8_t 	paddedBit;     
		   
           uint8_t *pPadded;   //nine-bit padded buffer
           uint8_t *pBuf = &rColor.bgra[2]; 

    _pSPI->select();

    while(byteToBeSend)
    {
        pPadded = (uint8_t*)_transferBuffer.get_empty_frame();
		paddedBit = 7;
		
		if(byteToBeSend > 9)
		{	
		  	if(byteToBeSend < _transferBuffer.get_size())
			{
			  	// splitting up the buffer
			  	length = 8; 
				sendSize = 9;
			}
			else
				length = actuallyByteLength;
			
			byteToBeSend -= sendSize;
		}
        else
		{
		  	length = remainder;			
			byteToBeSend = 0;
			sendSize = 9;
		}	
		
		// sending the main data value.
        for (*pPadded = 0; length; length--)
        {             
            *pPadded++ |= (LCD_DATA << paddedBit) | (*pBuf >> (8 - paddedBit));
            *pPadded = *pBuf << paddedBit;
            
            // bypass the alpha channel
            if(pBuf-- == &rColor.bgra[0])
                pBuf = &rColor.bgra[2];

            if (--paddedBit == 0xFF)
            {
                paddedBit = 7;
                *(++pPadded) = 0;
            }
        }		
		
		// comlete buffer last bytes with NOP command
		while(paddedBit != 7)
		{
		    //write 7 byte by nop cmd.
           *pPadded++ |= (LCD_CMD << paddedBit) | (TFT_NOP >> (8 - paddedBit));
           *pPadded = TFT_NOP << paddedBit;
			
			if (--paddedBit == 0xFF)
            {
                paddedBit = 7;
                *(++pPadded) = 0;
            }
		}

        // wait when prevous dispatch ends, if it need
        // because you cannot switch frames during transmission
        while(_pSPI->getStartEvent()){};
        // switching frames and send complete frame
        _pSPI->isrTransfer((char*)_transferBuffer.switch_frames(),sendSize);   
        // prepare empty frame for prevous filling with arranged bytes.
        _transferBuffer.clear_empty();  
    }

    _pSPI->deselect();
}

void TFT::transferData(const char *data, unsigned int len)
{
      unsigned int byteToBeSend = (unsigned int)(ceil(((float)len * 9.0f)/8.0f));
      unsigned int remainder = len % 8;
      unsigned int length;          //must be always multiplycity by 8
      unsigned int sendSize = _transferBuffer.get_size();        //must be  always multiplycity by 9
           uint8_t paddedBit;     
           
           uint8_t *pPadded;   //nine-bit padded buffer
        const char *pBuf = data;  	
	
    _pSPI->select();

    while(byteToBeSend)
    {
        pPadded = (uint8_t*)_transferBuffer.get_empty_frame();
        paddedBit = 7;
        
        if(byteToBeSend > 9)
        {   
            if(byteToBeSend < _transferBuffer.get_size())
            {
                // splitting up the buffer
                length = 8; 
                sendSize = 9;
            }
            else
                length = _transferBuffer.get_size();
            
            byteToBeSend -= length;
        }
        else
        {
            length = remainder;            
            byteToBeSend = 0;
            sendSize = 9;
        }   
        
        // sending the main data value.
        for (*pPadded = 0; length; length--)
        {             
           *pPadded++ |= (LCD_DATA << paddedBit) | (*pBuf >> (8 - paddedBit));
           *pPadded = *pBuf << paddedBit;
            pBuf++;

            if (--paddedBit == 0xFF)
            {
                paddedBit = 7;
                *(++pPadded) = 0;
            }
        }       
        
        // comlete buffer last bytes with NOP command
        while(paddedBit != 7)
        {
            //write 7 byte by nop cmd.
           *pPadded++ |= (LCD_CMD << paddedBit) | (TFT_NOP >> (8 - paddedBit));
           *pPadded = TFT_NOP << paddedBit;
            
            if (--paddedBit == 0xFF)
            {
                paddedBit = 7;
                *(++pPadded) = 0;
            }
        }

        // wait when prevous dispatch ends, if it need
        // because you cannot switch frames during transmission
        while(_pSPI->getStartEvent()){};
        // switching frames and send complete frame
        _pSPI->isrTransfer((char*)_transferBuffer.switch_frames(),sendSize);   
        // prepare empty frame for prevous filling with arranged bytes.
        _transferBuffer.clear_empty();  
    }

    _pSPI->deselect();
}

void TFT::drawPixel(int x, int y, uint32_t color)
{
    CRGB  rgb(color);
    char *pBuf;

    unsigned int  length = 16;    
         uint8_t  paddedBit = 7;
         uint8_t *pPadded = (uint8_t*)_transferBuffer.get_empty_frame();;   //nine-bit padded buffer 
	        char d[4] = 
   				{
					 (char)(x >> 8),
   					 (char)x,
					 (char)(y >> 8),
					 (char)(y)
   				};
		 
    _pSPI->select();

    for (*pPadded = 0; length; length--)
    {   
        switch(length)
		{
			case 16:
				// setting window first point
            	*pPadded++ |= (LCD_CMD << paddedBit) | (_MC >> (8 - paddedBit));
            	*pPadded = _MC << paddedBit;
				 pBuf = &d[0];
		  	break;
			case 13:
			  	 pBuf = &d[0];
			continue;
			case 10:
				// setting window second point
            	*pPadded++ |= (LCD_CMD << paddedBit) | (_MP >> (8 - paddedBit));
            	*pPadded = _MP << paddedBit;
				 pBuf = &d[2];
		  		break;
			case 7:
			  	 pBuf = &d[2];
			continue;
			case 4:
				// pixel data
            	*pPadded++ |= (LCD_CMD << paddedBit) | (_MW >> (8 - paddedBit));
            	*pPadded = _MW << paddedBit;
				 pBuf =  (char*)&rgb.bgra[2];
		  		break;
			default:
			  	// then  thrilobytes of pixel datat
        		*pPadded++ |= (LCD_DATA << paddedBit) | (*pBuf >> (8 - paddedBit));
        		*pPadded = *pBuf << paddedBit;
		
				if(length <= 3)
        			pBuf--;
				else
				  	pBuf++;
				
				break;
		}
        
        if (--paddedBit == 0xFF)
        {
            paddedBit = 7;
            *(++pPadded) = 0;
        }
    } 

    // comlete buffer last bytes with NOP command
    while(paddedBit != 7)
    {
        //write 7 byte by nop cmd.
       *pPadded++ |= (LCD_CMD << paddedBit) | (TFT_NOP >> (8 - paddedBit));
       *pPadded = TFT_NOP << paddedBit;
        
        if (--paddedBit == 0xFF)
        {
            paddedBit = 7;
            *(++pPadded) = 0;
        }
    }   

    // wait when prevous dispatch ends, if it need
    // because you cannot switch frames during transmission
     while(_pSPI->getStartEvent()){};
    // switching frames and send complete frame
    _pSPI->isrTransfer((char*)_transferBuffer.switch_frames(), 18);   
    // prepare empty frame for prevous filling with arranged bytes.
    _transferBuffer.clear_empty();

    _pSPI->deselect();  

}

void TFT::fillWithColor(uint32_t color)
{
	CRGB col = CRGB(color); 	

    writeCmd(_MW).transferColor(col,_Hight*_Width);
}

void TFT::setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1)
{      
   char d1[4] = 
   {
	 (char)(x >> 8),
   	 (char)x,
	 (char)(x1 >> 8),
	 (char)(x1)
   };
   char d2[4] = 
   {
	 (char)(y >> 8), 
	 (char)y, 
	 (char)(y1 >> 8),
	 (char)y1
   };
	
	writeCmd(_MC).transferData(d1,4);
	writeCmd(_MP).transferData(d2,4); 
}

uint32_t TFT::_get_pixel_from_background(const uint8_t pix, const uint32_t *background)
{
    switch(pix)
    {
        case 1:
          return background[static_cast<uint32_t>(EBackgroundMask::MASK_1)];
        case 2:
          return background[static_cast<uint32_t>(EBackgroundMask::MASK_2)];
        case 3:
          return background[static_cast<uint32_t>(EBackgroundMask::MASK_3)];
        case 4:
          return background[static_cast<uint32_t>(EBackgroundMask::MASK_4)];
        case 5:
          return background[static_cast<uint32_t>(EBackgroundMask::MASK_5)];
        case 0:
        default:
          return background[static_cast<uint32_t>(EBackgroundMask::MASK_0)];
    }
}



