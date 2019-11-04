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
    int init(const char * serverAddress);

public:

    Client(const char * serverAddress);

    //has to be called inside the connect function to get the right IP address and port for the server
    sockaddr_in getServerAddress();

    bool connectToServer();

};


#endif //HOMENETCTL_CLIENT_H
