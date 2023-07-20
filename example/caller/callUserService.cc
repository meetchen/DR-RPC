#include<iostream>
#include"user.pb.h"
#include"drrpcapplication.h"
#include"drrpcchannel.h"
int main(int argc, char ** argv)
{
    DrRpcApplication::Init(argc, argv);

    duan::UserServiceRpc_Stub(new DrRpcChannel());

    return 0;
}