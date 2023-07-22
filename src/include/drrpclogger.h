#pragma once
#include "drrpclockqueue.h"

// 定义宏 LOG_INFO("xxx %d %s", 20, "xxxx")
#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        DrRpcLogger &logger = DrRpcLogger::getInstance(); \
        logger.setLevel(INFO); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.log(c); \
    } while(0) \

#define LOG_ERR(logmsgformat, ...) \
    do \
    {  \
        DrRpcLogger &logger = DrRpcLogger::getInstance(); \
        logger.setLevel(ERROR); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.log(c); \
    } while(0) \

enum LogLevel
{
    INFO,
    ERROR,
};

class DrRpcLogger
{
public:
    void log(std::string data);
    static DrRpcLogger& getInstance();
    void setLevel(LogLevel level);
private:
    DrRpcLogger();
    DrRpcLogger(const DrRpcLogger& val) = delete;
    DrRpcLogger& operator=(DrRpcLogger& val) = delete;
    DrRpcLockQueue queue;
    LogLevel level;
};