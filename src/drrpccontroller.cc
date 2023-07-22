#include <iostream>
#include "drrpccontroller.h"

bool DrRpcController::Failed() const
{
    return isFailed;
}

std::string DrRpcController::ErrorText() const
{
    return msg;
}

DrRpcController::DrRpcController()
{
    isFailed = false;
    msg = "";
}

void DrRpcController::SetFailed(const std::string &reason)
{
    isFailed = true;
    msg = reason;
}

void DrRpcController::Reset()
{
    isFailed = false;
    msg = "";
}

void DrRpcController::StartCancel(){

};
bool DrRpcController::IsCanceled() const {
    return true;
};
void DrRpcController::NotifyOnCancel(google::protobuf::Closure *callback){

};