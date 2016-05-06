#include "main.hpp"

// Our main loop only runs while this flag is true
bool exiting = false;

Sensors sensors;
Brain brain;
Actuators actuators;

int main(int argc, char *argv[]) {
  // Default config file path
  std::string config_path = "./avc.ini";
  
  // If we've been passed a parameter, use it as the path to our config file
  if (argc == 2) {
    config_path = argv[1];
  }

  // Boot up the E101 library.
  init_hardware();

  // Read the config file and use the information in it to 
  init_hardware_controllers(config_path);

  // Here we set up listeners for program interruption (SIGINT) or termination
  // (SIGTERM) signals. These events would usually cause the program to exit
  // immediately, but by registering these listeners we're saying we'll handle
  // that ourselves. This gives us a chance to shut down gracefully.
  signal(SIGINT, terminate);
  signal(SIGTERM, terminate);

  // This is our main loop. It continues until the program exits.
  while (!exiting) {
    // Uses the camera to find the line
    double error = sensors.get_line_error();

    // Right now the sensors just give us the error directly, but eventually the
    // sensors should tell us were the line is and then the brain should give us
    // an error value.
    std::pair<double, double> velocities = brain.choose_velocities(error);

    // Use the value returned from the brain to set the speeds of our robot
    actuators.set_velocities(velocities.first, velocities.second);
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

  sensors.init(
    // The third value is the default
    config.GetInteger("sensors", "img_width", 320),
    config.GetInteger("sensors", "img_height", 240)
  );

  brain.init(
    // PID coefficients, for tuning the error response
    config.GetInteger("brain", "kp", 1),
    config.GetInteger("brain", "kd", 0)
  );

  actuators.init(
    // Minimum speed. Value to send to motors when speed is just above zero.
    config.GetInteger("actuators", "min_speed", 0),
    
    // Maximum speed
    config.GetInteger("actuators", "max_speed", 255),

    // Wheel speed coefficients, to adjust for physical errors with the robot
    config.GetReal("actuators", "left_multiplier", 1),
    config.GetReal("actuators", "right_multiplier", 1)
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
  actuators.stop_all();

  // Exit for real
  exit(signum);
}
