#ifndef __BRAIN_H_INCLUDED__
#define __BRAIN_H_INCLUDED__

#include <utility> // std::pair
#include <sys/time.h>
#include <iostream>

class Brain {
  public:
    void init(double kp, double ki, double kd);
    std::pair<double, double> choose_velocities(double error);
    std::pair<double, double> choose_velocities_pid(double error);

  private:
    double has_run_once = false;
    double kp;
    double ki;
    double kd;
    double last_error_value;
    double total_error = 0;
    long last_error_time;
};

#endif
