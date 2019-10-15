//
// Created by romain on 15/10/2019.
//

#include <string>
#include "equipment.h"

//CONSTRUCTORS
equipment::equipment()= default;
equipment::equipment(std::string id, int port)
{
    this->id=std::move(id); //the Id will be an user input, so we don't need it anymore afterwards, hence moving it is okay.
    this->port=port;
}

//DISPLAY
void equipment::display_CA() {}
void equipment::display_DA() {}
void equipment::display() {}

//GETTERS
std::string equipment::getName() {return this->id;}
RSAKeyPair equipment::getKeys() {return this->keys;}
int equipment::getPort() {return this->port;}

//SETTERS
void equipment::setName(std::string newId) {this->id=newId;}
void equipment::setKeys(RSAKeyPair newKeys) {this->keys=newKeys;}
void equipment::setPort(int newPort) {this->port=newPort;}