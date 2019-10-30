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

#define PORT 1234

class Server {

private:

    int mServer_fd, mNew_socket;
    struct sockaddr_in mAddress;

public:

    Server();
    bool listenForConnectionRequests();
    bool sendCert(Certificate cert);

};


#endif //HOMENETCTL_SERVER_H
