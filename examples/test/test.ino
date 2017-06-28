/*********************************************************************
This is an example sketch for our Monochrome Motorola C115 LCD Displays

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
#include <avr/pgmspace.h>
#include <Adafruit_GFX.h>
#include <ST7558.h>
#include <Wire.h>

#define RST A0
ST7558 lcd = ST7558(RST);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup()   {
  Serial.begin(9600);
  Serial.println("Iniciando...");

  Wire.begin();
  lcd.init();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  
  lcd.setContrast(65);
  lcd.display(); // show splashscreen
  delay(2000);
  lcd.clearDisplay();   // clears the screen and buffer

  // draw a single pixel
  lcd.drawPixel(10, 10, BLACK);
  lcd.display();
  delay(2000);
  lcd.clearDisplay();

  // draw many lines
  testdrawline();
  lcd.display();
  delay(2000);
  lcd.clearDisplay();

  // draw rectangles
  testdrawrect();
  lcd.display();
  delay(2000);
  lcd.clearDisplay();

  // draw multiple rectangles
  testfillrect();
  lcd.display();
  delay(2000);
  lcd.clearDisplay();

  // draw mulitple circles
  testdrawcircle();
  lcd.display();
  delay(2000);
  lcd.clearDisplay();

  // draw a circle, 10 pixel radius
  lcd.fillCircle(lcd.width()/2, lcd.height()/2, 10, BLACK);
  lcd.display();
  delay(2000);
  lcd.clearDisplay();

  testdrawroundrect();
  delay(2000);
  lcd.clearDisplay();

  testfillroundrect();
  delay(2000);
  lcd.clearDisplay();

  testdrawtriangle();
  delay(2000);
  lcd.clearDisplay();
   
  testfilltriangle();
  delay(2000);
  lcd.clearDisplay();

  // draw the first ~12 characters in the font
  testdrawchar();
  lcd.display();
  delay(2000);
  lcd.clearDisplay();

  // text display tests
  lcd.setTextSize(1);
  lcd.setTextColor(BLACK);
  lcd.setCursor(0,0);
  lcd.println("Hello, world!");
  lcd.setTextColor(BLACK); // 'inverted' text
  lcd.println(3.141592);
  lcd.setTextSize(2);
  lcd.setTextColor(BLACK);
  lcd.print("0x"); lcd.println(0xDEADBEEF, HEX);
  lcd.display();
  delay(2000);

  // rotation example
  lcd.clearDisplay();
  lcd.setRotation(1);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
  lcd.setTextSize(1);
  lcd.setTextColor(BLACK);
  lcd.setCursor(0,0);
  lcd.println("Rotation");
  lcd.setTextSize(2);
  lcd.println("Example!");
  lcd.display();
  delay(2000);

  // revert back to no rotation
  lcd.setRotation(0);

  // miniature bitmap display
  lcd.clearDisplay();
  lcd.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, BLACK);
  lcd.display();

  // invert the display
  lcd.invertDisplay(true);
  delay(1000); 
  lcd.invertDisplay(false);
  delay(1000); 

  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_WIDTH, LOGO16_GLCD_HEIGHT);
}


void loop() {
  
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
  randomSeed(666);     // whatever seed
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(lcd.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      lcd.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, BLACK);
    }
    lcd.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      lcd.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, WHITE);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > lcd.height()) {
	icons[f][XPOS] = random(lcd.width());
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}


void testdrawchar(void) {
  lcd.setTextSize(1);
  lcd.setTextColor(BLACK);
  lcd.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    lcd.write(i);
    //if ((i > 0) && (i % 14 == 0))
      //lcd.println();
  }    
  lcd.display();
}

void testdrawcircle(void) {
  for (int16_t i=0; i<lcd.height(); i+=2) {
    lcd.drawCircle(lcd.width()/2, lcd.height()/2, i, BLACK);
    lcd.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<lcd.height()/2; i+=3) {
    // alternate colors
    lcd.fillRect(i, i, lcd.width()-i*2, lcd.height()-i*2, color%2);
    lcd.display();
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(lcd.width(),lcd.height())/2; i+=5) {
    lcd.drawTriangle(lcd.width()/2, lcd.height()/2-i,
                     lcd.width()/2-i, lcd.height()/2+i,
                     lcd.width()/2+i, lcd.height()/2+i, BLACK);
    lcd.display();
  }
}

void testfilltriangle(void) {
  uint8_t color = BLACK;
  for (int16_t i=min(lcd.width(),lcd.height())/2; i>0; i-=5) {
    lcd.fillTriangle(lcd.width()/2, lcd.height()/2-i,
                     lcd.width()/2-i, lcd.height()/2+i,
                     lcd.width()/2+i, lcd.height()/2+i, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    lcd.display();
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<lcd.height()/2-2; i+=2) {
    lcd.drawRoundRect(i, i, lcd.width()-2*i, lcd.height()-2*i, lcd.height()/4, BLACK);
    lcd.display();
  }
}

void testfillroundrect(void) {
  uint8_t color = BLACK;
  for (int16_t i=0; i<lcd.height()/2-2; i+=2) {
    lcd.fillRoundRect(i, i, lcd.width()-2*i, lcd.height()-2*i, lcd.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    lcd.display();
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<lcd.height()/2; i+=2) {
    lcd.drawRect(i, i, lcd.width()-2*i, lcd.height()-2*i, BLACK);
    lcd.display();
  }
}

void testdrawline() {  
  for (int16_t i=0; i<lcd.width(); i+=4) {
    lcd.drawLine(0, 0, i, lcd.height()-1, BLACK);
    lcd.display();
  }
  for (int16_t i=0; i<lcd.height(); i+=4) {
    lcd.drawLine(0, 0, lcd.width()-1, i, BLACK);
    lcd.display();
  }
  delay(250);
  
  lcd.clearDisplay();
  for (int16_t i=0; i<lcd.width(); i+=4) {
    lcd.drawLine(0, lcd.height()-1, i, 0, BLACK);
    lcd.display();
  }
  for (int8_t i=lcd.height()-1; i>=0; i-=4) {
    lcd.drawLine(0, lcd.height()-1, lcd.width()-1, i, BLACK);
    lcd.display();
  }
  delay(250);
  
  lcd.clearDisplay();
  for (int16_t i=lcd.width()-1; i>=0; i-=4) {
    lcd.drawLine(lcd.width()-1, lcd.height()-1, i, 0, BLACK);
    lcd.display();
  }
  for (int16_t i=lcd.height()-1; i>=0; i-=4) {
    lcd.drawLine(lcd.width()-1, lcd.height()-1, 0, i, BLACK);
    lcd.display();
  }
  delay(250);

  lcd.clearDisplay();
  for (int16_t i=0; i<lcd.height(); i+=4) {
    lcd.drawLine(lcd.width()-1, 0, 0, i, BLACK);
    lcd.display();
  }
  for (int16_t i=0; i<lcd.width(); i+=4) {
    lcd.drawLine(lcd.width()-1, 0, i, lcd.height()-1, BLACK); 
    lcd.display();
  }
  delay(250);
}
