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

void Equipment::saveEquipment()
{
    std::string path = "/tmp/homenetctl/"+mId+"/saved.txt";
    RSAKeyPair bufferKey;
    std::ofstream file; // out file stream
    file.open(path);

    //Save the port
    file << mPort << std::endl;

    //save the certs
    CertificateHandler handler(Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()), mId);

    //for each cert in CA, extract the public key that was signed and add it and the certificate to the handler like this:
    X509Ptr x509;

    for (auto itr(CA.begin()); itr != CA.end(); itr++){
        bufferKey = RSAKeyPair((*itr).commonName(), (*itr));
        bufferKey.setId((*itr).commonName());
        x509 = std::make_shared<Poco::Crypto::X509Certificate>(*itr);
        handler.addCertificate(x509,Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()));
    }

    for (auto itr(DA.begin()); itr != DA.end(); itr++){
        bufferKey = RSAKeyPair((*itr).commonName(), (*itr));
        bufferKey.setId((*itr).commonName());
        x509 = std::make_shared<Poco::Crypto::X509Certificate>(*itr);
        handler.addCertificate(x509,Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()));
    }

    handler.save();

    file << handler.getCertsSavedPath() + "knownCerts.pem" << std::endl;

    file.close();
}

Equipment::Equipment(std::string id)
{
    std::string path = "/tmp/homenetctl/"+id+"/saved.txt";
    std::string certsPath, str;

    std::ifstream file;
    file.open(path);
    //The port
    std::getline(file, str);
    mPort = std::stoi(str);

    //Create the key using the ID
    mKeys = RSAKeyPair(id);

    //The list of certificates
    std::getline(file, certsPath);

    //Fill out CA and DA using --> load from cert handler and fillCA/fillDA
    CertificateHandler handler(Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()), id);

    handler.load();

    //There now fill CA and DA

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
