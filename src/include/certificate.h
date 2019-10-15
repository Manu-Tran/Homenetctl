//
// Created by romain on 15/10/2019.
//

#ifndef HOMENETCTL_CERTIFICATE_H
#define HOMENETCTL_CERTIFICATE_H


class certificate {

private:
    long int seqnum = 0;
    int certificate; //to be changed for the right type

public:

    certificate();
    void generateCertificate(); //should return a certif afterwards
    bool checkCertfification(int publicKey);

};


#endif //HOMENETCTL_CERTIFICATE_H
