#include "main.hpp"

// Our main loop only runs while this flag is true
bool exiting = false;

Controller controller;

Camera camera;
IR ir;
Gate gate;
Motors motors;
PID line_pid;
PID wall_pid;
Reporter reporter;

components bundle = { &camera, &ir, &gate, &motors, &line_pid, &wall_pid, &reporter };
control_params params;

int main(int argc, char *argv[]) {
  // Default config file path
  std::string config_path = "./avc.ini";
  
  // If we've been passed a parameter, use it as the path to our config file
  if (argc == 2) {
    config_path = argv[1];
  }

  // Boot up the E101 library.
  init(0);

  // Read the config file and use the information in it to initialise everything
  init_hardware_controllers(config_path);

  // Here we set up listeners for program interruption (SIGINT) or termination
  // (SIGTERM) signals. These events would usually cause the program to exit
  // immediately, but by registering these listeners we're saying we'll handle
  // that ourselves. This gives us a chance to shut down gracefully.
  signal(SIGINT, terminate);
  signal(SIGTERM, terminate);

  // This is our main loop. It continues until the program exits.
  while (!exiting) {
    controller.go();
  }
}

/**
  Here we take a path to settings file, parse that file, and use the information
  in it to config the classes that control our robot.
*/
void init_hardware_controllers(std::string config_path) {
  // Read the settings stored in the .ini file. Doing this allows us to tweak
  // parameters without compiling any code.
  INIReader config(config_path);

  // Check for errors parsing the .ini settings file
  if (config.ParseError() < 0) {
    std::cout << "Can't load 'test.ini'\n";
    exit(1);
  }

  // Now we have access to the settings file, we have the information we need
  // to start initialising the objects which control our robot.

  bundle.camera->init(
    // The third value is the default
    config.GetInteger("camera", "img_width", 320),
    config.GetInteger("camera", "img_height", 240),
    config.GetInteger("camera", "brightness_threshold", 140)
  );

  bundle.ir->init(
    config.GetInteger("ir", "left_chan", 0),
    config.GetInteger("ir", "right_chan", 1)
  );

  bundle.motors->init(
    // Min and max speeds. Min is sent to motors when speed is just above zero.
    config.GetInteger("motors", "min_speed", 0),
    config.GetInteger("motors", "max_speed", 255),

    // Wheel speed coefficients, to adjust for physical errors with the robot
    config.GetReal("motors", "left_multiplier", 1),
    config.GetReal("motors", "right_multiplier", 1)
  );

  bundle.gate->init(
    // Gate server config
    config.Get("gate", "server_ip", "130.195.6.196"),
    config.GetInteger("gate", "server_port", 1024),
    config.Get("gate", "server_password", "Please")
  );

  bundle.line_pid->init(
    // PID coefficients, for tuning the error response
    config.GetReal("line_following", "kp", 100),
    config.GetReal("line_following", "ki", 0),
    config.GetReal("line_following", "kd", 0)
  );

  bundle.wall_pid->init(
    // PID coefficients, for tuning the error response
    config.GetReal("wall_following", "kp", 100),
    config.GetReal("wall_following", "ki", 0),
    config.GetReal("wall_following", "kd", 0)
  );

  bundle.reporter->init(
    config.Get("reporter", "server_host", "localhost"),
    config.GetInteger("reporter", "server_port", 1024)
  );

  // reporter.connect_to_server();

  params.line_speed = config.GetReal("controller", "line_speed", 20);
  params.maze_speed = config.GetReal("controller", "maze_speed", 25);
  params.turn_180_time = config.GetReal("controller", "turn_180_time", 0.5);
  params.turn_left_time = config.GetReal("controller", "turn_left_time", 0.7);

  controller.init(
    &bundle,
    config.Get("controller", "stage", "line"),
    &params
  );
}

/**
  If the program is terminated while the motors are still running, the motors
  will randomly jump to either off (desired) or full power (definitely not
  desired). This is the shut down procedure, which ensures all motors are turned
  off, and then exits.
*/
void terminate(int signum) {
  // Stop the main loop
  exiting = true;

  // Stop the wheels
  controller.stop();

  // Exit for real
  exit(signum);
}
