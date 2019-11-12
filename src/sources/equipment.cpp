//
// Created by romain on 15/10/2019.
//

#include "equipment.h"

/**
 * Constructor for class Equipment. Handles the generation of selfsigned certificate and the first entry in CA
 * @param id
 * @param port
 */
Equipment::Equipment(std::string id, int port)
    : mId(id)
    , mKeys(mId)
{
    //ID and Port are gotten from user input
    pathCA = "/tmp/homenetctl/certs/" + mId + ".pem";
    mPort=port;

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
        addInCA(*mSelfSignedCertificate);
    }

}

/**
 * Creates a new certificate using a self signed certificate (extracts the public key) and his own certificate.
 * @param cert
 * @param clientName
 * @return
 */
Poco::Crypto::X509Certificate Equipment::newCertificate(Poco::Crypto::X509Certificate cert, std::string clientName)
{
    //get key from certificate
    RSAKeyPair clientKey(clientName, cert);

    mKeys.setId(mId);
    clientKey.setId(clientName);
    //create a new one and sign it using my key
    auto cert1 = CertificateHandler::sign(mId,Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()),clientName,Poco::Crypto::EVPPKey(clientKey.loadKeys(false).get()),20);

    //return it
    return *cert1;
}

/**
 * Adds an equipment in CA with the shape of a triplet (ID,PublicKey,Certificate signed by this)
 * @param id
 * @param pubkey
 * @param cert
 */
void Equipment::addInCA(Poco::Crypto::X509Certificate cert)
{
    CA.push_back(cert);
}
void Equipment::addInDA(Poco::Crypto::X509Certificate cert)
{
    DA.push_back(cert);
}

void Equipment::writeCertificateToFile(Poco::Crypto::X509Certificate cert, std::string path)
{
    std::vector<Poco::Crypto::X509Certificate> v;
    v.push_back(cert);

    Poco::Crypto::X509Certificate::writePEM(path,v);
}

Poco::Crypto::X509Certificate Equipment::readCertificateFromFile(std::string path)
{
    std::vector<Poco::Crypto::X509Certificate> v;
    v = Poco::Crypto::X509Certificate::readPEM(path);

    return  v[0];
}

int Equipment::getFileSize(std::string path)
{
    std::ifstream file(path);
    // get length of file:
    file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);
    file.close();

    return length;
}

//GETTERS
std::string Equipment::getName() { return mId; }
RSAKeyPair Equipment::getKeys() { return mKeys; }
int Equipment::getPort() { return mPort; }
/**
 * This getter is used specifically to get back a certificate and not a shared pointer on one
 * @return
 */
Poco::Crypto::X509Certificate Equipment::getSelfSignedCertificate() { return *mSelfSignedCertificate; }

//SETTERS
void Equipment::setName(std::string newId) { mId=newId; }
void Equipment::setKeys(RSAKeyPair newKeys) { mKeys=newKeys; }
void Equipment::setPort(int newPort) { mPort=newPort; }
