#ifndef MyPublisherFullSpeedThread_h__
#define MyPublisherFullSpeedThread_h__
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class MapSet;
class MyPublisherFullSpeedThread :public QObject
{
	Q_OBJECT
public:
	MyPublisherFullSpeedThread(QObject *parent = 0);
	~MyPublisherFullSpeedThread();
public slots:
	void slotsimPublisher();
	void slotsimPause();//暂停
	void slotsimGoOn();//继续
	void slotsimQuit();//退出
	bool ishistory(int num);//历史
private:
	QMutex g_mutex;
	QThread *thread;
	bool m_stop;
	bool m_pause;
	uint32_t n_samples;
	uint32_t samples;
	uint32_t totalsamples;
	QTime startTime;
	std::string destination;
	MapSet *m_historymap;
	bool m_first_flag;
	int nsize;
};


#endif // MyPublisherFullSpeedThread_h__


