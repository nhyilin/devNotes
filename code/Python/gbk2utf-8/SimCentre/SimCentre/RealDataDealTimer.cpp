#include "RealDataDealTimer.h"
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
#include "MyPublisherRealTimerTest.h"
#include "MapSet.h"
#include <QFile>
#include <QTimer>
#include <QTextStream>

using namespace std::chrono;
RealDataDealTimer::RealDataDealTimer(QTimer * timer,
	MapSet* mapset,
	QObject* parent)
	:m_pause(false)
	,dealcomplete(false)
	,currentframe(false)
	,m_stop(false)
	,m_first_flag(true)
	,index(0)
	,m_elapsed(0)
	,m_timer(timer)
	,m_historymap(new MapSet)
	,m_framemap(new MapSet)
	,m_currentframemap(mapset)
	,thread(new QThread)
{
	this->moveToThread(thread);
	nTimeStep = MIddleByValueSet::instance()->getpublishertime();
	connect(this, SIGNAL(timeStart()), 
		MIddleByValueSet::instance()->getPublisherRealTimeTest()
		, SLOT(slotTimeStart()));
	connect(this, SIGNAL(timeStop()), 
		MIddleByValueSet::instance()->getPublisherRealTimeTest()
		, SLOT(slotTimeStop()));
	slotsimPublisher();
}
RealDataDealTimer::~RealDataDealTimer()
{
}

void RealDataDealTimer::settimer(int timer)
{
	m_elapsed = timer;
}

bool RealDataDealTimer::getpause()
{
	return m_pause;
}

void RealDataDealTimer::setpause(bool sleep)
{
	m_pause = sleep;
}

bool RealDataDealTimer::getdatadealcomplete()
{
	return dealcomplete;
}

void RealDataDealTimer::setdatadealcomplete(bool deal)
{
	dealcomplete = deal;
}

void RealDataDealTimer::slotsimPublisher()
{
	connect(thread, SIGNAL(started()), this, SLOT(updateEventDeal()));
	thread->start();
}

void RealDataDealTimer::updateEventDeal()
{
	while (!m_stop)
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
				//m_framemap->SetMapData(iter->first, "0");
			}
			m_feedbackcorrun->unLockMapData();
			m_first_flag = false;
			continue;
		}
		if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1) { continue; }
		if (m_pause) { continue; }
		//SimpleLog::instance()->writelogStartTime();
		g_mutex.lock();
		//int elapsed = nTimeStep * index++;
		int elapsed = m_elapsed;
		auto mapset = m_historymap->GetMapSet();
		m_currentframemap->Clean();

		for (auto iter = mapset.begin(); iter != mapset.end(); iter++)
		{
			QString valuehistory = QString::fromLocal8Bit(iter->second.c_str());
			QStringList valuehistorylist = valuehistory.split('-');
			if (elapsed % valuehistorylist[0].toInt() == 0)
			{
				m_currentframemap->SetMapData(iter->first, iter->second);
				currentframe = true;
			}
		}
		//if (!currentframe)
		//{
		//	dealcomplete = true;
		//}
		m_historymap->unLockMapData();
		if (ishistory())
		{
			dealcomplete = true;
			//emit timeStart();
			m_pause = true;
			//SimpleLog::instance()->wrtielogEndTime();
		}
		g_mutex.unlock();
	}
}

bool RealDataDealTimer::ishistory()
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
			m_pause = true;
			//emit timeStop();
		}
	}
}

void RealDataDealTimer::slotsimPause()
{
	m_pause = true;
}

void RealDataDealTimer::slotsimGoOn()
{
	m_pause = false;
}

void RealDataDealTimer::slotsimQuit()
{
	m_stop = true;
}