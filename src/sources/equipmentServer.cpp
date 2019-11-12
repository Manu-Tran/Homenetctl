//
// Created by romain on 10/11/2019.
//

#include <Server.h>
#include "equipment.h"

/**
 * Adding of a new equipment to the domestic network, server side
 * @param serverAddress
 */
void Equipment::addEquipmentServerSide()
{
    bool result;
    std::string selfSignedPath = "/tmp/homenetctl/certs/server/serverSelfSignedCert.pem";
    std::string receivedSelfSignedPath = "/tmp/homenetctl/certs/server/clientSelfSignedCert.pem";
    std::string newCertPath = "/tmp/homenetctl/certs/server/newCert.pem";
    std::string receivedNewCertPath = "/tmp/homenetctl/certs/server/receivedNewCert.pem";

    //Create Server socket, bind it, listen and accept connections
    Server serv(mPort);
    std::cout << "server created and listening to port: " << mPort << std::endl;
    result = serv.listenForConnectionRequests();

    //poput to accept connection between devices
    if(result)
        result = serv.serverAcceptAccess(serv.getNewSocket(),mId);

    if(result) {
        std::cout << "server connected & listening:" << std::endl;

        //write selfsigned certificate to temp file --> writeCertificateToFile()
        this->writeCertificateToFile(*mSelfSignedCertificate, selfSignedPath);

        //Receive certificate from Client
        result = serv.receiveFile(receivedSelfSignedPath, serv.getNewSocket());
        if (result) std::cout << "Client Self signed certificate received" << std::endl;

        //send selfsigned certificate to client
        result = serv.sendFile(selfSignedPath, serv.getNewSocket());
        if (result) std::cout << "Server self signed certificate sent" << std::endl;

        //read received cert from file
        Poco::Crypto::X509Certificate subjectSelfSignedCert = readCertificateFromFile(receivedSelfSignedPath);
        //std::cout << "read selfsigned cert from file" << std::endl;

        //create new certificate
        Poco::Crypto::X509Certificate newCert = newCertificate(subjectSelfSignedCert, subjectSelfSignedCert.commonName());

        //Write new certificate to file
        this->writeCertificateToFile((newCert), newCertPath);

        //receive new one from server
        result = serv.receiveFile(receivedNewCertPath, serv.getNewSocket());
        if (result) std::cout << "New certificate received!" << std::endl;

        //send it to server
        result = serv.sendFile(newCertPath, serv.getNewSocket());
        if (result) std::cout << "New certificate sent" << std::endl;

        //read it from file
        newCert = readCertificateFromFile(receivedNewCertPath);

        if (CertificateHandler::checkCertificate(newCert, subjectSelfSignedCert))
            //add it to CA
            CA.push_back(newCert);
        else
            std::cout << "The received certificate is not correct!" << std::endl;
    }

    //Delete Temp files
    remove( selfSignedPath.c_str() );
    remove( receivedSelfSignedPath.c_str() );
    remove( newCertPath.c_str() );
    remove( receivedNewCertPath.c_str() );
}
