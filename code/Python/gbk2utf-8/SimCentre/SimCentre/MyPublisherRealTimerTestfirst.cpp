#include "MyPublisherRealTimerTestfirst.h"
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
#include "feedbackcorrunArrayTimer.h"
#include "MapSet.h"
#include <QFile>
#include <QTextStream>

using namespace std::chrono;
MyPublisherRealTimerTestfirst::MyPublisherRealTimerTestfirst(QObject* parent)
	:m_pause(false)
	, currentframe(false)
	, m_first_flag(true)
	, index(0)
	, m_historymap(new MapSet)
	//, m_framemap(new MapSet)
	, m_currentframemap(new MapSet)
	, samples(10)
	, framesamples(0)
	, timerevent(new QTimer)
{
	QString timepre = "";
	QtSettingSet::instance()->readConfig("TIME_OPTIMIZATION", "centertimepre", timepre);
	nTimepre = timepre.toInt();
	nTimeStep = MIddleByValueSet::instance()->getpublishertime();
	this->connect(timerevent, SIGNAL(timeout()), this, SLOT(updateEvent()));
	slotsimPublisher();
}
MyPublisherRealTimerTestfirst::~MyPublisherRealTimerTestfirst()
{
}

void MyPublisherRealTimerTestfirst::slotsimPublisher()
{
	eventtimeID = timerevent->timerId();
	timerevent->start(nTimeStep - nTimepre);
	timerevent->setTimerType(Qt::PreciseTimer);
	SimpleLog::instance()->writelogStartTime();
}

void MyPublisherRealTimerTestfirst::updateEvent()
{
	//if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1) { return; }
	if (m_pause) { return; }
	int elapsed = MIddleByValueSet::instance()->getpublishertime() * index++;

	FeedBackcorrunArrayTimer::src2Step;
	auto iter = FeedBackcorrunArrayTimer::src2Step.begin();
	for (;iter != FeedBackcorrunArrayTimer::src2Step.end(); iter++)
	{
		 QString value = QString::fromLocal8Bit(iter->second.c_str());
		if (elapsed %  value.toInt() == 0)
		{
			FeedBackcorrunArrayTimer::sendBufferTemp = FeedBackcorrunArrayTimer::src2TempMask[iter->first];
			FeedBackcorrunArrayTimer::currentsendBufferTemp |= FeedBackcorrunArrayTimer::sendBufferTemp;
		}
	}
	while (true)
	{
		if ((FeedBackcorrunArrayTimer::receiveBuffer & FeedBackcorrunArrayTimer::currentsendBufferTemp) !=
			FeedBackcorrunArrayTimer::currentsendBufferTemp)
		{
			continue;
			timerevent->stop();
		}
		else
		{
			break;
		}
	}


	SimMessageDDs simdds;
	{
		QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);
		std::string destination;
		for (int i = 0; i < MAX_NUDE_COUNT; i++)
		{
			if ((FeedBackcorrunArrayTimer::index2number[i] & FeedBackcorrunArrayTimer::currentsendBufferTemp) ==
				FeedBackcorrunArrayTimer::index2number[i])// 为true 则该节点发送消息
			{
				destination += FeedBackcorrunArrayTimer::index2str[i];
			}
		}
		simdds.dest = destination;
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = samples++;
		simdds.data.push_back((unsigned char)FeedBackcorrunArrayTimer::currentsendBufferTemp);//低8位
		simdds.data.push_back((unsigned char)(FeedBackcorrunArrayTimer::currentsendBufferTemp >> 8));//高8位
	}
	FeedBackcorrunArrayTimer::clear();
	if (!timerevent->isActive())
	{
		timerevent->start(nTimeStep - nTimepre);
	}
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	TerminalPubPublisherOutput(simdds);
}

