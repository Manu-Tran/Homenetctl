#ifndef HOMENETCTL_TEST_H
#define HOMENETCTL_TEST_H
#include <iostream>
#include <string>
#include <vector>
#include "certificateHandler.h"
#include "RSAKeyPair.h"
#include "equipment.h"

#include <openssl/pem.h>
#include <openssl/x509.h>
#include <Poco/Crypto/EVPPKey.h>

class TestHandler {
    private:
    static bool test1();
    static bool test2();
    static bool test3();
    static bool test4();
    static bool test5();

    public :
    static void launchTests(){
        /* std::cout << "Test 1... " << (test1() ? "Ok" : "Failed") << std::endl; */
        /* std::cout << "Test 2... " << (test2() ? "Ok" : "Failed") << std::endl; */
        /* std::cout << "Test 3... " << (test3() ? "Ok" : "Failed") << std::endl; */
        std::cout << "Test 4... " << (test4() ? "Ok" : "Failed") << std::endl;
        std::cout << "Test 5... " << (test5() ? "Ok" : "Failed") << std::endl;
    }

};

#endif
