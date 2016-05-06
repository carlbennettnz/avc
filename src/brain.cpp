#include "brain.hpp"

/**
  Stores kp and kd values for use in PID calculations.
*/
void Brain::init(double p, double d) {
  kp = p;
  kd = d;
}

/**
  Return a forward and turning speed pair, where the turning speed is
  proportional to the provided error.
*/
std::pair<double, double> Brain::choose_velocities(double error) {
  return std::make_pair(100.0, error * -100);
}

/**
  Return a forward and turning speed pair, where the turning speed is calculated
  using the proportional and derivative terms of a PID controller.
*/
std::pair<double, double> Brain::choose_velocities_pid(double error) {
  // Get the current time
  struct timeval now;
  gettimeofday(&now, 0);

  double p = error;
  double d;

  // If this is our first error reading, we can't calculate the rate of change
  // or the error, so just assume it's zero.
  if (has_run_once) {
    d = (error - last_error_value) / (now.tv_usec - last_error_time);
  } else {
    d = 0;
    has_run_once = true;
  }

  // Record the error and time for next time
  last_error_value = error;
  last_error_time = now.tv_usec;

  // Apply coefficients and return
  return std::make_pair(100.0, kp * p + kd * d);
}
