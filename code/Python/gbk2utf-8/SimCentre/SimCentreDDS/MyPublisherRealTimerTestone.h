#ifndef MyPublisherRealTimerTestone_h__
#define MyPublisherRealTimerTestone_h__
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class QTimer;
class MapSet;
class MyPublisherRealTimerTestone :public QObject
{
	Q_OBJECT
public:
	MyPublisherRealTimerTestone(QObject *parent = 0);
	~MyPublisherRealTimerTestone();
protected:
	bool ishistory();
	bool ishistorytest();
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
	uint32_t framesamples;
	MapSet *m_historymap;//节点传输的数据
	MapSet *m_framemap;
	MapSet *m_currentframemap;//当前一帧传输的数据。
	bool  currentframe;
	int   nTimeStep;
	int index;
	bool m_first_flag;
};
#endif // MyPublisherRealTimerTestone_h__


