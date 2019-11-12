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
    std::string contentSize = std::to_string(fileContents.length());


    send(socket, contentSize.c_str(), 20, 0);
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
    int size_int;
    size_t len;

    // Hardvalue, but just to store and int in base 10
    char sizeBuffer[20];

    std::ofstream myfile;
    myfile.open(path);

    read(socket, sizeBuffer, 20);
    std::stringstream(std::string(sizeBuffer)) >> size_int ;
    if (size_int < 940) {
        size_int = 940;
    }
    if (size_int > 940000) {
        size_int = 940000;
    }
    len = (size_t) size_int;
    char buffer[len];
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



