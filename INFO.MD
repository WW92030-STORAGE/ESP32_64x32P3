# INFORMATION

Useful information for working with this code.

# LIBRARIES

Library - [MatrixPanel-DMA](https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-DMA)

Pin values are integers. Integer pin values corresponding to GPIO pins are the same value (e.g. 18 = GPIO 18).<br/><br/>

# HUB75E ASSUMED PINOUT (source: MatrixPanel-DMA Library)

R1 | G1 <br/>
B1 | GND <br/>
R2 | G2 <br/>
B2 | E <br/>
A | B <br/>
C | D <br/>
CLK | LAT <br/>
OE | GND <br/>

# DEFAULT DMA PINS

#define R1_PIN 25 <br/>
#define G1_PIN 26 <br/>
#define B1_PIN 27 <br/>
#define R2_PIN 14 <br/>
#define G2_PIN 12 <br/>
#define B2_PIN 13 <br/>
#define A_PIN 23 <br/>
#define B_PIN 19 <br/>
#define C_PIN 5 <br/>
#define D_PIN 17 <br/>
#define E_PIN 18 // (Normally -1) <br/>
#define LAT_PIN 4 <br/>
#define OE_PIN 15 <br/>
#define CLK_PIN 16 <br/>
