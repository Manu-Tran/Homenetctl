//
// Created by romain on 15/10/2019.
//

#ifndef HOMENETCTL_EQUIPMENT_H
#define HOMENETCTL_EQUIPMENT_H

#include <string>
#include <cstring>
#include <utility>
#include "RSAKeyPair.h"
#include <memory>
#include "certificateHandler.h"
#include <vector>

class Equipment {

private:
    std::string mId;
    RSAKeyPair mKeys;
    int mPort;

    std::string pathCA;
    std::string pathDA;

    CertificateHandler::X509Ptr mSelfSignedCertificate;

    std::vector<Poco::Crypto::X509Certificate> CA;
    std::vector<Poco::Crypto::X509Certificate> DA;

public:

    //Create a new certificate from a received one
    Poco::Crypto::X509Certificate newCertificate(std::shared_ptr<Poco::Crypto::X509Certificate> cert, std::string clientName);

    //SAVE & LOAD
    void saveInCA(Poco::Crypto::X509Certificate cert, std::string path);
    std::vector<Poco::Crypto::X509Certificate> loadCA();

    //CONSTRUCTORS
    Equipment();
    Equipment(std::string id, int port);

    //DISPLAY
    void display_DA();
    void display_CA();
    void display(); //calls on the previous 2

    //GETTERS
    std::string getName();
    RSAKeyPair getKeys();
    int getPort();
    Poco::Crypto::X509Certificate getSelfSignedCertificate();

    //SETTERS
    void setName(std::string newId);
    void setKeys(RSAKeyPair newKeys);
    void setPort(int newPort);

};


#endif //HOMENETCTL_EQUIPMENT_H
