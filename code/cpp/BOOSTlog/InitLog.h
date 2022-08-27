
#pragma once

#include <string>
#include <boost/log/trivial.hpp>


using std::string;
#define LOG_TRACE\
    BOOST_LOG_SEV((InitLog::s_slg),(boost::log::trivial::trace))
#define LOG_DEBUG\
    BOOST_LOG_SEV((InitLog::s_slg),(boost::log::trivial::debug))
#define LOG_ERROR\
    BOOST_LOG_SEV((InitLog::s_slg),(boost::log::trivial::error))
//#define LOG_WARNING\
//    BOOST_LOG_SEV((InitLog::s_slg),(boost::log::trivial::warning))
// 在使用之前必须先调用 init
// 使用方式  LOG_DEBUG<<"test string";
// 也可以用boost 中的宏  BOOST_LOG_TRIVIAL(info)<<"test msg";




enum severity_level {
    trace,
    debug,
    error
};


class InitLog {
public:
    InitLog();

    ~InitLog(void);

    // 在使用之前必须先调用此函数
    static void Init(const string& dir);

    static void Log(const string& msg);

    static void init_filter();

    void SetFilterTrace();

    void SetFilterDebug();

    void SetFilterError();

    void setMinFreeSpace(size_t size);
    void setRotationSpace(size_t size);
    static boost::log::sources::severity_logger<boost::log::trivial::severity_level> s_slg;
    static std::string LogPath;
    static bool is_console_log;

private:

    void readINI();

};
