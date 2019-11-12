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

namespace fs = std::filesystem;

void init(std::string name);

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
              << "\t-i <Equipment Name>, --init <Equipment Name>\t\t Sets up your environment\n"
              << "\t-r,--reset\t\tReset the configuration\n"
              << "\t-a <Equipment Name> <PORT> ,--add <Equipment Name> <PORT> \t\t add a new equipment to my lists\n"
              << "\t-j <Equipment Name> <SERVER IP> <PORT>,--client <Equipment Name> <SERVER IP> <PORT>\t\t ask to join a domestic network\n"
              << "\t-d <Equipment Name>, --display <Equipment Name>\t\t display the current known devices to this equipment\n"
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
    int port;
    const char * addr;
    bool test=false;
    std::string name;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } else if ((arg == "-a") || (arg == "--add")) {
            if (i + 2 < argc) {
                name = argv[i + 1];
                port = std::stoi(argv[i+2]);

                Equipment A(name,port);
                A.addEquipmentServerSide();

                return 0;

            } else {
                std::cerr << "--add option requires two arguments." << std::endl;
                return 1;
            }

        } else if ((arg == "--join" || arg == "-j")) {

            if (i + 3 < argc) {
                name = argv[i + 1];
                addr = argv[i + 2];
                port = std::stoi(argv[i + 3]);

                Equipment B(name, port);
                B.addEquipmentClientSide(addr);

            } else {
                std::cerr << "--join option requires three arguments." << std::endl;
                return 1;
            }

            return 0;
        } else if((arg == "-i") || (arg == "--init")) {

            if(i+1 < argc)
            {
                name = argv[i+1];
                init(name);
            }
            else
            {
                std::cerr << "--init option requires one argument." << std::endl;
                return 1;
            }

            return 0;

        } else if((arg == "-d") || (arg == "--display")) {

            if(i+1 < argc)
            {
                name = argv[i+1];
                //Load equipment with said name
                //display it using eq.display();
            }
            else
            {
                std::cerr << "--display option requires one argument." << std::endl;
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

void init(std::string name)
{
    std::filesystem::path mPath = "/tmp/homenetctl";
    std::filesystem::path mPathEquipment = "/tmp/homenetctl/"+name;


    if(!fs::exists(mPath))
        fs::create_directory(mPath);

    if(!fs::exists(mPathEquipment))
        fs::create_directory(mPathEquipment);

    std::cout << "Directories were created" << std::endl;

    //Create equipment + Save it
}
