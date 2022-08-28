#include <iostream>
#include "InitLog.h"
#include "ParseINI.h"


int main() {
    
    
    InitLog::Init(InitLog::LogPath);
    LOG_TRACE << InitLog::InitFile;
    
    
    while (true) {
        LOG_TRACE << "TRACE 日志";
        LOG_DEBUG << "DEBUG 日志";
        LOG_ERROR << "ERROR 日志";
    };
    
    return 0;
}
