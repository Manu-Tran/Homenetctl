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
    std::string mId;
    RSAKeyPair mKeys;
    certificate mCertificate;
    int mPort;

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
    void setName(std::string newId);
    void setKeys(RSAKeyPair newKeys);
    void setPort(int newPort);

};


#endif //HOMENETCTL_EQUIPMENT_H
