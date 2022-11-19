
#include "StdAfx.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    InitLog::Init(InitLog::LogPath);
    LOG_TRACE << InitLog::InitFile;
    LOG_DEBUG << InitLog::InitFile;
    LOG_ERROR << InitLog::InitFile;
    QApplication a(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();
    return QCoreApplication::exec();
}
