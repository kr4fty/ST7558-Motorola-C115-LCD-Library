# ST7558
 
 
ST7558 lcd library for Arduino


Motorola C115 Display, chipset ST7558, compatible with:

     Motorola C113/C115/C116/C118/C123
     
## Pinouts
	Lcd chip: ST7558 - Wintek Lcd
	Resolution: 94x64
	Technology: FSTN
	I2C write address: 0x78 - (0x3C with *Wire* arduino funtion)

    Pin1 Vdd +2.8V              .-----------------------------.
    Pin2 Res (n/c)              |                             |
    Pin3 Sclk                   |        Motorola C115        |
    Pin4 Sdat                   |            102x65           |
    Pin5 A0 (Gnd)               |       (visible 94x64)       |
    Pin6 Gnd                    '-----------------------------'
    Pin7 Vlcd +12V                   |  |  |  |  |  |  |  |
    Pin8 Reset                       1  2  3  4  5  6  7  8 

## Basic connection

<p align="center">
  <br><br>
  <img src="https://github.com/kr4fty/ST7558-Motorola-C115-LCD-Library/blob/master/c115.png">
  <br>
</p>

## Bidirectional 5v-3.3v level shifter

<p align="center">
  <br><br>
  <img src="https://github.com/kr4fty/ST7558-Motorola-C115-LCD-Library/blob/master/levelShifter.png">
  <br>
</p>


## Video

<p align="center">
  <br><br>
  <a href="https://www.youtube.com/watch?v=zOoVFpy9CIY">
  <img src="https://img.youtube.com/vi/zOoVFpy9CIY/0.jpg">
  <br>
</p>

### Author
Tapia Favio <technicc@gmail.com>
