#ifndef MyFeedSubscrivberThread_h__
#define MyFeedSubscrivberThread_h__

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class MapSet;
class MyFeedSubscriverThread :public QObject
{
	Q_OBJECT
public:
	MyFeedSubscriverThread(QObject *parent = 0);
	~MyFeedSubscriverThread();
public slots:
	void slotsimPublisher();
	void slotsimPause();//ÔÝÍ£
	void slotsimGoOn();//¼ÌÐø
	void slotsimQuit();//ÍË³ö
	bool history();
	int generateRandomNumber();
signals:
	void workFinishedSignal(QString str);
private:
	QMutex g_mutex;
	QThread *thread;
	bool m_stop;
	bool m_pause;
	int  m_step;
	uint32_t samples;
	MapSet *m_historymap;
	QTime startTime;
	bool m_first_flag;
	bool nradom;
};


#endif // MyFeedSubscrivberThread_h__


