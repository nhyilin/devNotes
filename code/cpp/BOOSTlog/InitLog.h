#pragma once

#include <cassert>
#include <iostream>
#include <fstream>
#include <boost/locale/generator.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/filesystem.hpp>
#include <boost/log/detail/thread_id.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;


enum severity_level
{
    trace,
    warning,
    error
    
};

template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    static const char* const str[] =
            {
                    "trace",
                    "warning",
                    "error"
            };
    if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast< int >(lvl);
    return strm;
}

BOOST_LOG_ATTRIBUTE_KEYWORD(_severity,  "Severity",  severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(_timestamp, "TimeStamp", boost::posix_time::ptime)



class CLogger
{
public:
    CLogger(void);
    ~CLogger(void);
    static void Init();
    static void Start();
    static void Stop();
    
    
    //日志严重等级过滤输出
    static void SetFilterTrace();
    static void SetFilterWarning();
    static void SetFilterError();
    
    
    void SetLogFilePath(std::wstring strPath);
    void SetMinFreeSpace(size_t size);
    void SetRotationsize(size_t size);


private:
    static size_t m_szMinFreeSpace;
    static size_t m_szRotationSize;
    static std::wstring m_strFilePath;
    static bool m_bAutoFlush;
    
};