//void MyPublisherRealTimerTestfirst::updateEvent()
//{
//	if (m_first_flag)
//	{
//		MapSet* m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
//		if (m_feedbackcorrun == nullptr) { return; }
//		auto mapset = m_feedbackcorrun->GetMapSet();
//		for (auto iter = mapset.begin();
//			iter != mapset.end(); iter++)
//		{
//			m_historymap->SetMapData(iter->first, iter->second.c_str());
//			//m_framemap->SetMapData(iter->first, "0");
//		}
//		m_feedbackcorrun->unLockMapData();
//		m_first_flag = false;
//		return;
//	}
//	if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1) { return; }
//	if (m_pause) { return; }
//	g_mutex.lock();
//	//MapSet * m_feedbackstep = MIddleByValueSet::instance()->getfeedbacknodestepmap();//反馈步长回令
//	//MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
//	//if (m_feedbackstep == nullptr) { return; }
//	//if (m_feedbackcorrun == nullptr) { return; }
//	int elapsed = MIddleByValueSet::instance()->getpublishertime() * index++;
//	auto mapset = m_historymap->GetMapSet();
//	for (auto iter = mapset.begin(); iter != mapset.end(); iter++)
//	{
//		QString valuehistory = QString::fromLocal8Bit(iter->second.c_str());
//		QStringList valuehistorylist = valuehistory.split('-');
//		if (elapsed % valuehistorylist[0].toInt() == 0)
//		{
//			m_currentframemap->SetMapData(iter->first, iter->second);
//			currentframe = true;
//		}
//	}
//	if (ishistorytest())
//	{
//		auto mapset = m_currentframemap->GetMapSet();
//		std::string dest = "";
//		for (auto iter = mapset.begin(); iter != mapset.end(); iter++)
//		{
//			dest += iter->first;
//		}
//		SimMessageDDs simdds;
//		{
//			QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);
//			simdds.dest = dest;
//			simdds.time = currentDataTime().toLocal8Bit();
//			simdds.count = samples++;
//			//拼接数据 src + ,+ step + count;
//			for (int i = 0; i < simdds.src.length(); i++)
//			{
//				simdds.data.push_back(simdds.src[i]);
//			}
//			simdds.data.push_back(',');
//
//			std::string step = QString::number(
//				MIddleByValueSet::instance()->getpublishertime()).toStdString();
//			for (int j = 0; j < step.length(); j++)
//			{
//				simdds.data.push_back(step[j]);
//			}
//			simdds.data.push_back('-');
//			//count;
//			std::string num = QString::number(simdds.count).toStdString();
//			for (int k = 0; k < num.length(); k++)
//			{
//				simdds.data.push_back(num[k]);
//			}
//		}
//
//		SimDDS::instance()->SimDDSPubPublisher(simdds);
//		TerminalPubPublisherOutput(simdds);
//	}
//	m_currentframemap->unLockMapData();
//	m_historymap->LockMapData();
//	m_currentframemap->Clean();
//	if (!timerevent->isActive())
//	{
//		timerevent->start(MIddleByValueSet::instance()->getpublishertime());
//	}
//	m_historymap->unLockMapData();
//	g_mutex.unlock();
//	return;
//}

void MyPublisherRealTimerTestfirst::slotsimPause()
{
	m_pause = true;
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_PAUSE", simdds);
	simdds.time = currentDataTime().toLocal8Bit();
	simdds.count = samples++;
	//拼接数据 src + ,+ step;
	for (int i = 0; i < simdds.src.length(); i++)
	{
		simdds.data.push_back(simdds.src[i]);
	}
	simdds.data.push_back(',');
	std::string step = QString::number(
		MIddleByValueSet::instance()->getpublishertime()).toStdString();
	for (int j = 0; j < step.length(); j++)
	{
		simdds.data.push_back(step[j]);
	}
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	TerminalPubPublisherOutput(simdds);
}

void MyPublisherRealTimerTestfirst::slotsimGoOn()
{
	m_pause = false;
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_CONTINUE", simdds);
	simdds.time = currentDataTime().toLocal8Bit();
	simdds.count = samples++;
	//拼接数据 src + ,+ step;
	for (int i = 0; i < simdds.src.length(); i++)
	{
		simdds.data.push_back(simdds.src[i]);
	}
	simdds.data.push_back(',');
	std::string step = QString::number(
		MIddleByValueSet::instance()->getpublishertime()).toStdString();
	for (int j = 0; j < step.length(); j++)
	{
		simdds.data.push_back(step[j]);
	}
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	TerminalPubPublisherOutput(simdds);
}

void MyPublisherRealTimerTestfirst::slotsimQuit()
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


bool MyPublisherRealTimerTestfirst::ishistorytest()
{
	if (currentframe == false) { return false; }
	while (true)
	{
		int index = 0;
		MapSet* m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
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