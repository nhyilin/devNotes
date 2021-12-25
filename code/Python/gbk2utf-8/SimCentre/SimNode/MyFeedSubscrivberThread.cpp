#include "MyFeedSubscrivberThread.h"
#include "SimMessageDDs.h"
#include "simdds.h"
#include "MiddleByValueSet.h"
#include <QTime>
#include <QEvent>
#include "qtsettingset.h"
#include "qttestout.hpp"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator> 
#include <QDateTime>
#include "MapSet.h"
#include "SimDataAnalysis.h"
#include "simplelog.h"
#include <qtsettingset.h>

using namespace std::chrono;
MyFeedSubscriverThread::MyFeedSubscriverThread(QObject *parent)
	:m_stop(false)
	,m_pause(false)
	,nradom(false)
	,m_first_flag(true)
	,m_historymap(new MapSet)
	,thread(new QThread)
	,samples(10)
{
	this->moveToThread(thread);
	SimpleLog::instance()->writelogStartTime();
	QString radom = "";
	QtSettingSet::instance()->readConfig("TIME_OPTIMIZATION","nodetime",radom);
	nradom = radom.toInt();
	connect(thread, SIGNAL(started()), this, SLOT(slotsimPublisher()));
	connect(thread, SIGNAL(finished()), this, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	m_step = MIddleByValueSet::instance()->getsubscribersleep();
	thread->start();
}
MyFeedSubscriverThread::~MyFeedSubscriverThread()
{
	thread->quit();
	thread->wait();
}

void MyFeedSubscriverThread::slotsimPublisher()
{
	while (!m_stop)
	{
		if (m_first_flag)
		{
			MapSet * m_corbeginrun = MIddleByValueSet::instance()->getcorforwardrun();//协同推进
			if (m_corbeginrun == nullptr) { continue; }
			auto mapset = m_corbeginrun->GetMapSet();
			for (auto iter = mapset.begin();
				iter != mapset.end(); iter++)
			{
				m_historymap->SetMapData(iter->first, iter->second.c_str());
			}
			m_corbeginrun->unLockMapData();
			{
				SimMessageDDs simdds;
				{
					QtSettingSet::instance()->readConfig("FEEDBACK_COR_RUN", simdds);
					simdds.time = currentDataTime().toLocal8Bit();
					simdds.count = samples++;
					//拼接数据 +step - stepnum - count;
					std::string step = QString::number(m_step).toStdString();;
					for (int j = 0; j < step.length(); j++)
					{
						simdds.data.push_back(step[j]);
					}
					simdds.data.push_back('-');
					//step_num
					std::string stepnum = QString::number(simdds.count - 10).toStdString();
					for (int n = 0; n< stepnum.length();n++)
					{
						simdds.data.push_back(stepnum[n]);
					}
					simdds.data.push_back('-');
					//count;
					std::string num = QString::number(simdds.count).toStdString();
					for (int k = 0; k < num.length(); k++)
					{
						simdds.data.push_back(num[k]);
					}
				}
				SimDDS::instance()->SimDDSSubPublisher(simdds);
				TerminalPubPublisherOutput(simdds);
			}
			m_first_flag = false;
			continue;
		}
		//SimpleLog::instance()->writelogStartTime();
		if (SimDDS::instance()->SimDDSSubPublisherMatch() < 1) { continue; }
		if (m_pause) { continue; }
		g_mutex.lock();
		if (history())
		{
			SimMessageDDs simdds;
			{
				QtSettingSet::instance()->readConfig("FEEDBACK_COR_RUN", simdds);
				simdds.time = currentDataTime().toLocal8Bit();//发送当前时间
				simdds.count = samples++;
				//拼接数据 step + stepnum + count;
				std::string step = QString::number(m_step).toStdString();;
				for (int j = 0; j < step.length(); j++)
				{
					simdds.data.push_back(step[j]);
				}
				simdds.data.push_back('-');
				//stepnum
				std::string stepnum = QString::number(simdds.count - 10).toStdString();
				for (int n = 0; n < stepnum.length(); n++)
				{
					simdds.data.push_back(stepnum[n]);
				}
				simdds.data.push_back('-');
				//count;
				std::string num = QString::number(simdds.count).toStdString();
				for (int k = 0; k < num.length(); k++)
				{
					simdds.data.push_back(num[k]);
				}
			}
			SimDDS::instance()->SimDDSSubPublisher(simdds);
			TerminalPubPublisherOutput(simdds);

		}
		g_mutex.unlock();		
		//SimpleLog::instance()->wrtielogEndTime();
		if (nradom)
		{	
			QThread::msleep(generateRandomNumber());
		}
	}
}

void MyFeedSubscriverThread::slotsimPause()
{
	m_pause = true;
}

void MyFeedSubscriverThread::slotsimGoOn()
{
	m_pause = false;
}

void MyFeedSubscriverThread::slotsimQuit()
{
	m_stop = true;//停止
	SimpleLog::instance()->wrtielogEndTime();
}

bool MyFeedSubscriverThread::history()
{
	MapSet * m_corbeginrun = MIddleByValueSet::instance()->getcorbeginrun();//反馈推进回令
	if (m_corbeginrun == nullptr) { return false; }
	auto mapset = m_corbeginrun->GetMapSet();
	for (auto iter = mapset.begin();
		iter != mapset.end(); iter++)
	{
		if (m_historymap->GetMapData(iter->first) == iter->second)
		{
			continue;
		}
		else
		{
			m_historymap->SetMapData(iter->first, iter->second.c_str());
			m_corbeginrun->unLockMapData();
			return true;
		}
	}
	m_corbeginrun->unLockMapData();
	return false;
}

int MyFeedSubscriverThread::generateRandomNumber()
{
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	int test = qrand() % (m_step/2);
	return test;
}