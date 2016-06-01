#ifndef __GATE_H_INCLUDED__
#define __GATE_H_INCLUDED__

#include <string>
#include <iostream>

using namespace std;

extern "C" int connect_to_server( char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

class Gate {
  public:
    void init(string ip, int port, string password);
    void open_gate();

  private:
    string server_ip;
    int server_port;
    string server_password;
};

#endif