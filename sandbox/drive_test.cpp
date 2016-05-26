#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "../src/actuators.hpp"
#include "../lib/inih/cpp/INIReader.h"

extern "C" int init(int verbosity);
// extern "C" void set_motor(int motor, int speed);

Actuators actuators;

void terminate(int);

int main(int argc, char* argv[]) {
  init(2);

  signal(SIGTERM, terminate);
  signal(SIGINT, terminate);

  // Read the settings stored in the .ini file. Doing this allows us to tweak
  // parameters without compiling any code.
  INIReader config("./avc.ini");

  // Check for errors parsing the .ini settings file
  if (config.ParseError() < 0) {
    std::cout << "Can't load 'test.ini'\n";
    exit(1);
  }

  actuators.init(
    // Minimum speed. Value to send to motors when speed is just above zero.
    config.GetInteger("actuators", "min_speed", 0),
    
    // Maximum speed
    config.GetInteger("actuators", "max_speed", 255),

    // Wheel speed coefficients, to adjust for physical errors with the robot
    config.GetReal("actuators", "left_multiplier", 1),
    config.GetReal("actuators", "right_multiplier", 1),

    // Gate server config
    config.Get("actuators", "server_ip", "130.195.6.196"),
    config.GetInteger("actuators", "server_port", 1024),
    config.Get("actuators", "server_password", "Please")
  );

  actuators.set_velocities(100, 0, true);
  while (true) {
    usleep(1000 * 1000);
  }
}

void terminate(int signum) {
  actuators.set_velocities(0, 0);
  exit(signum);
}
