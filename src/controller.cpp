#include "controller.hpp"

void Controller::init(Sensors* s, Actuators* a, PID* l) {
  sensors = s;
  actuators = a;
  line_pid = l;
}

void Controller::go() {
  if (stage == "gate") {
    // open_gate();
  } else if (stage == "line") {
    follow_line();
  } else if (stage == "maze") {
    // nagivate_maze();
  }
}

void Controller::stop() {
  actuators->stop_all();
}

void Controller::follow_line() {
  // Uses the camera to find the line
  sensors->process_image();

  double turning_speed;

  if (sensors->could_find_line_ahead()) {
    line_error = sensors->get_line_error();
    turning_speed = line_pid->calc(line_error);
  } else if (sensors->could_find_line_left()) { // Prioritise left turns
    turning_speed = -100;
  } else if (sensors->could_find_line_right()) {
    turning_speed = 100;
  } else {
    // We've lost the line, so turn as fast as we can back towards the last
    // place we saw it.
    if (line_error < 0) turning_speed = -100;
    if (line_error > 0) turning_speed = 100;
  }

  // Use the value returned from the brain to set the speeds of our robot
  actuators->set_velocities(100, turning_speed);
}
