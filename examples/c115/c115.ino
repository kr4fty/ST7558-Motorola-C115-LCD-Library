#include <Adafruit_GFX.h>
#include <ST7558.h>
#include <Wire.h>

#define RST_PIN 7

ST7558 lcd = ST7558(RST_PIN);

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  
  Wire.begin();
  
  lcd.init();
  lcd.fillScreen(ST7558_BLACK);
  lcd.invertDisplay(false);  
  
  
  lcd.drawFastHLine(0, 32, 96, ST7558_BLACK);
  lcd.drawFastVLine(48, 0, 65, ST7558_BLACK);
  lcd.drawCircle(48, 32, 20, ST7558_BLACK);
  lcd.drawRect(28, 12, 40, 40, ST7558_BLACK);
  lcd.drawTriangle(48, 12, 28, 52, 68, 52, ST7558_BLACK);
  
  lcd.setCursor(15, 5);
  //lcd.setTextSize(2);
  
  lcd.setTextColor(ST7558_BLACK);
  lcd.print("Hello World!");
  delay(2000);
  
  extern const uint8_t utn_bits[];
  lcd.drawBitmap(0, 0, utn_bits, ST7558_WIDTH, ST7558_HEIGHT, ST7558_BLACK);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //lcd.drawCircle(random(96), random(64), random(32), ST7558_BLACK);
  //delay(100);
  //lcd.drawRect(random(96), random(64), random(48), random(32), ST7558_BLACK);
  //delay(100);
  //lcd.drawTriangle(random(96), random(64), random(96), random(64), random(96), random(64), ST7558_BLACK);
  //delay(100);
  
  lcd.invertDisplay(true); 
  delay(500);
  lcd.invertDisplay(false); 
  delay(500);
}
