#include "RealDataDealTimerTwo.h"
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
#include "MapSet.h"
#include <QFile>
#include <QTimer>
#include <QTextStream>

using namespace std::chrono;
RealDataDealTimerTwo::RealDataDealTimerTwo(QObject *parent)
	:m_pause(false)
	,dealcomplete(false)
	,currentframe(false)
	,m_stop(false)
	,m_first_flag(true)
	,index(0)
	, m_elapsed(2)
	,indexstep(0)
	,m_historymap(new MapSet)
	, m_nextframemap(new MapSet)
	,m_currentframemap(nullptr)
	,thread(new QThread)
{
	this->moveToThread(thread);
	nTimeStep = MIddleByValueSet::instance()->getpublishertime();
	slotsimPublisher();
}
RealDataDealTimerTwo::~RealDataDealTimerTwo()
{
}

void RealDataDealTimerTwo::settimer(int timer)
{
	m_elapsed = timer;
}

void RealDataDealTimerTwo::setcurrentmap(MapSet* mapset)
{
	m_currentframemap = mapset;
}

bool RealDataDealTimerTwo::getpause()
{
	return m_pause;
}

void RealDataDealTimerTwo::setpause(bool sleep)
{
	m_pause = sleep;
}

bool RealDataDealTimerTwo::getdatadealcomplete()
{
	return dealcomplete;
}

void RealDataDealTimerTwo::setdatadealcomplete(bool deal)
{
	dealcomplete = deal;
}

void RealDataDealTimerTwo::slotsimPublisher()
{
	connect(thread, SIGNAL(started()), this, SLOT(updateEventDeal()));
	thread->start();
}

void RealDataDealTimerTwo::updateEventDeal()
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
			}
			m_feedbackcorrun->unLockMapData();
			m_first_flag = false;
			continue;
		}
		if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1) { continue; }
		if (m_pause) { continue; }
		g_mutex.lock();
		int elapsed = nTimeStep * index;
		//int elapsed = m_elapsed;
		auto mapset = m_historymap->GetMapSet();
		m_nextframemap->Clean();
		for (auto iter = mapset.begin(); iter != mapset.end(); iter++)
		{
			QString valuehistory = QString::fromLocal8Bit(iter->second.c_str());
			QStringList valuehistorylist = valuehistory.split('-');
			if (elapsed % valuehistorylist[0].toInt() == 0)
			{
				m_nextframemap->SetMapData(iter->first, iter->second);
				currentframe = true;
			}
		}
		if (!currentframe)
		{
			dealcomplete = true;
			index = m_elapsed;
		}
		m_historymap->unLockMapData();
		if (ishistory())
		{
			dealcomplete = true;
			m_pause = false;
			index++;
		}
		g_mutex.unlock();
	}
}

bool RealDataDealTimerTwo::ishistory()
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
			if (m_nextframemap->GetMapData(iter->first) != "")
			{
				if (m_nextframemap->GetMapData(iter->first) == iter->second)
				{
					continue;
				}
				else
				{
					index++;
				}
			}
		}
		auto nextset = m_nextframemap->GetMapSet();
		if (index == nextset.size())
		{
			m_feedbackcorrun->unLockMapData();
			m_currentframemap->Clean();
			auto iter = nextset.begin();
			for (; iter != nextset.end(); ++iter)
			{
				m_historymap->SetMapData(iter->first,
					m_feedbackcorrun->GetMapData(iter->first));
				m_currentframemap->SetMapData(iter->first,
					m_feedbackcorrun->GetMapData(iter->first));
			}
			m_nextframemap->unLockMapData();
			currentframe = false;
			return true;
		}
		else
		{
			m_nextframemap->unLockMapData();
			m_feedbackcorrun->unLockMapData();
			m_pause = true;
		}
	}
}
void RealDataDealTimerTwo::slotsimPause()
{
	m_pause = true;
}

void RealDataDealTimerTwo::slotsimGoOn()
{
	m_pause = false;
}

void RealDataDealTimerTwo::slotsimQuit()
{
	m_stop = true;
}