//
// Created by romain on 15/10/2019.
//

#include "certificateHandler.h"
#include <memory>

namespace fs = std::filesystem;

// Constructor of the handler
// @params privKey The private key of the equipment is needed to verify its identity
// @params name Name of the equipement
// @params certDirPath (optional) path to store certificates (default : /tmp/homenetctl/cert)
// @params selfSignedCertName (optional) name of the self signed certificate to load
CertificateHandler::CertificateHandler(EVP_PKEY * privKey, std::string name, std::string certDirPath, std::string selfSignedCertName)
    : mCertDir(certDirPath+=name)
{
    CertificateHandler::X509Ptr selfSignedX509;
    // If the certificate exists, loads it
    if (fs::exists(certDirPath / (fs::path)selfSignedCertName)){
        std::cout << "Loading certificate..." << std::endl;
        selfSignedX509 = std::make_shared<Poco::Crypto::X509Certificate>(certDirPath / (fs::path)selfSignedCertName);
    } else {
        // Else generating it with the given name and private key
        std::cout << "Generating certificate..." << std::endl;
        selfSignedX509 = CertificateHandler::selfSign(name, privKey, 30);
    }

    bool abort = false;
    // Name check
    if (selfSignedX509->issuerName() != ("/CN="+name)){
        abort = true;
        std::cout << "ERROR : The given name does not match the one on the self signed certificate" << std::endl;
    }

    // Match public key / private key check
    if (!CertificateHandler::checkCertificate(*CertificateHandler::selfSign(name, privKey, 30), *selfSignedX509)){
        abort = true;
        std::cout << "ERROR : The given private key does not match the public key on the self signed certificate" << std::endl;
    }

    // If there are errors in root node, abort
    if (abort){
        std::exit(EXIT_FAILURE);
    }
    // Contructing the root node of the tree
    mSelfSignedCert=std::make_shared<certificate_node>();
    mSelfSignedCert->certificate=selfSignedX509;
    mSelfSignedCert->parent.reset();
    mSelfSignedCert->children=std::vector<std::shared_ptr<certificate_node>>();
    mSelfSignedCert->isRoot = true;

    // Adding the root node to the indexer
    mPubKeyIndex.emplace(std::make_pair("/CN="+name, Poco::Crypto::RSAKey(*selfSignedX509.get())));
    DevId selfId = DevId("/CN="+name, CertificateHandler::getPublicKey(*selfSignedX509));
    mX509Searcher[DevId(selfId)]=std::weak_ptr<certificate_node>(mSelfSignedCert);

}

/** Add a certificate to the tree data structure
 * @params cert The certificate to add
 * @params signerKey The public of the signer of the added certificate
 */
bool CertificateHandler::addCertificate(X509Ptr cert){
    if (!mPubKeyIndex.contains(cert->issuerName())){
        std::cout << "Signer " + cert->issuerName()+ " key not found, please provide it" << std::endl;
        return false;
    }
    std::shared_ptr<Poco::Crypto::RSAKey> pocoKey = std::make_shared<Poco::Crypto::RSAKey>(Poco::Crypto::RSAKey::KL_2048,Poco::Crypto::RSAKey::EXP_SMALL);
    std::shared_ptr<Poco::Crypto::RSAKey> issuerKey = std::make_shared<Poco::Crypto::RSAKey>(mPubKeyIndex.at(cert->issuerName()));
    /* if (!cert->issuedBy(*(sign("foo",Poco::Crypto::EVPPKey(pocoKey.get()) , cert->issuerName().substr(4, cert->issuerName().size()), Poco::Crypto::EVPPKey(issuerKey.get()), 1)))) { */
    /*     std::cout << "Found keys is not the right one..." << std::endl; */
        /* return false; */
    /* } */
    return(addCertificate(cert, mPubKeyIndex.at(cert->issuerName())));

}

/** Add a certificate to the tree data structure
 * @params cert The certificate to add
 * @params signerKey The public of the signer of the added certificate
 */
