//
// Created by romain on 02/11/2019.
//


#include "Client.h"

int Client::init(const char * serverAddress, int port)
{
    if ((mSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    mServerAddress.sin_family = AF_INET;
    mServerAddress.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverAddress, &mServerAddress.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    return 1;
}

Client::Client(const char * serverAddress, int port)
{
    int result = init(serverAddress, port);
    if(result == -1)
        exit(EXIT_FAILURE);
}

bool Client::connectToServer()
{
    if (connect(mSocket, (struct sockaddr *)&mServerAddress, sizeof(mServerAddress)) < 0)
    {
        printf("\nConnection Failed \n");
        return false;
    }
    return true;
}

int Client::getSocket() { return mSocket; }

