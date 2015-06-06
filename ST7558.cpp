/***************************************************
  This is a library for the ST7558 i2c display.

  These displays use I"Cto communicate, 2 or 3 pins are required to
  interface (RST is optional)
  
  Based on the driver written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution

  It depends on libraries Adafruit-GFX

  Author: Tapia Favio: technicc(at)gmail.com
 
 Pinout:
 
	Lcd chip: ST7558 - Wintek Lcd
	Resolution: 94x64
	Technology: FSTN
	I2C write address: 0x78 - (0c3C with Wire arduino funtion)

    Pin1 Vdd +2.8V		+-----------------------------+
    Pin2 Res (n/c)		|                             |
    Pin3 Sclk			|        Motorola C115        |
    Pin4 Sda 			|            102x65           |
    Pin5 A0 (Gnd)		|       (visible 94x64)       |
    Pin6 Gnd			+-----------------------------+
    Pin7 Vlcd +12V		     |  |  |  |  |  |  |  |
    Pin8 Reset			     1  2  3  4  5  6  7  8 

 ****************************************************/

#include <avr/pgmspace.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "ST7558.h"
 #include "Arduino.h"

ST7558::ST7558(uint8_t rst)
 : Adafruit_GFX(ST7558_WIDTH, ST7558_HEIGHT)
{
  _rst  = rst;
}

inline void ST7558::i2cwrite(const uint8_t *data, uint8_t len) {
        
  Wire.beginTransmission(I2C_ADDR_DISPLAY);
  Wire.write(data, len);
  Wire.endTransmission();

}

void ST7558::hwReset(void){
  
  if (_rst) {
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, HIGH);
    delay(500);
    digitalWrite(_rst, LOW);
    delay(500);
    digitalWrite(_rst, HIGH);
    delay(500);
  }
}
  
static const uint8_t 
          cmd_init[]= {CONTROL_RS_CMD, // Bit de Control A0=0
                                0x2E,                       // MXMY
                                0x21,                       // Extend Set H=1
                                0x12,                       // Bias
                                0xC0,                       // VOP
                                0x0B,                       // Boost
                                0x20,                       // Normal Set H=0
                                0x11,                       // PRS
                                0x00,                       // nop
                                0x40,                       // Y addr
                                0x80                        // X addr
	  },
          cmd_invert[]= {CONTROL_RS_CMD, 0x20, 0x0D},
          cmd_on[]= {CONTROL_RS_CMD, 0x20, 0x0C},
          cmd_off[]= {CONTROL_RS_CMD, 0x20, 0x08},
          zero16[] = { CONTROL_RS_RAM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void ST7558::displayOff(void){

  i2cwrite(cmd_off, sizeof(cmd_off));
}

void ST7558::setAddrXY(uint8_t x, uint8_t pageY){

  uint8_t cmdXY[]={CONTROL_RS_CMD, 0x20, colstart+x, rowstart+pageY};  
  
  i2cwrite( cmdXY, sizeof(cmdXY) );
}

void ST7558::init(void) {
  colstart= 0x80;
  rowstart= 0x40;
  
  hwReset();
  
  i2cwrite(cmd_init, sizeof(cmd_init));
  
}

void ST7558::drawPixel(int16_t posX, int16_t posY,  uint16_t color) {
  
   if((posX < 0) ||(posX >= _width) || (posY < 0) || (posY >= _height)) return;
   
  uint8_t posY1, posY2, maskY;
  uint8_t cmdByte[]={CONTROL_RS_RAM, 0};

  posY2= (uint8_t) posY/8;     // Page number in memory
  posY1= (uint8_t) posY%8;   // Bit number into the byte
  
  switch(posY1){
      case 0: maskY=1; break;
      case 1: maskY=2; break;
      case 2: maskY=4; break;
      case 3: maskY=8; break;
      case 4: maskY=16; break;
      case 5: maskY=32; break;
      case 6: maskY=64; break;
      case 7: maskY=128; break;
      default: break;
  }
  
  if(!color)
    _ram[posX][posY2] |= maskY;
  else
    _ram[posX][posY2] &= ~maskY;
  
  setAddrXY(posX, posY2);
  
  cmdByte[1]= _ram[posX][posY2];
  i2cwrite( cmdByte, sizeof(cmdByte) );
}

void ST7558::drawFastVLine(int16_t x, int16_t y, int16_t h,  uint16_t color){
  
  if((x >= _width) || (y >= _height)) return;
  if((y+h-1) >= _height) h = _height-y;
  
  for(uint8_t i=y; i<y+h; i++)
     drawPixel(x, i, color);
}

void ST7558::drawFastHLine(int16_t x, int16_t y, int16_t w,  uint16_t color){
  
  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  
  for(uint8_t i=x; i<x+w; i++)
     drawPixel(i, y, color);
}

void ST7558::fillScreen(uint16_t color) {
  
  for (int i = 0; i < 102*9; i += 16)
    i2cwrite(zero16, sizeof(zero16));
  
}

void ST7558::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
  uint16_t color) {
  
  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;
  
  for(y=h; y>=0; y--) {
    for(x=w; x>=0; x--) {
      drawPixel(x, y, color);
    }
  }
}

void ST7558::invertDisplay(boolean i){
   
   if(i==true)
     i2cwrite(cmd_invert, sizeof(cmd_invert));
   else if(i==false)
     i2cwrite(cmd_on, sizeof(cmd_on));
}

void ST7558::drawBitmap(int16_t x, int16_t y,
            const uint8_t *bitmap, int16_t w, int16_t h,
            uint16_t color) {

  int16_t i, j,k ;
  uint8_t buff[17];
  
  uint8_t cmdXY[]={CONTROL_RS_CMD, 0x20, colstart+x, rowstart+y};
  i2cwrite(cmdXY, sizeof(cmdXY));
  
  
  for (k=i=0; k < 102*9-8; k += 16)
  {    
    buff[0]= 0x40;
    for(j=1; j<17; j++){
      buff[j] = pgm_read_byte(bitmap + i);
      i++;
    }
    i2cwrite(buff, sizeof(buff));
  }
 
}
