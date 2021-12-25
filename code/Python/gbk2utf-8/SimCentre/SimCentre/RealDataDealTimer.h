#ifndef RealDataDealTimer_h__
#define RealDataDealTimer_h__
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class QTimer;
class MapSet;
class RealDataDealTimer :public QObject
{
	Q_OBJECT
public:
	RealDataDealTimer(QTimer * timer, 
		MapSet* mapset,
		QObject* parent = 0);
	~RealDataDealTimer();
	bool getpause();
	void setpause(bool sleep);
	void settimer(int timer);
	bool getdatadealcomplete();
	void setdatadealcomplete(bool deal);
private:
	bool ishistory();
signals:
	void timeStart();
signals:
	void timeStop();
public slots:
	void updateEventDeal();
	void slotsimPublisher();
	void slotsimPause();//ÔÝÍ£
	void slotsimGoOn();//¼ÌÐø
	void slotsimQuit();//ÍË³ö
private:
	QMutex g_mutex;
	QThread* thread;
	bool  currentframe;
	bool  dealcomplete;
	bool  m_pause;
	bool  m_stop;
	MapSet* m_historymap;
	MapSet* m_currentframemap;
	MapSet* m_framemap;
	QTimer* m_timer;
	int m_elapsed;
	int index;
	int nTimeStep;
	bool m_first_flag;
};
#endif // RealDataDealTimer_h__
