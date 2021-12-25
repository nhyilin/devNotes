#include "MyPubCallbackSubscriber.h"
#include "SimMessageDDs.h"
#include "simdds.h"
#include "MiddleByValueSet.h"
#include "qttestout.hpp"
#include <sstream>
#include "feedbackcorrunArrayTimer.h"

QMutex global_mutex;
//#pragma execution_character_set("utf-8")//解决中文乱码问题
MapSet *m_feedbacknodestepmap = new MapSet;//反馈节点步长消息
MapSet *m_feedbacknodestatemap = new MapSet;//反馈节点状态消息
MapSet *m_feedbackcorrun = new MapSet; //协同推进回令
void SubscriberCallback(SimMessageDDs simdds)
{
	if (SimDDS::instance()->SimDDSPubSubscriberMatch() < 1) { return; }
	global_mutex.lock();
	//SimMessageDDs simdds = SimDDS::instance()->SimDDSPubSubscriberData();
	//if (/*simdds.tastID == "" ||*/ simhistory == simdds)
	//{
	//	g_mutex.unlock();
	//	continue;
	//}
	//simhistory = simdds;
	int strkey = QString::fromLocal8Bit(simdds.type.c_str()).toInt();
	switch (strkey)
	{
	case 0002:
	{//接收反馈节点步长指令
		//std::stringstream stream;
		//for (int i = 0; i < simdds.data.size(); i++)
		//{
		//	stream << simdds.data.at(i);
		//}
		//std::string ss;
		//stream >> ss;
		//QString temp = QString::fromLocal8Bit(ss.c_str());
		//m_feedbacknodestepmap->SetMapData(simdds.src, temp.toStdString());
		//MIddleByValueSet::instance()->setfeedbacknodestepmap(m_feedbacknodestepmap);
		QString str = "";
		MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
		FeedBackcorrunArrayTimer::on_nodeconnected(simdds);
		FeedBackcorrunArrayTimer::on_nodeconnected(simdds);
		//emit valueChanged(str);
	}
		break;
	case 0005:
	{//接收反馈节点状态消息
		std::stringstream stream;
		for (int i = 0; i < simdds.data.size(); i++)
		{
			stream << simdds.data.at(i);
		}
		std::string ss;
		stream >> ss;
		QString temp = QString::fromLocal8Bit(ss.c_str());
		m_feedbacknodestatemap->SetMapData(simdds.src, temp.toStdString());
		QString str = "";
		MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
		//emit valueChanged(str);
	}
		break;
	case 0007:
	{//接收协同推进回令
		//MIddleByValueSet::instance()->setfeedbackcorrun(&(SimDDS::instance()->SimDDSPubSubscriberMapSetData()));
		//QString str = "";
		//MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
		//emit valueChanged(str);
	}
		break;
	case 0010:
	{
		QString str = "";
		MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
		//emit valueChanged(str);
	}
		break;
	case 0013:
	{//接收反馈节点快照信息
		QString str = "";
		MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
		//emit valueChanged(str);
	}
		break;
	case 0014:
	{//接收
		QString str = "";
		MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
		//emit valueChanged(str);
	}
		break;
	case 0015:
	{//接收
		QString str = "";
		MIddleByValueSet::instance()->getPubTextEdit()->setOut(simdds, str);
		//emit valueChanged(str);
	}
		break;
	default:
		break;
	}
	global_mutex.unlock();
}