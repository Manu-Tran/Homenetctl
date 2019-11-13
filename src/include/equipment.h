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

using X509Ptr = std::shared_ptr<Poco::Crypto::X509Certificate>;

class Equipment {

private:
    std::string mId;
    RSAKeyPair mKeys;
    std::unique_ptr<CertificateHandler> mHandler;
    int mPort;

    CertificateHandler::X509Ptr mSelfSignedCertificate;

    std::vector<Poco::Crypto::X509Certificate> CA;
    std::vector<Poco::Crypto::X509Certificate> DA;

public:

    //CONSTRUCTORS
    Equipment();
    Equipment(std::string id, int port);

    //Create a new certificate from a received one
    Poco::Crypto::X509Certificate newCertificate(Poco::Crypto::X509Certificate cert, std::string clientName);

    //SAVE & LOAD
    void addInCA(Poco::Crypto::X509Certificate cert, Poco::Crypto::RSAKey signerKey);
    void addInDA(Poco::Crypto::X509Certificate cert);
    void writeCertificateToFile(Poco::Crypto::X509Certificate cert, std::string path);
    Poco::Crypto::X509Certificate readCertificateFromFile(std::string path);

    void saveEquipment();
    Equipment(std::string id);

    //ADD New equipment
    void addEquipmentServerSide();
    void addEquipmentClientSide(const char * serverAddress);

    void synchroServerSide();
    void synchroClientSide(const char * serverAddress);

    bool authentificateServerSide();
    bool authentificateClientSide(const char * serverAddress);

    //DISPLAY
    static void display_certificate(const Poco::Crypto::X509Certificate& certif);
    void display_DA();
    void display_CA();
    void display(); //calls on the previous 2

    int getFileSize(std::string path);

    //GETTERS
    std::string getName();
    RSAKeyPair getKeys();
    int getPort();
    Poco::Crypto::X509Certificate getSelfSignedCertificate();
    std::vector<Poco::Crypto::X509Certificate> getCA() {return CA;}

    //SETTERS
    void setName(std::string newId);
    void setKeys(RSAKeyPair newKeys);
    void setPort(int newPort);

};


#endif //HOMENETCTL_EQUIPMENT_H
