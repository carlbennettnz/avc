#include "utils.hpp"

/**
  Checks value is inside the given boundry, and sets it to the closest valid
  value if it is not.
*/
void constrain(double min, double max, double *value) {
  if (*value < min) {
    *value = min;
  }

  if (*value > max) {
    *value = max;
  }
}

long get_time() {
  struct timeval now;
  gettimeofday(&now, 0);
  return  now.tv_sec * 1000 * 1000 + now.tv_usec; // Combine sec and usec components
}
