//
// Created by romain on 15/10/2019.
//

#include <Poco/Crypto/X509Certificate.h>
#include "RSAKeyPair.h"

namespace fs = std::filesystem;

/**
 * Constructor
 * It generates a pair of RSA keys or check their existence.
 */
RSAKeyPair::RSAKeyPair()
{
    if(!fs::exists(mPath))
    {
        fs::create_directory(mPath);
        std::cout << "Directory was created" << std::endl;
    }
    if(fs::exists(mPubKeyPath) && fs::exists(mPrivKeyPath))
    {
        std::cout << "Loading RSA keys" << std::endl;
        loadKeys(true);
    }
    else {
        std::cout << "Generating new keys..." << std::endl;
        bool result = generate_key();
        if(!result) {
            std::cerr << "error during the key generation! " << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

RSAKeyPair::RSAKeyPair(std::string keyname, Poco::Crypto::X509Certificate cert)
{
    Poco::Crypto::RSAKey clientKey(cert);
    std::string publicKeyName = "clientPublicKey";
    std::string privateKeyName = "clientPrivateKey";
    if (keyname != ""){
        publicKeyName  += "_" + keyname;
        privateKeyName += "_" + keyname;
    }
    publicKeyName  += ".pem";
    privateKeyName += ".pem";

    //Save said key into 2 PEM files, one for public key one for private key
    clientKey.save(mPath / publicKeyName,mPath / privateKeyName,"");

    //Load the public and private keys from their files into the classes's fields
    std::ifstream pub, priv;
    std::string line, pubKey, priKey;

    pub.open(mPath / publicKeyName);
    priv.open(mPath / privateKeyName);

    if (pub) {
        while (std::getline(pub, line)) {
            pubKey+=line;
        }
    } else {
        std::cout << "could not open public key file" << std::endl;
    }
    if (priv) {
        while (std::getline(priv, line)) {
            priKey+=line;
        }
    } else
        std::cout << "could not open private key file" << std::endl;
}

std::unique_ptr<Poco::Crypto::RSAKey> RSAKeyPair::loadKeys(bool priv){
    Key_ptr key = std::make_unique<Poco::Crypto::RSAKey>(mPubKeyPath);
    try {
        if (priv){
            key = std::make_unique<Poco::Crypto::RSAKey>(mPubKeyPath, mPrivKeyPath);
        }
    }
    catch (Poco::IOException){
        std::cout << "Unable to read the keys" << std::endl;
    }
    return key;
}

/**
 * Generates a 2048 bits key pair in 2 forms: const char * and EVP_PKEY, stored in the class fields
 * This function is called by the class constructor
 * @return
 */
bool RSAKeyPair::generate_key(std::string keyname) {

    //Generate key using Poco::Crypto::RSAKey constructor
    Poco::Crypto::RSAKey pocoKey = Poco::Crypto::RSAKey(Poco::Crypto::RSAKey::KL_2048,Poco::Crypto::RSAKey::EXP_SMALL);
    std::string publicKeyName = "publicKey";
    std::string privateKeyName = "privateKey";
    if (keyname != ""){
        publicKeyName  += "_" + keyname;
        privateKeyName += "_" + keyname;
    }
    publicKeyName  += ".pem";
    privateKeyName += ".pem";

    //Save said key into 2 PEM files, one for public key one for private key
    pocoKey.save(mPath / publicKeyName,mPath / privateKeyName,"");

    //Load the public and private keys from their files into the classes's fields
    std::ifstream pub, priv;
    std::string line, pubKey, priKey;

    pub.open(mPath / publicKeyName);
    priv.open(mPath / privateKeyName);

    if (pub) {
        while (std::getline(pub, line)) {
            pubKey+=line;
        }
    } else {
        std::cout << "could not open public key file" << std::endl;
        return false;
    }
    if (priv) {
        while (std::getline(priv, line)) {
            priKey+=line;
        }
        return true;
    } else
        std::cout << "could not open private key file" << std::endl;
        return false;
}

/**
 * getter for public key
 * @return
 */
/* const std::string RSAKeyPair::getPublicKeyStr() {return mPublicKey;} */
/**
 * getter for private key
 * @return
 */
/* const char * RSAKeyPair::getPrivateKeyStr() {return mPrivateKey;} */

/**
 * getter for public key
 * @return
 */
/* EVP_PKEY *  RSAKeyPair::getPublicKey() {return pbkey;} */
/**
 * getter for private key
 * @return
 */
/* EVP_PKEY * RSAKeyPair::getPrivateKey() {return pkey;} */

