#ifndef MyPublisherRealTimer_h__
#define MyPublisherRealTimer_h__
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class MapSet;
class MyPublisherRealTimer :public QObject
{
	Q_OBJECT
public:
	MyPublisherRealTimer(QObject *parent = 0);
	~MyPublisherRealTimer();
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
	MapSet *m_historymap;
	MapSet *m_framemap;
	QTime startTime;
	int index;
	bool m_first_flag;
};
#endif // MyPublisherRealTimer_h__