bool CertificateHandler::addCertificate(X509Ptr cert, Poco::Crypto::RSAKey signerKey){

    DevId issuer = DevId(cert->issuerName(), CertificateHandler::keyToString(signerKey));
    DevId subject = DevId(cert->subjectName(), CertificateHandler::keyToString(Poco::Crypto::RSAKey(*cert)));

    // If the issuer is indexed
    if (mX509Searcher.contains(subject)){
        std::shared_ptr<certificate_node> parentNode = mX509Searcher.at(subject).lock();

        // Creation of the child node
        std::shared_ptr<certificate_node> newNode=std::make_shared<certificate_node>();
        newNode->children=std::vector<std::shared_ptr<certificate_node>>();
        newNode->certificate = cert;
        newNode->parent = parentNode;
        newNode->isRoot = false;
        parentNode->children.push_back(newNode);

        // Index the new node
        if (!mX509Searcher.contains(DevId(cert->subjectName(), CertificateHandler::getPublicKey(*cert)))){
            mX509Searcher[DevId(cert->subjectName(), CertificateHandler::getPublicKey(*cert))]=std::weak_ptr<certificate_node>(newNode);
            mPubKeyIndex.emplace(std::make_pair(cert->issuerName(),signerKey));
            /* mPubKeyIndex.emplace(std::make_pair(cert->subjectName(),Poco::Crypto::RSAKey(*cert))); */
        }
        std::cout << "Signer" << cert->issuerName() << " Added !"  << std::endl;
        return true;
    } else {
        std::cout << "Signer not found, cannot be added to the tree" << std::endl;
        return false;
    }
}


bool CertificateHandler::addPubKey(std::string id, Poco::Crypto::RSAKey key){
    if (mPubKeyIndex.find(id) == mPubKeyIndex.end()){
        std::cout << "Could not have add " << id << " pubkey to the index cause it is already present" << std::endl;
        return false;
    }
    mPubKeyIndex.emplace(std::make_pair(id,key));
    return true;
}

void CertificateHandler::moveNodeToCA(X509Ptr cert){
    DevId id = DevId(cert->issuerName(), keyToString(mPubKeyIndex.at(cert->issuerName())));
    if (mX509Searcher.contains(id)){
        auto current_node = mX509Searcher.at(id).lock();
        auto parent_node = current_node->parent.lock();
        bool found =false;
        for (auto itr(parent_node->children.begin()); itr != parent_node->children.end();itr++){
            if (*itr == current_node){
                parent_node->children.erase(itr);
                found = true;
            }
        }
        if (!found) {
            std::cout << "Node not found in parent_node ! Error ! Aborting !" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        current_node->certificate = cert;
        mSelfSignedCert->children.push_back(current_node);
        std::cout << "Node found and moved to root" << std::endl;
    }
}

bool CertificateHandler::isStored(X509Ptr cert){
    DevId id = getIdFromX509(*cert);
    return mX509Searcher.contains(id);
    /* if (mX509Searcher.contains(id)){ */
        /* return true; */
    /* } else */
        /* return false; */
}

/* Go through the tree starting from a certificate in order to get the chain to the root
 * @params cert Certificate starting point of the chain
 * @return a list of certificate to be used by checkCertificateChain
 */
Poco::Crypto::X509Certificate::List CertificateHandler::findChainCert(CertificateHandler::X509Ptr cert){
    Poco::Crypto::X509Certificate::List res;
    DevId clientId = DevId(cert->subjectName(), CertificateHandler::getPublicKey(*cert));
    if (!mX509Searcher.contains(clientId)){
        return Poco::Crypto::X509Certificate::List();
    } else {
        // If the client is in the indexer
        std::shared_ptr<certificate_node> currentNode = mX509Searcher.at(clientId).lock();
        // Going all the way to the root node while saving the path taken
        while (currentNode.get() and !currentNode->parent.expired()){
            res.push_back(*currentNode->certificate);
            currentNode = currentNode->parent.lock();
        }
        // Adding the root node to the chain certification too
        if (currentNode.get()){
            res.push_back(*currentNode->certificate);
        }
    }
    return res;
}


/// Generate a new signed certificate
/// @param nameIssuer
/// @param privkeyIssuer
/// @param nameClient name of the client that will need the certificate
/// @param pubkeyClient public key of the client that will need the certificate
/// @param validityDate
/// @return a pointer to a new certificate

CertificateHandler::X509Ptr CertificateHandler::sign(std::string issuerName, EVP_PKEY *issuerKey, std::string clientName, EVP_PKEY *clientKey, int validityDays)
{
    X509 *x509 = X509_new();
    char * cIssuerName = (char *) issuerName.c_str();
    char * cClientName = (char *) clientName.c_str();
    if(!x509) {
        std::cerr << "Unable to create X509 structure." << std::endl;
    }
    /* Set the date limits of the certificate */
    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), validityDays*24*60*60);

    /* Set the public key of the certificate */
    X509_set_pubkey(x509, clientKey);

    /* We want to copy the subject name to the issuer name. */
    X509_NAME * x509IssuerName = X509_NAME_new();
    X509_NAME * x509ClientName = X509_NAME_new();


    X509_NAME_add_entry_by_txt(x509IssuerName, "CN", MBSTRING_ASC, (unsigned char *)cIssuerName, -1, -1, 0);
    X509_NAME_add_entry_by_txt(x509ClientName, "CN", MBSTRING_ASC, (unsigned char *)cClientName, -1, -1, 0);
    /* Set the issuer name. */
    X509_set_issuer_name(x509, x509IssuerName);
    X509_set_subject_name(x509, x509ClientName);

    /* Sign the certificate with our key. */
    if(!X509_sign(x509, issuerKey, EVP_sha1()))
    {
        std::cerr << "Error signing certificate." << std::endl;
        X509_free(x509);
    }
    X509_NAME_free(x509IssuerName);
    X509_NAME_free(x509ClientName);
    return std::make_shared<Poco::Crypto::X509Certificate>(x509);
}

