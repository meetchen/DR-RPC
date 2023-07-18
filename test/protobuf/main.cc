#include"test.pb.h"
#include<iostream>
#include<string>

int main()
{
    test_proto::LoginRequest req;
    req.set_name("duanran");
    req.set_pwd("gogogo");
    
    std::string serialize;
    if(req.SerializeToString(&serialize))
    {
        std::cout << serialize << std::endl;
    }

    test_proto::LoginRequest toObj;
    if (toObj.ParseFromString(serialize))
    {
        std::cout<< toObj.name() << std::endl;
        std::cout<< toObj.pwd() << std::endl;
    }

    return 0;
}