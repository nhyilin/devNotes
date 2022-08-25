#include "InitLog.h"
#include <iostream>


size_t CLogger::m_szMinFreeSpace=10*1024*1024;
size_t CLogger::m_szRotationSize=1*1024*1024;
std::wstring CLogger::m_strFilePath=_T("C:\\Log\\");
bool CLogger::m_bAutoFlush=true;;

CLogger::CLogger(void)
{

}

CLogger::~CLogger(void)
{
}
void CLogger::Init()
{
    
    std::locale::global(std::locale("chs"));
    
    auto pSink = logging::add_file_log
            (
                    keywords::open_mode = std::ios::app,//追加写入
                    keywords::file_name =m_strFilePath+_T("%Y-%m-%d.log"),
                    keywords::rotation_size = m_szRotationSize,
                    keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
                    keywords::min_free_space=m_szMinFreeSpace,
                    
                    keywords::format =(
                            expr::stream
                                    <<  "["<<expr::attr<UINT>("RecordID")
                                    << "]["<<expr::format_date_time(_timestamp,"%Y-%m-%d %H:%M:%S.%f")
                                    << "]["<<_severity
                                    << "]" <<expr::wmessage)
            );
    
    pSink->locked_backend()->auto_flush(m_bAutoFlush);
    
    logging::add_common_attributes();
    
    attrs::counter<UINT> RecordID(1);
    logging::core::get()->add_global_attribute("RecordID", RecordID);
    
    ;
}
void CLogger::Start()
{
    logging::core::get()->set_logging_enabled(true);
}
void CLogger::Stop()
{
    logging::core::get()->set_logging_enabled(false);
}

void CLogger::SetFilterTrace()
{
    logging::core::get()->set_filter(expr::attr<severity_level>("Severity") >= trace);
}

void CLogger::SetFilterWarning()
{
    logging::core::get()->set_filter(expr::attr<severity_level>("Severity")>= warning);
}
void CLogger::SetFilterError()
{
    logging::core::get()->set_filter(expr::attr<severity_level>("Severity")>= error);
}


void CLogger::SetLogFilePath(std::wstring strPath)
{
    m_strFilePath=strPath;
}

void CLogger::SetMinFreeSpace(size_t size)
{
    m_szMinFreeSpace=size* 1024 * 1024;
    
}
void CLogger::SetRotationsize(size_t size)
{
    m_szRotationSize=size* 1024 * 1024;
}