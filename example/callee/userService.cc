#include<iostream>
#include<string>
#include"user.pb.h"
#include"drrpcapplication.h"
#include"rpcprovider.h"

class UserService : public::duan::UserServiceRpc
{
    public:
        bool Login(std::string name, std::string password)
        {
            
            std::cout << "this is rpc login  " << std::endl;
            std::cout << "name : " << name << "\npassword : " << password << std::endl;
            return true;
        }
        
        void Login(::google::protobuf::RpcController* controller,
                    const ::duan::LoginRequest* request,
                    ::duan::LoginResponse* response,
                    ::google::protobuf::Closure* done)
        {
            std::string name = request->name();
            std::string password = request->password();

            bool success = Login(name, password);

            duan::ResultMsg *msg = response->mutable_msg();
            msg->set_statecode(200);
            msg->set_msg("good");
            response->set_success(success);

            done->Run();
        }

        void Register(std::string& name, std::string& password)
        {
            std::cout << "this is local Register" << std::endl;
            return;
        }

        void Register(::google::protobuf::RpcController* controller,
                    const ::duan::RegisterRequest* request,
                    ::duan::RegisterRespone* response,
                    ::google::protobuf::Closure* done)
        {
            std::string name = request->name();
            std::string password = request->password();
            Register(name, password);
            
            duan::ResultMsg *msg = response->mutable_msg();
            msg->set_statecode(200);
            msg->set_msg("register finish");

            done->Run();

            return;
        }


};

void weclomeInfo()
{
    // std::cout << "Hello DR RPC" << std::endl;

    // std::cout << "  /\\_/\\ " << std::endl;
    // std::cout << " ( o.o )" << std::endl;
    // std::cout << "  > ^ < " << std::endl;
    std::cout << "" << std::endl;
    std::cout << "     /\\_/\\   _____  _____    _____  _____    _____ " << std::endl;
    std::cout << "    ( o.o ) |  __ \\|   __ \\  |  __ \\|  __ \\ / ____|" << std::endl;
    std::cout << "     > ^ <  | |  | || |__) | | |__) | |__) | |     " << std::endl;
    std::cout << "            | |  | ||  _  /  |  _  /|  ___/| |     " << std::endl;
    std::cout << "            | |__| || | \\ \\  | | \\ \\| |    | |____ " << std::endl;
    std::cout << "            |_____/ |_|  \\_\\ |_|  \\_\\_|     \\_____|" << std::endl;
    std::cout << "                                                    " << std::endl;
}

int main(int argc, char **argv)
{
    weclomeInfo();

    LOG_INFO("ddddd");

    //初始化框架
    DrRpcApplication::Init(argc, argv);

    // 发布rpc
    RpcProvider pro;
    pro.NofityService(new UserService());
    
    // 启动服务
    pro.Run();

    return 0;
}