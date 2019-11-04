//
// Created by romain on 02/11/2019.
//

#include "Socket.h"

//"/home/romain/Documents/tests/clientSend.txt"

Socket::Socket() {}

std::string Socket::readFile(std::string path)
{
    std::string line, buff;
    std::ifstream file(path);
    while (std::getline(file, line))
        buff += line;
    return buff;
}

bool Socket::sendFile(std::string path)
{
    std::string fileContents = readFile(path);
    if (!fileContents.empty()) {
        send(mSocket, fileContents.c_str(), strlen(fileContents.c_str()), 0);
        printf("Certificate Sent!\n");
        return true;
    } else
        return false;
}

bool Socket::receiveFile(std::string path)
{
    int valread;
    size_t len = 1024* sizeof(char);
    char buffer[len];
    std::ofstream myfile;
    myfile.open(path);

    valread = read(mSocket, buffer, len);
    if (valread == -1)
        return false;
    else {
        printf("%s\n", buffer);
        myfile << buffer;
        myfile.close();
        return true;
    }
}
