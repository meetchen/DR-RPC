#include<iostream>
#include<string>
#include"user.pb.h"
#include"drrpcapplication.h"
#include"rpcprovider.h"

class UserService : public::DUAN::UserServiceRpc
{
    public:
        bool Login(std::string name, std::string password)
        {
            std::cout << "name : " << name << "password : " << password << std::endl;
            return true;
        }
        
        void Login(::google::protobuf::RpcController* controller,
                    const ::DUAN::LoginRequest* request,
                    ::DUAN::LoginResponse* response,
                    ::google::protobuf::Closure* done)
        {
            std::string name = request->name();
            std::string password = request->password();

            bool success = Login(name, password);

            DUAN::ResultMsg *msg = response->mutable_msg();
            msg->set_statecode(200);
            msg->set_msg("good");
            response->set_success(success);

            done->Run();
        }
};

int main(int argc, char **argv)
{
    std::cout << "Hello CMake" << std::endl;

    //初始化框架
    DrRpcApplication::Init(argc, argv);

    // 发布rpc
    RpcProvider pro;
    pro.NofityService(new UserService());

    // 启动服务
    pro.Run();

    return 0;
}