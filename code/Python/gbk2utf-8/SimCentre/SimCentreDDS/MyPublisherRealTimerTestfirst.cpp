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
	, index(0)
	, samples(0)
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
	int elapsed = nTimeStep * index++;
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
	//TerminalPubPublisherOutput(simdds);
	std::cout << "type" << simdds.type << "count" << simdds.count << endl;
}


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