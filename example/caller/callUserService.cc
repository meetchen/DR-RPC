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
    loginRequst.set_password("qifei");

    duan::LoginResponse loginResponse;
    
    stub.Login(nullptr, &loginRequst, &loginResponse, nullptr);

    auto msg = loginResponse.msg();
    if (msg.statecode() == 0)
    {
        std::cout << "loginResponse error , msg : " << msg.msg() << std::endl;
    }

    std::cout << loginResponse.success() << std::endl;
 

    return 0;
}