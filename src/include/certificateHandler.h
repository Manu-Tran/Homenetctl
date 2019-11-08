#ifndef HOMENETCTL_CERTIFICATEHANDLER_H
#define HOMENETCTL_CERTIFICATEHANDLER_H

#include <string>
#include <cstdio>
#include <iostream>
#include <memory>

#include <Poco/Crypto/X509Certificate.h>
#include "RSAKeyPair.h"
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>

/* int test() */
/* { */
/*     std::vector<char> input({ 'a', 'b', 'c' }); */

/*     std::string s; */
/*     std::transform(input.begin(), input.end(), std::back_inserter(s), */
/*             [](char c) { */
/*             return c; */
/*             }); */

/*     std::cout << s; */

/*     return 0; */
/* } */

class CertificateHandler {

public:
    using X509Ptr = std::shared_ptr<Poco::Crypto::X509Certificate>;
    using DevId = std::pair<std::string, std::string>;
    struct certificate_node
    {
        std::vector<std::shared_ptr<certificate_node>> children;
        std::weak_ptr<certificate_node> parent;
        CertificateHandler::X509Ptr certificate;
    };

private:
    // Map between a pair<Id,PublicKey> to a pointer to a Poco::Crypto::X509Certificate
    std::map<DevId, std::weak_ptr<certificate_node> >mX509Searcher;
    std::filesystem::path mCertDir;
    std::shared_ptr<certificate_node> mSelfSignedCert;

public:
    CertificateHandler(EVP_PKEY * priKey, std::string name, std::string certDirPath="/tmp/homenetctl/cert/", std::string selfSignedCertName="selfSigned.pem");
    void addCertificate(X509Ptr cert, Poco::Crypto::RSAKey signerPubKey);
    Poco::Crypto::X509Certificate::List findChainCert(X509Ptr cert);

    static X509Ptr sign(std::string issuerName, EVP_PKEY *issuerKey, std::string clientName, EVP_PKEY *clientKey, int validityDays);
    static X509Ptr selfSign(std::string name, EVP_PKEY *keyPair, int validityDays);

    static bool checkCertificateChain( Poco::Crypto::X509Certificate::List certChain, Poco::Crypto::X509Certificate userCert);
    static bool checkCertificate( Poco::Crypto::X509Certificate clientCert, Poco::Crypto::X509Certificate userCert);
    static std::string getPublicKey(Poco::Crypto::X509Certificate cert);
    static std::string keyToString(Poco::Crypto::RSAKey key);

};

#endif //HOMENETCTL_CERTIFICATE_H
