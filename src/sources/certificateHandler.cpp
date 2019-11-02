//
// Created by romain on 15/10/2019.
//

#include "certificateHandler.h"
#include <memory>


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
bool CertificateHandler::checkCertificateChain( Poco::Crypto::X509Certificate::List certChain, Poco::Crypto::X509Certificate userCert)
{
    int status;

    X509_STORE_CTX *ctx;
    X509_STORE *store = X509_STORE_new();

    //Adding the entire list to the store
    for (auto itr(certChain.begin()); itr != certChain.end(); itr++){
        X509_STORE_add_cert(store, itr->dup());
    }
    X509 * x509Cert = userCert.dup();

    ctx = X509_STORE_CTX_new();

    // Adding certificate to the chain in order to prepare for the verification
    X509_STORE_CTX_init(ctx, store, x509Cert, NULL);

    // The actual verification
    status = X509_verify_cert(ctx);

    // Because OpenSSL is a "C++" library
    X509_free(x509Cert);
    X509_STORE_CTX_free(ctx);
    X509_STORE_free(store);

    if(status == 1)
    {
        std::cout << ("Certificate verified ! ");
        return true;
    } else
    {
        std::cout << ("Certificate NOT verified ! ");
        return false;
    }
}
bool checkCertificate( Poco::Crypto::X509Certificate clientCert, Poco::Crypto::X509Certificate userCert)
{
    return CertificateHandler::checkCertificateChain(Poco::Crypto::X509Certificate::List(1,clientCert), userCert);
}

