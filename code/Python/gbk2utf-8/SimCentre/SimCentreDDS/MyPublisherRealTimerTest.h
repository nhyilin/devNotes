#ifndef MyPublisherRealTimerTest_h__
#define MyPublisherRealTimerTest_h__
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class QTimer;
class MapSet;
class RealDataDealTimer;
class MyPublisherRealTimerTest :public QObject
{
	Q_OBJECT
public:
	MyPublisherRealTimerTest(QObject *parent = 0);
	~MyPublisherRealTimerTest();
public slots:
	void slotstimeEvent();
	void slotsimPublisher();
	void slotsimPause();//暂停
	void slotsimGoOn();//继续
	void slotsimQuit();//退出
	void slotTimeStart();
	void slotTimeStop();
private:
	RealDataDealTimer* m_realdatadealtimer;
	QMutex g_mutex_send;
	QTimer * eventtimer;
	bool m_pause;
	uint32_t samples;
	MapSet *m_currentframemap;//当前一帧传输的数据。
	int   nTimeStep;
	int   nTimepre;//优化时间差
	int index;
};

#endif // MyPublisherRealTimerTest_h__


