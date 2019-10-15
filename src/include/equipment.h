//
// Created by romain on 15/10/2019.
//

#ifndef HOMENETCTL_EQUIPMENT_H
#define HOMENETCTL_EQUIPMENT_H

#include <string>
#include <utility>
#include "RSAKeyPair.h"

class equipment {

private:
    std::string id;
    RSAKeyPair keys;
    //probably will need to link the domestic network to have a link to CA and DA. we'll see how

public:
    equipment();
    equipment(std::string id, RSAKeyPair keys);

};


#endif //HOMENETCTL_EQUIPMENT_H
