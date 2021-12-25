#ifndef RealDataDealTimerTwo_h__
#define RealDataDealTimerTwo_h__
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QTime>

class MapSet;
class RealDataDealTimerTwo :public QObject
{
	Q_OBJECT
public:
	RealDataDealTimerTwo(QObject *parent = 0);
	~RealDataDealTimerTwo();
	void setcurrentmap(MapSet* mapset);
	bool getpause();
	void setpause(bool sleep);
	void settimer(int timer);
	bool getdatadealcomplete();
	void setdatadealcomplete(bool deal);
private:
	bool ishistory();
public slots:
	void updateEventDeal();
	void slotsimPublisher();
	void slotsimPause();//ÔÝÍ£
	void slotsimGoOn();//¼ÌÐø
	void slotsimQuit();//ÍË³ö
private:
	QMutex g_mutex;
	QThread *thread;
	bool  currentframe;
	bool  dealcomplete;
	bool  m_pause;
	bool  m_stop;
	MapSet *m_historymap;
	MapSet *m_currentframemap;
	MapSet *m_nextframemap;
	int m_elapsed;
	int index;
	int indexstep;
	int nTimeStep;
	bool m_first_flag;
};
#endif // RealDataDealTimerTwo_h__



