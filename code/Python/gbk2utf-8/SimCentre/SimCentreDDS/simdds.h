#ifndef simdds_h__
#define simdds_h__

#include "SimMessageDDs.h"
#include "SimCentrePublisher.h"
#include "SimCentreSubscriber.h"

class  SimDDS
{
public:
	SimDDS();
	virtual ~SimDDS();
	void   SimDDSPublisherInit(bool only = false);//发布端初始化

	void   SimDDSPubPublisher(SimMessageDDs sim);//发布端发布

	int    SimDDSPubPublisherMatch();//匹配的数量
	int    SimDDSPubSubscriberMatch();//匹配的数量

	SimMessageDDs SimDDSPubSubscriberData();//订阅订阅

	MapSet&  SimDDSPubSubscriberMapSetData();
	static SimDDS* instance();
	static void destroy();
private:
	static SimDDS* m_pInstance;
	SimMessageDDs m_sim;
	SimCentrePublisher mypubpublisher;//发布发布
	SimCentreSubscriber mypubsubscriber;//发布订阅
};
#endif // simdds_h__