#pragma once
#include "drrpcconfig.h"
class DrRpcApplication
{
public:
    static void Init(int argc, char **argv);
    static DrRpcApplication &getInstance();

private:
    static DrRpcConfig myConfig;
    DrRpcApplication() {}
    DrRpcApplication(const DrRpcApplication &src) = delete;
    DrRpcApplication(const DrRpcApplication &&src) = delete;
};