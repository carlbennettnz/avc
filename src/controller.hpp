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
    void check();

  private:
    void follow_line();

    Sensors* sensors;
    Actuators* actuators;
    PID* line_pid;

    std::string stage = "line";

    // Line following
    double line_error;
};

#endif
