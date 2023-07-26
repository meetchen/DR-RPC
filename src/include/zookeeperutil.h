#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>

class ZkClient
{
    public:
    ZkClient();
    ~ZkClient();
    // 连接zkServer
    void start();

    // 在zk指定path上创建znode节点
    // state 表示永久节点 或者 临时节点 0默认为临时节点
    void create(const char *path, const char *data, int datalen, int state = 0);

    // 从指定路径上查询数据
    std::string getData(const char *path);
    private:

    // zk客户端句柄
    zhandle_t *m_zhandle;
};