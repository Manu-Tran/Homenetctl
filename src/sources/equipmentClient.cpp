//
// Created by romain on 10/11/2019.
//

#include <Client.h>
#include "equipment.h"

void Equipment::addEquipmentClientSide(const char * serverAddress)
{
    bool result;

    std::string selfSignedPath = "/tmp/homenetctl/certs/client/clientSelfSignedCert.pem";
    std::string receivedSelfSignedPath = "/tmp/homenetctl/certs/client/serverSelfSignedCert.pem";
    std::string newCertPath = "/tmp/homenetctl/certs/client/newCert.pem";

    //Create Client socket and connect to server using address and port
    Client cl(serverAddress,mPort);
    std::cout << "client created" << std::endl;
    cl.connectToServer();
    std::cout << "client connected" << std::endl;

    //write selfsigned certificate to temp file --> writeCertificateToFile()
    this->writeCertificateToFile(*mSelfSignedCertificate,selfSignedPath);

    //Send temp file to server
    result = cl.sendFile(selfSignedPath, cl.getSocket());
    if(result) std::cout << "Client Self Signed Certificate sent!" << std::endl;

    //Delete temp file
    //if(remove( selfSignedPath.c_str() ) != 0)
    //    std::cout << "error deleting temp file" << std::endl;
    //else
    //    std::cout << "Temp file successfully deleted!" << std::endl;

    //Receive new certificate from server INTO TEMP FILE
    result = cl.receiveFile(receivedSelfSignedPath, cl.getSocket());
    if(result) std::cout << "Server self signed certificate received!" << std::endl;

    //read temp file to a certificate --> readCertificateFromFile()
    Poco::Crypto::X509Certificate newCert = readCertificateFromFile(receivedSelfSignedPath);
    std::cout << "read selfsigned cert from file" << std::endl;

    //Create the new certificate from this file --> newCertfificate()
    //newCert = newCertificate(newCert,newCert.commonName());

    //Write new certificate to file
    //this->writeCertificateToFile((newCert),newCertPath);

    //Send That file
    //result = cl.sendFile(newCertPath, cl.getSocket());
    //if(result) std::cout << "new Certificate sent!" << std::endl;

    //delete it from local
    //if(remove( newCertPath.c_str() ) != 0)
    //    std::cout << "error deleting temp file" << std::endl;
    //else
    //    std::cout << "Temp file successfully deleted!" << std::endl;

    //Receive the new one
    //result = cl.receiveFile(newCertPath, cl.getSocket());
    //if(result) std::cout << "New certificate received!" << std::endl;

    //read it from file
    //newCert = readCertificateFromFile(newCertPath);

    //Add it to CA
    //CA.push_back(newCert);

}
