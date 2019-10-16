//
// Created by romain on 15/10/2019.
//

#include "RSAKeyPair.h"

RSAKeyPair::RSAKeyPair()
{
    //define keys here and assign back to variable(s)
};

//GETTERS
int RSAKeyPair::getpublicKey() {return this->mPublicKey;}
int RSAKeyPair::getPrivateKey() {return this->mPrivateKey;}

//SETTERS
void RSAKeyPair::setPublicKey(int newPublicKey) {this->mPublicKey=newPublicKey;}
void RSAKeyPair::setPrivateKey(int newPrivateKey) {this->mPrivateKey=newPrivateKey;}
