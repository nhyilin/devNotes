#include "MyPubSubscriberThread.h"
#include "SimMessageDDs.h"
#include "simdds.h"
#include "MiddleByValueSet.h"
#include "qttestout.hpp"
#include <sstream>
//#pragma execution_character_set("utf-8")//解决中文乱码问题

MyPubSubscriberThread::MyPubSubscriberThread()
{
	m_stop = false;
	m_pause = false;
	n_samples = 0;
	thread = new QThread;
	m_feedbacknodestepmap = new MapSet;
	m_feedbacknodestatemap = new MapSet;
	m_feedbackcorrun = new MapSet;
	this->moveToThread(thread);
	connect(thread,SIGNAL(started()),this,SLOT(slotsimPublisher()));
	connect(thread, SIGNAL(finished()), this, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(this, SIGNAL(valueChanged(QString)),
		MIddleByValueSet::instance()->getPubTextEdit(),
		SLOT(append(QString)));
	thread->start();
}
MyPubSubscriberThread::~MyPubSubscriberThread()
{
	thread->quit();
	thread->wait();
}

void MyPubSubscriberThread::slotsimPublisher()
{
	while (!m_stop)
	{
		if (SimDDS::instance()->SimDDSPubSubscriberMatch() < 1) { continue; }
		if (m_pause) { continue; }
		g_mutex.lock();
		SimMessageDDs simdds = SimDDS::instance()->SimDDSPubSubscriberData();
		if (simdds.tastID == "" || simhistory == simdds)
		{
			g_mutex.unlock();
			continue;
		}
		simhistory = simdds;
		if (simdds.type == "0002")
		{//接收反馈节点步长指令
			std::stringstream stream;
			for (int i = 0;i< simdds.data.size();i++)
			{
				stream << simdds.data.at(i);
			}
			std::string ss;
			stream >> ss;
			QString temp = QString::fromLocal8Bit(ss.c_str());
			m_feedbacknodestepmap->SetMapData(simdds.src,temp.toStdString());
			MIddleByValueSet::instance()->setfeedbacknodestepmap(m_feedbacknodestepmap);
			QString str = "";
			MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds,str);
			emit valueChanged(str);
		}
		else if (simdds.type == "0005")
		{//接收反馈节点状态消息
			std::stringstream stream;
			for (int i= 0;i< simdds.data.size();i++)
			{
				stream << simdds.data.at(i);
			}
			std::string ss;
			stream >> ss;
			QString temp = QString::fromLocal8Bit(ss.c_str());
			m_feedbacknodestatemap->SetMapData(simdds.src,temp.toStdString());
			QString str = "";
			MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds,str);
			emit valueChanged(str);
		}
		else if (simdds.type == "0007")
		{//接收协同推进回令
			MIddleByValueSet::instance()->setfeedbackcorrun(&(SimDDS::instance()->SimDDSPubSubscriberMapSetData()));
			QString str = "";
			MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		else if (simdds.type == "0010")
		{
			QString str = "";
			MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		else if (simdds.type == "0013")
		{//接收反馈节点快照信息
			QString str = "";
			MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		else if (simdds.type == "0014")
		{//接收
			QString str = "";
			MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}
		else if (simdds.type == "0015")
		{//接收
			QString str = "";
			MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
			emit valueChanged(str);
		}	
		g_mutex.unlock();
	}
	//QThread::msleep(MIddleByValueSet::instance()->getsubscribertime());
	QThread::msleep(0);

}

void MyPubSubscriberThread::slotsimPause()
{
	m_pause = true;
}

void MyPubSubscriberThread::slotsimGoOn()
{
	m_pause = false;
}

void MyPubSubscriberThread::slotsimQuit()
{
	m_stop = true;//停止
}