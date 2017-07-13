/***************************************************
  This is a library for the ST7558 i2c display.

  These displays use I²C to communicate, 2 or 3 pins are required to
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

#ifndef _ST7558_H
#define _ST7558_H

    #if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
    #else
    #include "WProgram.h"
    #include "pins_arduino.h"
    #endif

    #define ST7558_WIDTH    96  // 94 visibles de 102 (de 0 a 95)
    #define ST7558_HEIGHT   65  // 64 visibles de 65 (de 0 a 64)

    #define BLACK 1
    #define WHITE 0

    #define ST7558_BLACK BLACK
    #define ST7558_WHITE WHITE

    #define I2C_ADDR_DISPLAY  0x3C

    #define MORE_CONTROL       0x80
    #define CONTROL_RS_RAM     0x40
    #define CONTROL_RS_CMD     0x00


    #define ST7558_POWERDOWN 0x04
    #define ST7558_ENTRYMODE 0x02
    #define ST7558_EXTENDEDINSTRUCTION 0x01

    #define ST7558_DISPLAYBLANK 0x0
    #define ST7558_DISPLAYNORMAL 0x4
    #define ST7558_DISPLAYALLON 0x1
    #define ST7558_DISPLAYINVERTED 0x5

    // H = 0
    #define ST7558_FUNCTIONSET 0x20
    #define ST7558_DISPLAYCONTROL 0x08
    #define ST7558_SETYADDR 0x40
    #define ST7558_SETXADDR 0x80

    // H = 1
    #define ST7558_SETTEMP 0x04
    #define ST7558_SETBIAS 0x10
    #define ST7558_SETVOP 0x80


    class ST7558 : public Adafruit_GFX{

    public:
    
        ST7558(uint8_t rst=-1);
        
        void init(void),
             setContrast(uint8_t val),
             clearDisplay(void),
             display(void),
             drawPixel(int16_t posX, int16_t posY,  uint16_t color),
             invertDisplay(boolean i),
             displayOff(void),
             displayOn(void);
    uint8_t  getPixel(int8_t x, int8_t y),
             getPixel(int8_t x, int8_t y, const uint8_t *bitmap, uint8_t w, uint8_t h);
            
    
    private:
        void i2cwrite(uint8_t *data, uint8_t len),
             hwReset(void),
             setAddrXY(uint8_t x, uint8_t pageY);

        uint8_t _rst,
             colstart, rowstart;
        
    };

#endif
