//
// Created by romain on 02/11/2019.
//

#include <sstream>
#include "Socket.h"

//"/home/romain/Documents/tests/clientSend.txt"

Socket::Socket() {}

/**
 * Reads file at given path
 * @param path
 * @return
 */
std::string Socket::readFile(std::string path)
{
    std::string line, buff;
    std::ifstream file(path);
    while (std::getline(file, line))
        buff += line + "\n";
    return buff;
}

/**
 * Sends file through given socket
 * @param path
 * @param socket
 * @return
 */
bool Socket::sendFile(std::string path, int socket)
{
    std::string fileContents = readFile(path);
    if (!fileContents.empty()) {
        send(socket, fileContents.c_str(), strlen(fileContents.c_str()), 0);
        return true;
    } else
        return false;
}

bool Socket::sendSize(int socket, int size)
{
    int valread;

    valread = send(socket, std::to_string(size).c_str(), strlen(std::to_string(size).c_str()), 0);

    return valread != -1;
}

/**
 * Receives file and stores it at given path
 * @param path
 * @param socket
 * @return
 */
bool Socket::receiveFile(std::string path, int socket, int size)
{
    int valread;
    size_t len = size;
    char buffer[len];
    std::ofstream myfile;
    myfile.open(path);


    valread = read(socket, buffer, len);


    if (valread == -1) {
        std::cout << "failed to read!" << std::endl;
        return false;
    }
    else {
        //std::cout << "I received this: " << buffer << std::endl;
        myfile << buffer;
        myfile.close();
        return true;
    }
}

int Socket::receiveSize(int socket)
{
    int size = 0;
    char buffer[20];
    read(socket, buffer, strlen(buffer));

    std::stringstream(std::string(buffer)) >> size ;

    return size;
}
