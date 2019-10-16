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
char* RSAKeyPair::getPublicKey() {return publicKey;}
/**
 * getter for private key
 * @return
 */
char* RSAKeyPair::getPrivateKey() {return privateKey;}



/**
 * Generates a 2048-bit RSA key.
 * it comes from here: https://gist.github.com/nathan-osman/5041136
 * \return The success
 */
bool RSAKeyPair::generate_key() {
    size_t pri_len;            // Length of private key
    size_t pub_len;            // Length of public key
    char *pri_key;           // Private key in PEM
    char *pub_key;           // Public key in PEM

    int ret = 0;
    RSA *r = NULL;
    BIGNUM *bne = NULL;
    BIO *bp_public = NULL, *bp_private = NULL;
    int bits = 2048;
    unsigned long e = RSA_F4;

    RSA *pb_rsa = NULL;
    RSA *p_rsa = NULL;

    EVP_PKEY *evp_pbkey = NULL;
    EVP_PKEY *evp_pkey = NULL;

    BIO *pbkeybio = NULL;
    BIO *pkeybio = NULL;

    // 1. generate rsa key
    bne = BN_new();
    ret = BN_set_word(bne, e);
    if (ret != 1) {
        goto free_all;
    }

    r = RSA_new();
    ret = RSA_generate_key_ex(r, bits, bne, NULL);
    if (ret != 1) {
        goto free_all;
    }

    // 2. save public key
    //bp_public = BIO_new_file("public.pem", "w+");
    bp_public = BIO_new(BIO_s_mem());
    ret = PEM_write_bio_RSAPublicKey(bp_public, r);
    if (ret != 1) {
        goto free_all;
    }

    // 3. save private key
    //bp_private = BIO_new_file("private.pem", "w+");
    bp_private = BIO_new(BIO_s_mem());
    ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

    //4. Get the keys are PEM formatted strings
    pri_len = BIO_pending(bp_private);
    pub_len = BIO_pending(bp_public);

    pri_key = (char*) malloc(pri_len + 1);
    pub_key = (char*) malloc(pub_len + 1);

    BIO_read(bp_private, pri_key, pri_len);
    BIO_read(bp_public, pub_key, pub_len);

    pri_key[pri_len] = '\0';
    pub_key[pub_len] = '\0';

    publicKey = pub_key;
    privateKey = pri_key;
    //printf("\n%s\n%s\n", pri_key, pub_key);

    //verify if you are able to re-construct the keys
    pbkeybio = BIO_new_mem_buf((void*) pub_key, pub_len);
    if (pbkeybio == NULL) {
        return -1;
    }
    pb_rsa = PEM_read_bio_RSAPublicKey(pbkeybio, &pb_rsa, NULL, NULL);
    if (pb_rsa == NULL) {
        char buffer[120];
        ERR_error_string(ERR_get_error(), buffer);
        printf("Error reading public key:%s\n", buffer);
    }

    evp_pbkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(evp_pbkey, pb_rsa);

    pkeybio = BIO_new_mem_buf((void*) pri_key, pri_len);
    if (pkeybio == NULL) {
        return -1;
    }
    p_rsa = PEM_read_bio_RSAPrivateKey(pkeybio, &p_rsa, NULL, NULL);
    if (p_rsa == NULL) {
        char buffer[120];
        ERR_error_string(ERR_get_error(), buffer);
        printf("Error reading private key:%s\n", buffer);
    }

    evp_pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(evp_pkey, p_rsa);

    BIO_free(pbkeybio);
    BIO_free(pkeybio);

    // 4. free
    free_all:

    BIO_free_all(bp_public);
    BIO_free_all(bp_private);
    RSA_free(r);
    BN_free(bne);

    return (ret == 1);
}
