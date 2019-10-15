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
void equipment::display_CA() {};
void equipment::display_DA() {};
void equipment::display() {};

//GETTERS
std::string equipment::getName() {};
RSAKeyPair equipment::getKeys() {};
int equipment::getPort() {};

//SETTERS
void equipment::setName() {};
void equipment::setKeys() {};
void equipment::setPort() {};