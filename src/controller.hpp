#ifndef __CONTROLLER_H_INCLUDED__
#define __CONTROLLER_H_INCLUDED__

#include <iostream>
#include <string>

#include "defines.hpp"
#include "camera.hpp"
#include "ir.hpp"
#include "gate.hpp"
#include "motors.hpp"
#include "pid.hpp"
#include "reporter.hpp"
#include "utils.hpp"

class Controller {
  public:
    void init(components* comp, std::string _stage, control_params* _params);
    void go();
    void stop();

  private:
    void update_stage();
    void follow_line();
    void navigate_maze();

    // Components
    Camera* camera;
    IR* ir;
    Gate* gate;
    Motors* motors;
    PID* line_pid;
    PID* wall_pid;
    Reporter* reporter;

    // Config
    control_params* params;

    // State tracking
    std::string stage;

    // Line following
    double line_error;
    bool is_turning_left;
    bool is_turning_right;

    // Maze navigation
    int current_manoeuvre = 0;
    long current_manoeuvre_end_time;
};

#endif
