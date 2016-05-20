#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../src/actuators.hpp"

extern "C" int init(int verbosity);

int main(int argc, char* argv[]) {
  init(2);

  Actuators actuators;
  actuators.init(30, 80, 0.95, 1, "130.195.6.196", 1024, "Please");
  
  while (true) {
    actuators.set_velocities(100, 0);
    usleep(1000 * 1000);
  }
}
