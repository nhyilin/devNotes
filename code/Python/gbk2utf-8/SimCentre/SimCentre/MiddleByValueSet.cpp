#include "MIddleByValueSet.h"
#include <iostream>
#include "MapSet.h"
#include "MyPublisherRealTimerTestfirst.h"

MIddleByValueSet* MIddleByValueSet::m_pInstance = nullptr;
MIddleByValueSet::MIddleByValueSet():
	m_subscribersleep(0)
	,m_publishertime(0)
	, m_pause(false)
	, m_num(0)
	, m_check(false)
	,m_feedbacknodestepmap(nullptr)
	,m_feedbacknodestatemap(nullptr)
	,m_feedbackcorrun(nullptr)
	, m_realtimertest(nullptr)
{
}
MIddleByValueSet::~MIddleByValueSet()
{

}

MIddleByValueSet* MIddleByValueSet::instance()
{
	if (nullptr == m_pInstance)
	{
		m_pInstance = new MIddleByValueSet();
	}
	return m_pInstance;
}

void MIddleByValueSet::destroy()
{
	if (nullptr != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void MIddleByValueSet::setsubscribersleep(long sleep)
{
	m_subscribersleep = sleep;
}

void MIddleByValueSet::setsubscribertime(long time)
{
	m_subscribertime = time;
}

void MIddleByValueSet::setpublishertime(long sleep)
{
	m_publishertime = sleep;
}

void MIddleByValueSet::setpublishernum(unsigned int num)
{
	m_num = num;
}

void MIddleByValueSet::setConditionCheck(bool check)
{
	m_check = check;
}

void MIddleByValueSet::setfeedbackstate(unsigned int state)
{
	m_state = state;
}
void MIddleByValueSet::setpublishpause(bool pause)
{
	m_pause = pause;
}

void MIddleByValueSet::setpublishstop(bool stop)
{
	m_stop = stop;
}

QtMyTextEdit* MIddleByValueSet::getPubTextEdit()
{
	return m_mypubtextedit;
}

void MIddleByValueSet::setPubTextEdit(QtMyTextEdit * textedit)
{
	m_mypubtextedit = textedit;
}

MyPublisherRealTimerTestfirst* MIddleByValueSet::getPublisherRealTimeTest()
{
	return m_realtimertest;
}

void MIddleByValueSet::setMyPublisherRealTimeTest(MyPublisherRealTimerTestfirst* realtimetest)
{
	m_realtimertest = realtimetest;
}


void MIddleByValueSet::setfeedbacknodestepmap(MapSet* map)
{
	m_feedbacknodestepmap = map;
}

void  MIddleByValueSet::setfeedbacknodestatemap(MapSet* map)
{
	m_feedbacknodestatemap = map;
}

void  MIddleByValueSet::setfeedbackcorrun(MapSet* map)
{
	m_feedbackcorrun = map;
}
