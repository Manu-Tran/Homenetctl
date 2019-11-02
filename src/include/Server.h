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
#include "certificate.h"
#include "Socket.h"

#define PORT 1234

class Server : public Socket{

private:

    int mServer_fd, mNew_socket;
    struct sockaddr_in mAddress;

public:

    Server();
    bool listenForConnectionRequests();

};


#endif //HOMENETCTL_SERVER_H
