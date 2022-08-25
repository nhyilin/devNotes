#include <iostream>
#include "InitLog.h"

int main() {

#ifdef _WIN32
    MyLog::Init("./Log");
#else
    MyLog::Init("./Log");
#endif

    LOG_DEBUG << "debug 日志";

    LOG_TRACE << "trace 日志";
    LOG_ERROR << "error 日志";


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
