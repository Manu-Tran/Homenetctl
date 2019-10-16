//
// Created by romain on 15/10/2019.
//

#ifndef HOMENETCTL_CERTIFICATE_H
#define HOMENETCTL_CERTIFICATE_H

#include <string>
#include <cstdio>
#include <iostream>

#include <openssl/pem.h>
#include <openssl/x509.h>

class Certificate {

private:
    long int mSeqnum = 0;
    X509* mCertificate; //to be changed for the right type

public:
    Certificate(char* nom, EVP_PKEY * pubKey, int validityDays);
    bool checkCertfification( EVP_PKEY * publicKey);

};


#endif //HOMENETCTL_CERTIFICATE_H
