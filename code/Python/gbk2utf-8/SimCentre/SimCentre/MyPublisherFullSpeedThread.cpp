#include "MyPublisherFullSpeedThread.h"
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

using namespace std::chrono;
MyPublisherFullSpeedThread::MyPublisherFullSpeedThread(QObject *parent)
{
	m_stop = false;
	m_pause = false;
	m_first_flag = true;
	destination = "";
	nsize = 0;
	samples = 10;
	m_historymap = new MapSet;
	thread = new QThread;
	this->moveToThread(thread);
	connect(thread, SIGNAL(started()), this, SLOT(slotsimPublisher()));
	connect(thread, SIGNAL(finished()), this, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	totalsamples = 0;
	thread->start();
}
MyPublisherFullSpeedThread::~MyPublisherFullSpeedThread()
{
	thread->quit();
	thread->wait();
}

void MyPublisherFullSpeedThread::slotsimPublisher()
{
	SimpleLog::instance()->writelogStartTime();
	while (!m_stop)
	{
		if (m_first_flag)
		{
			MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
			if (m_feedbackcorrun == nullptr) { continue; }
			auto mapset = m_feedbackcorrun->GetMapSet();
			nsize = mapset.size();
			for (auto iter = mapset.begin();
				iter != mapset.end(); iter++)
			{
				destination += iter->first.c_str();
				m_historymap->SetMapData(iter->first, iter->second.c_str());
			}
			m_feedbackcorrun->unLockMapData();
			m_first_flag = false;
			continue;
		}
		if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1) { continue;}
		if (m_pause) { continue; }
		g_mutex.lock();
		//MapSet * m_feedbackstep = MIddleByValueSet::instance()->getfeedbacknodestepmap();//反馈步长回令
		MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
		//if (m_feedbackstep == nullptr) { continue; }
		if (m_feedbackcorrun == nullptr) { continue; }
		//int nsize = m_feedbackstep->GetMapSet().size();
		//m_feedbackstep->unLockMapData();
		if (m_feedbackcorrun->GetMapSet().size() == nsize)
		{//全部反馈
			m_feedbackcorrun->unLockMapData();
			if (ishistory(nsize))
			{
				SimMessageDDs simdds;
				{
					QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);
					simdds.dest = destination;
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
				}
				SimDDS::instance()->SimDDSPubPublisher(simdds);
				TerminalPubPublisherOutput(simdds);
			}
			g_mutex.unlock();
			continue;
		}
		m_feedbackcorrun->unLockMapData();
		g_mutex.unlock();
	}
	//QThread::msleep(10);
}

void MyPublisherFullSpeedThread::slotsimPause()
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

void MyPublisherFullSpeedThread::slotsimGoOn()
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

void MyPublisherFullSpeedThread::slotsimQuit()
{
	m_stop = true;//停止
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_END", simdds);
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
	SimpleLog::instance()->wrtielogEndTime();
}

bool MyPublisherFullSpeedThread::ishistory(int num)
{
	int index = 0;
	MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
	auto mapset = m_feedbackcorrun->GetMapSet();
	for (auto iter = mapset.begin();
		iter != mapset.end(); iter++)
	{
		if (m_historymap->GetMapData(iter->first) == iter->second)
		{
			continue;
		}
		else
		{
			index++;
		}
	}
	if (index == num)
	{
		auto iter = mapset.begin();
		for (; iter != mapset.end(); ++iter)
		{
			m_historymap->SetMapData(iter->first, iter->second.c_str());	
		}

		m_feedbackcorrun->unLockMapData();
		return true;
	}
	m_feedbackcorrun->unLockMapData();
	return false;
}