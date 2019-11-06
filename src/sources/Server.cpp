//
// Created by romain on 30/10/2019.
//

#include "Server.h"

Server::Server(const char * addr, int port)
{
    int opt = 1;

    // Creating socket file descriptor
    if ((mSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    mServerAddress.sin_family = AF_INET;
    mServerAddress.sin_addr.s_addr = inet_addr(addr);
    mServerAddress.sin_port = htons( port );

    if (bind(mSocket, (struct sockaddr *)&mServerAddress,
             sizeof(mServerAddress))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

bool Server::listenForConnectionRequests()
{

    int addrlen = sizeof(mServerAddress);

    if (listen(mSocket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((mNew_socket = accept(mSocket, (struct sockaddr *)&mServerAddress,
                             (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else
        return true;

}

int Server::getNewSocket() { return mNew_socket; }