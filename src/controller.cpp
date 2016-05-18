#include "controller.hpp"

void Controller::init(Sensors* s, Actuators* a, PID* l) {
  sensors = s;
  actuators = a;
  line_pid = l;
}

void Controller::go() {
  sensors->process_image();
  sensors->process_ir_data();

  update_stage();

  if (stage == "gate") {
    actuators->open_gate();
    stage = "line";
  } else if (stage == "line") {
    follow_line();
  } else if (stage == "maze") {
    navigate_maze();
  }
}

void Controller::stop() {
  actuators->stop_all();
}

void Controller::update_stage() {
  if (sensors->could_find_walls()) {
    stage = "maze";
  }
}

void Controller::follow_line() {
  // Uses the camera to find the line
  sensors->process_image();

  double turning_speed;

  if (sensors->could_find_line_ahead()) {
    line_error = sensors->get_line_error();
    turning_speed = line_pid->calc(line_error);

    is_turning_left = false;
    is_turning_right = false;
  } else {
    sensors->print_image();

    if ((sensors->could_find_line_left() || is_turning_left) && !is_turning_right) { // Prioritise left turns
      std::cout << "is turning left" << std::endl;
      turning_speed = -100;
      is_turning_left = true;
    } else if (sensors->could_find_line_right() || is_turning_right) {
      std::cout << "is turning right" << std::endl;
      turning_speed = 100;
      is_turning_right = true;
    } else {
      // We've lost the line, so turn as fast as we can back towards the last
      // place we saw it.
      if (line_error < 0) turning_speed = 100;
      if (line_error > 0) turning_speed = -100;
      std::cout << "lost line. error: " << line_error << "\tturning speed: " << turning_speed << std::endl;
    }
  }

  // Use the value returned from the brain to set the speeds of our robot
  actuators->set_velocities(100, turning_speed);
}

void Controller::navigate_maze() {
  return;
}
