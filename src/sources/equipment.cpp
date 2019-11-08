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
    pathCA = "/tmp/homenetctl/certs/" + mId + ".pem";
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
    } else {
        saveInCA(*(mSelfSignedCertificate),pathCA);
    }

}

//SAVE & LOAD
void Equipment::saveInCA(Poco::Crypto::X509Certificate cert, std::string path)
{
    CA.push_back(cert);
    Poco::Crypto::X509Certificate::writePEM(path,CA);
    std::cout << "CA was saved in: " << pathCA << std::endl;
}

std::vector<Poco::Crypto::X509Certificate> Equipment::loadCA()
{
    return Poco::Crypto::X509Certificate::readPEM(pathCA);
}

//DISPLAY
void Equipment::display_CA()
{
    std::string certs;
    std::ifstream fileCA (pathCA);
    if (fileCA.is_open())
    {
        std::cout << "certs from CA: " << std::endl;
        while ( getline (fileCA,certs) )
        {
            std::cout << certs << '\n';
        }
        fileCA.close();
    }

    else std::cout << "Unable to open CA file";
}
void Equipment::display_DA()
{
    std::string certs;
    std::ifstream fileDA (pathDA);
    if (fileDA.is_open())
    {
        std::cout << "certs from DA: " << std::endl;
        while ( getline (fileDA,certs) )
        {
            std::cout << certs << '\n';
        }
        fileDA.close();
    }

    else std::cout << "Unable to open DA file";
}
void Equipment::display()
{
    display_CA();
    display_DA();
}

//GETTERS
std::string Equipment::getName() {return mId;}
RSAKeyPair Equipment::getKeys() {return mKeys;}
int Equipment::getPort() {return mPort;}

//SETTERS
void Equipment::setName(std::string newId) {mId=newId;}
void Equipment::setKeys(RSAKeyPair newKeys) {mKeys=newKeys;}
void Equipment::setPort(int newPort) {mPort=newPort;}
