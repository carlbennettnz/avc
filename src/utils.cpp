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
