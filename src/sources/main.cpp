#include <iostream>
#include <string>
#include <vector>
#include "certificateHandler.h"
#include "RSAKeyPair.h"
#include "test.h"

#include <openssl/pem.h>
#include <openssl/x509.h>
#include <Poco/Crypto/EVPPKey.h>
#include <Client.h>
#include <Server.h>

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
        } else if ((arg == "-s") || (arg == "--server")) {
            /*if (i + 1 < argc) {
                port = argv[i++];
            } else {
                  std::cerr << "--server option requires one argument." << std::endl;
                return 1;
            }*/

            Server serv;
            std::cout << "server created" << std::endl;
            serv.listenForConnectionRequests();
            std::cout << "server connected" << std::endl;
            serv.receiveFile("/home/romain/Documents/tests/certs/serverRecv.txt");
            std::cout << "server file received" << std::endl;
            serv.sendFile("/home/romain/Documents/tests/certs/serverSend.txt");
            std::cout << "server file sent" << std::endl;
            return 0;

        } else if ((arg == "--client")) {
            Client cl("127.0.0.1");
            std::cout << "client created" << std::endl;
            cl.connectToServer();
            std::cout << "client connected" << std::endl;
            cl.sendFile("/home/romain/Documents/tests/certs/clientSend.txt");
            std::cout << "client file sent" << std::endl;
            cl.receiveFile("/home/romain/Documents/tests/certs/clientRecv.txt");
            std::cout << "client file received" << std::endl;
            return 0;

        } else if ((arg == "-r") || (arg == "--reset")) {
            show_usage(argv[0]);
            return 0;
        } else if ((arg == "--test")) {
            test = true;
        }
    }

    if (test) {
       std::cout << "Launching Tests :" << std::endl;
       TestHandler::launchTests();
    }
    return 0;
}
