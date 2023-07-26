#include "drrpcchannel.h"
#include "drrpcapplication.h"
#include "drrpcheader.pb.h"
#include <google/protobuf/descriptor.h>
#include "drrpcheader.pb.h"
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include <functional>
#include <zookeeperutil.h>

void DrRpcChannel::CallMethod(const google::protobuf::MethodDescriptor *method,
                google::protobuf::RpcController *controller, const google::protobuf::Message *request,
                google::protobuf::Message *response, google::protobuf::Closure *done) 
{
    // 报文的格式4字节的数据头长度 
    // 数据头 serviceName + methodName + argsLen
    const google::protobuf::ServiceDescriptor* service = method->service();
    

    std::string requstStr;
    if (!request->SerializeToString(&requstStr))
    {
        LOG_ERR("Serialize to string error for requsetStr");
        controller->SetFailed("Serialize to string error for requsetStr");
        return;
    }

    duan::RpcHeader rpcHeader;
    rpcHeader.set_servicename(service->name());
    rpcHeader.set_methodname(method->name());
    rpcHeader.set_argssize(requstStr.size());

    std::string headerStr;
    if (!rpcHeader.SerializeToString(&headerStr))
    {
        LOG_ERR("Serialize to string error for headerStr");
        controller->SetFailed("Serialize to string error for headerStr");
        return;
    }

    uint32_t headerStrLen = headerStr.size();


    // 将rpc数据头的长度 以长度为4字节（4个char）插入到 数据前面
    // 在arg1位置插入字符串arg2的前arg3个字符
    headerStr.insert(0, reinterpret_cast<char*>(&headerStrLen), 4);

    // 将参数 即request跟在数据后面
    headerStr.append(requstStr);


    // 使用tcp请求发送rpc请求

    // 创建套接字 
    // 所使用的网络协议ipv4
    // 链接类型 
    // 协议指定了与套接字一起使用的特定协议。 通常情况下，在给定的协议族中，只有一种协议支持特定的套接字类型，在这种情况下，protocol 可以指定为 0。
    // TODO: 可以使用智能指针 管理这个描述符 从而自动关闭
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 使用unique_ptr 自定义删除器 管理clienSocket 
    // 即栈上的对象退出作用域时，会自动析构，调用clientPtr的析构函数，析构函数中执行删除器
    std::unique_ptr<int, std::function<void(int *)>> clientPtr(&clientSocket, 
            [](int *fd){
                LOG_ERR("ClientSocket closed ");
                close(*fd);
            });

    if (clientSocket == -1) {
        LOG_ERR("Could not create socket");
        controller->SetFailed("Error: Could not create socket");
        return;
    }

    // 从配置文件获取ip地址与端口号 
    // DrRpcConfig& config = DrRpcApplication::getConfigMap();
    // uint32_t port = atoi(config.getConfig("rpcserverport").c_str());
    // std::string ip = config.getConfig("rpcserverip");

    // 从zookeeper获取对应服务的ip地址与端口号
    ZkClient zkClient;
    zkClient.start();
    std::string path = "/" + service->name() + '/' + method -> name();
    std::string info = zkClient.getData(path.c_str());
    if (info == "")
    {
        LOG_ERR("GET ip info error from zookeeper");
        return;
    }
    int pos = info.find(':');
    if (pos == -1)
    {   
        LOG_ERR("ip info parse error from zookeeper");
        return;
    }
    std::string ip = info.substr(0, pos);
    uint32_t port = atoi(info.substr(pos + 1).c_str());


    // 设置服务器地址和端口
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); // 替换为目标服务器的端口号
    /*
         This function converts the character string src into a network address structure in the af address family, then copies the network address structure to dst
    */
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr); // 替换为目标服务器的IP地址

    // 连接服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Connection failed" << std::endl;
        LOG_ERR("Error: Connection failed");
        controller->SetFailed("Error: Connection failed");
        return;
    }
    

    // 发送数据
    int messageLen = headerStr.size();
    
    if (send(clientSocket, headerStr.c_str(), headerStr.size(), 0) != messageLen) {
        std::cerr << "Error: Send failed" << std::endl;
        LOG_ERR("Error: Send failed");

        controller->SetFailed("Error: Send failed");
        return;
    }

    // 接收服务器的响应
    char buffer[1024] = {0};
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        if (bytesRead == 0) {
            LOG_ERR("Connection closed by peer");
            std::cerr << "Connection closed by peer" << std::endl;
        } else {
            LOG_ERR("Error: Receive failed");
            std::cerr << "Error: Receive failed" << std::endl;
        }
        controller->SetFailed("Error: Receive failed");
        return;
    } else {
        buffer[bytesRead] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }


    // 将最终的结果写回到response
    if (!response->ParseFromString(buffer))
    {
        std::cout << "Parse From String Error " << std::endl;
        LOG_ERR("Parse From String Error ");
        controller->SetFailed("Parse From String Error ");
        return;
    }

     // 打印调试信息
    // std::cout << "===============DrRpcChannel=====================" << std::endl;
    // std::cout << "header_size: " << headerStrLen << std::endl;
    // std::cout << "rpc_header_str: " << headerStr << std::endl;
    // std::cout << "service_name: " << service->name() << std::endl;
    // std::cout << "method_name: " << method->name()<< std::endl;
    // std::cout << "args_str: " << requstStr << std::endl;
    // std::cout << "===============DrRpcChannel===================" << std::endl;


}

DrRpcChannel::DrRpcChannel()
{

}