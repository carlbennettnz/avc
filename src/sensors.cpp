#include "sensors.hpp"

/**
  Stores the image dimensions for later use.
*/
void Sensors::init(double width, double height) {
  img_width = width;
  img_height = height;
}

/**
  Performs an extremely basic error calculation, simply taking data from the
  middle line of pixels and finding the brightness on the left side verses the
  right.
*/
double Sensors::get_line_error() {
  take_picture();

  // The color value above which the pixel is considered white
  int expected_mid = 140;
  int error = 0;

  for (int x = 0; x < img_width; x++) {
    if (get_pixel(x, img_height / 2, 3) > expected_mid) {
      error += x - (img_width / 2);
    }
  }

  // Normalise the error so -1 < err < 1
  return (double) error / img_width / (img_width / 2);
}

/**
  A more complicated error calculation. Work in progress.
*/
double Sensors::get_line_error_2() {
  take_picture();

  double expected_low = 0;
  double expected_high = 255;

  double p[img_height][img_width];
  // double maxP[img_height];
  // double maxX[img_height];

  for (int y = 0; y < img_height; y++) {
    // Probability of this pixel being the center of the line
    double sumP = 0;
    
    for (int x = 0; x < img_width; x++) {
      // Trying to find the probability that a pixel is the center of the line
      int range = std::min(x, img_width - x);
      int half_range = range / 2;
      double left = 0;
      double right = 0;
      
      for (int z = 0; z < range; z++) {
        double value = get_pixel(y, x + z - half_range, 3);
        constrain(expected_low, expected_high, &value);
        
        if (z < half_range) left += value;
        if (z > half_range) right += value;
      }

      p[y][x] = std::min(left, right);
      sumP += p[y][x];
    }

    int max = 0;

    for (int x = 0; x < img_width; x++) {
      // Normalise p so it sums to 1
      p[y][x] *= img_width / sumP;

      // Track the highest value
      if (p[y][x] > p[y][max]) {
        max = x;
      }
    }

    // maxP[y] = p[y][max];
    // maxX[y] = max;
  }

  return 0;
}