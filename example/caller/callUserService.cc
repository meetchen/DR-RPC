#include <iostream>
#include "user.pb.h"
#include "drrpcapplication.h"
#include "drrpcchannel.h"

int main(int argc, char **argv)
{
    DrRpcApplication::Init(argc, argv);

    duan::UserServiceRpc_Stub stub(new DrRpcChannel());

    //  请求login方法 封装传入的参数
    duan::LoginRequest loginRequst;
    loginRequst.set_name("duanran");
    loginRequst.set_password("password");

    duan::LoginResponse loginResponse;
    DrRpcController controller;

    stub.Login(&controller, &loginRequst, &loginResponse, nullptr);

    auto msg = loginResponse.msg();
    if (controller.Failed())
    {
        std::cout << controller.ErrorText() << std::endl;
        return 0;
    }
    std::cout << "-----callUserService LoginRequest------" << std::endl;
    std::cout << "stateCode :" << msg.statecode() << std::endl;
    std::cout << "mgs :" << msg.msg() << std::endl;
    std::cout << "success :" << loginResponse.success() << std::endl;
    std::cout << "-----callUserService LoginRequest------" << std::endl;
    
    // 请求register 方法
    duan::RegisterRequest regReq;
    duan::RegisterRespone regResp;
    
    regReq.set_name("kill joy");
    regReq.set_password("joy kill");

    stub.Register(nullptr, &regReq, &regResp, nullptr);
    auto regMsg = regResp.msg();
    std::cout << "-----callUserService RegisterRequest------" << std::endl;
    std::cout << "stateCode :" << regMsg.statecode() << std::endl;
    std::cout << "mgs :" << regMsg.msg() << std::endl;
    std::cout << "-----callUserService RegisterRequest------" << std::endl;

    return 0;
}