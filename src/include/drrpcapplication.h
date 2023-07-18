 #pragma once

 class DrRpcApplication
 {
    public:
        static void Init(int argc, char **argv);
        static DrRpcApplication& getInstance();
    private:
        DrRpcApplication(){}
        DrRpcApplication(const DrRpcApplication& src) = delete;
        DrRpcApplication(const DrRpcApplication&& src) = delete;
 };