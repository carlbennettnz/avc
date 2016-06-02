#include "camera.hpp"

/**
  Stores the image dimensions for later use.
*/
void Camera::init(double width, double height, int threshold) {
  img_width = width;
  img_height = height;
  brightness_threshold = threshold;
}

/**
  Performs an extremely basic error calculation, simply taking data from the
  middle line of pixels and finding the brightness on the left side verses the
  right.
*/
void Camera::process_image() {
  take_picture();

  double ahead_pixels[320];
  double left_pixels[240];
  double right_pixels[240];

  double average_brightness = get_average_brightness();

  get_row(ahead_pixels, img_height - 30 - 1, 15);
  get_col(left_pixels, img_width - 10 - 1, 10);
  get_col(right_pixels, 10 - 1, 3);

  auto ahead = get_error_from_array(ahead_pixels, img_width, average_brightness);
  auto left  = get_error_from_array(left_pixels, img_height, average_brightness);
  auto right = get_error_from_array(right_pixels, img_height, average_brightness);
  
  found_line_ahead = std::get<0>(ahead);
  found_line_left  = std::get<0>(left);
  found_line_right = std::get<0>(right);
  line_error = std::get<1>(ahead);
}

double Camera::get_average_brightness(int color) {
  int total = 0;

  for (int y = 0; y < img_height; y++) {
    for (int x = 0; x < img_width; x++) {
      total += get_pixel(x, y, color);
    }
  }

  return (double) total / img_width / img_height;
}

double Camera::get_line_error() {
  return line_error;
}

bool Camera::could_find_line_ahead() { return found_line_ahead; }
bool Camera::could_find_line_left()  { return found_line_left;  }
bool Camera::could_find_line_right() { return found_line_right; }

void Camera::get_row(double row[], int rowIndex, int spread) {
  for (int i = 0; i < img_width; i++) {
    int total = 0;

    for (int j = -spread; j <= spread; j++) {
      total += get_pixel(i, rowIndex + j, 3);
    }

    row[i] = (double) total / (2 * spread + 1);
  }
}

void Camera::get_col(double col[], int colIndex, int spread) {
  for (int i = 0; i < img_height; i++) {
    int total = 0;

    for (int j = -spread; j <= spread; j++) {
      total += get_pixel(colIndex + j, i, 3);
    }

    col[i] = (double) total / (2 * spread + 1);
  }
}

std::tuple<bool, double> Camera::get_error_from_array(double pixels[], int array_size, double average_brightness) {
  int number_found = 0;
  double error = 0;

  for (int i = 0; i < array_size; i++) {
    if (pixels[i] - brightness_threshold > average_brightness) {
      number_found++;
      error += i - (img_width / 2);
    }
  }

  // Normalise the error so -1 < err < 1
  error = error * 10000 / number_found / img_width / (img_width / 2);

  return std::make_tuple(number_found > 0, error);
}

bool Camera::can_see_red() {
  double level = get_average_brightness(1) / get_average_brightness();
  // std::cout << "redness " << level << std::endl;
  return level < 0.95;
}

void Camera::print_image() {
  for (int y = 0; y < 240; y += 10) {
    for (int x = 0; x < 320; x += 10) {
      std::cout << (get_pixel(x, y, 3) > 120) << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
