//
// Created by romain on 02/11/2019.
//

#ifndef HOMENETCTL_CLIENT_H
#define HOMENETCTL_CLIENT_H

#include <netinet/in.h>
#include <arpa/inet.h>

#include "Socket.h"

#define PORT 1234

class Client : public Socket {

private:

    int mSocket = 0;
    int mPort;
    int init(const char * serverAddress, int port);

public:

    Client(const char * serverAddress, int port);
    bool connectToServer();
    bool clientAcceptAccess(int socket, std::string name);
    int getSocket();

};


#endif //HOMENETCTL_CLIENT_H
