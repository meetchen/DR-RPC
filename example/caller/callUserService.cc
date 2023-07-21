#include <iostream>
#include "user.pb.h"
#include "drrpcapplication.h"
#include "drrpcchannel.h"

int main(int argc, char **argv)
{
    DrRpcApplication::Init(argc, argv);

    duan::UserServiceRpc_Stub stub(new DrRpcChannel());

    // 封装传入的参数
    duan::LoginRequest loginRequst;
    loginRequst.set_name("duanran");
    loginRequst.set_password("password");

    duan::LoginResponse loginResponse;
    
    stub.Login(nullptr, &loginRequst, &loginResponse, nullptr);

    auto msg = loginResponse.msg();

    std::cout << "------------------" << std::endl;
    if (msg.statecode() == 0)
    {
        std::cout << "Login Response error, msg : " << msg.msg() << std::endl;
    }
    std::cout << "------------------" << std::endl;
 

    return 0;
}