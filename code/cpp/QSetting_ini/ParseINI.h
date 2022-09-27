#ifndef C_PARSE_INI_FILE_H_
#define C_PARSE_INI_FILE_H_

#include "stable.h"


class ParseINI
{
public:
    ParseINI();
    explicit ParseINI(const QString _filePathStr);
    ~ParseINI();

public:
    QString IniRead(const QString session, const QString key);  //读
    QStringList IniReadAllKeys(const QString group);        //读取指定结点下的所有键
    QStringList IniReadAllGroups();        //读取所有结点
    void IniWrite(const QString session, const QString key, const QString value); //写
    void setIniPath(const QString _filePathStr);   //修改ini文件读取写入的路径

    void IniClear();
private:
    QSettings* settings = nullptr;      //settings对象
    QString iniKeyAndSessionTemplate = "%1/%2"; //key和session的模板
};

#endif
