#include <iostream>
#include <string>
#include <vector>

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> \n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-r,--reset\t\tReset the configuration\n"
              << "\t-s <PORT>,--server <PORT>\t\tReset the configuration\n"
              << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }
    std::vector <std::string> sources;
    std::string port;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } else
        if ((arg == "-s") || (arg == "--server")) {
            if (i + 1 < argc) {
                port = argv[i++];
            } else {
                  std::cerr << "--server option requires one argument." << std::endl;
                return 1;
            }
        } else
        if ((arg == "-r") || (arg == "--reset")) {
            show_usage(argv[0]);
            return 0;
        } else
        {
            sources.push_back(argv[i]);
        }
    }
    return 0;
}
