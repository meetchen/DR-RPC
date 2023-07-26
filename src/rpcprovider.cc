#include "rpcprovider.h"
#include <string>
#include <iostream>
#include "drrpcapplication.h"
#include <muduo/net/TcpServer.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <muduo/net/TcpConnection.h>
#include "drrpcheader.pb.h"
#include "zookeeperutil.h"

void RpcProvider::NofityService(google::protobuf::Service *service)
{
    ServiceInfo service_info;

    // 获取了服务对象的描述信息
    const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();

    // 获取服务的名字
    std::string service_name = pserviceDesc->name();

    // 获取服务对象service的方法的数量
    int methodCnt = pserviceDesc->method_count();

    for (int i = 0; i < methodCnt; ++i)
    {
        // 获取了服务对象指定下标的服务方法的描述（抽象描述） UserService   Login
        const google::protobuf::MethodDescriptor *pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        service_info.methodMap.emplace(method_name, pmethodDesc);
    }
    service_info.service = service;
    serviceMap.emplace(service_name, service_info);
}

void RpcProvider::Run()
{
    // 读取配置文件rpcserver的信息
    std::string ip = DrRpcApplication::getInstance().getConfigMap().getConfig("rpcserverip");
    uint16_t port = atoi(DrRpcApplication::getInstance().getConfigMap().getConfig("rpcserverport").c_str());

    muduo::net::InetAddress address(ip, port);

    // 创建TcpServer对象
    muduo::net::TcpServer server(&eventLoop, address, "RpcProvider");

    // 绑定连接回调和消息读写回调方法  分离了网络代码和业务代码
    server.setConnectionCallback(std::bind(&RpcProvider::onConneciton, this, std::placeholders::_1));

    server.setMessageCallback(std::bind(&RpcProvider::onMessage, this, std::placeholders::_1,
                                        std::placeholders::_2, std::placeholders::_3));

    // 设置muduo库的线程数量
    server.setThreadNum(4);

    // rpc服务端准备启动，打印信息
    std::cout << "RpcProvider start service at ip: " << ip << " port:" << port << std::endl;

  
    // 注册zookeeper服务
    // eventLoop.loop(); 一直存在ZkClient，不会被析构，除非关闭drrpc服务
    ZkClient zkClient;
    zkClient.start();

    for (auto &service : serviceMap)
    {
        auto &serviceName = service.first;
        auto &serviceINfo = service.second.methodMap;
        std::string path = '/' + serviceName;
        zkClient.create(path.c_str(),nullptr, 0, 0);

        for (auto& func : serviceINfo)
        {
            std::string funcPath = path + '/' + func.first;
            std::string data = ip + ":" + std::to_string(port);
            // ZOO_EPHEMERAL 临时性节点
            zkClient.create(funcPath.c_str(), data.c_str(), data.size(), ZOO_EPHEMERAL);
        }
    }

    // 启动网络服务
    server.start();
    eventLoop.loop();
}

// 连接回调
void RpcProvider::onConneciton(const muduo::net::TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        // 和rpc client的连接断开了
        conn->shutdown();
    }
}

