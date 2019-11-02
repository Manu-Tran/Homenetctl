#ifndef HOMENETCTL_CERTIFICATEHANDLER_H
#define HOMENETCTL_CERTIFICATEHANDLER_H

#include <string>
#include <cstdio>
#include <iostream>
#include <memory>

#include <Poco/Crypto/X509Certificate.h>
#include "RSAKeyPair.h"

class CertificateHandler {

private:
    long int mSeqnum = 0;

public:
    using X509Ptr = std::shared_ptr<Poco::Crypto::X509Certificate>;

    static X509Ptr sign(std::string issuerName, EVP_PKEY *issuerKey, std::string clientName, EVP_PKEY *clientKey, int validityDays);
    static X509Ptr selfSign(std::string name, EVP_PKEY *keyPair, int validityDays);

    static bool checkCertificateChain( Poco::Crypto::X509Certificate::List certChain, Poco::Crypto::X509Certificate userCert);
    static bool checkCertificate( Poco::Crypto::X509Certificate clientCert, Poco::Crypto::X509Certificate userCert);
};


#endif //HOMENETCTL_CERTIFICATE_H
