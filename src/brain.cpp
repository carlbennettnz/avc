#include "brain.hpp"

/**
  Stores kp and kd values for use in PID calculations.
*/
void Brain::init(double p, double i, double d) {
  kp = p;
  ki = i;
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
  long error_time = now.tv_sec * 1000 * 1000 + now.tv_usec; // Combine sec and usec components

  double p = error;
  double d;

  // If this is our first error reading, we can't calculate the rate of change
  // of the error, so just assume it's zero.
  if (has_run_once) {
    d = (error - last_error_value) / (error_time - last_error_time) * 1000 * 1000;
    total_error += error / (error_time - last_error_time) * 1000 * 1000;
  } else {
    d = 0;
    has_run_once = true;
  }

  // Record the error and time for next time
  last_error_value = error;
  last_error_time = error_time;

  double i = total_error;

  std::cout
    << "p: " << kp * p << '\t'
    << "i: " << ki * i << '\t'
    << "d: " << kd * d << '\t';

  // Apply coefficients and return
  return std::make_pair(100.0, kp * p + ki * i + kd * d);
}
