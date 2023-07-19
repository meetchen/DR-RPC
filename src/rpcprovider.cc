#include"rpcprovider.h"
#include<string>
#include<iostream>
#include"drrpcapplication.h"
#include<muduo/net/TcpServer.h>
#include<google/protobuf/descriptor.h>
void RpcProvider::NofityService(google::protobuf::Service *service)
{
    ServiceInfo service_info;

    // 获取了服务对象的描述信息
    const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();
    // 获取服务的名字
    std::string service_name = pserviceDesc->name();
    // 获取服务对象service的方法的数量
    int methodCnt = pserviceDesc->method_count();



    for (int i=0; i < methodCnt; ++i)
    {
        // 获取了服务对象指定下标的服务方法的描述（抽象描述） UserService   Login
        const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        service_info.methodMap.emplace(method_name, pmethodDesc);

    }
    service_info.service = service;
    serviceMap.emplace(service_name, service_info);
}

void RpcProvider::Run()
{
    std::string ip = DrRpcApplication::getConfigMap().getConfig("rpcserverip");
    std::string port = DrRpcApplication::getConfigMap().getConfig("rpcserverport");
    
}

// 连接回调
void RpcProvider::onConneciton(const muduo::net::TcpConnectionPtr &)
{

}

// 消息读写回调
void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *, muduo::Timestamp)
{

}