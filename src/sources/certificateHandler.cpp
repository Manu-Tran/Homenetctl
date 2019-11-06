//
// Created by romain on 15/10/2019.
//

#include "certificateHandler.h"
#include <memory>

namespace fs = std::filesystem;

CertificateHandler::CertificateHandler(EVP_PKEY * privKey, std::string name, std::string certDirPath, std::string selfSignedCertName)
    : mCertDir(certDirPath)
{
    CertificateHandler::X509Ptr selfSignedX509;
    if (fs::exists(certDirPath / (fs::path)selfSignedCertName)){
        selfSignedX509 = std::make_shared<Poco::Crypto::X509Certificate>(certDirPath / (fs::path)selfSignedCertName);
    } else {
        selfSignedX509 = CertificateHandler::selfSign(name, privKey, 30);
    }

    bool abort = false;
    if (selfSignedX509->issuerName() != name){
        abort = true;
        std::cout << "ERROR : The given name does not match the one on the self signed certificate";
    }

    if (CertificateHandler::checkCertificate(*CertificateHandler::selfSign(name, privKey, 30), *selfSignedX509)){
        abort = true;
        std::cout << "ERROR : The given private key does not match the public key on the self signed certificate";
    }

    if (abort){
        std::exit(EXIT_FAILURE);
    }
    /* mX509Searcher[DevId(name,  )] */
}


/// Generate a new signed certificate
/// @param nameIssuer
/// @param privkeyIssuer
/// @param nameClient name of the client that will need the certificate
/// @param pubkeyClient public key of the client that will need the certificate
/// @param validityDate
/// @return a pointer to a new certificate

CertificateHandler::X509Ptr CertificateHandler::sign(std::string issuerName, EVP_PKEY *issuerKey, std::string clientName, EVP_PKEY *clientKey, int validityDays)
{
    X509 *x509 = X509_new();
    char * cIssuerName = (char *) issuerName.c_str();
    char * cClientName = (char *) clientName.c_str();
    if(!x509) {
        std::cerr << "Unable to create X509 structure." << std::endl;
    }
    /* Set the date limits of the certificate */
    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), validityDays*24*60*60);

    /* Set the public key of the certificate */
    X509_set_pubkey(x509, clientKey);

    /* We want to copy the subject name to the issuer name. */
    X509_NAME * x509IssuerName = X509_NAME_new();
    X509_NAME * x509ClientName = X509_NAME_new();


    X509_NAME_add_entry_by_txt(x509IssuerName, "CN", MBSTRING_ASC, (unsigned char *)cIssuerName, -1, -1, 0);
    X509_NAME_add_entry_by_txt(x509ClientName, "CN", MBSTRING_ASC, (unsigned char *)cClientName, -1, -1, 0);
    /* Set the issuer name. */
    X509_set_issuer_name(x509, x509IssuerName);
    X509_set_subject_name(x509, x509ClientName);

    /* Sign the certificate with our key. */
    if(!X509_sign(x509, issuerKey, EVP_sha1()))
    {
        std::cerr << "Error signing certificate." << std::endl;
        X509_free(x509);
    }
    X509_NAME_free(x509IssuerName);
    X509_NAME_free(x509ClientName);
    return std::make_shared<Poco::Crypto::X509Certificate>(x509);
}

/// Generate a new self signed certificate
/// @param name
/// @param privkeyIssuer
/// @param validityDate
/// @return a pointer to a new self signed certificate

CertificateHandler::X509Ptr CertificateHandler::selfSign(std::string name, EVP_PKEY* keyPair, int validityDays){
    return CertificateHandler::sign(name, keyPair, name, keyPair, validityDays);
}

/* Check whether the client certificate has been signed by our
 * @param Client certificate
 * @return result of the verification
 */
bool CertificateHandler::checkCertificateChain( Poco::Crypto::X509Certificate::List certChain, Poco::Crypto::X509Certificate selfSignedCert)
{
    bool status = true;

    //Adding the entire list to the store
    Poco::Crypto::X509Certificate::List::iterator itr;
    /* int i(0); */
    for (itr = certChain.begin(); (itr+1) != certChain.end(); itr++){
        if (!itr->issuedBy(*(itr+1))){
            status = false;
            /* std::cout << i; */
        }
        /* i++; */
    }
    status = status and itr->issuedBy(selfSignedCert);
    /* std::stringstream ss; */
    /* selfSignedCert.print( ss ); */
    /* std::cout << ss.str(); */
    std::cout << CertificateHandler::getPublicKey(selfSignedCert);
    return status;
}


/* Check whether the client certificate has been signed by our
 * @param Client certificate
 * @return result of the verification
 */
bool CertificateHandler::checkCertificate( Poco::Crypto::X509Certificate clientCert, Poco::Crypto::X509Certificate selfSignedCert)
{
    return clientCert.issuedBy(selfSignedCert);
}

/* Return the string value of the public key in the X509Certificate
 * @param certificate's key to print
 * @return Public key in PEM format in a string
 */
std::string CertificateHandler::getPublicKey(Poco::Crypto::X509Certificate cert){
    std::unique_ptr<std::stringstream>  ss = std::make_unique<std::stringstream>();
    Poco::Crypto::RSAKeyImpl a = Poco::Crypto::RSAKeyImpl(cert);
    a.save(ss.get());
    return ss->str();
}
