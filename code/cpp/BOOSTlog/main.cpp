#include <iostream>
#include "InitLog.h"
#include "ParseINI.h"


int main() {

    InitLog::Init(InitLog::LogPath);
    LOG_TRACE << InitLog::LogPath;


    while (true)
    {
        LOG_ERROR << "error 日志";
    };

    return 0;
}
