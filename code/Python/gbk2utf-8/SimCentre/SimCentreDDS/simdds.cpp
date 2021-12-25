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



int SimDDS::SimDDSPubPublisherMatch()
{
	return mypubpublisher.m_listener.n_matched;
}

int  SimDDS::SimDDSPubSubscriberMatch()
{
	return mypubsubscriber.m_listener.n_matched;
}


SimMessageDDs SimDDS::SimDDSPubSubscriberData()
{
	return mypubsubscriber.getsimdata();
}

MapSet&  SimDDS::SimDDSPubSubscriberMapSetData()
{
	return mypubsubscriber.getmap();
}