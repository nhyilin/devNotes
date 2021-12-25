#ifndef MyPublisherRealTimerTestTwo_h__
#define MyPublisherRealTimerTestTwo_h__

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class QTimer;
class MapSet;
class RealDataDealTimerTwo;
class MyPublisherRealTimerTestTwo :public QObject
{
	Q_OBJECT
public:
	MyPublisherRealTimerTestTwo(QObject *parent = 0);
	~MyPublisherRealTimerTestTwo();
protected:
	void timerEvent(QTimerEvent *event);
public slots:
	void slotsimPublisher();
	void slotsimPause();//暂停
	void slotsimGoOn();//继续
	void slotsimQuit();//退出
private:
	RealDataDealTimerTwo* m_realdatadealtimertwo;
	QMutex g_mutex_send;
	int eventtimeID;
	bool m_pause;
	uint32_t samples;
	MapSet *m_currentframemap;//当前一帧传输的数据。
	int   nTimeStep;
	int   nTimepre;//优化时间差
	int index;
};

#endif // MyPublisherRealTimerTestTwo_h__


