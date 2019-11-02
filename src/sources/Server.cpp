//
// Created by romain on 30/10/2019.
//

#include "Server.h"

Server::Server()
{
    int opt = 1;

    // Creating socket file descriptor
    if ((mServer_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(mServer_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    mAddress.sin_family = AF_INET;
    mAddress.sin_addr.s_addr = INADDR_ANY;
    mAddress.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(mServer_fd, (struct sockaddr *)&mAddress,
             sizeof(mAddress))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

bool Server::listenForConnectionRequests()
{

    int addrlen = sizeof(mAddress);

    if (listen(mServer_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((mNew_socket = accept(mServer_fd, (struct sockaddr *)&mAddress,
                             (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else
        return true;

}