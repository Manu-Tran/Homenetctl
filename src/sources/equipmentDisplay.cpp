//
// Created by romain on 12/11/2019.
//

#include <Socket.h>
#include "equipment.h"

//DISPLAY
/**
 * Displays CA
 */
void Equipment::display_CA()
{
    std::cout << "========================================" << std::endl;
    std::cout << "Here is the CA of equipment " << this->mId << std::endl;
    for(const auto& cert : this->CA)
        Equipment::display_certificate(cert);
    std::cout << "========================================" << std::endl;
}
/**
 * Displays DA
 */
void Equipment::display_DA()
{
    std::cout << "========================================" << std::endl;
    std::cout << "Here is the DA of equipment " << this->mId << std::endl;
    for(const auto& cert : this->DA)
        Equipment::display_certificate(cert);
    std::cout << "========================================" << std::endl;
}
/**
 * Displays both CA and DA
 */
void Equipment::display()
{
    display_CA();
    display_DA();
}

/**
 * Displays a given certificate's information
 * @param certif
 */
void Equipment::display_certificate(const Poco::Crypto::X509Certificate& certif)
{
    std::string certPath = "/tmp/homenetctl/displayCert.pem";
    std::string keyPath;
    std::string public_key;

    //Write cert to temp file
    std::vector<Poco::Crypto::X509Certificate> v;
    v.push_back(certif);
    Poco::Crypto::X509Certificate::writePEM(certPath,v);

    //read from it into a string
    std::string line, cert_content;
    std::ifstream file(certPath);
    while (std::getline(file, line))
        cert_content += line + "\n";

    //write key to temp file
    RSAKeyPair pubKey(certif.commonName(), certif);
    keyPath = pubKey.getPublicKeyPath();

    //get the public key string back from the file
    std::ifstream keyFile(keyPath);
    while (std::getline(keyFile, line))
        public_key += line + "\n";

    std::string issuerName = certif.issuerName();
    std::cout << "========================================" << std::endl;
    std::cout << "GENERAL INFORMATION:" << std::endl;
    std::cout << "Public key comes from: " << certif.commonName() << std::endl;
    std::cout << "Certificate was signed by: " << issuerName.erase(0,4) << std::endl;
    std::cout << "Valid until: " << certif.expiresOn().day() << "/" << certif.expiresOn().month() << "/"  << certif.expiresOn().year() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "CERTIFICATE DETAILS:" << std::endl;
    std::cout << cert_content << std::endl;
    std::cout << public_key << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    remove(certPath.c_str());
}