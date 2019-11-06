//
// Created by romain on 30/10/2019.
//

#ifndef HOMENETCTL_SERVER_H
#define HOMENETCTL_SERVER_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

#include "Socket.h"

#define PORT 1234

class Server : public Socket{

private:

    int  mNew_socket;

public:

    Server();
    bool listenForConnectionRequests();
    int getNewSocket();

};


#endif //HOMENETCTL_SERVER_H
