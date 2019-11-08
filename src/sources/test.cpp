#include "test.h"

/* bool TestHandler::test1(){ */
/*     Poco::Crypto::EVPPKey key = Poco::Crypto::EVPPKey("", "/tmp/homenetctl/test"); */
/*     Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test"); */
/*     key.save("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test"); */
/*     /1* RSAKeyPair key = RSAKeyPair(); *1/ */
/*     char nom[10] = "as"; */
/*     char nom2[10] = "fuck"; */
/*     /1* std::cout << "test " << key.getPublicKeyStr() << std::endl; *1/ */
/*     Certificate testCert(nom, key, 10); */
/*     X509* certificate = testCert.mCertificate.dup(); */
/*     int status; */
/*     X509_STORE_CTX *ctx; */
/*     ctx = X509_STORE_CTX_new(); */
/*     X509_STORE *store = X509_STORE_new(); */

/*     X509_STORE_add_cert(store, certificate); */

/*     X509_STORE_CTX_init(ctx, store, certificate, NULL); */

/*     status = X509_verify_cert(ctx); */

/*     // This test should return false cause the name are different */
/*     /1* Certificate testCert2(nom2, key, 10); *1/ */
/*     /1* testCert2.checkCertificate(testCert.mCertificate); *1/ */
/*     return (status == 1); */
/* }; */

/* bool TestHandler::test2(){ */
/*     Poco::Crypto::EVPPKey key = Poco::Crypto::EVPPKey("", "/tmp/homenetctl/test"); */
/*     Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/test.pub", "/tmp/homenetctl/test"); */
/*     /1* RSAKeyPair key = RSAKeyPair(); *1/ */
/*     char nom[10] = "name1"; */
/*     char nom2[10] = "name2"; */
/*     /1* std::cout << "test " << key.getPublicKeyStr() << std::endl; *1/ */
/*     Certificate testCert(nom, key, 10); */
/*     Certificate testCert2(nom2, key, 10); */
/*     return (!testCert2.checkCertificate(testCert.mCertificate)); */
/* } */

bool TestHandler::test3(){
    RSAKeyPair a;
    a.generate_key("1");
    Poco::Crypto::EVPPKey key = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_1.pem", "/tmp/homenetctl/privateKey_1.pem");
    std::string nom = "name";
    return CertificateHandler::checkCertificate(*CertificateHandler::selfSign(nom, key, 30), *CertificateHandler::selfSign(nom,key,30));
}

bool TestHandler::test4(){
    RSAKeyPair a;
    a.generate_key("1");
    a.generate_key("2");
    a.generate_key("3");
    a.generate_key("4");

    Poco::Crypto::EVPPKey keyClient = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey.pem", "/tmp/homenetctl/privateKey.pem");
    Poco::Crypto::EVPPKey key1 = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_1.pem", "/tmp/homenetctl/privateKey_1.pem");
    Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_2.pem", "/tmp/homenetctl/privateKey_2.pem");
    Poco::Crypto::EVPPKey key3 = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_3.pem", "/tmp/homenetctl/privateKey_3.pem");
    Poco::Crypto::EVPPKey keyServer = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_1.pem", "/tmp/homenetctl/privateKey_4.pem");

    std::string nom = "name";
    std::string nom1 = "name1";
    std::string nom2 = "name2";
    std::string nom3 = "name3";
    std::string nom4 = "name4";

    auto cert1 = CertificateHandler::sign(nom1, key1,nom, keyClient,10);
    auto cert2 = CertificateHandler::sign(nom2, key2, nom1, key1, 10);
    auto cert3 = CertificateHandler::sign(nom3, key3, nom2, key2, 10);
    auto cert4 = CertificateHandler::sign(nom4, keyServer, nom3, key3,10);

    auto selfsigncert = CertificateHandler::selfSign(nom4, keyServer,10);

    Poco::Crypto::X509Certificate::List chainCert;
    chainCert.push_back(*cert1);
    chainCert.push_back(*cert2);
    chainCert.push_back(*cert3);
    chainCert.push_back(*cert4);

    return CertificateHandler::checkCertificateChain(chainCert, *selfsigncert);
}

bool TestHandler::test5(){

    RSAKeyPair a;
    a.generate_key("1");
    a.generate_key("2");
    a.generate_key("3");
    a.generate_key("4");

    Poco::Crypto::EVPPKey keyClient = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey.pem", "/tmp/homenetctl/privateKey.pem");
    Poco::Crypto::EVPPKey key1 = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_1.pem", "/tmp/homenetctl/privateKey_1.pem");
    Poco::Crypto::EVPPKey key2 = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_2.pem", "/tmp/homenetctl/privateKey_2.pem");
    Poco::Crypto::EVPPKey key3 = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_3.pem", "/tmp/homenetctl/privateKey_3.pem");
    Poco::Crypto::EVPPKey keyServer = Poco::Crypto::EVPPKey("/tmp/homenetctl/publicKey_1.pem", "/tmp/homenetctl/privateKey_4.pem");

    std::string nom = "name";
    std::string nom1 = "name1";
    std::string nom2 = "name2";
    std::string nom3 = "name3";
    std::string nomServ = "nameServ";

    auto cert1 = CertificateHandler::sign(nom1, key1,nom, keyClient,10);
    auto cert2 = CertificateHandler::sign(nom2, key2, nom1, key1, 10);
    auto cert3 = CertificateHandler::sign(nom3, key3, nom2, key2, 10);
    auto cert4 = CertificateHandler::sign(nomServ, keyServer, nom3, key3,10);

    auto selfsigncert = CertificateHandler::selfSign(nomServ, keyServer,10);
    CertificateHandler handler(keyServer, nomServ);
    handler.addCertificate(cert4, keyServer);
    handler.addCertificate(cert3, key3);
    handler.addCertificate(cert2, key2);
    handler.addCertificate(cert1, key1);
    return CertificateHandler::checkCertificateChain(handler.findChainCert(cert1), *selfsigncert);
}

bool TestHandler::test6()
{
    Equipment A("A",1234);
    A.display_CA();
    return true;
}
