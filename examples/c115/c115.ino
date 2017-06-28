/***************************************************

  Simple example using the ST7558 and Adafruit-GFX librarie
  
  Author: Tapia Favio: technicc(at)gmail.com

****************************************************/

#include <avr/pgmspace.h>
#include <Adafruit_GFX.h>
#include <ST7558.h>
#include <Wire.h>

#define RST_PIN 7

ST7558 lcd = ST7558(RST_PIN);

extern const unsigned char flecha[];
extern const unsigned char cara[];
extern const unsigned char logo16[];
extern const unsigned char black[];

int8_t i=88;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
  
  lcd.init();
  lcd.setContrast(65);
  lcd.setRotation(0);
  //lcd.display();
  //delay(1500);
  
  //lcd.clearDisplay();
  //lcd.setTextColor(BLACK);
  //lcd.setCursor(15,0);
  //lcd.print("Hello World!");
  //lcd.display();
  //delay(1500);
  //lcd.clearDisplay();
  //lcd.drawBitmap(70, 0, cara,8, 8, BLACK);
  //lcd.drawBitmap(0, 0, black, 96, 65, BLACK);
  lcd.drawBitmap(69, 0, logo16, 16, 16, BLACK);
  //lcd.drawFastVLine(50, 0, ST7558_HEIGHT, BLACK);
  //grid();
  //delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(i<ST7558_WIDTH){
    lcd.drawBitmap(i, 10, flecha, 16, 8, BLACK);
    lcd.display();
    delay(50);
    lcd.drawBitmap(i, 10, flecha, 16, 8, WHITE);
    i++;
  }
  else
    i=-15;
}

void grid(){
  uint8_t x, y;
  lcd.clearDisplay();
  for(x=0; x<ST7558_WIDTH; x+=5)
    for(y=0; y<ST7558_WIDTH; y+=5)
      lcd.drawPixel(x, y, BLACK);
  lcd.display();
}

