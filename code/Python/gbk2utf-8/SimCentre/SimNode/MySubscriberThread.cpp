#include "MySubscriberThread.h"
#include "SimMessageDDs.h"
#include "simdds.h"
#include "MiddleByValueSet.h"
#include "qttestout.hpp"
#include <sstream>
#include "MapSet.h"


MySubscriberThread::MySubscriberThread() 
{
	m_stop = false;
	m_pause = false;
	n_samples = 0;
	m_corforward = new MapSet;
	thread = new QThread;
	this->moveToThread(thread);
	connect(thread,SIGNAL(started()),this,SLOT(slotsimSubscriber()));
	connect(this, SIGNAL(workFinishedSignal(QString)), thread, SLOT(quit()));
	connect(thread, SIGNAL(finished()), this, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(this, SIGNAL(valueChanged(QString)),
		MIddleByValueSet::instance()->getSubTextEdit(),
		SLOT(append(QString)));
	thread->start();
}
MySubscriberThread::~MySubscriberThread()
{
	thread->quit();
	thread->wait();
}

void MySubscriberThread::slotsimSubscriber()
{
	while (!m_stop)
	{
		if (SimDDS::instance()->SimDDSSubSubscriberMatch() < 1) { continue; }
		if (m_pause) { continue; }
		g_mutex.lock();
		////先找回令队列 再判断是否是其它命令
		//queue<SimMessage>& msgQueue = SimDDS::instance()->simDDsSubSubscriberQueueData();
		//if (!msgQueue.empty())
		//{
		//	SimMessage latestMsg = msgQueue.front();
		//	//to MQ 此处添加对消息的操作
		//	{


		//	}
		//	msgQueue.pop();
		//	return;
		//}
		SimMessageDDs simdds = SimDDS::instance()->SimDDSSubSubscriberData();
		QString str = QString::fromLocal8Bit(simdds.dest.c_str());
		if (!str.contains(MIddleByValueSet::instance()->getnodename()) || simhistory == simdds)
		{
			g_mutex.unlock();
			continue;
		}
		simhistory = simdds;
		int key = QString::fromLocal8Bit(simdds.type.c_str()).toInt();
		switch (key)
		{
		case 0001:
		{
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 0003:
		{
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 0004:
		{
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 0006:
		{
			std::stringstream stream;
			for (int j = 0; j < simdds.data.size(); j++)
			{
				stream << simdds.data.at(j);
			}
			std::string ss;
			stream >> ss;
			QString temp = QString::fromLocal8Bit(ss.c_str());
			m_corforward->SetMapData(simdds.src, temp.toStdString());
			MIddleByValueSet::instance()->setcorforwardrun(m_corforward);
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 8:
		{//协同推进

			//MIddleByValueSet::instance()->setcorbeginrun(&(SimDDS::instance()->simDDsSubSubscriberMapSetData()));
			//QString str;
			//MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			//emit valueChanged(str);
		}
		break;
		case 9:
		{
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 10:
		{
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 11:
		{
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 12:
		{
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 14:
		{
			QString str;
			TerminalSubSubsciberOutput(simdds);
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		case 15:
		{
			QString str;
			MIddleByValueSet::instance()->getSubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		break;
		default:
			break;
		}
		g_mutex.unlock();
	}
	QThread::msleep(MIddleByValueSet::instance()->getsubscribersleep());

}

void MySubscriberThread::slotsimPause()
{
	m_pause = true;
}

void MySubscriberThread::slotsimGoOn()
{
	m_pause = false;
}

void MySubscriberThread::slotsimQuit()
{
	m_stop = true;//停止
}