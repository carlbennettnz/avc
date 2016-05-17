#ifndef __ACTUATORS_H_INCLUDED__
#define __ACTUATORS_H_INCLUDED__

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>

#include "utils.hpp"

extern "C" int set_motor(int motor, int speed);
extern "C" int connect_to_server( char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

class Actuators {
  public:
    void init(
        double min_speed,
        double max_speed,
        double left_coef,
        double right_coef,
        std::string ip,
        int port,
        std::string password
    );
    void set_velocities(double, double);
    void stop_all();
    void open_gate();

  private:
    double forward_speed;
    double turning_speed;
    double min_speed;
    double max_speed;
    double left_multiplier;
    double right_multiplier;
    double speed_range;
    std::string server_ip;
    int server_port;
    std::string server_password;
    void update();
};

#endif