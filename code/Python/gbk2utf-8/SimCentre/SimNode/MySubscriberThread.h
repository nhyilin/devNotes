#ifndef MySubscriberThread_H
#define MySubscriberThread_H
#include <QObject>
#include <QThread>
#include <QMutex>
#include "SimMessageDDs.h"

class MapSet;
class MySubscriberThread :public QObject
{
	Q_OBJECT
public:
	MySubscriberThread();
	~MySubscriberThread();

signals:
	void valueChanged(QString);
public slots:
	void slotsimSubscriber();
	void slotsimPause();//暂停
	void slotsimGoOn();//继续
	void slotsimQuit();//退出
signals:
	void workFinishedSignal(QString str);
private:
	QThread *thread;	
	bool m_stop;
	bool m_pause;
	uint32_t n_samples;
	QMutex g_mutex;
	SimMessageDDs simhistory;
	MapSet *m_corforward;//协同推进
};


#endif // !MyThread_H


