#ifndef _ST7558_H
#define _ST7558_H

#define ST7558_WIDTH    102  // 94 visibles
#define ST7558_HEIGHT   65    // 64 visibles

#define ST7558_BLACK    0
#define ST7558_WHITE    1

#define I2C_ADDR_DISPLAY  0x3C

#define MORE_CONTROL        0x80
#define CONTROL_RS_RAM     0x40
#define CONTROL_RS_CMD     0x00


class ST7558 : public Adafruit_GFX{

  public:
 
    ST7558(uint8_t rst=-1);
    
    void init(void),
           drawPixel(int16_t posX, int16_t posY,  uint16_t color),
           drawFastVLine(int16_t x, int16_t y, int16_t h,  uint16_t color),
           drawFastHLine(int16_t x, int16_t y, int16_t w,  uint16_t color),
           fillScreen(uint16_t color),
           fillRect(int16_t x, int16_t y, int16_t w, int16_t h,  uint16_t color),
           invertDisplay(boolean i),
           drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h,
                               uint16_t color) ;
           
 
  private:
    void i2cwrite(const uint8_t *data, uint8_t len),
            hwReset(void),
            displayOff(void),
            setAddrXY(uint8_t x, uint8_t pageY);

    uint8_t _rst,
                _ram[ST7558_WIDTH][9],  // 102x65
                colstart, rowstart;
    
};

#endif