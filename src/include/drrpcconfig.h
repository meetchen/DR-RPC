#include <unordered_map>
#include <string>

class DrRpcConfig
{
public:
    void loadConfigFile(const char *file);
    std::string getConfig(const char *key);
private:
    std::unordered_map<std::string, std::string> myConfigMap;
};