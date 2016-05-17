#ifndef __PID_H_INCLUDED__
#define __PID_H_INCLUDED__

#include <iostream>
#include "utils.hpp"

class PID {
  public:
    void init(double kp, double ki, double kd);
    double calc(double error);

  private:
    double kp;
    double ki;
    double kd;
    double last_error_value;
    double last_error_time = 0;
    double total_error;
};

#endif
