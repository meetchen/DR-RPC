#include "drrpcchannel.h"
#include "drrpcapplication.h"
#include "drrpcheader.pb.h"
#include <google/protobuf/descriptor.h>
#include "drrpcheader.pb.h"


void DrRpcChannel::CallMethod(const google::protobuf::MethodDescriptor *method,
                google::protobuf::RpcController *controller, const google::protobuf::Message *request,
                google::protobuf::Message *response, google::protobuf::Closure *done) 
{
    // 报文的格式4字节的数据头长度 
    // 数据头 serviceName + methodName + argsLen
    const google::protobuf::ServiceDescriptor* service = method->service();
    
    std::string headerStr = service->name();
    headerStr += method->name();

    std::string requstStr;
    if (!request->SerializeToString(&requstStr))
    {
        std::cout << "Serialize to string error for " << method->name() << std::endl;
    }

    // int headerLen = requstStr.
    duan::RpcHeader rpcHeader;
    rpcHeader.set_servicename(service->name());
    rpcHeader.set_methodname(method->name());
    rpcHeader.set_argssize(requstStr.size());

    std::string headerStr;
    if (!rpcHeader.SerializeToString(&headerStr))
    {
        std::cout << "Serialize to string error for " << method->name() << std::endl;
    }

    uint32_t headerStrLen = headerStr.size();

    // 将rpc数据头的长度 以长度为4字节（4个char）插入到 数据前面
    // 在arg1位置插入字符串arg2的前arg3个字符
    headerStr.insert(0, reinterpret_cast<char*>(headerStrLen), 4);

    // 将参数 即request跟在数据后面
    headerStr.append(requstStr);

}

DrRpcChannel::DrRpcChannel()
{

}