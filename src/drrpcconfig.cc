#include <iostream>
#include <string>
#include "drrpcconfig.h"
#include <fstream>

void DrRpcConfig::trim(std::string &str)
{
    auto first = str.find_first_not_of(' ');
    if (first == std::string::npos)
    {
        str = "";
        return;
    }
    auto last = str.find_last_not_of(' ');
    str = str.substr(first, last - first + 1);
}

void DrRpcConfig::loadConfigFile(const char *file)
{
    std::ifstream inputFile(file);
    if (inputFile.is_open())
    {
        std::string msg;
        while (std::getline(inputFile, msg))
        {
            // 去除首尾空格
            trim(msg);
            // 如果为空 或者注释
            if (msg.empty() || msg[0] == '#')
                continue;

            std::string key, value;
            auto pos = msg.find('=');
            if (pos != std::string::npos)
            {
                key = msg.substr(0, pos);
                value = msg.substr(pos + 1);
                trim(key), trim(value);
                myConfigMap.emplace(key, value);
            }
        }
        inputFile.close();
    }
    else
    {
        std::cout << file << "isn't exist" << std::endl;
        exit(EXIT_FAILURE);
    }
}
std::string DrRpcConfig::getConfig(const char *key)
{
    if (myConfigMap.count(key))
        return myConfigMap[key];
    
    return "";
}