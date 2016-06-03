#include "controller.hpp"

void Controller::init(components* comp, std::string _stage, control_params* _params) {
  camera = comp->camera;
  ir = comp->ir;
  gate = comp->gate;
  motors = comp->motors;
  line_pid = comp->line_pid;
  wall_pid = comp->wall_pid;
  reporter = comp->reporter;

  stage = _stage;

  params = _params;
}

void Controller::go() {
  update_stage();

  if (stage == "gate") {
    gate->open_gate();
    stage = "line";
  } else if (stage == "line") {
    follow_line();
  } else if (stage == "maze") {
    navigate_maze();
  }
}

void Controller::stop() {
  motors->stop_all();
}

void Controller::update_stage() {
  if (stage == "line" && camera->can_see_red()) {
    std::cout << "--- starting maze ---" << std::endl;
    stage = "maze";
  }
}

void Controller::follow_line() {
  // Uses the camera to find the line
  camera->process_image();

  double turning_speed;

  if (camera->could_find_line_ahead()) {
    line_error = camera->get_line_error();
    turning_speed = line_pid->calc(line_error);

    is_turning_left = false;
    is_turning_right = false;
  } else {
    camera->print_image();

    if ((camera->could_find_line_left() || is_turning_left) && !is_turning_right) { // Prioritise left turns
      std::cout << "--- lost left ---" << std::endl;
      turning_speed = -100;
      is_turning_left = true;
    } else if (camera->could_find_line_right() || is_turning_right) {
      std::cout << "--- lost right ---" << std::endl;
      turning_speed = 100;
      is_turning_right = true;
    } else {
      // We've lost the line, so turn as fast as we can back towards the last
      // place we saw it.
      std::cout << "--- completely lost ---" << std::endl;
      if (line_error < 0) turning_speed = 100;
      if (line_error > 0) turning_speed = -100;
    }
  }

  // Use the value returned from the brain to set the speeds of our robot
  motors->set_velocities(params->line_speed, turning_speed);
}

void Controller::navigate_maze() {
  double left = ir->get_left();
  double right = ir->get_right();
  double front = ir->get_front();

  // std::cout
  //   << "l " << left << '\t'
  //   << "r " << right << '\t'
  //   << "f " << front << '\t'
  //   << "e " << (right - 350) << '\t'
  //   << std::endl;

  long time = get_time();

  if (current_manoeuvre && current_manoeuvre_end_time < time) {
    current_manoeuvre = 0;
    // std::cout << "--- ended left turn ---" << std::endl;
  }

  // Check for new manoeuvres to perform
  if (current_manoeuvre == 0) {
    if (front > 190 && left < 175 && right > 250) {
      current_manoeuvre = 1;
      current_manoeuvre_end_time = time + params->turn_left_time * 1000 * 1000;
      // std::cout << "--- started left turn ---" << std::endl;
    } else if (front > 350 && left > 350 && right > 350) {
      current_manoeuvre = 2;
      current_manoeuvre_end_time = time + params->turn_180_time * 1000 * 1000;
    }
  }

  // Perform manoeuvre or keep right
  if (current_manoeuvre == 1) {
    motors->set_velocities(params->maze_speed, -100);
  } else if (current_manoeuvre == 2) {
    motors->set_velocities(params->maze_speed * 0.5, 0, true);
  } else {
    double error = (double) ir->get_right_wall_error();
    double turning_speed = wall_pid->calc(error);
    constrain(-95, 95, &turning_speed);
    motors->set_velocities(params->maze_speed, turning_speed);
  }
}
