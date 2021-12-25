#include "MIddleByValueSet.h"
#include <iostream>
#include "MapSet.h"

MIddleByValueSet* MIddleByValueSet::m_pInstance = nullptr;
MIddleByValueSet::MIddleByValueSet():
	m_subscribersleep(0)
	,m_publishertime(0)
	, m_pause(false)
	, m_num(0)
	, m_check(false)
	,m_corbeginrun(nullptr)
	,m_corforwardrun(nullptr)
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

void MIddleByValueSet::setcorforwardrun(MapSet * map)
{
	m_corforwardrun = map;
}

QtMyTextEdit* MIddleByValueSet::getSubTextEdit()
{
	return m_mysubtextedit;
}

void MIddleByValueSet::setSubTextEdit(QtMyTextEdit * textedit)
{
	m_mysubtextedit = textedit;
}

void MIddleByValueSet::setcorbeginrun(MapSet* map)
{
	m_corbeginrun = map;
}

void MIddleByValueSet::setnodename(QString strname)
{
	m_nodename = strname;
}