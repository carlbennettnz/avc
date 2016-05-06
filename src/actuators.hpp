#ifndef __ACTUATORS_H_INCLUDED__
#define __ACTUATORS_H_INCLUDED__

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include "utils.hpp"

extern "C" int set_motor(int motor, int speed);

class Actuators {
  public:
    void init(double = 0, double = 255, double = 1, double = 1);
    void set_velocities(double, double);
    void stop_all();

  private:
    double forward_speed;
    double turning_speed;
    double min_speed;
    double max_speed;
    double left_multiplier;
    double right_multiplier;
    double speed_range;
    void update();
};

#endif