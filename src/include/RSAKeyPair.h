//
// Created by romain on 15/10/2019.
//

#ifndef HOMENETCTL_RSAKEYPAIR_H
#define HOMENETCTL_RSAKEYPAIR_H


class RSAKeyPair {

private:
    //1 pair field or 2 fields, one for public one for private.
    //types to define according to crypto API chosen
    int mPublicKey;
    int mPrivateKey;

public:
    //default constructor should simply generate keys and assign them to the fields
    RSAKeyPair();

    //GETTERS
    int getpublicKey();
    int getPrivateKey();

    //SETTERS
    void setPublicKey(int newPublicKey);
    void setPrivateKey(int newPrivateKey);

};


#endif //HOMENETCTL_RSAKEYPAIR_H
