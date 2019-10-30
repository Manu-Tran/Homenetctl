//
// Created by romain on 15/10/2019.
//

#include "certificate.h"
#include <memory>

/// Generate a new certificate
/// @param name
/// @param pubkey
/// @param validityDate
/// @return a new certificate
Certificate::Certificate(char *nom, EVP_PKEY *pubKey, int validityDays)
: mCertificate(X509_new())
{
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
        X509_NAME_free(name);
    }
    mCertificate = Poco::Crypto::X509Certificate(x509);
}

/* Check whether the client certificate has been signed by our
 * @param Client certificate
 * @return result of the verification
 */
bool Certificate::checkCertificate(Poco::Crypto::X509Certificate clientCert)
{
    int status;
    X509 * x509ClientCert = clientCert.dup();
    X509 * x509Cert = mCertificate.dup();
    X509_STORE_CTX *ctx;

    ctx = X509_STORE_CTX_new();
    X509_STORE *store = X509_STORE_new();

    // Adding certificate to the chain in order to prepare for the verification
    X509_STORE_add_cert(store, x509ClientCert);
    X509_STORE_CTX_init(ctx, store, x509Cert, NULL);

    // The actual verification
    status = X509_verify_cert(ctx);

    // Because OpenSSL is a "C++" library
    X509_free(x509Cert);
    X509_free(x509ClientCert);
    X509_STORE_CTX_free(ctx);
    X509_STORE_free(store);

    if(status == 1)
    {
        printf("Certificate verified ok\n");
        return true;
    } else
    {
        printf("Certificate NOT verified\n");
        /* printf("%s\n", X509_verify_cert_error_string(ct)); */
        return false;
    }
}
