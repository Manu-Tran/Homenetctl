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
        AddInCA(mSelfSignedCertificate);
    }

}

/**
 * Creates a new certificate using a self signed certificate (extracts the public key) and his own certificate.
 * @param cert
 * @param clientName
 * @return
 */
Poco::Crypto::X509Certificate Equipment::newCertificate(CertificateHandler::X509Ptr cert, std::string clientName)
{
    //get key from certificate
    RSAKeyPair clientKey(clientName, *cert);

    //create a new one and sign it using my key
    auto cert1 = CertificateHandler::sign(mId,Poco::Crypto::EVPPKey(mKeys.loadKeys(true).get()),clientName,Poco::Crypto::EVPPKey(clientKey.loadKeys(false).get()),30);

    //return it
    return *cert1;
}

/**
 * Adds an equipment in CA with the shape of a triplet (ID,PublicKey,Certificate signed by this)
 * @param id
 * @param pubkey
 * @param cert
 */
void Equipment::AddInCA(CertificateHandler::X509Ptr cert)
{
    CA.push_back(*cert);
}

//DISPLAY
/**
 * Displays CA
 */
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
/**
 * Displays DA
 */
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
/**
 * Displays both CA and DA
 */
void Equipment::display()
{
    display_CA();
    display_DA();
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
