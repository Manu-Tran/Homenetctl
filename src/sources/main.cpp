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
              << "\t-s <PORT> <SERVER IP>,--server <PORT> <SERVER IP>\t\tReset the configuration\n"
              << "\t-c <PORT> <SERVER IP>,--client <PORT> <SERVER IP>\t"
              << "\t--test\t\tLaunch tests"
              << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }
    bool result = false;
    std::vector <std::string> sources;
    int port;
    const char * addr;
    bool test=false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } else if ((arg == "-s") || (arg == "--server")) {
            if (i + 2 < argc) {
                addr = argv[i+1];
                port = std::stoi(argv[i+2]);

                Server serv(addr, port);
                std::cout << "server created at address: " << addr << " and port: " << port << std::endl;
                serv.listenForConnectionRequests();
                std::cout << "server connected" << std::endl;
                result = serv.receiveFile("/home/romain/Documents/tests/certs/serverRecv.txt",serv.getNewSocket());
                if(result) std::cout << "server file received" << std::endl;
                result = serv.sendFile("/home/romain/Documents/tests/certs/serverSend.txt", serv.getNewSocket());
                if(result) std::cout << "server file sent" << std::endl;
                return 0;

            } else {
                  std::cerr << "--server option requires two arguments." << std::endl;
                return 1;
            }

        } else if ((arg == "--client" || arg == "-c")) {

            if(i+2 < argc) {
                addr = argv[i+1];
                port = std::stoi(argv[i+2]);

                Client cl(addr,port);
                std::cout << "client created" << std::endl;
                cl.connectToServer();
                std::cout << "client connected" << std::endl;
                result = cl.sendFile("/home/romain/Documents/tests/certs/clientSend.txt", cl.getSocket());
                if(result) std::cout << "client file sent" << std::endl;
                result = cl.receiveFile("/home/romain/Documents/tests/certs/clientRecv.txt", cl.getSocket());
                if(result) std::cout << "client file received" << std::endl;

            } else {
                std::cerr << "--client option requires two arguments." << std::endl;
                return 1;
            }

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
