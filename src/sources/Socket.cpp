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

bool Socket::sendFile(std::string path, int socket)
{
    std::string fileContents = readFile(path);
    if (!fileContents.empty()) {
        send(socket, fileContents.c_str(), strlen(fileContents.c_str()), 0);
        std::cout << "I sent this: " << fileContents.c_str() << std::endl;
        return true;
    } else
        return false;
}

bool Socket::receiveFile(std::string path, int socket)
{
    int valread;
    size_t len = 1024;
    char buffer[1024];
    std::ofstream myfile;
    myfile.open(path);

    std::cout << "opened the file!" << std::endl;

    valread = read(socket, buffer, len);

    std::cout << "valread: " << valread << std::endl;

    if (valread == -1) {
        std::cout << "failed to read!" << std::endl;
        return false;
    }
    else {
        std::cout << "I received this: " << buffer << std::endl;
        myfile << buffer;
        myfile.close();
        return true;
    }
}
