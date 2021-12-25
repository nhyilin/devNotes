#include "MyPublisherRealTimerTestTwo.h"
#include "SimMessageDDs.h"
#include "simdds.h"
#include "MiddleByValueSet.h"
#include <QTimer>
#include <QEvent>
#include "qtsettingset.h"
#include "qttestout.hpp"
#include <QApplication>
#include "simplelog.h"
#include "SimDataAnalysis.h"
#include "RealDataDealTimerTwo.h"
#include "MapSet.h"
#include <QFile>
#include <QTextStream>

using namespace std::chrono;
MyPublisherRealTimerTestTwo::MyPublisherRealTimerTestTwo(QObject *parent)
	:m_pause(false)
	,nTimeStep(0)
	,index(3)
	,m_currentframemap(new MapSet)
	,m_realdatadealtimertwo(new RealDataDealTimerTwo)
	,samples(10)
{
	QString timepre = "";
	QtSettingSet::instance()->readConfig("TIME_OPTIMIZATION", "centertimepre", timepre);
	nTimepre = timepre.toInt();
	nTimeStep = MIddleByValueSet::instance()->getpublishertime() - nTimepre;
	slotsimPublisher();
}
MyPublisherRealTimerTestTwo::~MyPublisherRealTimerTestTwo()
{
}

void MyPublisherRealTimerTestTwo::slotsimPublisher()
{
	m_realdatadealtimertwo->setcurrentmap(m_currentframemap);
	eventtimeID = startTimer(nTimeStep,Qt::PreciseTimer);
	SimpleLog::instance()->writelogStartTime();
}


void MyPublisherRealTimerTestTwo::timerEvent(QTimerEvent *event)
{
	eventtimeID = event->timerId();
	SimpleLog::instance()->writelogStartTime();
	if (m_pause) { m_realdatadealtimertwo->setpause(true); return; }
	if (!m_realdatadealtimertwo->getdatadealcomplete()) { return; }
	int elapsed = nTimeStep * index++;
	//m_realdatadealtimer->settimer(2);
	g_mutex_send.lock();
	auto mapset = m_currentframemap->GetMapSet();
	std::string dest = "";
	for (auto iter = mapset.begin(); iter != mapset.end(); iter++)
	{
		dest += iter->first;
	}
	//int nstepnum =
	//QString::fromLocal8Bit(m_framemap->GetMapData(iter->first).c_str()).toInt();
	SimMessageDDs simdds;
	{
		QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);
		simdds.dest = dest;
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = samples++;
		//拼接数据 step + steptime + count;
		std::string step = QString::number(
			MIddleByValueSet::instance()->getpublishertime()).toStdString();
		for (int j = 0; j < step.length(); j++)
		{
			simdds.data.push_back(step[j]);
		}
		simdds.data.push_back('-');
		//stepnum 
		//std::string stepnum = QString::number(nstepnum).toStdString();
		//for (int n = 0; n < stepnum.length(); n++)
		//{
		//	simdds.data.push_back(stepnum[n]);
		//}
		//simdds.data.push_back('-');
		//nstepnum++;
		//m_framemap->SetMapData(iter->first, QString::number(nstepnum).toStdString());
		//count;
		std::string num = QString::number(simdds.count).toStdString();
		for (int k = 0; k < num.length(); k++)
		{
			simdds.data.push_back(num[k]);
		}

		SimDDS::instance()->SimDDSPubPublisher(simdds);
		TerminalPubPublisherOutput(simdds);
	}
	m_currentframemap->unLockMapData();
	m_realdatadealtimertwo->setdatadealcomplete(false);
	//m_realdatadealtimer->setpause(false);
	g_mutex_send.unlock();
	SimpleLog::instance()->wrtielogEndTime();
	return;
}

void MyPublisherRealTimerTestTwo::slotsimPause()
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

void MyPublisherRealTimerTestTwo::slotsimGoOn()
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

void MyPublisherRealTimerTestTwo::slotsimQuit()
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