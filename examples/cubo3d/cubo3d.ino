/******************************************************************************
 * Cubo 3D basado en en ejemplo de la libreria Arduino-tvout 
 * 		<https://code.google.com/p/arduino-tvout/>
 * 
 * ***************************************************************************/

#include <avr/pgmspace.h>
#include <math.h>
#include <Adafruit_GFX.h>
#include <ST7558.h>
#include <Wire.h>

#define RST_PIN 7

ST7558 lcd = ST7558(RST_PIN);

int zOff = 150;
int xOff = 0;
int yOff = 0;
int cSize = 50;
int view_plane = 36;
float angle = PI/60;

float cube3d[8][3] = {
  {xOff - cSize,yOff + cSize,zOff - cSize},
  {xOff + cSize,yOff + cSize,zOff - cSize},
  {xOff - cSize,yOff - cSize,zOff - cSize},
  {xOff + cSize,yOff - cSize,zOff - cSize},
  {xOff - cSize,yOff + cSize,zOff + cSize},
  {xOff + cSize,yOff + cSize,zOff + cSize},
  {xOff - cSize,yOff - cSize,zOff + cSize},
  {xOff + cSize,yOff - cSize,zOff + cSize}
};
unsigned char cube2d[8][2];

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);

  Wire.begin();
  
  lcd.init();
  lcd.setContrast(65);
  lcd.setRotation(0);
  
  lcd.clearDisplay();
  lcd.display();
  delay(500);
}

void loop() {
int rsteps = random(10,60);
  switch(random(6)) {
    case 0:
      for (int i = 0; i < rsteps; i++) {
        zrotate(angle);
        printcube();
      }
      break;
    case 1:
      for (int i = 0; i < rsteps; i++) {
        zrotate(2*PI - angle);
        printcube();
      }
      break;
    case 2:
      for (int i = 0; i < rsteps; i++) {
        xrotate(angle);
        printcube();
      }
      break;
    case 3:
      for (int i = 0; i < rsteps; i++) {
        xrotate(2*PI - angle);
        printcube();
      }
      break;
    case 4:
      for (int i = 0; i < rsteps; i++) {
        yrotate(angle);
        printcube();
      }
      break;
    case 5:
      for (int i = 0; i < rsteps; i++) {
        yrotate(2*PI - angle);
        printcube();
      }
      break;
  }
}

void printcube() {
  //calculate 2d points
  for(byte i = 0; i < 8; i++) {
    cube2d[i][0] = (unsigned char)((cube3d[i][0] * view_plane / cube3d[i][2]) + (lcd.width()/2));
    cube2d[i][1] = (unsigned char)((cube3d[i][1] * view_plane / cube3d[i][2]) + (lcd.height()/2));
  }
  lcd.clearDisplay();
  draw_cube();
}

void zrotate(float q) {
  float tx,ty,temp;
  for(byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    ty = cube3d[i][1] - yOff;
    temp = tx * cos(q) - ty * sin(q);
    ty = tx * sin(q) + ty * cos(q);
    tx = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][1] = ty + yOff;
  }
}

void yrotate(float q) {
  float tx,tz,temp;
  for(byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    tz = cube3d[i][2] - zOff;
    temp = tz * cos(q) - tx * sin(q);
    tx = tz * sin(q) + tx * cos(q);
    tz = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][2] = tz + zOff;
  }
}

void xrotate(float q) {
  float ty,tz,temp;
  for(byte i = 0; i < 8; i++) {
    ty = cube3d[i][1] - yOff;
    tz = cube3d[i][2] - zOff;
    temp = ty * cos(q) - tz * sin(q);
    tz = ty * sin(q) + tz * cos(q);
    ty = temp;
    cube3d[i][1] = ty + yOff;
    cube3d[i][2] = tz + zOff;
  }
}

void draw_cube() {
  lcd.drawLine(cube2d[0][0],cube2d[0][1],cube2d[1][0],cube2d[1][1],ST7558_BLACK);
  lcd.drawLine(cube2d[0][0],cube2d[0][1],cube2d[2][0],cube2d[2][1],ST7558_BLACK);
  lcd.drawLine(cube2d[0][0],cube2d[0][1],cube2d[4][0],cube2d[4][1],ST7558_BLACK);
  lcd.drawLine(cube2d[1][0],cube2d[1][1],cube2d[5][0],cube2d[5][1],ST7558_BLACK);
  lcd.drawLine(cube2d[1][0],cube2d[1][1],cube2d[3][0],cube2d[3][1],ST7558_BLACK);
  lcd.drawLine(cube2d[2][0],cube2d[2][1],cube2d[6][0],cube2d[6][1],ST7558_BLACK);
  lcd.drawLine(cube2d[2][0],cube2d[2][1],cube2d[3][0],cube2d[3][1],ST7558_BLACK);
  lcd.drawLine(cube2d[4][0],cube2d[4][1],cube2d[6][0],cube2d[6][1],ST7558_BLACK);
  lcd.drawLine(cube2d[4][0],cube2d[4][1],cube2d[5][0],cube2d[5][1],ST7558_BLACK);
  lcd.drawLine(cube2d[7][0],cube2d[7][1],cube2d[6][0],cube2d[6][1],ST7558_BLACK);
  lcd.drawLine(cube2d[7][0],cube2d[7][1],cube2d[3][0],cube2d[3][1],ST7558_BLACK);
  lcd.drawLine(cube2d[7][0],cube2d[7][1],cube2d[5][0],cube2d[5][1],ST7558_BLACK);

  lcd.display();
}

