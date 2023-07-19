#include"rpcprovider.h"
#include<string>
#include<iostream>
#include"drrpcapplication.h"
#include<muduo/net/TcpServer.h>
void RpcProvider::NofityService(google::protobuf::Service *service)
{

}

void RpcProvider::Run()
{
    std::string ip = DrRpcApplication::getConfigMap().getConfig("rpcserverip");
    std::string port = DrRpcApplication::getConfigMap().getConfig("rpcserverport");
}