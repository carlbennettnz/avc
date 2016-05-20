#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include <tuple>
#include <iostream>
#include <algorithm>

#include "utils.hpp"

extern "C" int take_picture();
extern "C" char get_pixel(int x, int y, int color);

class Camera {
 public:
  void init(double, double, int);
  void process_image();
  bool could_find_line_ahead();
  bool could_find_line_left();
  bool could_find_line_right();
  double get_line_error();
  bool can_see_red();

  void print_image();
 private:
  double get_average_brightness(int color = 3);
  void get_row(double row[], int rowIndex, int spread = 0);
  void get_col(double col[], int colIndex, int spread = 0);
  std::tuple<bool, double> get_error_from_array(double pixels[], int array_size, double average_brightness);

  int img_width;
  int img_height;
  int brightness_threshold;
  double line_error;
  bool found_line_ahead;
  bool found_line_left;
  bool found_line_right;
};

#endif
