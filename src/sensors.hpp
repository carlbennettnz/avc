#ifndef __SENSORS_H_INCLUDED__
#define __SENSORS_H_INCLUDED__

#include <iostream>
#include <algorithm>

#include "utils.hpp"

extern "C" int take_picture();
extern "C" char get_pixel(int x, int y, int color);

class Sensors {
 public:
  void init(double = 240, double = 160);
  void process_image();
  bool could_find_line();
  double get_line_error();
  // void get_ir_position();
  double line_error;
 
 private:
  int img_width;
  int img_height;
  int found_line;
};

#endif
