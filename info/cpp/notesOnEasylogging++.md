# 使用

将`.cc`文件与`.h`文件放在指定目录（可以include到即可）

程序入口处安装`log`

```CPP
#include "loggerFiles/easylogging++.h"//放在同级文件夹内的loggerFiles文件夹内，以便代码整洁
#include "loggerFiles/easylogging++.cc"

INITIALIZE_EASYLOGGINGPP//安装log
```

# 配置

## 方法一
.cc文件中，配置`kDefaultLogFile`项，可配置生成log文件路径及文件名，将其改为：`log_%datetime`(格式为：%Y%M%d），可实现日志按日期且设置最大值进行滚动记录

## 方法二（推荐）

也可以不直接修改cc文件，在项目源代码中修改参数：

```cpp
#include <QtWidgets/QApplication>
#define ELPP_NO_DEFAULT_LOG_FILE//此处定义宏，一定要在include之前，否则引入即失效
#include "loggerFiles/easylogging++.h"
#include "loggerFiles/easylogging++.cc"

INITIALIZE_EASYLOGGINGPP
//#define DELPP_NO_DEFAULT_LOG_FILE//此处定义宏无效

int main(int argc, char *argv[])
{

    el::Configurations conf("D:/myDevelop/happyLogging/loggerFiles/myLog.conf");
    //注意，此处同el::Configurations conf;只不过多了conf对象的具体指向地址
    conf.setToDefault();
    //需确保default的conf文件不被修改（上一步会涉及到修改）
    conf.setGlobally(el::ConfigurationType::Filename, "D:/myDevelop/logs/log_%datetime.log");
    conf.setGlobally(el::ConfigurationType::Enabled, "true");
    conf.setGlobally(el::ConfigurationType::ToFile, "true");
    conf.setGlobally(el::ConfigurationType::Format, "%datetime | %level | %line | %loc | %msg");
    //此处不能阻止项目文件夹生成myeasylog.log生成
    //可在工程中添加宏:ELPP_NO_DEFAULT_LOG_FILE
    //CMakelists.txt中:add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)
    //最终生成“log_2021-10-19_14-23.log”格式文件
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");




    LOG(ERROR) << "-----error log";
    LOG(WARNING) << "------warning log";
    LOG(INFO) << "------info log";
    LOG(TRACE) << "------trace log";
    LOG(DEBUG) << "------debug log";

    QApplication a(argc, argv);
    logger w;
    w.show();
    VLOG(3) << "Test verbose";
    system("pause");
    return a.exec();
}

```