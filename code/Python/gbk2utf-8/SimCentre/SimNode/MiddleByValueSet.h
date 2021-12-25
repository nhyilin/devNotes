#ifndef MiddleByValueSet_h__
#define MiddleByValueSet_h__
#include <QString>
#include "QtMyTextEdit.h"
#include <QMutexLocker>

class MapSet;
class MIddleByValueSet
{
public:
	MIddleByValueSet();
	virtual ~MIddleByValueSet();
	void setsubscribersleep(long sleep);
	long getsubscribersleep() { return m_subscribersleep; }

	void setsubscribertime(long time);
	long getsubscribertime() { return m_subscribertime; }

	void setpublishertime(long sleep);
	long getpublishertime() { return  m_publishertime; }

	void setpublishernum(unsigned int num);
	unsigned int getpublishernum() { return m_num; }

	void setConditionCheck(bool check);
	bool getConditionCheck() { return m_check; }

	void setfeedbackstate(unsigned int state);
	unsigned int getfeedbackstate() { return m_state; }

	void setpublishpause(bool pause);
	bool getpublishpause() { return m_pause; }

	void setpublishstop(bool stop);
	bool getpublishstop() { return m_stop; }
	
	void setnodename(QString strname);
	QString getnodename() { return m_nodename; }

	void setcorbeginrun(MapSet*);
	MapSet *getcorbeginrun() { return m_corbeginrun; }

	void setcorforwardrun(MapSet*);
	MapSet *getcorforwardrun() {  return m_corforwardrun; }

	QtMyTextEdit* getPubTextEdit();
	void setPubTextEdit(QtMyTextEdit * textedit);

	QtMyTextEdit* getSubTextEdit();
	void setSubTextEdit(QtMyTextEdit * textedit);
	static MIddleByValueSet* instance();
	static void destroy();
private:
	static MIddleByValueSet* m_pInstance;
	QtMyTextEdit * m_mysubtextedit;
	QString m_nodename;
	long  m_subscribertime;
	long  m_subscribersleep;
	long  m_publishertime;
	int m_num;
	bool  m_pause;
	bool  m_stop;
	bool  m_check;
	QMutex g_mutex;
	unsigned int m_state;
	MapSet *m_corbeginrun;//协同开始指令
	MapSet *m_corforwardrun;//协同推进指令
};

#endif // MiddleByValueSet_h__