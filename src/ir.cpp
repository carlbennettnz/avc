#include "ir.hpp"

void IR::init(int left, int right) {
  left_chan = left;
  right_chan = right;
}

bool IR::can_see_walls() {
  int left = read_analog(left_chan);
  int right = read_analog(left_chan);

  return right > 270 && left > 270;
}

int IR::get_left() {
  int total = 0;

  for (int i = 0; i < num_readings; i++) {
    total += read_analog(left_chan);
  }

  return total / num_readings;
}

int IR::get_right() {
  int total = 0;

  for (int i = 0; i < num_readings; i++) {
    total += read_analog(right_chan);
  }

  return total / num_readings;
}

int IR::get_front() {
  int total = 0;

  for (int i = 0; i < num_readings; i++) {
    total += read_analog(2);
  }

  return total / num_readings;
}

int IR::get_wall_error() {
  return get_right() - get_left();
}

int IR::get_left_wall_error() {
  return get_left() - 500;
}

int IR::get_right_wall_error() {
  return get_right() - 500;
}
