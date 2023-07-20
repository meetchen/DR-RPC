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
        std::cout << "Serialize to string error for " << method->name() << std::endl;
        return;
    }

    duan::RpcHeader rpcHeader;
    rpcHeader.set_servicename(service->name());
    rpcHeader.set_methodname(method->name());
    rpcHeader.set_argssize(requstStr.size());

    std::string headerStr;
    if (!rpcHeader.SerializeToString(&headerStr))
    {
        std::cout << "Serialize to string error for " << method->name() << std::endl;
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
    if (clientSocket == -1) {
        std::cerr << "Error: Could not create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 从配置文件获取ip地址与端口号
    DrRpcConfig& config = DrRpcApplication::getConfigMap();
    uint32_t port = atoi(config.getConfig("rpcserverport").c_str());
    std::string ip = config.getConfig("rpcserverip");


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
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
    
    std::cout << headerStr << std::endl;

    // 发送数据
    int messageLen = headerStr.size();
    
    if (send(clientSocket, headerStr.c_str(), headerStr.size(), 0) != messageLen) {
        std::cerr << "Error: Send failed" << std::endl;
    }

    // 接收服务器的响应
    char buffer[1024] = {0};
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Error: Receive failed" << std::endl;
    } else {
        buffer[bytesRead] = '\0';
    }

    // 关闭套接字
    close(clientSocket);

    // 将最终的结果写回到response
    if (!response->ParseFromString(buffer))
    {
        std::cout << "Parse From String Error " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "send over !!!" << std::endl;


}

DrRpcChannel::DrRpcChannel()
{

}