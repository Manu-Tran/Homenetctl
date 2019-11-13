//
// Created by romain on 10/11/2019.
//

#include <Client.h>
#include "equipment.h"

/**
 * Adding of a new equipment to the domestic network, client side
 * @param serverAddress
 */
void Equipment::addEquipmentClientSide(const char * serverAddress)
{
    bool result;

    std::string selfSignedPath = "/tmp/homenetctl/certs/client/clientSelfSignedCert.pem";
    std::string receivedSelfSignedPath = "/tmp/homenetctl/certs/client/serverSelfSignedCert.pem";
    std::string newCertPath = "/tmp/homenetctl/certs/client/newCert.pem";

    //Create Client socket and connect to server using address and port
    Client cl(serverAddress,mPort);
    std::cout << "client created" << std::endl;
    result = cl.connectToServer();

    if(result)
        result = cl.clientAcceptAccess(cl.getSocket(),mId);

    if(result) {
        std::cout << "client connected" << std::endl;

        //write selfsigned certificate to temp file --> writeCertificateToFile()
        this->writeCertificateToFile(*mSelfSignedCertificate, selfSignedPath);

        //Send temp file to server
        result = cl.sendFile(selfSignedPath, cl.getSocket());
        if (result) std::cout << "Client Self Signed Certificate sent!" << std::endl;

        //Receive new certificate from server INTO TEMP FILE
        result = cl.receiveFile(receivedSelfSignedPath, cl.getSocket());
        if (result) std::cout << "Server self signed certificate received!" << std::endl;

        //read temp file to a certificate --> readCertificateFromFile()
        Poco::Crypto::X509Certificate subjectSelfSignedCert = readCertificateFromFile(receivedSelfSignedPath);
        //std::cout << "read selfsigned cert from file" << std::endl;

        //Create the new certificate from this file --> newCertfificate()
        Poco::Crypto::X509Certificate newCert = newCertificate(subjectSelfSignedCert, subjectSelfSignedCert.commonName());

        //Write new certificate to file
        this->writeCertificateToFile((newCert), newCertPath);

        //Send That file
        result = cl.sendFile(newCertPath, cl.getSocket());
        if (result) std::cout << "New Certificate sent!" << std::endl;

        //Receive the new one
        result = cl.receiveFile(newCertPath, cl.getSocket());
        if (result) std::cout << "New certificate received!" << std::endl;

        //read it from file
        newCert = readCertificateFromFile(newCertPath);

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
}

void Equipment::synchroClientSide(const char * serverAddress){

    bool result;
    std::string toSendPath = "/tmp/homenetctl/certs/client/knownCerts.pem";
    std::string receivedPath = "/tmp/homenetctl/certs/client/knownCertsReceived.pem";
    std::string toSendPubKeyPath = "/tmp/homenetctl/certs/client/knownHosts";
    std::string receivedPubKeyPath = "/tmp/homenetctl/certs/client/knownHostsReceived";

    Client cl(serverAddress,mPort);
    std::cout << "client created" << std::endl;
    result = cl.connectToServer();

    if(result)
        result = cl.clientAcceptAccess(cl.getSocket(),mId);

    if(result) {
        std::cout << "client connected" << std::endl;

        // Updating the certificates file
        mHandler->save();

        //send certificates to client
        result = cl.sendFile(toSendPath, cl.getSocket());
        if (result) std::cout << "DA and CA certificate sent" << std::endl;

        //send pubkeys to client
        result = cl.sendFile(toSendPath, cl.getSocket());
        if (result) std::cout << "Pubkeys certificate sent" << std::endl;

        //Receive certificates from Client
        result = cl.receiveFile(receivedPath, cl.getSocket());
        if (result) std::cout << "DA and CA certificates received" << std::endl;

        //Receive pubkey from Client
        result = cl.receiveFile(receivedPubKeyPath, cl.getSocket());
        if (result) std::cout << "Pubkeys received" << std::endl;


        //Loads the received cert
        Poco::Crypto::X509Certificate::List receivedList = Poco::Crypto::X509Certificate::readPEM(receivedPath);
        std::map<std::string,Poco::Crypto::RSAKey> receivedPubList = CertificateHandler::readPubKeys("/tmp/homenetctl/certs/server/knownHosts");
        std::set<std::string> idPresent;
        for (auto pair : receivedPubList) {
            idPresent.insert(pair.first);
        }

        for (auto itr(receivedList.begin()); itr != receivedList.end(); itr++){
            if (idPresent.contains(itr->issuerName())){
                CertificateHandler::X509Ptr x509 = std::make_shared<Poco::Crypto::X509Certificate>(*itr);
                mHandler->addCertificate(x509, receivedPubList.at(itr->issuerName()));
            }
        }
    }

    //Delete Temp files
    remove( receivedPath.c_str() );
    remove( receivedPubKeyPath.c_str() );
}
/* void Equipment::synchroClientSide(const char * serverAddress){ */

/* } */
