#ifndef __DEFINES_H_INCLUDED__
#define __DEFINES_H_INCLUDED__

#include "camera.hpp"
#include "ir.hpp"
#include "gate.hpp"
#include "motors.hpp"
#include "pid.hpp"
#include "reporter.hpp"

struct components {
  Camera* camera;
  IR* ir;
  Gate* gate;
  Motors* motors;
  PID* line_pid;
  PID* wall_pid;
  Reporter* reporter;
};

struct control_params {
  double line_speed;
  double maze_speed;
  double turn_180_time;
  double turn_left_time;
};

#endif
