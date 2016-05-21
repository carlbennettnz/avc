#ifndef __COMPONENTS_H_INCLUDED__
#define __COMPONENTS_H_INCLUDED__

#include "camera.hpp"
#include "ir.hpp"
#include "actuators.hpp"
#include "pid.hpp"
#include "reporter.hpp"

struct components {
  Camera* camera;
  IR* ir;
  Actuators* actuators;
  PID* line_pid;
  PID* wall_pid;
  Reporter* reporter;
};

#endif
