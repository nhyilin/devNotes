#include "MyPublisherTimer.h"
#include "SimMessageDDs.h"
#include "simdds.h"
#include "MiddleByValueSet.h"
#include <QTime>
#include <QEvent>
#include "qtsettingset.h"
#include "qttestout.hpp"
#include <QApplication>
#include "simplelog.h"
#include "SimDataAnalysis.h"
#include <QFile>
#include <QTextStream>

using namespace std::chrono;
MyPublisherTimer::MyPublisherTimer(QObject *parent)
{
	m_pause = false;
	samples = 0;
	totalsamples = 0;
	slotsimPublisher();
}
MyPublisherTimer::~MyPublisherTimer()
{
}

void MyPublisherTimer::slotsimPublisher()
{
	startTimer(MIddleByValueSet::instance()->getpublishertime(),Qt::PreciseTimer);
	totalsamples = MIddleByValueSet::instance()->getpublishernum();
	startTime = QTime::currentTime();
	SimpleLog::instance()->writelogStartTime();
}

void MyPublisherTimer::timerEvent(QTimerEvent *event)
{
	if (totalsamples == 0)
	{
		eventtimeID = event->timerId();
		if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1){ return;}
		if (m_pause) { return;}
		g_mutex.lock();
		SimMessageDDs simdds;
		QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = samples++;
		//拼接数据 step + stepnum + count;
		std::string step = QString::number(
			MIddleByValueSet::instance()->getpublishertime()).toStdString();
		for (int j = 0; j < step.length(); j++)
		{
			simdds.data.push_back(step[j]);
		}
		simdds.data.push_back('-');
		//count;
		std::string num = QString::number(simdds.count).toStdString();
		for (int k = 0; k < num.length(); k++)
		{
			simdds.data.push_back(num[k]);
		}
	
		SimDDS::instance()->SimDDSPubPublisher(simdds);
		TerminalPubPublisherOutput(simdds);
		g_mutex.unlock();
		QTime stoptime = QTime::currentTime();
		int elapsed = startTime.msecsTo(stoptime);
		if (elapsed / 1800000 == 1.0)
		{//半个小时保存一次
			QString strPath = QApplication::applicationDirPath();
			QFile file(strPath + "/log.txt");
			if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
				return;

			QTextStream out(&file);
			out << "The  number is: " << samples << "\n";
			startTime = QTime::currentTime();
		}
	} 
	else
	{
		eventtimeID = event->timerId();
		if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1) { return; }
		if (m_pause) { return;}
		g_mutex.lock();
		SimMessageDDs simdds;
		QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = samples++;
		//拼接数据 step + stepnum + count;
		std::string step = QString::number(
			MIddleByValueSet::instance()->getpublishertime()).toStdString();
		for (int j = 0; j < step.length(); j++)
		{
			simdds.data.push_back(step[j]);
		}
		SimDDS::instance()->SimDDSPubPublisher(simdds);
		TerminalPubPublisherOutput(simdds);
		g_mutex.unlock();
		QTime stoptime = QTime::currentTime();
		int elapsed = startTime.msecsTo(stoptime);
		if (--totalsamples == 0)
		{
			slotsimQuit();
		}
	}
}

void MyPublisherTimer::slotsimPause()
{
	m_pause = true;
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_PAUSE", simdds);
	simdds.time = currentDataTime().toLocal8Bit();
	simdds.count = samples++;
	//拼接数据 step + stepnum + count;
	std::string step = QString::number(
		MIddleByValueSet::instance()->getpublishertime()).toStdString();
	for (int j = 0; j < step.length(); j++)
	{
		simdds.data.push_back(step[j]);
	}
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	TerminalPubPublisherOutput(simdds);
}

void MyPublisherTimer::slotsimGoOn()
{
	m_pause = false;
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_CONTINUE", simdds);
	simdds.time = currentDataTime().toLocal8Bit();
	simdds.count = samples++;
	//拼接数据 step + stepnum + count;
	std::string step = QString::number(
		MIddleByValueSet::instance()->getpublishertime()).toStdString();
	for (int j = 0;j< step.length();j++)
	{
		simdds.data.push_back(step[j]);
	}
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	TerminalPubPublisherOutput(simdds);
}

void MyPublisherTimer::slotsimQuit()
{
	killTimer(eventtimeID);//停止
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_END", simdds);
	simdds.time = currentDataTime().toLocal8Bit();
	simdds.count = samples++;
	simdds.data.push_back('1');//10ms的步长
	simdds.data.push_back('0');
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	TerminalPubPublisherOutput(simdds);
	SimpleLog::instance()->wrtielogEndTime();
}