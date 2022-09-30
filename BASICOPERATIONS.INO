// The matrix panel is usually always called matrixpanel

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
