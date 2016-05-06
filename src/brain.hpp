#ifndef __BRAIN_H_INCLUDED__
#define __BRAIN_H_INCLUDED__

#include <utility> // std::pair
#include <sys/time.h>

class Brain {
  public:
    void init(double kp, double kd);
    std::pair<double, double> choose_velocities(double error);
    std::pair<double, double> choose_velocities_pid(double error);

  private:
    double has_run_once = false;
    double kp;
    double kd;
    double last_error_value;
    suseconds_t last_error_time;
};

#endif
