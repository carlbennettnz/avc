#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <utility>
#include <string>

#include "../lib/inih/cpp/INIReader.h"
#include "controller.hpp"
#include "camera.hpp"
#include "gate.hpp"
#include "motors.hpp"
#include "pid.hpp"
#include "reporter.hpp"
#include "components.hpp"

extern "C" int init(int);
extern "C" int set_motor(int motor, int speed);

int main(int, char**);
void init_hardware_controllers(std::string config_path);
void terminate(int);

#endif
