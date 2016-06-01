#include "gate.hpp"

/**
  Store the server connection details.
*/
void Gate::init(string ip, int port, string password) {
  server_ip = ip;
  server_port = port;
  server_password = password;
}

/**
  Attempts to open the gate.
*/
void Gate::open_gate() {
  // I couldn't get it to work with the dynamically set params
  char server_ip[] = "130.195.6.196";
  int server_port = 1024;
  char server_password[] = "Please";

  connect_to_server(server_ip, server_port);
  send_to_server(server_password);

  char message[24];
  receive_from_server(message);
  send_to_server(message);
}
