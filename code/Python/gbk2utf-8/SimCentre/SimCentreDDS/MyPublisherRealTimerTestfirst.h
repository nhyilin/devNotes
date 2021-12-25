#ifndef MyPublisherRealTimerTestfirst_h__
#define MyPublisherRealTimerTestfirst_h__

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class QTimer;
class MapSet;
class MyPublisherRealTimerTestfirst :public QObject
{
	Q_OBJECT
public:
	MyPublisherRealTimerTestfirst(QObject *parent = 0);
	~MyPublisherRealTimerTestfirst();
public slots:	
	void updateEvent();
	void slotsimPublisher();
	void slotsimPause();//暂停
	void slotsimGoOn();//继续
	void slotsimQuit();//退出
signals:
	void workFinishedSignal(QString str);
private:
	QMutex g_mutex;
	int eventtimeID;
	QTimer *timerevent;
	bool m_pause;
	uint32_t samples;
	int   nTimeStep;
	int   nTimepre;//优化时间差
	int index;
};

#endif // MyPublisherRealTimerTestfirst_h__

