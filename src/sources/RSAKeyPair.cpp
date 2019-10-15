//
// Created by romain on 15/10/2019.
//

#include "RSAKeyPair.h"

RSAKeyPair::RSAKeyPair()
{
    //define keys here and assign back to variable(s)
};

//GETTERS
int RSAKeyPair::getpublicKey() {return this->publicKey;}
int RSAKeyPair::getPrivateKey() {return this->privateKey;}

//SETTERS
void RSAKeyPair::setPublicKey(int newPublicKey) {this->publicKey=newPublicKey;}
void RSAKeyPair::setPrivateKey(int newPrivateKey) {this->privateKey=newPrivateKey;}