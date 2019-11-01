#ifndef HOMENETCTL_TEST_H
#define HOMENETCTL_TEST_H
#include <iostream>
#include <string>
#include <vector>
#include "certificate.h"
#include "RSAKeyPair.h"
#include "equipment.h"

#include <openssl/pem.h>
#include <openssl/x509.h>
#include <Poco/Crypto/EVPPKey.h>

bool test1(){
    Poco::Crypto::EVPPKey key = Poco::Crypto::EVPPKey("", "/tmp/homenetctl/swag");
    Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/swag.pub", "/tmp/homenetctl/swag");
    key.save("/tmp/homenetctl/lol.pub", "/tmp/homenetctl/lol");
    /* RSAKeyPair key = RSAKeyPair(); */
    char nom[10] = "as";
    char nom2[10] = "fuck";
    /* std::cout << "test " << key.getPublicKeyStr() << std::endl; */
    Certificate testCert(nom, key, 10);
    X509* certificate = testCert.mCertificate.dup();
    int status;
    X509_STORE_CTX *ctx;
    ctx = X509_STORE_CTX_new();
    X509_STORE *store = X509_STORE_new();

    X509_STORE_add_cert(store, certificate);

    X509_STORE_CTX_init(ctx, store, certificate, NULL);

    status = X509_verify_cert(ctx);

    // This test should return false cause the name are different
    /* Certificate testCert2(nom2, key, 10); */
    /* testCert2.checkCertificate(testCert.mCertificate); */
    return (status == 1);
};

bool test2(){
    Poco::Crypto::EVPPKey key = Poco::Crypto::EVPPKey("", "/tmp/homenetctl/test");
    Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test");
    /* RSAKeyPair key = RSAKeyPair(); */
    char nom[10] = "name1";
    char nom2[10] = "name2";
    /* std::cout << "test " << key.getPublicKeyStr() << std::endl; */
    Certificate testCert(nom, key, 10);
    Certificate testCert2(nom2, key, 10);
    return (!testCert2.checkCertificate(testCert.mCertificate));
};

bool test3(){
    Poco::Crypto::EVPPKey key = Poco::Crypto::EVPPKey("/tmp/homenetctl/test1.pub", "/tmp/homenetctl/test1");
    char nom[10] = "name";
    Certificate testCert(nom, key, 10);
    Certificate testCert2(nom, key, 10);
    return (testCert2.checkCertificate(testCert.mCertificate));
};

bool test4(){
    Poco::Crypto::EVPPKey keyclient = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test");

    return true;
};

bool test5(){
    Poco::Crypto::EVPPKey keyclient = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test");
    char nom1[10] = "name1";
    char nom2[10] = "name2";
    char nom3[10] = "name3";
    char nom4[10] = "name4";
    Certificate cert(nom1, keyclient,10);
    return true;
};

void launchTests(){
    std::cout << "Test 1... " << (test1() ? "Ok" : "Failed") << std::endl;
    std::cout << "Test 2... " << (test2() ? "Ok" : "Failed") << std::endl;
    std::cout << "Test 3... " << (test3() ? "Ok" : "Failed") << std::endl;
    std::cout << "Test 4... " << (test4() ? "Ok" : "Failed") << std::endl;
    std::cout << "Test 5... " << (test5() ? "Ok" : "Failed") << std::endl;
};

#endif
