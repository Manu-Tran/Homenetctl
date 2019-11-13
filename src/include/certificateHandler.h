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
#include <deque>

class CertificateHandler {

public:
    using X509Ptr = std::shared_ptr<Poco::Crypto::X509Certificate>;
    using DevId = std::pair<std::string, std::string>;
    struct certificate_node
    {
        std::vector<std::shared_ptr<certificate_node>> children;
        std::weak_ptr<certificate_node> parent;
        CertificateHandler::X509Ptr certificate;
        bool isRoot;
    };

private:
    // Map between a pair<Id,PublicKey> to a pointer to a node of the tree
    std::map<DevId, std::weak_ptr<certificate_node> >mX509Searcher;
    std::map<std::string, Poco::Crypto::RSAKey> mPubKeyIndex;
    std::filesystem::path mCertDir;
    std::shared_ptr<certificate_node> mSelfSignedCert;

    std::string recursionSave(certificate_node node);

public:
    CertificateHandler(EVP_PKEY * priKey, std::string name, std::string certDirPath="/tmp/homenetctl/", std::string selfSignedCertName="selfSigned.pem");
    bool addCertificate(X509Ptr cert);
    bool addCertificate(X509Ptr cert, Poco::Crypto::RSAKey signerPubKey);
    Poco::Crypto::X509Certificate::List findChainCert(X509Ptr cert);

    bool addPubKey(std::string id, Poco::Crypto::RSAKey key);

    void moveNodeToCA(X509Ptr cert);
    /* void synchronisation(Poco::Crypto::X) */

    bool isStored(X509Ptr cert);

    static X509Ptr sign(std::string issuerName, EVP_PKEY *issuerKey, std::string clientName, EVP_PKEY *clientKey, int validityDays);
    static X509Ptr selfSign(std::string name, EVP_PKEY *keyPair, int validityDays);

    static bool checkCertificateChain( Poco::Crypto::X509Certificate::List certChain, Poco::Crypto::X509Certificate userCert);
    static bool checkCertificate( Poco::Crypto::X509Certificate clientCert, Poco::Crypto::X509Certificate userCert);

    // Utility functions
    static std::string getPublicKey(Poco::Crypto::X509Certificate cert);
    static std::string keyToString(Poco::Crypto::RSAKey key);
    static std::string getSignatureId(DevId id);
    static DevId getIdFromX509(Poco::Crypto::X509Certificate cert);

    Poco::Crypto::X509Certificate::List getAllNodes();
    void save();
    void load();
    static std::map<std::string,Poco::Crypto::RSAKey> readPubKeys(std::string path);

    X509Ptr getSelfSigned();
    std::string getCertsSavedPath();
};

#endif //HOMENETCTL_CERTIFICATE_H