// 消息读写回调
void RpcProvider::onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp tsp)
{

    // 网络上接收的远程rpc调用请求的字符流    Login args
    std::string recv_buf = buffer->retrieveAllAsString();

    // 从字符流中读取前4个字节的内容
    uint32_t header_size = 0;
    recv_buf.copy((char *)&header_size, 4, 0);

    // 根据header_size读取数据头的原始字符流，反序列化数据，得到rpc请求的详细信息
    std::string rpc_header_str = recv_buf.substr(4, header_size);
    duan::RpcHeader rpcHeader;

    std::string service_name;
    std::string method_name;
    uint32_t args_size;

    if (rpcHeader.ParseFromString(rpc_header_str))
    {
        // 数据头反序列化成功
        service_name = rpcHeader.servicename();
        method_name = rpcHeader.methodname();
        args_size = rpcHeader.argssize();
    }
    else
    {
        // 数据头反序列化失败
        std::cout << "rpc_header_str:" << rpc_header_str << " parse error!" << std::endl;
        return;
    }

    // 获取rpc方法参数的字符流数据
    std::string args_str = recv_buf.substr(4 + header_size, args_size);

    // 打印调试信息
    std::cout << "===============RpcProvider=====================" << std::endl;
    std::cout << "header_size: " << header_size << std::endl;
    std::cout << "rpc_header_str: " << rpc_header_str << std::endl;
    std::cout << "service_name: " << service_name << std::endl;
    std::cout << "method_name: " << method_name << std::endl;
    std::cout << "args_str: " << args_str << std::endl;
    std::cout << "===============RpcProvider===================" << std::endl;

    // 获取service对象
    auto serviceInfoIt = serviceMap.find(service_name);
    if (serviceInfoIt == serviceMap.end())
    {
        std::cout << "Don't find " << service_name << std::endl;
        return;
    }

    auto service = serviceInfoIt->second.service;
    auto methodMap = serviceInfoIt->second.methodMap;

    auto methodIt = methodMap.find(method_name);
    if (methodIt == methodMap.end())
    {
        std::cout << "Don't find " << method_name << std::endl;
        return;
    }
    auto method = methodIt->second;
    google::protobuf::Message *req = service->GetRequestPrototype(method).New();
    google::protobuf::Message *resp = service->GetResponsePrototype(method).New();

    /*
        template <typename Class, typename Arg1, typename Arg2>
        inline Closure* NewCallback(Class* object, void (Class::*method)(Arg1, Arg2),
                                    Arg1 arg1, Arg2 arg2) {
        return new internal::MethodClosure2<Class, Arg1, Arg2>(
            object, method, true, arg1, arg2);
        }
    */

    // TODO: 我不明白为什么模板进行，自动类型推演的话，会编译错误，多出来一个&
    auto callBack = google::protobuf::NewCallback<RpcProvider, const muduo::net::TcpConnectionPtr &, google::protobuf::Message *>
                                        (this, &RpcProvider::sendRpcResponse, conn, resp);

    if (req->ParseFromString(args_str))
    {
        /*
            virtual void CallMethod(const MethodDescriptor* method,
                                    RpcController* controller, const Message* request,
                                    Message* response, Closure* done) = 0;
        */
        /**
         * class UserService : public::duan::UserServiceRpc
         *  class UserServiceRpc : public ::PROTOBUF_NAMESPACE_ID::Service 
         *      void CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                  ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                  const ::PROTOBUF_NAMESPACE_ID::Message* request,
                  ::PROTOBUF_NAMESPACE_ID::Message* response,
                  ::google::protobuf::Closure* done);

                    void UserServiceRpc::CallMethod(const ::PROTOBUF_NAMESPACE_ID::MethodDescriptor* method,
                             ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
                             const ::PROTOBUF_NAMESPACE_ID::Message* request,
                             ::PROTOBUF_NAMESPACE_ID::Message* response,
                             ::google::protobuf::Closure* done) {
                        GOOGLE_DCHECK_EQ(method->service(), file_level_service_descriptors_user_2eproto[0]);
                        switch(method->index()) {
                            case 0:
                            Login(controller,
                                    ::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ::duan::LoginRequest*>(
                                        request),
                                    ::PROTOBUF_NAMESPACE_ID::internal::DownCast<::duan::LoginResponse*>(
                                        response),
                                    done);
                            break;
                            default:
                            GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
                            break;
                        }
                        }

        */
        service->CallMethod(method, nullptr, req, resp, callBack);
    }

}

// google::protobuf::Closure 回调函数 用于 down方法中，反序列化 与网络传输
void RpcProvider::sendRpcResponse(const muduo::net::TcpConnectionPtr &conn, google::protobuf::Message *resp)
{
    std::string responseStr;
    if (!resp->SerializeToString(&responseStr))
    {
        std::cout << " Send Back failure " << std::endl;
        exit(EXIT_FAILURE);
    } 
    conn->send(responseStr);
    // 模拟http短链接 由rpcprovider主动断开链接
    conn->shutdown();

} 