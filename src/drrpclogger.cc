#include "drrpclogger.h"
#include <thread>
#include <ctime>
#include <iostream>
#include <string>
#include <experimental/filesystem>

// 将日志写入到缓冲区 队列
void DrRpcLogger::log(std::string data)
{
    queue.push(data);
}

DrRpcLogger &DrRpcLogger::getInstance()
{
    static DrRpcLogger logger;
    return logger;
}

// 初始化logger服务， 启动写入文件的线程，即从缓冲区读数据写入到文件中
DrRpcLogger::DrRpcLogger()
{
    std::thread writeLogTask([&]()
    {
        if (!std::experimental::filesystem::exists("log") || !std::experimental::filesystem::is_directory("log"))
        {
            LOG_INFO("log dir is not exists");
            if (std::experimental::filesystem::create_directory("log"))
            {
                LOG_INFO("mkdir log success ");
            }
            else
            {
                LOG_ERR("mkdir log success ");
            }
        }
        while(true)
        {
            // 获取日期时间等
            time_t cur = time(nullptr);
            tm *tmstruct = localtime(&cur);
            char fileName[128] = {0};
            sprintf(fileName, "log/%d-%d-%d-log.txt", tmstruct -> tm_year + 1900, tmstruct -> tm_mon + 1, tmstruct -> tm_mday);    
            FILE *pf = fopen(fileName, "a+");
            if (pf == nullptr)
            {
                std::cout << fileName << " open error " << std::endl;
                exit(EXIT_FAILURE);
            }
            std::string msg = queue.pop();

            char timeBuf[128] = {0};
            sprintf(timeBuf, "%d:%d:%d : [%s] "
                            , tmstruct -> tm_hour, 
                            tmstruct -> tm_min, 
                            tmstruct -> tm_sec,
                            (this -> level == INFO ? "INFO" : "ERROR")
                        ); 
            msg.insert(0, timeBuf);
            msg.append("\n");
            fputs(msg.c_str(), pf);
            fclose(pf);
        } });
    writeLogTask.detach();
}

void DrRpcLogger::setLevel(LogLevel level)
{
    this->level = level;
}