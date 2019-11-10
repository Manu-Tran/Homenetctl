//
// Created by romain on 10/11/2019.
//

#include <Server.h>
#include "equipment.h"

void Equipment::addEquipmentServerSide(const char * serverAddress)
{
    bool result;
    std::string selfSignedPath = "/tmp/homenetctl/certs/server/serverSelfSignedCert.pem";
    std::string receivedSelfSignedPath = "/tmp/homenetctl/certs/server/clientSelfSignedCert.pem";
    std::string newCertPath = "/tmp/homenetctl/certs/server/newCert.pem";
    std::string receivedNewCertPath = "/tmp/homenetctl/certs/server/receivedNewCert.pem";


    //Create Server socket, bind it, listen and accept connections
    Server serv(serverAddress, mPort);
    std::cout << "server created at address: " << serverAddress << " and port: " << mPort << std::endl;
    serv.listenForConnectionRequests();
    std::cout << "server connected & listening:" << std::endl;

    //write selfsigned certificate to temp file --> writeCertificateToFile()
    this->writeCertificateToFile(*mSelfSignedCertificate,selfSignedPath);

    //Receive certificate from Client
    result = serv.receiveFile(receivedSelfSignedPath,serv.getNewSocket());
    if(result) std::cout << "server file received" << std::endl;

    //send selfsigned certificate to client
    result = serv.sendFile(selfSignedPath, serv.getNewSocket());
    if(result) std::cout << "server file sent" << std::endl;

    //Delete Temp file
    if(remove( selfSignedPath.c_str() ) != 0)
        std::cout << "error deleting temp file" << std::endl;
    else
        std::cout << "Temp file successfully deleted!" << std::endl;

    //read received cert from file
    Poco::Crypto::X509Certificate newCert = readCertificateFromFile(receivedSelfSignedPath);
    std::cout << "read selfsigned cert from file" << std::endl;

    //create new certificate
    newCert = newCertificate(newCert,newCert.commonName());

    //Write new certificate to file
    this->writeCertificateToFile((newCert),newCertPath);

    //receive new one from server
    result = serv.receiveFile(receivedNewCertPath, serv.getNewSocket());
    if(result) std::cout << "New certificate received!" << std::endl;

    //send it to server
    result = serv.sendFile(newCertPath, serv.getNewSocket());
    if(result) std::cout << "server file sent" << std::endl;

    //read it from file
    newCert = readCertificateFromFile(receivedNewCertPath);

    if(CertificateHandler::checkCertificate(newCert,*mSelfSignedCertificate))
        //add it to CA
        CA.push_back(newCert);
    else
        std::cout << "The received certificate is not correct!" << std::endl;
}