/// Generate a new self signed certificate
/// @param name
/// @param privkeyIssuer
/// @param validityDate
/// @return a pointer to a new self signed certificate

CertificateHandler::X509Ptr CertificateHandler::selfSign(std::string name, EVP_PKEY * keyPair, int validityDays){
    return CertificateHandler::sign(name, keyPair, name, keyPair, validityDays);
}

/** Check whether the client certificate has been signed by our
 * @param Client certificate
 * @return result of the verification
 */
bool CertificateHandler::checkCertificateChain( Poco::Crypto::X509Certificate::List certChain, Poco::Crypto::X509Certificate selfSignedCert)
{
    bool status = true;
    if (certChain.size() < 1){
        return false;
    }
    // Verification loop
    Poco::Crypto::X509Certificate::List::iterator itr;
    for (itr = certChain.begin(); (itr+1) != certChain.end() and (itr) != certChain.end(); itr++){
        if (!itr->issuedBy(*(itr+1))){
            std::cout << "Failed between " + itr->subjectName() + " and "+ (itr+1)->subjectName() << std::endl;;
            status = false;
        }
    }
    status = status and itr->issuedBy(selfSignedCert);
    return status;
}


/** Check whether the client certificate has been signed by our
 * @param Client certificate
 * @return result of the verification
 */
bool CertificateHandler::checkCertificate( Poco::Crypto::X509Certificate clientCert, Poco::Crypto::X509Certificate selfSignedCert)
{
    return clientCert.issuedBy(selfSignedCert);
}

/** Return the string value of the public key in the X509Certificate
 * @param certificate's key to print
 * @return Public key in PEM format in a string
 */
std::string CertificateHandler::getPublicKey(Poco::Crypto::X509Certificate cert){
    std::unique_ptr<std::stringstream>  ss = std::make_unique<std::stringstream>();
    Poco::Crypto::RSAKeyImpl a = Poco::Crypto::RSAKeyImpl(cert);
    a.save(ss.get());
    return ss->str();
}

/* Return the string value of the public RSAKey
 * @param public key to print
 * @return Public key in PEM format in a string
 */
std::string CertificateHandler::keyToString(Poco::Crypto::RSAKey key){
    std::unique_ptr<std::stringstream>  ss = std::make_unique<std::stringstream>();
    Poco::Crypto::RSAKeyImpl::Ptr a = key.impl();
    a->save(ss.get());
    return ss->str();
}

/** Return a storable string describing the device based on its id
 * @params id DevId of the device
 */
std::string CertificateHandler::getSignatureId(DevId id){
    std::string signature = "";
    if (id.first.size() > 10){
        signature += id.first.substr(0,10);
    } else {
        signature = id.first;
    }
    signature += '_';
    signature += id.second.substr(id.second.find("\n"),id.second.find("\n")+20);
    return signature;
}

CertificateHandler::DevId CertificateHandler::getIdFromX509(Poco::Crypto::X509Certificate cert){
    return DevId(cert.subjectName(), CertificateHandler::getPublicKey(cert));
}

