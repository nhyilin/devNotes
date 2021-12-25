#include "MyPublisherRealTimer.h"
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
#include <QTextStream>

using namespace std::chrono;
MyPublisherRealTimer::MyPublisherRealTimer(QObject *parent)
{
	m_pause = false;
	m_first_flag = true;
	index = 0;
	m_historymap = new MapSet;
	m_framemap = new MapSet;
	samples = 10;
	slotsimPublisher();
}
MyPublisherRealTimer::~MyPublisherRealTimer()
{
}

void MyPublisherRealTimer::slotsimPublisher()
{
	startTimer(MIddleByValueSet::instance()->getpublishertime(),Qt::PreciseTimer);
	startTime = QTime::currentTime();
	SimpleLog::instance()->writelogStartTime();
}

void MyPublisherRealTimer::timerEvent(QTimerEvent *event)
{
	eventtimeID = event->timerId();
	if (m_first_flag)
	{
		MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
		if (m_feedbackcorrun == nullptr) { return; }
		auto mapset = m_feedbackcorrun->GetMapSet();
		for (auto iter = mapset.begin();
			iter != mapset.end(); iter++)
		{
			m_historymap->SetMapData(iter->first, iter->second.c_str());
			m_framemap->SetMapData(iter->first,"0");
		}
		m_feedbackcorrun->unLockMapData();
		m_first_flag = false;
		return;
	}
	if (SimDDS::instance()->SimDDSPubPublisherMatch() < 1) { return; }
	if (m_pause) { return; }
	g_mutex.lock();
	MapSet * m_feedbackstep = MIddleByValueSet::instance()->getfeedbacknodestepmap();//反馈步长回令
	MapSet * m_feedbackcorrun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
	if (m_feedbackstep == nullptr) { return; }
	if (m_feedbackcorrun == nullptr) { return; }
	int elapsed = MIddleByValueSet::instance()->getpublishertime() * index++;
	auto mapset = m_historymap->GetMapSet();
	for (auto iter = mapset.begin(); iter != mapset.end(); iter++)
	{
		QString valuehistory = QString::fromLocal8Bit(iter->second.c_str());
		QStringList valuehistorylist = valuehistory.split('-');
		if (elapsed % valuehistorylist[0].toInt() == 0)
		{
			MapSet* feedbackcorun = MIddleByValueSet::instance()->getfeedbackcorrun();//反馈推进回令
			QString strvalue = QString::fromLocal8Bit(feedbackcorun->GetMapData(iter->first).c_str());
			QStringList strlist = strvalue.split('-');
			if (strlist[2].toInt() > valuehistorylist[2].toInt())
			{
				m_historymap->unLockMapData();
				m_historymap->SetMapData(iter->first,strvalue.toLocal8Bit().data());

				int nstepnum =  
					QString::fromLocal8Bit(m_framemap->GetMapData(iter->first).c_str()).toInt();
				SimMessageDDs simdds;
				{
					QtSettingSet::instance()->readConfig("COR_RUN_BEGIN", simdds);
					simdds.dest = iter->first;
					simdds.time = currentDataTime().toLocal8Bit();
					simdds.count = samples++;
					//拼接数据 +step + steptime + count;
					std::string step = QString::number(
						MIddleByValueSet::instance()->getpublishertime()).toStdString();
					for (int j = 0; j < step.length(); j++)
					{
						simdds.data.push_back(step[j]);
					}
					simdds.data.push_back('-');
					//stepnum 
					std::string stepnum = QString::number(nstepnum).toStdString();
					for (int n = 0;n< stepnum.length();n++)
					{
						simdds.data.push_back(stepnum[n]);
					}
					simdds.data.push_back('-');
					nstepnum++;
					m_framemap->SetMapData(iter->first,QString::number(nstepnum).toStdString());
					//count;
					std::string num = QString::number(simdds.count).toStdString();
					for (int k = 0; k < num.length(); k++)
					{
						simdds.data.push_back(num[k]);
					}
				}
				m_historymap->LockMapData();
				SimDDS::instance()->SimDDSPubPublisher(simdds);
				TerminalPubPublisherOutput(simdds);
			}
		}
	}
	m_historymap->unLockMapData();
	g_mutex.unlock();
	return;
}

void MyPublisherRealTimer::slotsimPause()
{
	m_pause = true;
	SimMessageDDs simdds;
	QtSettingSet::instance()->readConfig("COR_RUN_PAUSE", simdds);
	simdds.time = currentDataTime().toLocal8Bit();
	simdds.count = samples++;
	//拼接数据 +step + stepnum + count;
	std::string step = QString::number(
		MIddleByValueSet::instance()->getpublishertime()).toStdString();
	for (int j = 0; j < step.length(); j++)
	{
		simdds.data.push_back(step[j]);
	}
	SimDDS::instance()->SimDDSPubPublisher(simdds);
	TerminalPubPublisherOutput(simdds);
}

void MyPublisherRealTimer::slotsimGoOn()
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

void MyPublisherRealTimer::slotsimQuit()
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