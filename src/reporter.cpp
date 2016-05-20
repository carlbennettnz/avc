#include "reporter.hpp"

using namespace std;

#define MAXDATASIZE 100

void Reporter::init(string _addr, int _port) {
  return;
  addr = _addr.c_str();
  port = to_string(_port).c_str();

  //Ensure that servinfo is clear
  memset(&hints, 0, sizeof hints); // make sure the struct is empty

  //setup hints
  hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

  //Setup the structs if error print why
  int res;
  if ((res = getaddrinfo(addr, port, &hints, &servinfo)) != 0) {
    fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(res));
    return;
  }

  //setup the socket
  if ((s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1) {
    perror("client: socket");
  }
}

void Reporter::connect_to_server() {
  if (connect(s, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
    close(s);
    perror("Failed to connect");
  }
}

bool Reporter::send_data(string msg) {
  int len = strlen(msg.c_str());
  int bytes_sent = send(s, msg.c_str(), len, 0);

  return bytes_sent == 0;
}
