// Original library and code base - https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-I2S-DMA
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <bits/stdc++.h> 
using namespace std;

#include <esp_random.h>

#include "matrices.h"
#include "panels.h"

vector<vector<vector<bool>>> animation{grid0, grid1, grid2, grid3, grid4, grid5, grid6, grid7, grid8};

void setup() {
  matrixsetup();
  disp(grid0);
}

int blinkdelay = 0;
int blinkthreshold = 0;

void loop() {
  uint16_t color = protogenfullhue();
  color = matrixpanel->color565(255, 255, 255);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m * chain; j++) col[i][j] = color;
  }
  delay(100);
  // Serial.println(rand() % 1024);
  disp(grid0);
  
  blinkdelay++;
  if (blinkdelay >= blinkthreshold) {
    blinkdelay = 0;
    blinkthreshold = (int)(runif(64, 256));
    playAnimation(animation, 20, false);
    playAnimation(animation, 20, true);
    dispstats();
  }
}
