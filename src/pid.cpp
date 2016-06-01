#include "pid.hpp"

void PID::init(double p, double i, double d) {
  kp = p;
  ki = i;
  kd = d;
}

double PID::calc(double error) {
  long error_time = get_time();
  double p = error;
  double d;

  // If this is our first error reading, we can't calculate the rate of change
  // of the error, so just assume it's zero.
  if (last_error_time != 0) {
    d = (error - last_error_value) / (error_time - last_error_time) * 1000 * 1000;
    total_error += error / (error_time - last_error_time) * 1000 * 1000;
  } else {
    d = 0;
  }

  // Record the error and time for next time
  last_error_value = error;
  last_error_time = error_time;

  double i = total_error;

  std::cout
    << "kp: " << kp << '\t'
    << "e: " << error << '\t'
    << "p: " << kp * p << '\t'
    << "i: " << ki * i << '\t'
    << "d: " << kd * d << '\t'
    << std::endl;

  // Apply coefficients and return
  return -1 * (kp * p + ki * i + kd * d);
}