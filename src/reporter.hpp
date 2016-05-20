#ifndef __REPORTER_H_INCLUDED__
#define __REPORTER_H_INCLUDED__

using namespace std;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
 
class Reporter {
  public:
    void init(string _host, int _port);
    void connect_to_server();
    bool send_data(string msg);
 
  private:
    addrinfo hints, *servinfo;
    const char *addr;
    const char *port;
    int s; //the socket descriptor
 
    void manageRecv(int numbytes, char * buf);
};

#endif
