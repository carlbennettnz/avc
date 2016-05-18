#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../src/sensors.hpp"

extern "C" int init(int verbosity);
extern "C" int take_picture();
extern "C" char get_pixel(int x, int y, int color);

int main(int argc, char* argv[]) {
  init(2);

  int threshold = 140;

  if (argc > 1) {
    threshold = atoi(argv[1]);
  }

  Sensors sensors;
  sensors.init(320, 240, threshold);
  
  while (true) {
    sensors.process_image();

    printf(
      "%d %d %d\n",
      sensors.could_find_line_ahead(),
      sensors.could_find_line_left(),
      sensors.could_find_line_right()
    );
    sensors.print_image();

    usleep(1000 * 1000);
  }
}
