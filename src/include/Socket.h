//
// Created by romain on 02/11/2019.
//

#ifndef HOMENETCTL_SOCKET_H
#define HOMENETCTL_SOCKET_H

#include "certificate.h"

class Socket {

public:

    Socket();

    bool sendCert(Certificate cert);
    bool recvCert();

};


#endif //HOMENETCTL_SOCKET_H
