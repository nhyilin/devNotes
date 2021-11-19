#include "logger.h"
#include <QtWidgets/QApplication>
#define ELPP_NO_DEFAULT_LOG_FILE
#include "loggerFiles/easylogging++.h"
#include "loggerFiles/easylogging++.cc"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{

    el::Configurations conf("D:/myDevelop/happyLogging/loggerFiles/myLog.conf");
    conf.setToDefault();
    conf.setGlobally(el::ConfigurationType::Filename, "D:/myDevelop/logs/log_%datetime.log");
    conf.setGlobally(el::ConfigurationType::Enabled, "true");
    conf.setGlobally(el::ConfigurationType::ToFile, "true");
    conf.setGlobally(el::ConfigurationType::Format, "%datetime | %level | %line | %loc | %msg");
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");

    LOG(INFO) << "first log!" << std::endl;

    QApplication a(argc, argv);
    logger w;
    w.show();
    return a.exec();
}
