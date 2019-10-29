//
// Created by romain on 15/10/2019.
//

#include <string>
#include "equipment.h"

//CONSTRUCTORS
Equipment::Equipment(std::string id, int port)
{
    this->mId=std::move(id); //the Id will be an user input, so we don't need it anymore afterwards, hence moving it is okay.
    this->mPort=port;
}

//DISPLAY
void Equipment::display_CA() {}
void Equipment::display_DA() {}
void Equipment::display() {}

//GETTERS
std::string Equipment::getName() {return this->mId;}
RSAKeyPair Equipment::getKeys() {return this->mKeys;}
int Equipment::getPort() {return this->mPort;}

//SETTERS
void Equipment::setName(std::string newId) {this->mId=newId;}
void Equipment::setKeys(RSAKeyPair newKeys) {this->mKeys=newKeys;}
void Equipment::setPort(int newPort) {this->mPort=newPort;}
