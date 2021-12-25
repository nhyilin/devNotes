#ifndef MyPubSubscriberThread_h__
#define MyPubSubscriberThread_h__

#include <QObject>
#include <QThread>
#include <QMutex>
#include "SimMessageDDs.h"
#include "MapSet.h"

class MyPubSubscriberThread :public QObject
{
	Q_OBJECT
public:
	MyPubSubscriberThread();
	~MyPubSubscriberThread();
signals:
	void valueChanged(QString);
public slots:
	void slotsimPublisher();
	void slotsimPause();//暂停
	void slotsimGoOn();//继续
	void slotsimQuit();//退出
private:
	QThread *thread;
	bool m_stop;
	bool m_pause;
	uint32_t n_samples;
	QMutex g_mutex;
	SimMessageDDs simhistory;
	MapSet *m_feedbacknodestepmap;//反馈节点步长消息
	MapSet *m_feedbacknodestatemap;//反馈节点状态消息
	MapSet *m_feedbackcorrun; //协同推进回令
};


#endif // MyPubSubscriberThread_h__


