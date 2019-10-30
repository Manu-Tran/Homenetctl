//
// Created by romain on 15/10/2019.
//

#include "RSAKeyPair.h"

/**
 * Constructor
 * It generates 2 RSA keys and assign them to public and private key respectively.
 */
RSAKeyPair::RSAKeyPair()
{
    bool result = generate_key();
    if(!result) {
        std::cerr << "error during the key generation! " << std::endl;
        std::exit(EXIT_FAILURE);
    }

}

/**
 * getter for public key
 * @return
 */
const char * RSAKeyPair::getPublicKeyStr() {return mPublicKey;}
/**
 * getter for private key
 * @return
 */
const char * RSAKeyPair::getPrivateKeyStr() {return mPrivateKey;}

/**
 * getter for public key
 * @return
 */
EVP_PKEY *  RSAKeyPair::getPublicKey() {return pbkey;}
/**
 * getter for private key
 * @return
 */
EVP_PKEY * RSAKeyPair::getPrivateKey() {return pkey;}



/**
 * Generates a 2048 bits key pair in 2 forms: const char * and EVP_PKEY, stored in the class fields
 * This function is called by the class constructor
 * @return
 */
bool RSAKeyPair::generate_key() {



    //Generate key using Poco::Crypto::RSAKey constructor
    Poco::Crypto::RSAKey pocoKey = Poco::Crypto::RSAKey(Poco::Crypto::RSAKey::KL_2048,Poco::Crypto::RSAKey::EXP_SMALL);

    //Save said key into 2 PEM files, one for public key one for private key
    pocoKey.save("/tmp/homenetctl/publicKey.pem","/tmp/homenetctl/privateKey.pem","");

    //Load the public and private keys from their files into the classes's fields
    std::ifstream pub, priv;
    std::string line, pubKey, priKey;

    pub.open("/tmp/homenetctl/publicKey.pem");
    priv.open("/tmp/homenetctl/privateKey.pem");

    if (pub) {
        while (std::getline(pub, line)) {
            pubKey+=line;
        }
    } else
        std::cout << "could not open public key file" << std::endl;

    if (priv) {
        while (std::getline(priv, line)) {
            priKey+=line;
        }
    } else
        std::cout << "could not open private key file" << std::endl;

    //convert strings to const char *
    mPublicKey = pubKey.c_str();
    mPrivateKey = priKey.c_str();

    //Now we need these two keys in EVP_PKEY types
    //so, we'll first go from a const char* to a BIO* (BIO_write())
    //And then go to an EVP_PKEY* (PEM_read_bio_*****())
    BIO* bo = BIO_new( BIO_s_mem() );
    pkey = 0;
    pbkey = 0;

    try {
        //private key
        BIO_write(bo, mPrivateKey, strlen(mPrivateKey));
        PEM_read_bio_PrivateKey(bo, &pkey, 0, 0);

        //public key
        BIO_write(bo, mPublicKey, strlen(mPublicKey));
        PEM_read_bio_PUBKEY(bo, &pbkey, 0, 0);

        return true;
    }

    catch(std::exception const& e)
    {
        std::cerr << "error : " << e.what() << std::endl;
        return false;
    }


}
