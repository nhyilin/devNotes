#ifndef MyTimer_H
#define MyTimer_H
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class MyPublisherTimer :public QObject
{
	Q_OBJECT
public:
	MyPublisherTimer(QObject *parent = 0);
	~MyPublisherTimer();
protected:
	void timerEvent(QTimerEvent *event);
public slots:
	void slotsimPublisher();
	void slotsimPause();//ÔÝÍ£
	void slotsimGoOn();//¼ÌÐø
	void slotsimQuit();//ÍË³ö
signals:
	void workFinishedSignal(QString str);
private:
	QMutex g_mutex;
	int eventtimeID;
	bool m_pause;
	uint32_t samples;
	uint32_t totalsamples;
	QTime startTime;
};


#endif // !MyTimer_H


