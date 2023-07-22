#include "drrpclockqueue.h"


// 多个线程写入info缓冲区
void DrRpcLockQueue::push(const std::string &data)
{
    std::lock_guard<std::mutex> lock(mtx);
    que.push(data);
    cond_variable.notify_one();
}

// 单个线程弹出info
std::string DrRpcLockQueue::pop()
{
    std::unique_lock<std::mutex> lock(mtx);
    while (que.empty())
    {
        cond_variable.wait(lock);
    }
    std::string msg = que.front();
    que.pop();
    return msg;
}


