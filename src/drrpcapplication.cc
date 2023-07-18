#include"drrpcapplication.h"

void DrRpcApplication::Init(int argc, char **argv)
{

}

DrRpcApplication& DrRpcApplication::getInstance()
{
    static DrRpcApplication app;
    return app;
}