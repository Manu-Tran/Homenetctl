//
// Created by romain on 15/10/2019.
//

#include <string>
#include "equipment.h"

equipment::equipment()= default;

equipment::equipment(std::string id, RSAKeyPair keys)
{
    this->id=std::move(id); //the Id will be an user input, so we don't need it anymore afterwards, hence moving it is okay.
    this->keys=keys;
}