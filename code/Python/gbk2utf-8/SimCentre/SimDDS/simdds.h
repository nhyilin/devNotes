#ifndef simdds_h__
#define simdds_h__

#include "SimMessageDDs.h"
#include "SimCentrePublisher.h"
#include "SimCentreSubscriber.h"
#if defined(_WIN32)
#if defined(SIM_USER_DLL_EXPORT)
#define Sim_user_DllExport __declspec( dllexport )
#else
#define Sim_user_DllExport
#endif
#else
#define Sim_user_DllExport
#endif

#if defined(_WIN32)
#if defined(SIM_USER_DLL_EXPORT)
#if defined(SIM_SOURCE)
#define SIM_DllAPI __declspec( dllexport )
#else
#define SIM_DllAPI __declspec( dllimport )
#endif // HelloWorld_SOURCE
#else
#define SIM_DllAPI
#endif
#else
#define SIM_DllAPI
#endif // _WIN32


class  SimDDS
{
public:
	SimDDS();
	virtual ~SimDDS();
	void   Sim_user_DllExport SimDDSPublisherInit(bool only = false);//发布端初始化
	void   Sim_user_DllExport SimDDSSubscriberInit(bool only = false);//订阅端初始化

	void   Sim_user_DllExport SimDDSPubPublisher(SimMessageDDs sim);//发布端发布
	void   Sim_user_DllExport SimDDSSubPublisher(SimMessageDDs sim);//订阅端发布

	int    Sim_user_DllExport SimDDSPubPublisherMatch();//匹配的数量
	int    Sim_user_DllExport SimDDSPubSubscriberMatch();//匹配的数量

	int    Sim_user_DllExport SimDDSSubPublisherMatch();//匹配的数量
	int    Sim_user_DllExport SimDDSSubSubscriberMatch();//匹配的数量

	SimMessageDDs Sim_user_DllExport SimDDSPubSubscriberData();//订阅订阅
	SimMessageDDs Sim_user_DllExport SimDDSSubSubscriberData();

	MapSet&  Sim_user_DllExport SimDDSPubSubscriberMapSetData();
	MapSet&  Sim_user_DllExport simDDsSubSubscriberMapSetData();
	queue<SimMessage>& Sim_user_DllExport  simDDsSubSubscriberQueueData();
	static SimDDS* instance();
	static void destroy();
private:
	static SimDDS* m_pInstance;
	SimMessageDDs m_sim;
	SimCentrePublisher mypubpublisher;//发布发布
	SimCentreSubscriber mypubsubscriber;//发布订阅
	SimCentrePublisher mysubpublisher;//订阅发布
	SimCentreSubscriber mysubsubscriber;//订阅订阅
};
#endif // simdds_h__