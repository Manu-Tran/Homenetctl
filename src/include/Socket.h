//
// Created by romain on 02/11/2019.
//

#ifndef HOMENETCTL_SOCKET_H
#define HOMENETCTL_SOCKET_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>

class Socket {

protected:

    int mSocket = 0;
    struct sockaddr_in mServerAddress;

public:

    Socket();

    std::string readFile(std::string path);
    bool sendFile(std::string path, int socket);
    bool sendSize(int socket, int size);
    bool receiveFile(std::string path, int socket, int size);
    int receiveSize(int socket);

};


#endif //HOMENETCTL_SOCKET_H
