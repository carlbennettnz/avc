#ifndef __IR_H_INCLUDED__
#define __IR_H_INCLUDED__

#include <iostream>

extern "C" int read_analog(int pin); 

class IR {
  public:
    void init(int, int);
    bool can_see_walls();
    int get_left();
    int get_right();
    int get_front();
    int get_wall_error();
    int get_left_wall_error();
    int get_right_wall_error();

  private:
    int left_chan;
    int right_chan;
    bool could_see_wall;
    int could_see_wall_count;

    int num_readings = 2;
};

#endif
