#pragma once
#include "google/protobuf/service.h"
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <unordered_map>


class RpcProvider
{
public:
    void NofityService(google::protobuf::Service *service);
    void Run();

private:
    muduo::net::EventLoop eventLoop;

    struct ServiceInfo
    {
        google::protobuf::Service* service;
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> methodMap;
    };
    
    std::unordered_map<std::string, ServiceInfo> serviceMap;

    // 连接回调
    void onConneciton(const muduo::net::TcpConnectionPtr &);

    // 消息读写回调
    void onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *, muduo::Timestamp);

    // google::protobuf::Closure 回调函数 用于 down方法中，反序列化 与网络传输
    void sendRpcResponse(const muduo::net::TcpConnectionPtr &, google::protobuf::Message *);
};