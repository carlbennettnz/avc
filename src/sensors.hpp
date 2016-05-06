#ifndef __SENSORS_H_INCLUDED__
#define __SENSORS_H_INCLUDED__

#include <algorithm>

#include "utils.hpp"

extern "C" int take_picture();
extern "C" char get_pixel(int x, int y, int color);

class Sensors {
 public:
  void init(double = 240, double = 160);
  double get_line_error();
  double get_line_error_2();
  // void get_ir_position();
 
 private:
  int img_width;
  int img_height;
};

#endif
