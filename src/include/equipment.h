//
// Created by romain on 15/10/2019.
//

#ifndef HOMENETCTL_EQUIPMENT_H
#define HOMENETCTL_EQUIPMENT_H

#include <string>
#include <utility>
#include "RSAKeyPair.h"
#include "certificate.h"

class equipment {

private:
    std::string id;
    RSAKeyPair keys;
    certificate myCertificate;
    int port;

public:

    //CONSTRUCTORS
    equipment();
    equipment(std::string id, int port);

    //DISPLAY
    void display_DA();
    void display_CA();
    void display(); //calls on the previous 2

    //GETTERS
    std::string getName();
    RSAKeyPair getKeys();
    int getPort();

    //SETTERS
    void setName();
    void setKeys();
    void setPort();

};


#endif //HOMENETCTL_EQUIPMENT_H
