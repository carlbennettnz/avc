#ifndef __CONTROLLER_H_INCLUDED__
#define __CONTROLLER_H_INCLUDED__

#include <iostream>
#include <string>

#include "components.hpp"
#include "camera.hpp"
#include "ir.hpp"
#include "actuators.hpp"
#include "pid.hpp"
#include "reporter.hpp"
#include "utils.hpp"

class Controller {
  public:
    void init(components* comp);
    void go();
    void stop();

  private:
    void update_stage();
    void follow_line();
    void navigate_maze();

    Camera* camera;
    IR* ir;
    Actuators* actuators;
    PID* line_pid;
    PID* wall_pid;
    Reporter* reporter;

    unsigned long maze_start_time;
    std::string stage = "maze";

    // Line following
    double line_error;
    bool is_turning_left;
    bool is_turning_right;

    int last_front = 0;
    int current_manoeuvre = 0;
    long current_manoeuvre_end_time;
};

#endif
