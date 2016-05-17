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
void Sensors::process_image() {
  take_picture();

  // The color value above which the pixel is considered white
  int expected_mid = 140;
  int error = 0;

  found_line = false;

  for (int x = 0; x < img_width; x++) {
    if (get_pixel(x, img_height / 2, 3) > expected_mid) {
      found_line = true;
      error += x - (img_width / 2);
    }
  }

  // Normalise the error so -1 < err < 1
  line_error = (double) error / img_width / (img_width / 2);
}

double Sensors::get_line_error() {
  return line_error;
}

bool Sensors::could_find_line() {
  return found_line;
}
