#include "drrpcapplication.h"
#include <unistd.h>
#include <iostream>
#include <string>

DrRpcConfig DrRpcApplication::myConfig;

void showArgsHelp()
{
    std::cout << "format : command -c <config file> " << std::endl;
}

void DrRpcApplication::Init(int argc, char **argv)
{
    if (argc < 2)
    {
        showArgsHelp();
        exit(EXIT_FAILURE);
    }

    int opt;
    std::string configFile;
    while ((opt = getopt(argc, argv, "c:")) != -1)
    {
        switch (opt)
        {
            case 'c':
                configFile = optarg;
                break;
            case '?':
                showArgsHelp();
                exit(EXIT_FAILURE);
            default:
                showArgsHelp();
                exit(EXIT_FAILURE);
        }
    }

    myConfig.loadConfigFile(configFile.c_str());
    std::cout << "rpcserverip:" << myConfig.getConfig("rpcserverip") << std::endl;
}

DrRpcApplication &DrRpcApplication::getInstance()
{
    static DrRpcApplication app;
    return app;
}