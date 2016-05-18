#ifndef __CONTROLLER_H_INCLUDED__
#define __CONTROLLER_H_INCLUDED__

#include <iostream>
#include <string>

#include "sensors.hpp"
#include "actuators.hpp"
#include "pid.hpp"

class Controller {
  public:
    void init(Sensors* s, Actuators* a, PID* l);
    void go();
    void stop();

  private:
    void update_stage();
    void follow_line();
    void navigate_maze();

    Sensors* sensors;
    Actuators* actuators;
    PID* line_pid;

    std::string stage = "line";

    // Line following
    double line_error;
    bool is_turning_left;
    bool is_turning_right;
};

#endif
