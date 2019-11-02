#ifndef HOMENETCTL_CERTIFICATE_H
#define HOMENETCTL_CERTIFICATE_H

#include <string>
#include <cstdio>
#include <iostream>

#include <Poco/Crypto/X509Certificate.h>

class Certificate {

private:
    long int mSeqnum = 0;

public:
    Poco::Crypto::X509Certificate mCertificate; //to be changed for the right type
    Certificate();
    Certificate(char* nom, EVP_PKEY * pubKey, int validityDays);
    bool checkCertificate( Poco::Crypto::X509Certificate clientCert);

};


#endif //HOMENETCTL_CERTIFICATE_H
