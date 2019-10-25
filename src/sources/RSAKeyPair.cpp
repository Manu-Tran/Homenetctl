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
    generate_key();
}

/**
 * getter for public key
 * @return
 */
const char * RSAKeyPair::getPublicKey() {return publicKey;}
/**
 * getter for private key
 * @return
 */
const char * RSAKeyPair::getPrivateKey() {return privateKey;}



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
    publicKey = pubKey.c_str();
    privateKey = priKey.c_str();

    //Now we need these two keys in EVP_PKEY types
    //so, we'll first go from a const char* to a BIO* (BIO_write())
    //And then go to an EVP_PKEY* (PEM_read_bio_*****())
    BIO* bo = BIO_new( BIO_s_mem() );
    pkey = 0;
    pbkey = 0;

    try {
        //private key
        BIO_write(bo, privateKey, strlen(privateKey));
        PEM_read_bio_PrivateKey(bo, &pkey, 0, 0);

        //public key
        BIO_write(bo, publicKey, strlen(publicKey));
        PEM_read_bio_PUBKEY(bo, &pbkey, 0, 0);
    }
    catch(std::exception const& e)
    {
        std::cerr << "error : " << e.what() << std::endl;
    }


}
