//
// Created by romain on 02/11/2019.
//

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
        buff += line;
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

/**
 * Receives file and stores it at given path
 * @param path
 * @param socket
 * @return
 */
bool Socket::receiveFile(std::string path, int socket)
{
    int valread;
    size_t len = 924;
    char buffer[924];
    std::ofstream myfile;
    myfile.open(path);


    valread = read(socket, buffer, len);
    buffer[strlen(buffer)-2] = (char) '\0';


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
