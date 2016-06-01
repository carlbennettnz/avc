#ifndef __MOTOR_H_INCLUDED__
#define __MOTOR_H_INCLUDED__

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>

#include "utils.hpp"

extern "C" int set_motor(int motor, int speed);

class Motors {
  public:
    void init(double min_speed, double max_speed, double left_coef, double right_coef);
    void set_velocities(double, double, bool = false);
    void stop_all();

  private:
    double forward_speed;
    double turning_speed;
    double min_speed;
    double max_speed;
    double left_multiplier;
    double right_multiplier;
    double speed_range;
    bool doDonuts;

    void update();
};

#endif