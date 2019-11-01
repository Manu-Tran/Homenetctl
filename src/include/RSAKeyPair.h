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
    bool generate_key();
    /* Poco::Crypto::RSAKey loadKeys(bool priv); */
    std::filesystem::path mPath = "/tmp/homenetctl";
    std::filesystem::path mPubKeyPath = mPath / (std::filesystem::path) "publicKey.pem";
    std::filesystem::path mPrivKeyPath = mPath / (std::filesystem::path) "privateKey.pem";

public:
    using Key_ptr = std::unique_ptr<Poco::Crypto::RSAKey>;
    //default constructor should simply generate keys and assign them to the fields
    RSAKeyPair();
    std::unique_ptr<Poco::Crypto::RSAKey> loadKeys(bool priv);

    //GETTERS
    /* const std::string getPublicKeyPath(); */
    /* const std::string getPrivateKeyPath(); */
    /* EVP_PKEY * getPublicKey(); */
    /* EVP_PKEY * getPrivateKey(); */


};


#endif //HOMENETCTL_RSAKEYPAIR_H
