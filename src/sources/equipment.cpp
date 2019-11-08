//
// Created by romain on 15/10/2019.
//

#include <string>
#include "equipment.h"

//CONSTRUCTORS
Equipment::Equipment(std::string id, int port)
{
    //ID and Port are gotten from user input
    mId=id;
    mPort=port;

    //Key generation
    mKeys.generate_key(id);

    Poco::Crypto::EVPPKey evpkey = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_" + id + ".pem", "/tmp/homenetctl/privateKey_" + id + ".pem");

    //Generate self signed certificate
    mSelfSignedCertificate = CertificateHandler::selfSign(mId, Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()), 30);

    /* mSelfSignedCertificate = Certificate((char *) mId.c_str(), Poco::Crypto::EVPPKey(mKeys.get()), 30); */

    //Check that everything went well by checking the certificate's signature
    bool result = CertificateHandler::checkCertificate(*CertificateHandler::selfSign(mId, Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()), 30), *mSelfSignedCertificate);
    if(!result)
    {
        std::cout << "error in the selfsigned certificate" << std::endl;
        exit(EXIT_FAILURE);
    }

}

//DISPLAY
void Equipment::display_CA() {}
void Equipment::display_DA() {}
void Equipment::display() {}

//GETTERS
std::string Equipment::getName() {return mId;}
RSAKeyPair Equipment::getKeys() {return mKeys;}
int Equipment::getPort() {return mPort;}

//SETTERS
void Equipment::setName(std::string newId) {mId=newId;}
void Equipment::setKeys(RSAKeyPair newKeys) {mKeys=newKeys;}
void Equipment::setPort(int newPort) {mPort=newPort;}
