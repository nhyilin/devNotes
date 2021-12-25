#include "simdds.h"
#include "SimCentrePublisher.h"
#include "SimCentreSubscriber.h"
#include <QString>
#include <qtsettingset.h>

SimDDS* SimDDS::m_pInstance = nullptr;
SimDDS::SimDDS()
{
}

SimDDS::~SimDDS()
{

}

SimDDS* SimDDS::instance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new SimDDS();
	}
	return m_pInstance;
}

void SimDDS::destroy()
{
	if (nullptr != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void   SimDDS::SimDDSPublisherInit(bool only)
{
	if (!mypubpublisher.init("SimMessageTopic"))
	{
		std::cout << "Init failed !" << std::endl;
	}
	if (only) { return; }
	if (mypubsubscriber.init("SimMessageTopicDDS"))
	{
		mypubsubscriber.run();
	}
	return;
}

void   SimDDS::SimDDSPubPublisher(SimMessageDDs sim)
{
	mypubpublisher.publish(sim,true);
}

void   SimDDS::SimDDSSubPublisher(SimMessageDDs sim)
{
	mysubpublisher.publish(sim, true);
}

void SimDDS::SimDDSSubscriberInit(bool only)
{
	std::cout << "Start Subscriber " << std::endl;
	if (mysubsubscriber.init("SimMessageTopic"))
	{
		mysubsubscriber.run();
		QString nodename;
		QtSettingSet::instance()->readConfig("FEEDBACK_NODE_STEP", "src", nodename);
		mysubsubscriber.setnodename(nodename.toStdString());
	}
	if (only) { return; }
	if (!mysubpublisher.init("SimMessageTopicDDS"))
	{
		std::cout << "Init failed !" << std::endl;
	}

	return;
}


int SimDDS::SimDDSPubPublisherMatch()
{
	return mypubpublisher.m_listener.n_matched;
}

int  SimDDS::SimDDSPubSubscriberMatch()
{
	return mypubsubscriber.m_listener.n_matched;
}

int  SimDDS::SimDDSSubPublisherMatch()
{
	return mysubpublisher.m_listener.n_matched;
}

int SimDDS::SimDDSSubSubscriberMatch()
{
	return mysubsubscriber.m_listener.n_matched;
}

SimMessageDDs SimDDS::SimDDSPubSubscriberData()
{
	return mypubsubscriber.getsimdata();
}

SimMessageDDs SimDDS::SimDDSSubSubscriberData()
{
	return mysubsubscriber.getsimdata();
}

MapSet&  SimDDS::SimDDSPubSubscriberMapSetData()
{
	return mypubsubscriber.getmap();
}

MapSet&  SimDDS::simDDsSubSubscriberMapSetData()
{
	return mysubsubscriber.getmap();
}

queue<SimMessage>& SimDDS::simDDsSubSubscriberQueueData()
{
	return mysubsubscriber.getsimQueue();
}