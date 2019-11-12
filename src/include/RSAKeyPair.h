//
// Created by romain on 15/10/2019.
//

#ifndef HOMENETCTL_RSAKEYPAIR_H
#define HOMENETCTL_RSAKEYPAIR_H

#include <iostream>
#include <exception>
#include <openssl/err.h>
#include "openssl/pem.h"
#include "openssl/evp.h"
#include "openssl/x509.h"
#include <openssl/bio.h>
#include <fstream>
#include <cstring>
#include <memory>
#include "Poco/Crypto/RSAKey.h"
#include <filesystem>
#include <memory>

#define MAX_PATH 200


class RSAKeyPair {


private:
    /* Poco::Crypto::RSAKey loadKeys(bool priv); */
    std::string mId;
    std::filesystem::path mPath = "/tmp/homenetctl";

public:
    bool generate_key(std::string keyname = "");
    using Key_ptr = std::unique_ptr<Poco::Crypto::RSAKey>;
    //default constructor should simply generate keys and assign them to the fields
    RSAKeyPair(std::string id="");
    RSAKeyPair(std::string keyname, Poco::Crypto::X509Certificate cert);
    std::unique_ptr<Poco::Crypto::RSAKey> loadKeys(bool priv);

    //GETTERS
    const std::filesystem::path getPublicKeyPath();
    const std::filesystem::path getPrivateKeyPath();
    /* EVP_PKEY * getPublicKey(); */
    /* EVP_PKEY * getPrivateKey(); */


};


#endif //HOMENETCTL_RSAKEYPAIR_H
