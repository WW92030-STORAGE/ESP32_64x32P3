// Original library and code base - https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-I2S-DMA
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

// The matrix panel is usually always called matrixpanel. This needs to be in all codes using the above library
MatrixPanel_I2S_DMA *matrixpanel = nullptr;

// Basic operations

double rng() { // Random real number [0, 1)
  return rand() / (RAND_MAX + 1.0);
}

double runif(double a, double b) { // Random real number [a, b)
  return (rng() * (b - a)) + a;
}

uint16_t protogen() { // Random hex color in color formats
  return matrixpanel->color565((int)runif(0, 256), (int)runif(0, 256), (int)runif(0, 256));
}

uint16_t protogenfullhue() { // Random hex hue at full brightness and full saturation
  int red = 0;
  int green = 0;
  int blue = 0;
  int partition = (int)runif(0, 255);
  int pos = (int)runif(0, 6);
  switch (pos) {
    case 0:
      return matrixpanel->color565(255, partition, 0);
    case 1:
      return matrixpanel->color565(255 - partition, 255, 0);
    case 2:
      return matrixpanel->color565(0, 255, partition);
    case 3:
      return matrixpanel->color565(0, 255 - partition, 255);
    case 4:
      return matrixpanel->color565(partition, 0, 255);
    default:
      return matrixpanel->color565(255, 255 - partition, 0);
  }
}



// Example template program

const int n = 32;
const int m = 64;

bool grid[n][m]; // 
uint16_t col[n][m]; // Grid of colors

void disp() { // Display the colors in col based on the bitmask provided by grid
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j]) matrixpanel->drawPixel(j, i, col[i][j]);
      else matrixpanel->drawPixel(j, i, matrixpanel->color565(0, 0, 0));
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  HUB75_I2S_CFG mxconfig(m, n, 1);

  mxconfig.gpio.e = 18;
  mxconfig.clkphase = false;
  mxconfig.driver = HUB75_I2S_CFG::FM6126A;

  // Display Setup
  matrixpanel = new MatrixPanel_I2S_DMA(mxconfig);
  matrixpanel->setLatBlanking(2);
  matrixpanel->begin();
  matrixpanel->clearScreen();
  matrixpanel->setBrightness8(64);
  
  for (int i = 0; i < n; i++) { // Go through the matrix
    for (int j = 0; j < m; j++) {
      grid[i][j] = true; // Enables all LEDs to show color (provided this color is visible)
      col[i][j] = protogen(); // Sets a random color to each slot in the matrix
    }
  }
  disp(); // Display the contents of col in accordance to the bitmask grid
}

void loop() {

}

