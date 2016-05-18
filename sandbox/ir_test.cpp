#include <iostream>
#include <unistd.h>

extern "C" int init_hardware();
extern "C" int read_analog(int pin);

int main() {
  init_hardware();

  while (true) {
    int left = read_analog(1);
    int right = read_analog(0);
    std::cout << left << '\t' << right << '\t' << right - left << std::endl;
    usleep(50000);
  }
}
