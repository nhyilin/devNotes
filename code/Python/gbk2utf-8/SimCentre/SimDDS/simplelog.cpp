#include "simplelog.h"
#include <QApplication>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QTime>
#include <QDateTime> 
#include <QDataStream>
#include "SimDataAnalysis.h"

SimpleLog* SimpleLog::m_pInstance = NULL;
SimpleLog::SimpleLog(QObject *parent)
	: QObject(parent)
{
}

SimpleLog::~SimpleLog()
{
}

void SimpleLog::writelog(SimMessageDDs simdds)
{
	static uint32_t sample = 0;
	int nCount = simdds.data.size();
	QString strPath = QApplication::applicationDirPath();
	QString filename = currentData() + "-logdds.txt";
	QFile file(strPath + "/" + filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
		return;
	QTextStream out(&file);
	out << "TastID" << QString::fromLocal8Bit(simdds.tastID.c_str()) << " "
		<< "src" << QString(simdds.src.c_str()) << " "
		<< "dest" << QString(simdds.dest.c_str()) << " "
		<< QString::fromLocal8Bit("发送时间")<< QString(simdds.time.c_str()) << " "
		<< QString::fromLocal8Bit("接收时间") << currentDataTime() << " "
		<< "type" << QString(simdds.type.c_str()) << " "
		<< "subtype" << QString(simdds.subtype.c_str()) << " "
		<< "count" << simdds.count << " "
		<< QString::fromLocal8Bit("接收的总数据量") << sample++ << " "
		<< QString::fromLocal8Bit("接收数据") << "\n\r";
	file.close();
}

void SimpleLog::writelogStartTime()
{
	QString strPath = QApplication::applicationDirPath();
	QString filename = currentData() + "-log.txt";
	QFile file(strPath + "/" + filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
		return;

	QTextStream out(&file);
		out << "The start time is: " << currentDataTime() << "\n";
		file.close();
}


void SimpleLog::wrtielogEndTime()
{
	QString strPath = QApplication::applicationDirPath();
	QString filename = currentData() + "-log.txt";
	QFile file(strPath + "/" + filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
		return;
	QTextStream out(&file);
		out << "The end time is: " << currentDataTime() << "\n";
		file.close();
}

QString SimpleLog::readlog()
{
	QString strPath = QApplication::applicationDirPath();
	QFile file(strPath + "/testData.txt");
	bool isok = file.open(QIODevice::ReadOnly);
	if (isok == true)
	{
		//读取文本文件
#if 1
		QByteArray array = file.readAll();
		return QString(array);
#else
		QDataStream stream(&file);
		stream.setVersion(QDataStream::Qt_5_9);
		QString str;
		for (int i = 0;i< 10;i++)
		{
			stream >> str;
			//stream >> str;
			//stream >> str;
			//stream >> str;
			//stream >> str;
			//stream >> str;
		}
		return str;
#endif
	}
	file.close();
}

void  SimpleLog::writelog()
{
	QString strPath = QApplication::applicationDirPath();
	QFile file(strPath + "/testData.txt");
	bool isok = file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	if (isok == true)
	{
		//读取文本文件
#if 0
		QByteArray array = file.readAll();
		return QString(array);
#else
		QDataStream stream(&file);
		stream.setVersion(QDataStream::Qt_5_9);

		for (int i = 0; i < 10; i++)
		{
			std::cout << " " << "反馈发送指令" << " " << std::endl;
			stream << QString("TastID");
			stream << QString("src");
			stream << QString("dest");
			stream << QString("type");
			stream << QString("subtype");
			stream << QString("count");
		}
#endif
	}
	file.close();
}
SimpleLog* SimpleLog::instance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new SimpleLog();
	}
	return m_pInstance;
}

void SimpleLog::destroy()
{
	if (nullptr != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}