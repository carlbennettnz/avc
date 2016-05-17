#ifndef __SENSORS_H_INCLUDED__
#define __SENSORS_H_INCLUDED__

#include <tuple>
#include <iostream>
#include <algorithm>

#include "utils.hpp"

extern "C" int take_picture();
extern "C" char get_pixel(int x, int y, int color);

class Sensors {
 public:
  void init(double = 240, double = 160);
  void process_image();
  bool could_find_line_ahead();
  bool could_find_line_left();
  bool could_find_line_right();
  double get_line_error();
  // void get_ir_position();
  double line_error;
 
 private:
  std::tuple<bool, double> get_error_from_row(int rowIndex);
  std::tuple<bool, double> get_error_from_col(int colIndex);
  int img_width;
  int img_height;
  int brightness_threshold;
  bool found_line_ahead;
  bool found_line_left;
  bool found_line_right;
};

#endif
