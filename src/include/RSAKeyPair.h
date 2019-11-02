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

#define MAX_PATH 200


class RSAKeyPair {

private:
    const char * mPublicKey;
    const char * mPrivateKey;
    EVP_PKEY * pkey;
    EVP_PKEY * pbkey;
    bool generate_key();

public:
    //default constructor should simply generate keys and assign them to the fields
    RSAKeyPair();

    //GETTERS
    const char * getPublicKeyStr();
    const char * getPrivateKeyStr();
    EVP_PKEY * getPublicKey();
    EVP_PKEY * getPrivateKey();


};


#endif //HOMENETCTL_RSAKEYPAIR_H
