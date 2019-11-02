#include "test.h"

bool TestHandler::test1(){
    Poco::Crypto::EVPPKey key = Poco::Crypto::EVPPKey("", "/tmp/homenetctl/test");
    Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test");
    key.save("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test");
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

bool TestHandler::test2(){
    Poco::Crypto::EVPPKey key = Poco::Crypto::EVPPKey("", "/tmp/homenetctl/test");
    Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test");
    /* RSAKeyPair key = RSAKeyPair(); */
    char nom[10] = "name1";
    char nom2[10] = "name2";
    /* std::cout << "test " << key.getPublicKeyStr() << std::endl; */
    Certificate testCert(nom, key, 10);
    Certificate testCert2(nom2, key, 10);
    return (!testCert2.checkCertificate(testCert.mCertificate));
}

bool TestHandler::test3(){
    Poco::Crypto::RSAKey * key =new Poco::Crypto::RSAKey("", "/tmp/homenetctl/test2");
    Poco::Crypto::EVPPKey kkey(key);
    char nom[10] = "name";
    Certificate testCert(nom, kkey, 10);
    Certificate testCert2(nom,kkey, 10);
    return (testCert2.checkCertificate(testCert.mCertificate));
}

bool TestHandler::test4(){
    Poco::Crypto::EVPPKey keyclient = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test");
    Poco::Crypto::EVPPKey key1 = Poco::Crypto::EVPPKey("", "/tmp/homenetctl/test1");
    Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/test2.pub", "/tmp/homenetctl/test2");
    Poco::Crypto::EVPPKey key3 = Poco::Crypto::EVPPKey("/tmp/homenetctl/test3.pub", "/tmp/homenetctl/test3");
    Poco::Crypto::EVPPKey keynewclient = Poco::Crypto::EVPPKey("/tmp/homenetctl/test4.pub", "/tmp/homenetctl/test4");
    std::string nom = "name";
    std::string nom1 = "name1";
    std::string nom2 = "name2";
    std::string nom3 = "name3";
    std::string nom4 = "name4";
    EVP_PKEY * aa = (EVP_PKEY *) key1;
    auto b = CertificateHandler::selfSign(nom, aa,10);
    /* auto a = CertificateHandler::sign(nom,(EVP_PKEY *) key1, nom2,(EVP_PKEY *) key2,10); */
    /* Poco::Crypto::X509Certificate::List a(1,*(CertificateHandler::sign(nom1, key1, nom, keyclient, 10 ))); */

    return true;
}

bool TestHandler::test5(){
    Poco::Crypto::EVPPKey keyclient = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test");
    char nom1[10] = "name1";
    char nom2[10] = "name2";
    char nom3[10] = "name3";
    char nom4[10] = "name4";
    Certificate cert(nom1, keyclient,10);
    return true;
}
