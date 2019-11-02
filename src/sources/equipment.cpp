//
// Created by romain on 15/10/2019.
//

#include <string>
#include "equipment.h"

//CONSTRUCTORS
Equipment::Equipment(std::string id, int port)
    : mSelfSignedCertificate(CertificateHandler::selfSign(mId, Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()), 30))
{
    mId=std::move(id); //the Id will be an user input, so we don't need it anymore afterwards, hence moving it is okay.
    mPort=port;
    mKeys = RSAKeyPair();
    /* mSelfSignedCertificate = Certificate((char *) mId.c_str(), Poco::Crypto::EVPPKey(mKeys.get()), 30); */
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
