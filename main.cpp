#include <iostream>
#include <unistd.h>

using namespace std;

extern "C" int init_hardware();
extern "C" int set_motor(int motor, int speed);

int main() {
  init_hardware();
  set_motor(1, 100);
  set_motor(2, 100);
  usleep(1000*1000);
  set_motor(1, 0);
  set_motor(2, 0);
}
