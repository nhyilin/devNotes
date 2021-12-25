#include "MyPublisherRealTimerTest.h"
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
#include "RealDataDealTimer.h"
#include "MapSet.h"
#include <QFile>
#include <QTextStream>

using namespace std::chrono;
MyPublisherRealTimerTest::MyPublisherRealTimerTest(QObject* parent)
	:m_pause(false)
	, nTimeStep(0)
	, index(0)
	, eventtimer(new QTimer)
	, m_currentframemap(new MapSet)
	, samples(10)
{
	QString timepre = "";
	QtSettingSet::instance()->readConfig("TIME_OPTIMIZATION", "centertimepre", timepre);
	nTimepre = timepre.toInt();
	nTimeStep = MIddleByValueSet::instance()->getpublishertime() ;
	MIddleByValueSet::instance()->setMyPublisherRealTimeTest(this);
	m_realdatadealtimer = new RealDataDealTimer(eventtimer,m_currentframemap);
	slotsimPublisher();
}
MyPublisherRealTimerTest::~MyPublisherRealTimerTest()
{
}

void MyPublisherRealTimerTest::slotsimPublisher()
{
	this->connect(eventtimer, SIGNAL(timeout()),this,SLOT(slotstimeEvent()));
	eventtimer->setTimerType(Qt::PreciseTimer);
	eventtimer->setInterval(nTimeStep - nTimepre);
	eventtimer->start();
	SimpleLog::instance()->writelogStartTime();
}


void MyPublisherRealTimerTest::slotstimeEvent()
{
	//SimpleLog::instance()->writelogStartTime();
	if (m_pause) { m_realdatadealtimer->setpause(true); return; }
	if (!m_realdatadealtimer->getdatadealcomplete()) { return; }
	int elapsed = nTimeStep * ++index;
	m_realdatadealtimer->settimer(elapsed);
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
	m_realdatadealtimer->setdatadealcomplete(false);
	m_realdatadealtimer->setpause(false);
	g_mutex_send.unlock();
	//SimpleLog::instance()->wrtielogEndTime();
	return;
}

void MyPublisherRealTimerTest::slotsimPause()
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

void MyPublisherRealTimerTest::slotsimGoOn()
{
	m_pause = false;
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_CONTINUE", simdds);
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

void MyPublisherRealTimerTest::slotsimQuit()
{
	eventtimer->stop();
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

void MyPublisherRealTimerTest::slotTimeStart()
{
	if (!eventtimer->isActive())
	{
		eventtimer->start(nTimeStep - nTimepre);
	}
}

void MyPublisherRealTimerTest::slotTimeStop()
{
	if (eventtimer->isActive())
	{
		eventtimer->stop();
	}
}