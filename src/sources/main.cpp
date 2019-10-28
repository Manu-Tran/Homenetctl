#include <iostream>
#include <string>
#include <vector>
#include "certificate.h"

#include <openssl/pem.h>
#include <openssl/x509.h>

/* Generates a 2048-bit RSA key. */
EVP_PKEY * generate_key()
{
    /* Allocate memory for the EVP_PKEY structure. */
    EVP_PKEY * pkey = EVP_PKEY_new();
    if(!pkey)
    {
        std::cerr << "Unable to create EVP_PKEY structure." << std::endl;
        return NULL;
    }

    /* Generate the RSA key and assign it to pkey. */
    RSA * rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    if(!EVP_PKEY_assign_RSA(pkey, rsa))
    {
        std::cerr << "Unable to generate 2048-bit RSA key." << std::endl;
        EVP_PKEY_free(pkey);
        return NULL;
    }

    /* The key has been generated, return it. */
    return pkey;
}

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> \n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-r,--reset\t\tReset the configuration\n"
              << "\t-s <PORT>,--server <PORT>\t\tReset the configuration\n"
              << "\t--test\t\tLaunch tests"
              << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout <<"test launched 1 ! ";
    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }
    std::vector <std::string> sources;
    std::string port;
    bool test=false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } else
        if ((arg == "-s") || (arg == "--server")) {
            if (i + 1 < argc) {
                port = argv[i++];
            } else {
                  std::cerr << "--server option requires one argument." << std::endl;
                return 1;
            }
        } else
        if ((arg == "-r") || (arg == "--reset")) {
            show_usage(argv[0]);
            return 0;
        } else
        if ((arg == "--test")) {
            std::cout <<"test launched 1 ! ";
            test=true;
        }
    }
    if (test) {
        std::cout <<"Test Launched ! ";
        char nom[10] = "as";
        Certificate testCert(nom, generate_key(), 10);
        X509* certificate = testCert.mCertificate;
        int status;
        X509_STORE_CTX *ctx;
        ctx = X509_STORE_CTX_new();
        X509_STORE *store = X509_STORE_new();

        X509_STORE_add_cert(store, certificate);

        X509_STORE_CTX_init(ctx, store, certificate, NULL);

        status = X509_verify_cert(ctx);
        if(status == 1)
        {
            printf("Autosigned Certificate : Ok\n");
        }else
        {
            std::cout << ("Autosigned Certificate : Nop");
        }
        Certificate testCert2(nom, generate_key(), 10);

        testCert2.checkCertificate(certificate);
    }



    return 0;
}
