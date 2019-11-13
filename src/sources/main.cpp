#include <iostream>
#include <string>
#include <vector>
#include "certificateHandler.h"
#include "RSAKeyPair.h"
#include "test.h"

#include <openssl/pem.h>
#include <openssl/x509.h>
#include <Poco/Crypto/EVPPKey.h>
#include <Client.h>
#include <Server.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <iterator>

namespace fs = std::filesystem;

void init(std::string name);

static void daemonStart(){
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("firstdaemon", LOG_PID, LOG_DAEMON);
}

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> \n"
              << "Options:\n"
              << "\t-h,--help                     \t Show this help message\n"
              << "\t-i,--init <Name>              \t Sets up your environment\n"
              << "\t-r,--reset                    \t Reset the configuration\n"
              << "\t-a,--add <Name> <PORT>        \t Add a new equipment to my lists\n"
              << "\t-j,--client <Name> <IP> <PORT>\t Ask to join a domestic network\n"
              << "\t-d,--display <Name>           \t Display the current known devices to this equipment\n"
              << "\t-b,--background <Name> <PORT> \t Daemonize the process\n"
              << "\t-t,--test                     \t Launch tests"
              << std::endl;
}

int main(int argc, char* argv[])
{
    std::vector <std::string> sources;
    int port;
    const char * addr;
    bool test=false;
    std::string name;
    std::string command;
    std::vector<std::string> options;
    size_t size;

    if(argc < 2 )
    {
        show_usage("homenetctl");
        return 0;
    }

    Equipment eq = Equipment(argv[1],8888);
    eq.saveEquipment();

    while(true) {

        std::cout << "type in your next command " << std::endl;
        getline(std::cin,command);

        std::stringstream ss(command);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);

        for (size_t i = 0; i < vstrings.size(); ++i) {
            std::string arg = vstrings[i];
            if ((arg == "-h") || (arg == "--help")) {
                show_usage(vstrings[0]);
                return 0;
            } else if ((arg == "-a") || (arg == "--add")) {
                if (i + 2 < vstrings.size()) {
                    name = vstrings[i+1];
                    port = std::stoi(vstrings[i+2]);

                    eq = Equipment(name,port);
                    eq.addEquipmentServerSide();
                    eq.saveEquipment();

                } else {
                    std::cerr << "--add option requires two arguments." << std::endl;
                    return 1;
                }

            } else if ((arg == "--join" || arg == "-j")) {

                if (i + 3 < vstrings.size()) {
                    name = vstrings[i+1];
                    addr = vstrings[i + 2].c_str();
                    port = std::stoi(vstrings[i+3]);

                    eq = Equipment(name,port);
                    eq.addEquipmentClientSide(addr);
                    eq.saveEquipment();

                } else {
                    std::cerr << "--join option requires three arguments." << std::endl;
                    return 1;
                }

            } else if ((arg == "-i") || (arg == "--init")) {

                if (i + 1 < vstrings.size()) {
                    name = vstrings[i+1];
                    init(name);
                } else {
                    std::cerr << "--init option requires one argument." << std::endl;
                    return 1;
                }


            } else if ((arg == "-d") || (arg == "--display")) {

                if (i + 1 < vstrings.size()) {
                    name = vstrings[i];
                    //Load equipment with said name
                    //display it using eq.display();
                    eq.saveEquipment();
                    eq.display();

                } else {
                    std::cerr << "--display option requires one argument." << std::endl;
                    return 1;
                }

                //Request syncro
            } else if ((arg == "-S") || (arg == "--requestSynchro")) {

                if (i + 3 < vstrings.size()) {
                    name = vstrings[i+1];
                    addr = vstrings[i + 2].c_str();
                    port = std::stoi(vstrings[i+3]);

                    //REQUEST SYNC FROM CLIENT


                } else {
                    std::cerr << "--sync option requires three arguments." << std::endl;
                    return 1;
                }

            } else if ((arg == "-s") || (arg == "--sync")) {

                if (i + 2 < vstrings.size()) {

                    name = vstrings[i+1];
                    port = std::stoi(vstrings[i+2]);
                    
                    //SYNC FROM SERVER

                } else {
                    std::cerr << "--sync option requires one argument." << std::endl;
                    return 1;
                }


            } else if ((arg == "-r") || (arg == "--reset")) {
                show_usage(vstrings[0]);
                return 0;
            } else if ((arg == "--test")) {
                test = true;
            } else if ((arg == "-b") || (arg == "--background")) {
                daemonStart();
                while (1) {
                    syslog(LOG_NOTICE, "First daemon started.");
                    sleep(1);
                }
            } else if ((arg == "-q") || (arg == "--quit")) {
                eq.saveEquipment();
                return 0;
            }
        }
    }

    if (test) {
       std::cout << "Launching Tests :" << std::endl;
       TestHandler::launchTests();
    }
    return 0;
}

void init(std::string name)
{
    std::filesystem::path mPath = "/tmp/homenetctl";
    std::filesystem::path mPathEquipment = "/tmp/homenetctl/"+name;


    if(!fs::exists(mPath))
        fs::create_directory(mPath);

    if(!fs::exists(mPathEquipment))
        fs::create_directory(mPathEquipment);

    std::cout << "Directories were created" << std::endl;

    //Create equipment + Save it
}
