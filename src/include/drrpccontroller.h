#pragma once
#include "google/protobuf/service.h"

class DrRpcController : public google::protobuf::RpcController
{

public:
    DrRpcController();
    bool Failed() const override;
    std::string ErrorText() const override;
    void SetFailed(const std::string &reason) override;
    void Reset() override;

    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure *callback);

private:
    bool isFailed;
    std::string msg;
};