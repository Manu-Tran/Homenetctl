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
    std::string selfSignedPath = "/tmp/homenetctl/"+mId+"/serverSelfSignedCert.pem";
    std::string receivedSelfSignedPath = "/tmp/homenetctl/"+mId+"/clientSelfSignedCert.pem";
    std::string newCertPath = "/tmp/homenetctl/"+mId+"/newCert.pem";
    std::string receivedNewCertPath = "/tmp/homenetctl/"+mId+"/receivedNewCert.pem";

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

        if (CertificateHandler::checkCertificate(newCert, subjectSelfSignedCert)) {
            //add it to CA
            addInCA(newCert,Poco::Crypto::RSAKey(subjectSelfSignedCert));
            std::cout << "received cert OK" << std::endl;
        }
        else
            std::cout << "The received certificate is not correct!" << std::endl;
    }

    //Delete Temp files
    remove( selfSignedPath.c_str() );
    remove( receivedSelfSignedPath.c_str() );
    remove( newCertPath.c_str() );
    remove( receivedNewCertPath.c_str() );
}


void Equipment::synchroServerSide(){

    //if (!authentificateServerSide()){
    //    std::cout << "Authentification failed ! " << std::endl;
    //}
    bool result;
    std::string toSendPath = "/tmp/homenetctl/"+ mId+"/knownCerts.pem";
    std::string receivedPath = "/tmp/homenetctl/"+mId+"/knownCertsReceived.pem";
    std::string toSendPubKeyPath = "/tmp/homenetctl/"+mId+"/knownHosts";
    std::string receivedPubKeyPath = "/tmp/homenetctl/"+mId+"/knownHostsReceived";

    //Create Server socket, bind it, listen and accept connections
    Server serv(mPort);
    std::cout << "server created and listening to port: " << mPort << std::endl;
    result = serv.listenForConnectionRequests();

    //poput to accept connection between devices
    //if(result)
    //    result = serv.serverAcceptAccess(serv.getNewSocket(),mId);

    if(result) {
        std::cout << "server connected & listening:" << std::endl;

        // Updating the certificates file
        mHandler->save();

        //Receive certificates from Client
        result = serv.receiveFile(receivedPath, serv.getNewSocket());
        if (result) std::cout << "DA and CA certificates received" << std::endl;
        else std::cout << "failed" << std::endl;

        //send certificates to client
        result = serv.sendFile(toSendPath, serv.getNewSocket());
        if (result) std::cout << "DA and CA certificate sent" << std::endl;
        else std::cout << "failed" << std::endl;

        //Receive pubkey from Client
        result = serv.receiveFile(receivedPubKeyPath, serv.getNewSocket());
        if (result) std::cout << "Pubkeys received" << std::endl;
        else std::cout << "failed" << std::endl;

        //send pubkeys to client
        result = serv.sendFile(toSendPath, serv.getNewSocket());
        if (result) std::cout << "Pubkeys certificate sent" << std::endl;
        else std::cout << "failed" << std::endl;

        //Loads the received cert
        Poco::Crypto::X509Certificate::List receivedList = Poco::Crypto::X509Certificate::readPEM(receivedPath);
        std::map<std::string,Poco::Crypto::RSAKey> receivedPubList = CertificateHandler::readPubKeys(receivedPubKeyPath);
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


bool Equipment::authentificateServerSide(){

    bool result;

    std::string chainPath = "/tmp/homenetctl/"+mId+"/chain.pem";
    std::string receivedChainPath = "/tmp/homenetctl/"+mId+"/receivedChain.pem";
    std::string receivedSelfSignedPath = "/tmp/homenetctl/"+mId+"/receivedSelfSigned.pem";
    std::string selfSignedPath = "/tmp/homenetctl/"+mId+"/selfSigned.pem";

    //Create Server socket, bind it, listen and accept connections
    Server serv(mPort);
    std::cout << "server created and listening to port: " << mPort << std::endl;
    result = serv.listenForConnectionRequests();

    if(result) {
        std::cout << "server connected and listening" << std::endl;

        //write selfsigned certificate to temp file --> writeCertificateToFile()
        this->writeCertificateToFile(*mSelfSignedCertificate, selfSignedPath);

        //Receive new certificate from server INTO TEMP FILE
        result = serv.receiveFile(receivedSelfSignedPath, serv.getNewSocket());
        if (result) std::cout << "Client self signed certificate received!" << std::endl;

        //Send temp file to server
        result = serv.sendFile(selfSignedPath, serv.getNewSocket());
        if (result) std::cout << "Server Self Signed Certificate sent!" << std::endl;

        //Receive new certificate from server INTO TEMP FILE
        result = serv.receiveFile(receivedChainPath, serv.getNewSocket());
        if (result) std::cout << "Client chain certificate received!" << std::endl;

        CertificateHandler::X509Ptr subjectSelfSignedCert = std::make_shared<Poco::Crypto::X509Certificate>(readCertificateFromFile(receivedSelfSignedPath));
        Poco::Crypto::X509Certificate::writePEM(chainPath ,this->mHandler->findChainCert(subjectSelfSignedCert));

        //Send chain file to server
        result = serv.sendFile(chainPath, serv.getNewSocket());
        if (result) std::cout << "Server Chain Certificate sent!" << std::endl;


        return CertificateHandler::checkCertificateChain(Poco::Crypto::X509Certificate::readPEM(receivedChainPath), *mSelfSignedCertificate);
    }
}
