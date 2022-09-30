// Original library and code base - https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-I2S-DMA
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
 
//MatrixPanel_I2S_DMA matrixpanel;
MatrixPanel_I2S_DMA *matrixpanel = nullptr;


const int n = 64;
const int m = 32;
bool grid[n][m];
uint16_t col[n][m];

bool isPrime(int n)
{
  if (n <= 1) return false;
  for (int i = 2; i * i < 1.5 * n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

bool inBounds(int x, int y) {
  if (x < 0 || x >= n) return false;
  if (y < 0 || y >= m) return false;
  return true;
}

void setup() {

  // Module configuration
  HUB75_I2S_CFG mxconfig(n, m, 1);

  mxconfig.gpio.e = 18;
  mxconfig.clkphase = false;
  mxconfig.driver = HUB75_I2S_CFG::FM6126A;

  // Display Setup
  matrixpanel = new MatrixPanel_I2S_DMA(mxconfig);
  matrixpanel->setLatBlanking(2);
  matrixpanel->begin();
  matrixpanel->setBrightness8(64); //0-255
  matrixpanel->clearScreen();

  // Initial configuration, you can set grid to whatever you want
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      grid[i][j] = isPrime(n * j + i);
    }
  } 
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int color = grid[i][j] ? 255 : 0;
      matrixpanel->drawPixel(i, j, matrixpanel->color565(color, color, color));
    }
  }

}

int dx[8] = {01, 01, 00, -1, -1, -1, 00, 01};
int dy[8] = {00, 01, 01, 01, 00, -1, -1, -1};

void loop() { // Update function (cuts off at borders)
  bool grid2[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int count = 0;
      for (int k = 0; k < 8; k++) {
        int xp = i + dx[k];
        int yp = j + dy[k];
        if (!inBounds(xp, yp)) continue;
        if (grid[xp][yp]) count++;
      }
      if (count < 2) grid2[i][j] = false;
      if (count == 3 && !grid[i][j]) grid2[i][j] = true;
      if ((count == 2 || count == 3) && grid[i][j]) grid2[i][j] = true;
      if (count > 3) grid2[i][j] = false;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) grid[i][j] = grid2[i][j];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int color = grid[i][j] ? 255 : 0;
      matrixpanel->drawPixel(i, j, matrixpanel->color565(color, color, color));
    }
  }
  delay(100);
}
