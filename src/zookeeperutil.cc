#include <zookeeperutil.h>
#include <drrpcapplication.h>
#include <iostream>

/*
    typedef void (*watcher_fn)(zhandle_t *zh, int type, 
            int state, const char *path,void *watcherCtx);

 * \param zh zookeeper handle
 * \param type event type. This is one of the *_EVENT constants. 
 * \param state connection state. The state value will be one of the *_STATE constants.
 * \param path znode path for which the watcher is triggered. NULL if the event 
 * type is
 *   ZOO_SESSION_EVENT
 * \param watcherCtx watcher context.
*/

void watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx)
{
    if (type == ZOO_SESSION_EVENT)
    {
        if (state == ZOO_CONNECTED_STATE)
        {
            sem_t *sem = (sem_t*)(zoo_get_context(zh));
            sem_post(sem);
        }
    }
}

ZkClient::ZkClient() : m_zhandle(nullptr) {}

ZkClient::~ZkClient()
{
    if (m_zhandle != nullptr) zookeeper_close(m_zhandle);
}

void ZkClient::start()
{
    std::string ip = DrRpcApplication::getInstance().getConfigMap().getConfig("zookeeperip");
    std::string port = DrRpcApplication::getInstance().getConfigMap().getConfig("zookeeperport");
    std::string path = ip + ":" + port;
    /*
        ZOOAPI zhandle_t *zookeeper_init(const char *host, watcher_fn fn,
            int recv_timeout, const clientid_t *clientid, void *context, int flags);

         * This method creates a new handle and a zookeeper session that corresponds
            * to that handle. Session establishment is asynchronous, meaning that the
            * session should not be considered established until (and unless) an
            * event of state 
            *   ZOO_CONNECTED_STATE is received.
            
        typedef void (*watcher_fn)(zhandle_t *zh, int type, 
            int state, const char *path,void *watcherCtx);
    */
    m_zhandle = zookeeper_init(path.c_str(), watcher,30000, nullptr, nullptr, 0); 
    
    if (m_zhandle == nullptr) 
    {
        LOG_ERR("zookeeper init error");
        return;
    }

    sem_t sem;
    /* Initialize semaphore object SEM to VALUE.  If PSHARED then share it
    with other processes.  */
    sem_init(&sem, 0, 0);

    /**
     * \brief set the context for this handle.
     */
    zoo_set_context(m_zhandle, &sem);

    sem_wait(&sem);

    LOG_INFO("Zookeeper init Finish ");

}

// 在zk指定path上创建znode节点
// state 表示永久节点 或者 临时节点 0默认为临时节点
void ZkClient::create(const char *path, const char *data, int datalen, int state)
{
    int flag = zoo_exists(m_zhandle, path, 0, nullptr);
    if (flag == ZNONODE) 
    {
        char path_buffer[128];
        flag = zoo_create(m_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, path_buffer, sizeof(path_buffer));
        if (flag == ZOK)
        {
            LOG_INFO(std::string("Znodel Create success ").append(path).c_str());
        } 
        else
        {
            LOG_ERR(std::string("Znodel Create error ").append(path).c_str());
            return;
        }
    }
}

// 从指定路径上查询数据
std::string ZkClient::getData(const char *path)
{
    char buff[128];
    int size = sizeof(buff);
    int flag = zoo_get(m_zhandle, path, 0, buff, &size, nullptr);

    if (flag != ZOK)
    {
        LOG_ERR(std::string("Znodel getData error : ").append(path).c_str());
        return "";
    }
    return buff;
}