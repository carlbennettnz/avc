#include "sensors.hpp"

/**
  Stores the image dimensions for later use.
*/
void Sensors::init(double width, double height) {
  img_width = width;
  img_height = height;
  brightness_threshold = 140;
}

/**
  Performs an extremely basic error calculation, simply taking data from the
  middle line of pixels and finding the brightness on the left side verses the
  right.
*/
void Sensors::process_image() {
  take_picture();

  auto ahead = get_error_from_row(img_height / 2);
  auto left  = get_error_from_col(10);
  auto right = get_error_from_col(img_width - 10);
  
  found_line_ahead = std::get<0>(ahead);
  found_line_left  = std::get<0>(left);
  found_line_right = std::get<0>(right);
  line_error = std::get<1>(ahead);
}

double Sensors::get_line_error() {
  return line_error;
}

bool Sensors::could_find_line_ahead() { return found_line_ahead; }
bool Sensors::could_find_line_left()  { return found_line_left;  }
bool Sensors::could_find_line_right() { return found_line_right; }

std::tuple<bool, double> Sensors::get_error_from_row(int rowIndex) {
  bool found_line = false;
  double error = 0;

  for (int x = 0; x < img_width; x++) {
    if (get_pixel(x, rowIndex, 3) > brightness_threshold) {
      found_line = true;
      error += x - (img_width / 2);
    }
  }

  // Normalise the error so -1 < err < 1
  error = error / img_width / (img_width / 2);

  return std::make_tuple(found_line, error);
}

std::tuple<bool, double> Sensors::get_error_from_col(int colIndex) {
  bool found_line = false;
  double error = 0;

  for (int y = 0; y < img_height; y++) {
    if (get_pixel(y, colIndex, 3) > brightness_threshold) {
      found_line = true;
      error += y - (img_height / 2);
    }
  }

  // Normalise the error so -1 < err < 1
  error = error / img_height / (img_height / 2);

  return std::make_tuple(found_line, error);
}
