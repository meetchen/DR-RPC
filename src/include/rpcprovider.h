#pragma once
#include "google/protobuf/service.h"
class RpcProvider
{
public:
    void NofityService(google::protobuf::Service *service);
    void Run();
};