//
// Created by romain on 15/10/2019.
//

#include <string>
#include "equipment.h"

//CONSTRUCTORS
equipment::equipment()= default;
equipment::equipment(std::string id, int port)
{
    this->mId=std::move(id); //the Id will be an user input, so we don't need it anymore afterwards, hence moving it is okay.
    this->mPort=port;
}

//DISPLAY
void equipment::display_CA() {}
void equipment::display_DA() {}
void equipment::display() {}

//GETTERS
std::string equipment::getName() {return this->mId;}
RSAKeyPair equipment::getKeys() {return this->mKeys;}
int equipment::getPort() {return this->mPort;}

//SETTERS
void equipment::setName(std::string newId) {this->mId=newId;}
void equipment::setKeys(RSAKeyPair newKeys) {this->mKeys=newKeys;}
void equipment::setPort(int newPort) {this->mPort=newPort;}