Poco::Crypto::X509Certificate::List CertificateHandler::getAllNodes(){
    Poco::Crypto::X509Certificate::List certificateList;

    std::deque<std::shared_ptr<certificate_node>> currentDepth;
    std::deque<std::shared_ptr<certificate_node>> nextDepth;

    certificateList.push_back(*mSelfSignedCert->certificate) ;
    for (auto node : mSelfSignedCert->children){
        currentDepth.push_back(node);
    }

    while (currentDepth.size()){
        for (auto node : currentDepth){
            certificateList.push_back(*node->certificate);
            for (auto child : node->children){
                nextDepth.push_back(child);
            }
        }
        currentDepth.swap(nextDepth);
        nextDepth.clear();
    }
    return certificateList;
}
void CertificateHandler::save(){
    Poco::Crypto::X509Certificate::List certificateList;

    std::deque<std::shared_ptr<certificate_node>> currentDepth;
    std::deque<std::shared_ptr<certificate_node>> nextDepth;
    // Dont think we should save the self signed certificate that way
    /* certificateList.push_back(*mSelfSignedCert->certificate); */
    for (auto node : mSelfSignedCert->children){
        currentDepth.push_back(node);
    }

    while (currentDepth.size()){
        for (auto node : currentDepth){
            certificateList.push_back(*node->certificate);
            for (auto child : node->children){
                nextDepth.push_back(child);
            }
        }
        currentDepth.swap(nextDepth);
        nextDepth.clear();
    }
    if (fs::exists(mCertDir / (fs::path) "knownCerts.pem")){
        fs::rename(mCertDir / (fs::path) "knownCerts.pem",mCertDir / (fs::path) "knownCerts.pem.backp");
    }
    Poco::Crypto::X509Certificate::writePEM(mCertDir / (fs::path) "knownCerts.pem", certificateList);
    std::cout << "Saving certificates..." << std::endl;

    std::string res = "";
    std::ofstream file(mCertDir / (fs::path) "knownHosts");
    for (auto itr(mPubKeyIndex.begin()); itr != mPubKeyIndex.end(); itr++){
        res += itr->first + "\n" + keyToString(itr->second) + "\n";
        res += "\n";
    }
    file << res;
}

void CertificateHandler::load(){
    if (fs::exists(mCertDir / (fs::path) "knownCerts.pem")){
        Poco::Crypto::X509Certificate::List certificateList = Poco::Crypto::X509Certificate::readPEM(mCertDir / (fs::path) "knownCerts.pem");
        std::cout << "Certificate Loaded, building tree..." << std::endl;
        X509Ptr x509;
        for (auto itr(certificateList.begin()); itr != certificateList.end(); itr++){
            x509 = std::make_shared<Poco::Crypto::X509Certificate>(*itr);
            this->addCertificate(x509);
        }
    } else {
        std::cout << "knownCerts.pem not found ! Not loading conf..." << std::endl;
    }
}

std::map<std::string,Poco::Crypto::RSAKey> CertificateHandler::readPubKeys(std::string path){
    std::map<std::string,Poco::Crypto::RSAKey> res;
    if (fs::exists(path)){
        std::string line, buff;
        std::ifstream file(path);
        std::string id = "";
        while (std::getline(file, line)){
            if (id == ""){
                id = line;
            } else {
                if (line != ""){
                    buff += line + "\n";
                } else {
                    res.emplace(std::make_pair(id, Poco::Crypto::RSAKey(buff)));
                    id = "";
                    buff = "";
                }
            }
        }
    } else {
        std::cout << "knownHosts not found ! Not loading conf..." << std::endl;
    }
    return res;
}

CertificateHandler::X509Ptr CertificateHandler::getSelfSigned(){
    return mSelfSignedCert->certificate;
}

std::string CertificateHandler::getCertsSavedPath()
{
    return mCertDir;
}

std::vector<Poco::Crypto::X509Certificate> CertificateHandler::getCA(){
    std::vector<Poco::Crypto::X509Certificate> res;
    for (auto child : mSelfSignedCert->children){
        res.push_back(*child->certificate);
    }
    return res;
}

/* bool CertificateHandler::save(){ */
/*     bool status = false; */
/*     std::deque<std::shared_ptr<certificate_node>> currentDepth; */
/*     std::string res = ""; */
/*     std::deque<std::shared_ptr<certificate_node>> nextDepth; */

/*     res += CertificateHandler::getSignatureId(CertificateHandler::getIdFromX509(*mSelfSignedCert->certificate)); */
/*     res += CertificateHandler::getSignatureId(CertificateHandler::getIdFromX509(*mSelfSignedCert->certificate)); */
/*     res += ";\n"; */
/*     for (auto node : mSelfSignedCert->children){ */
/*         currentDepth.push_back(node); */
/*     } */

/*     while (currentDepth.size()){ */
/*         for (auto node : currentDepth){ */
/*             res += CertificateHandler::getSignatureId(CertificateHandler::getIdFromX509(*node->parent.lock()->certificate)); */
/*             res += "_"; */
/*             res += CertificateHandler::getSignatureId(CertificateHandler::getIdFromX509(*node->certificate)); */
/*             res += ";"; */
/*             for (auto child : node->children){ */
/*                 nextDepth.push_back(child); */
/*             } */
/*         } */
/*         currentDepth.swap(nextDepth); */
/*         nextDepth.clear(); */
/*         res += "\n"; */
/*     } */

/*     return status; */
/* } */
