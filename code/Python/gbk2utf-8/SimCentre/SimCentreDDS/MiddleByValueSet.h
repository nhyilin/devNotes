#ifndef MiddleByValueSet_h__
#define MiddleByValueSet_h__
#include <QString>
#include "QtMyTextEdit.h"
#include <QMutexLocker>

class MapSet;
class MyPublisherRealTimerTestfirst;
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
	
	void setfeedbacknodestepmap(MapSet*);
	MapSet *getfeedbacknodestepmap(){ return m_feedbacknodestepmap; }

	void  setfeedbacknodestatemap(MapSet*);
	MapSet *getfeedbacknodestatemap() { return m_feedbacknodestatemap; }

	void  setfeedbackcorrun(MapSet*);
	MapSet *getfeedbackcorrun() {  return m_feedbackcorrun; }


	void setcorforwardrun(MapSet*);

	QtMyTextEdit* getPubTextEdit();
	void setPubTextEdit(QtMyTextEdit * textedit);


	static MIddleByValueSet* instance();
	static void destroy();
private:
	static MIddleByValueSet* m_pInstance;
	QtMyTextEdit * m_mypubtextedit;
	long  m_subscribertime;
	long  m_subscribersleep;
	long  m_publishertime;
	int m_num;
	bool  m_pause;
	bool  m_stop;
	bool  m_check;
	QMutex g_mutex;
	unsigned int m_state;
	MapSet *m_feedbacknodestepmap;//反馈节点步长消息
	MapSet *m_feedbacknodestatemap;//反馈节点状态消息
	MapSet *m_feedbackcorrun; //协同推进回令
	MyPublisherRealTimerTestfirst *m_realtimertest;
};

#endif // MiddleByValueSet_h__