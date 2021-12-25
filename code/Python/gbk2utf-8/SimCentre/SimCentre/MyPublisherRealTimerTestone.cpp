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
#include "MapSet.h"
#include <QFile>
#include <QTextStream>

using namespace std::chrono;
MyPublisherRealTimerTest::MyPublisherRealTimerTest(QObject *parent)
	:m_pause(false)
	,currentframe(false)
	,m_first_flag(true)
	,index (0)
	,m_historymap(new MapSet)
	,m_framemap(new MapSet)
	, m_currentframemap(new MapSet)
	,samples(10)
	,framesamples(0)
	,timerevent(new QTimer)
{
	connect(timerevent, SIGNAL(timeout()), this, SLOT(updateEvent()));
	nTimeStep = MIddleByValueSet::instance()->getpublishertime();
	slotsimPublisher();
}
MyPublisherRealTimerTest::~MyPublisherRealTimerTest()
{
}

void MyPublisherRealTimerTest::slotsimPublisher()
{
	timerevent->start(nTimeStep);
	timerevent->setTimerType(Qt::PreciseTimer);
	SimpleLog::instance()->writelogStartTime();
}

void MyPublisherRealTimerTest::updateEvent()
{
	if (m_first_flag)
	{
		MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
		if (m_feedbackcorrun == nullptr) { return; }
		auto mapset = m_feedbackcorrun->GetMapSet();
		for (auto iter = mapset.begin();
			iter != mapset.end(); iter++)
		{
			m_historymap->SetMapData(iter->first, iter->second.c_str());
			m_framemap->SetMapData(iter->first, "0");
		}
		m_feedbackcorrun->unLockMapData();
		m_first_flag = false;
		return;
	}
	//SimpleLog::instance()->writelogStartTime();
	if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1) { return; }
	if (m_pause) { return; }
	g_mutex.lock();
	int elapsed = MIddleByValueSet::instance()->getpublishertime() * index++;

	while (true)
	{
		int index = 0;
		MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
		if (m_feedbackcorrun == nullptr) { return; }
		auto mapset = m_feedbackcorrun->GetMapSet();
		for (auto iter = mapset.begin();
			iter != mapset.end(); iter++)
		{
			QString valuehistory = QString::fromLocal8Bit(iter->second.c_str());
			QStringList valuehistorylist = valuehistory.split('-');
			if (elapsed % valuehistorylist[0].toInt() == 0)
			{
				if (m_historymap->GetMapData(iter->first) == iter->second)
				{
					continue;
				}
				else
				{
					index++;
					m_historymap->SetMapData(iter->first, iter->second.c_str());
					m_currentframemap->SetMapData(iter->first, iter->second.c_str());
				}
			}
		}
		auto currentset = m_currentframemap->GetMapSet();
		if (index == currentset.size())
		{
			m_feedbackcorrun->unLockMapData();
			m_currentframemap->unLockMapData();
			break;
		}
		else
		{
			m_feedbackcorrun->unLockMapData();

			timerevent->stop();
		}
	}

	auto mapset = m_currentframemap->GetMapSet();
	for (auto iter = mapset.begin(); iter != mapset.end(); iter++)
	{
		int nstepnum =
			QString::fromLocal8Bit(m_framemap->GetMapData(iter->first).c_str()).toInt();
		SimMessageDDs simdds;
		{
			QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);
			simdds.dest = iter->first;
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
			std::string stepnum = QString::number(nstepnum).toStdString();
			for (int n = 0; n < stepnum.length(); n++)
			{
				simdds.data.push_back(stepnum[n]);
			}
			simdds.data.push_back('-');
			nstepnum++;
			m_framemap->SetMapData(iter->first, QString::number(nstepnum).toStdString());
			//count;
			std::string num = QString::number(simdds.count).toStdString();
			for (int k = 0; k < num.length(); k++)
			{
				simdds.data.push_back(num[k]);
			}
		}

		SimDDS::instance()->SimDDSPubPublisher(simdds);
		TerminalPubPublisherOutput(simdds);
	}
	m_currentframemap->unLockMapData();
	m_currentframemap->Clean();
	if (!timerevent->isActive())
	{
		timerevent->start(nTimeStep);
	}
	g_mutex.unlock();
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
	for (int j = 0;j< step.length();j++)
	{
		simdds.data.push_back(step[j]);
	}
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	TerminalPubPublisherOutput(simdds);
}

void MyPublisherRealTimerTest::slotsimQuit()
{
	//killTimer(eventtimeID);//停止
	timerevent->stop();
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

bool MyPublisherRealTimerTest::ishistory()
{
	if (currentframe == false) { return false; }
	int index = 0;
	MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
	auto mapset = m_feedbackcorrun->GetMapSet();
	for (auto iter = mapset.begin();
		iter != mapset.end(); iter++)
	{
			if (m_currentframemap->GetMapData(iter->first) != "")
			{
				if (m_currentframemap->GetMapData(iter->first) == iter->second)
				{
					continue;
				}
				else
				{
					index++;
				}
			}
	}
	auto currentset = m_currentframemap->GetMapSet();
	if (index == currentset.size())
	{
		m_historymap->unLockMapData();
		m_feedbackcorrun->unLockMapData();
		auto iter = currentset.begin();
		for (; iter != currentset.end(); ++iter)
		{
			m_historymap->SetMapData(iter->first,
			m_feedbackcorrun->GetMapData(iter->first));
		}
		m_currentframemap->unLockMapData();
		currentframe = false;
		return true;
	}
	m_currentframemap->unLockMapData();
	m_feedbackcorrun->unLockMapData();
	currentframe = false;
	return false;
}


bool MyPublisherRealTimerTest::ishistorytest()
{	
	if (currentframe == false) { return false; }
	while (true)
	{
		int index = 0;
		MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
		auto mapset = m_feedbackcorrun->GetMapSet();
		for (auto iter = mapset.begin();
			iter != mapset.end(); iter++)
		{
			if (m_currentframemap->GetMapData(iter->first) != "")
			{
				if (m_currentframemap->GetMapData(iter->first) == iter->second)
				{
					continue;
				}
				else
				{
					index++;
				}
			}
		}
		auto currentset = m_currentframemap->GetMapSet();
		if (index == currentset.size())
		{
			m_historymap->unLockMapData();
			m_feedbackcorrun->unLockMapData();
			auto iter = currentset.begin();
			for (; iter != currentset.end(); ++iter)
			{
				m_historymap->SetMapData(iter->first,
				m_feedbackcorrun->GetMapData(iter->first));
			}
			m_currentframemap->unLockMapData();
			currentframe = false;
			return true;
		}
		else
		{
			m_currentframemap->unLockMapData();
			m_feedbackcorrun->unLockMapData();
			timerevent->stop();
		}
	}
}