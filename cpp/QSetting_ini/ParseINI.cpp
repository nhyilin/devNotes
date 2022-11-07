#include "ParseINI.h"
#include "InitLog.h"
#if defined(_MSC_VER)&&(_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif
ParseINI::ParseINI()
{
    //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
    QString InitFile = QCoreApplication::applicationDirPath() + "./TZSatelliteSimTool.ini";//TODO:后期可以放在预编译头文件中
    settings = new QSettings(InitFile, QSettings::IniFormat);
	settings->setIniCodec("utf-8");
}

ParseINI::ParseINI(QString _filePathStr)
{
    settings = new QSettings(_filePathStr, QSettings::IniFormat);
	settings->setIniCodec("utf-8");
}

ParseINI::~ParseINI()
{
    delete  settings;
}
QString ParseINI::IniRead(const QString session, const QString key)
{
    QString KAS = QString(iniKeyAndSessionTemplate).arg(session).arg(key);
    QString result = settings->value(KAS).toString();
    return result;
}


QStringList ParseINI::IniReadAllKeys(const QString group) {
    QStringList result;
    settings->beginGroup(group);
    result = settings->childKeys();
    settings->endGroup();
    return  result;
}

QStringList ParseINI::IniReadAllGroups()
{
    return  settings->childGroups();
}


void ParseINI::IniWrite(const QString session, const QString key, const QString value)
{
    QString  KAS = QString(iniKeyAndSessionTemplate).arg(session).arg(key);
    qDebug() << "KAS=" << KAS;
    settings->setValue(KAS, value);
}

void ParseINI::setIniPath(const QString _filePathStr)
{
    if (settings != nullptr) {
        delete settings;
        qDebug() << "删除了settings对象";
    }
    settings = new QSettings(_filePathStr, QSettings::IniFormat);
}

void ParseINI::IniClear()
{
    settings->clear();
}
