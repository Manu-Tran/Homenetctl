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


class RSAKeyPair {

private:
    char * publicKey;
    char * privateKey;
    bool generate_key();

public:
    //default constructor should simply generate keys and assign them to the fields
    RSAKeyPair();

    //GETTERS
    char * getPublicKey();
    char * getPrivateKey();


};


#endif //HOMENETCTL_RSAKEYPAIR_H
