//
// Created by romain on 15/10/2019.
//

#include "certificate.h"


/// Generate a new certificate
/// @param name
/// @param pubkey
/// @param validityDate
/// @return a new certificate
Certificate::Certificate(char *nom, EVP_PKEY *pubKey, int validityDays){
    X509 *x509 = X509_new();
    if(!x509) {
        std::cerr << "Unable to create X509 structure." << std::endl;
    }
    /* Set the date limits of the certificate */
    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), validityDays*24*60*60);

    /* Set the public key of the certificate */
    X509_set_pubkey(x509, pubKey);

    /* We want to copy the subject name to the issuer name. */
    X509_NAME * name = X509_get_subject_name(x509);


    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *)nom, -1, -1, 0);
    /* Set the issuer name. */
    X509_set_issuer_name(x509, name);

    /* Sign the certificate with our key. */
    if(!X509_sign(x509, pubKey, EVP_sha1()))
    {
        std::cerr << "Error signing certificate." << std::endl;
        X509_free(x509);
    }
}

bool Certificate::checkCertfification(EVP_PKEY * publicKey)
{
    return false;
    //check signature using parameter key
};
