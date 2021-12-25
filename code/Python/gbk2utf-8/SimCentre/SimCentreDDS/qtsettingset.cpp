#include "qtsettingset.h"
#include <QApplication>
#include <QSettings>
#include <QVariant>

QtSettingSet* QtSettingSet::m_pInstance = nullptr;
QtSettingSet::QtSettingSet(QObject *parent)
	: QObject(parent)
{
	QString strPath = QApplication::applicationDirPath();
	settings = new QSettings(strPath + "/config.ini",QSettings::IniFormat);
	settings->setIniCodec("UTF-8");
}

QtSettingSet::~QtSettingSet()
{
}

QtSettingSet* QtSettingSet::instance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new QtSettingSet();
	}
	return m_pInstance;
}

void QtSettingSet::destroy()
{
	if (nullptr != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void QtSettingSet::readConfig(QString group, SimMessageDDs& dds)
{
	settings->beginGroup(group);
	dds.tastID = settings->value("tastID").toString().toLocal8Bit();
	dds.src = settings->value("src").toString().toLocal8Bit();
	dds.dest = settings->value("dest").toString().toLocal8Bit();
	dds.type = settings->value("type").toString().toLocal8Bit();
	settings->endGroup();
}

void QtSettingSet::writeConfig(QString group, SimMessageDDs dds)
{
	settings->beginGroup(group);
	settings->setValue("tastID",QString::fromLocal8Bit(dds.tastID.c_str()));
	settings->setValue("src", QString::fromLocal8Bit(dds.src.c_str()));
	settings->setValue("dest",QString::fromLocal8Bit(dds.dest.c_str()));
	settings->setValue("type",QString::fromLocal8Bit(dds.type.c_str()));
	settings->endGroup();
}

void QtSettingSet::writeConfig(QString group, QString key, QString value)
{
	settings->beginGroup(group);
	settings->setValue(key,value);
	settings->endGroup();
}

void QtSettingSet::readConfig(QString group, QString key, QString& value)
{
	settings->beginGroup(group);
	value = settings->value(key).toString().toLocal8Bit();
	settings->endGroup();
}