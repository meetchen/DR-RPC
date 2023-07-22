#pragma once
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <memory.h>
#include <string>

class DrRpcLockQueue
{
public:
    void push(const std::string &data);
    std::string pop();
private:
    std::condition_variable cond_variable;
    std::queue<std::string> que;
    std::mutex mtx;
};