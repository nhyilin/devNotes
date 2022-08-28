#include "InitLog.h"

#include <iostream>
#include <string>

#include <boost/filesystem.hpp>


#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/detail/thread_id.hpp>
#include <boost/log/detail/format.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

#include "ParseINI.h"


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;

std::string InitLog::InitFile = "./test.ini";//后期可以放在stdafx 中
std::string InitLog::LogPath = "./Logs";
severity_level InitLog::logLevel = trace;

//TODO:什么时候适合用静态函数

bool InitLog::is_console_log = false;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)//TODO: 设置默认log

boost::log::sources::severity_logger<boost::log::trivial::severity_level> InitLog::s_slg;

InitLog::InitLog() {

}

InitLog::~InitLog(void) {

}

void InitLog::Init(const string &dir) {
    InitLog::readINI();
    InitLog::init_filter(InitLog::logLevel);
    if (boost::filesystem::exists(dir) == false) {
        boost::filesystem::create_directories(dir);
    }
    
    if (is_console_log) {
        auto consoleSink = boost::log::add_console_log
                (       //控制台日志
                        std::cout,
                        keywords::auto_flush = true,
                        keywords::format =
                                (
                                        expr::stream
                                                << "[" << expr::attr<int>("RecordID") << "] "
                                                << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
                                                                                                           "%Y-%m-%d %H:%M:%S.%f")
                                                << " " << expr::attr<boost::log::aux::thread::id>("ThreadID")
                                                << "] " << "[" << logging::trivial::severity << "] "
                                                << expr::smessage
                                )
                );
        consoleSink->locked_backend()->auto_flush(true);
    }
    
    
    auto pSink = logging::add_file_log
            (       //文件日志
                    keywords::target = InitLog::LogPath,
                    keywords::max_size = 100 * 1024 * 1024,
                    keywords::open_mode = std::ios::app,
                    keywords::file_name = dir + "/%Y-%m-%d_%N.log",
                    keywords::rotation_size = 10 * 1024 * 1024,
                    keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
                    keywords::format =
                            (
                                    expr::stream
                                            << "[" << expr::attr<int>("RecordID") << "] "
                                            << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp",
                                                                                                       "%Y-%m-%d %H:%M:%S.%f")
                                            << " " << expr::attr<boost::log::aux::thread::id>("ThreadID")
                                            << "] " << "[" << logging::trivial::severity << "] "
                                            << expr::smessage
                            )
            );
    
    
    
    // 如果不写这个 它不会实时的把日志写下去, 而是等待缓冲区满了,或者程序正常退出时写下,这样做的好处是减少IO操作.提高效率,  不过我这里不需要它. 因为我的程序可能会异常退出.
    pSink->locked_backend()->auto_flush(true);//使日志实时更新
    
    //pSink->imbue(std::locale("zh_CN.UTF-8")); // 本地化
    logging::add_common_attributes();
    
    attrs::counter<int> RecordID(1);
    logging::core::get()->add_global_attribute("RecordID", RecordID);
    
}


void InitLog::Log(const string &msg) {
    src::logger lg;
    BOOST_LOG(lg) << msg;
}


void InitLog::SetFilterTrace() {
    logging::core::get()->set_filter(expr::attr<severity_level>("Severity") >= trace);
}

void InitLog::SetFilterDebug() {
    logging::core::get()->set_filter(expr::attr<severity_level>("Severity") >= debug);
}

void InitLog::SetFilterError() {
    logging::core::get()->set_filter(expr::attr<severity_level>("Severity") >= error);
}


void InitLog::init_filter(const severity_level& logLevel_INI) {
    logging::core::get()->set_filter(
//            logging::trivial::severity >= logging::trivial::trace
            logging::trivial::severity >= logLevel_INI
            );//日志级别过滤，分trace、debug、error由低到高
}

void InitLog::readINI() {
    //此函数查询区分大小写
    
    //解析log保存路径
    ParseINI ini;
    map<string, string> log_select;
    const char *log_section = "LOG";//在设置文件中的LOG节点查找
    InitLog logger;
    std::string ini_file_Path = logger.InitFile;
    ini.ReadConfig(ini_file_Path, log_select, log_section);
    auto search_log_path = log_select.find("logpath");
    if (search_log_path != log_select.end()) {
        InitLog::LogPath = search_log_path->second;
    } else {
        std::cout << "Not found " << log_section << "in INI File!\n";
        LOG_ERROR << "Not found " << log_section << "in INI File!\n";
    }
    
    //解析logLevel
    auto search_log_level = log_select.find("loglevel");
    if (search_log_level != log_select.end()) {
        std::string level_INI = search_log_level->second;
        logger.setLogLevel(InitLog::logLevel, level_INI);
        //InitLog::logLevel = search_log_level->second;//TODO: 从设置文件读取log层级
        
    } else {
        std::cout << "Not found " << InitLog::logLevel << "in INI File!\n";
        LOG_ERROR << "Not found " << InitLog::logLevel << "in INI File!\n";
    }
}

void InitLog::setLogLevel(severity_level &logLevel, std::string &logLevel_INI) {
    if (logLevel_INI == "trace")
        InitLog::logLevel = trace;
    else if (logLevel_INI == "debug")
        InitLog::logLevel = debug;
    else InitLog::logLevel = error;
}
