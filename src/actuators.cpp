#include "actuators.hpp"

/**
  Stores wheel speed modifiers for later use. Min and max compress the used
  range of wheel speed, while left and right multipliers are used to adjust for
  inequalities in power between the two wheels.
*/
void Actuators::init(double min, double max, double left, double right) {
  left_multiplier = left;
  right_multiplier = right;
  min_speed = min;
  max_speed = max;
  speed_range = abs(max - min);
}

/**
  Sets the wheel velocities to the closest valid values. Forward speed is from 0
  to 100, while turning speed is from -100 (hard left) to 100 (hard right).
*/
void Actuators::set_velocities(double forward, double turning) {
  // Ensure the given values are valid
  constrain(0, 100, &forward);
  constrain(-100, 100, &turning);

  // Set the instance fields
  forward_speed = forward / 100;
  turning_speed = turning / 100;

  // Send the change to the motors
  update();
}

/**
  Force all wheel speeds to return to zero
*/
void Actuators::stop_all() {
  // Reset both values
  forward_speed = 0;
  turning_speed = 0;

  // Send the change to the motors
  set_motor(1, 0);
  set_motor(2, 0);
}

/**
  Apply speeds, proportionally adjusting to account for the requested turning
  speed.
*/
void Actuators::update() {
  if (turning_speed < 0 ) {
    set_motor(1, forward_speed * max_speed * left_multiplier * (1 + turning_speed));
    set_motor(2, forward_speed * max_speed * right_multiplier);
  } else if (turning_speed > 0) {
    set_motor(1, forward_speed * max_speed * left_multiplier);
    set_motor(2, forward_speed * max_speed * right_multiplier * (1 - turning_speed));
  } else {
    set_motor(1, forward_speed * max_speed * left_multiplier);
    set_motor(2, forward_speed * max_speed * right_multiplier);
  }
}