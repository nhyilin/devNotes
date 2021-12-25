#include "SimCentreDDS.h"
#include <iostream>
#include "simdds.h"
#include "SimMessageDDs.h"
#include <fastrtps/Domain.h>
#include <fastrtps/log/Log.h>
#include "MyPublisherTimer.h"
#include "MyPubSubscriberThread.h"
#include "MyPublisherFullSpeedThread.h"
#include "MyPublisherRealTimer.h"
#include "MyPublisherRealTimerTest.h"
#include "MyPublisherRealTimerTestfirst.h"
#include "MyPublisherRealTimerTestone.h"
#include "MyPublisherRealTimerTestTwo.h"
#include "MIddleByValueSet.h"
#include "simplelog.h"
#include "qtsettingset.h"
#include "SimDataAnalysis.h"
#include "qttestout.hpp"
#include <QDebug>
#define  TIME_BY_FIRST
using namespace std;
using namespace eprosima;
using namespace fastrtps;
using namespace rtps;
SimCentreDDS::SimCentreDDS(QWidget *parent)
	: QWidget(parent)
	, m_pubsubscriberthread(NULL)
	, m_mypublishertimer(NULL)
	, m_mypublisherfullspeedthread(NULL)
	, m_mypublisherrealtimer(NULL)
	, m_mypublisherrealtimertest(NULL)
	, m_mypublisherrealtimerfist(NULL)
	, m_mypublisherrealtimerone(NULL)
	, m_mypublisherrealtimertesttwo(NULL)
	, m_buttongroup(new QButtonGroup)
{
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("协同控制中心"));
	Init();
	Inconnect();
}

void SimCentreDDS::Init()
{
	MIddleByValueSet::instance()->setPubTextEdit(ui.textEdit_publisher);
	ui.lineEdit_publisher->setText(QStringLiteral("10"));
	ui.lineEdit_publishernum->setText(QStringLiteral("0"));
	m_buttongroup->setExclusive(true);
	m_buttongroup->addButton(ui.radioButton_direct_push, 0);
	m_buttongroup->addButton(ui.radioButton_fullspeed_push, 1);
	m_buttongroup->addButton(ui.radioButton_real_push, 2);
	m_buttongroup->addButton(ui.radioButton_real_pushtest, 3);
	ui.radioButton_direct_push->setChecked(true);
}

void SimCentreDDS::Inconnect()
{
	this->connect(ui.pushButton_publisher, SIGNAL(clicked()), this, SLOT(slot_publisher()));
	this->connect(ui.pushButton_stop_publisher, SIGNAL(clicked()), this, SLOT(slot_stop_publisher()));
	this->connect(ui.pushButton_pause_publisher, SIGNAL(clicked()), this, SLOT(slot_pause_publisher()));
	this->connect(ui.pushButton_cor_publisher, SIGNAL(clicked()), this, SLOT(slot_cor_publisher()));
	this->connect(ui.pushButton_advance_publisher, SIGNAL(clicked()), this, SLOT(slot_command_pubpublisher()));
	this->connect(ui.pushButton_node_search, SIGNAL(clicked()), this, SLOT(slot_command_pubpublisher()));
	this->connect(ui.pushButton_node_statesearch, SIGNAL(clicked()), this, SLOT(slot_command_pubpublisher()));
	this->connect(ui.pushButton_recover_snapshoot, SIGNAL(clicked()), this, SLOT(slot_skp_publisher()));
	//connect(m_buttongroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_button_group(QAbstractButton*)));
	//connect(m_feedbackbuttongroup, SIGNAL(buttonClicked(int)),this,SLOT(slot_feedbutton_group(int)));

}

void SimCentreDDS::slot_publisher()
{
	std::cout << "协同控制中心" << std::endl;
	long time = ui.lineEdit_publisher->text().toLong();
	this->setWindowTitle(QStringLiteral("协同控制中心"));
	MIddleByValueSet::instance()->setpublishertime(time);
	int num = ui.lineEdit_publishernum->text().toInt();
	MIddleByValueSet::instance()->setpublishernum(num);
	bool only = ui.checkBox_only_publisher->isChecked();//只作为发布端
	SimDDS::instance()->SimDDSPublisherInit(only);
	if (only) { return; }
	slot_recv_pubsubscriber();
	return;
}


void SimCentreDDS::slot_pause_publisher()
{
	if (ui.pushButton_pause_publisher->text() == QStringLiteral("协同暂停指令"))
	{
		ui.pushButton_pause_publisher->setText(QStringLiteral("协同继续指令"));
		int nradio = m_buttongroup->checkedId();
		switch (nradio)
		{
		case 0:
		{//直接推进
			if (nullptr != m_mypublishertimer)
			{
				m_mypublishertimer->slotsimPause();
			}
		}
		break;
		case 1:
		{//全速推进
			if (nullptr != m_mypublisherfullspeedthread)
			{
				m_mypublisherfullspeedthread->slotsimPause();
			}
		}
		break;
		case 2:
		{//实时推进
			if (nullptr != m_mypublisherrealtimer)
			{
				m_mypublisherrealtimer->slotsimPause();
			}
		}
		break;
		case 3:
		{//实时推进2

#if defined(TIME_BY_TEST)
			if (nullptr != m_mypublisherrealtimertest)
			{
				m_mypublisherrealtimertest->slotsimPause();
			}
#elif defined (TIME_BY_FIRST)
			if (nullptr != m_mypublisherrealtimerfist)
			{
				m_mypublisherrealtimerfist->slotsimPause();
			}
#elif defined(TIME_BY_TWO)
			if (nullptr != m_mypublisherrealtimertesttwo)
			{
				m_mypublisherrealtimertesttwo->slotsimPause();
			}
#elif defined(TIME_BY_ONE)
			if (nullptr != m_mypublisherrealtimerone)
			{
				m_mypublisherrealtimerone->slotsimPause();
			}
#endif
		}
		break;
		default:
			break;
		}
	}
	else if (ui.pushButton_pause_publisher->text() == QStringLiteral("协同继续指令"))
	{
		ui.pushButton_pause_publisher->setText(QStringLiteral("协同暂停指令"));

		int nradio = m_buttongroup->checkedId();
		switch (nradio)
		{
		case 0:
		{
			if (nullptr != m_mypublishertimer)
			{
				m_mypublishertimer->slotsimGoOn();
			}
		}
		break;
		case 1:
		{
			if (nullptr != m_mypublisherfullspeedthread)
			{
				m_mypublisherfullspeedthread->slotsimGoOn();
			}
		}
		break;
		case 2:
		{
			if (nullptr != m_mypublisherrealtimer)
			{
				m_mypublisherrealtimer->slotsimGoOn();
			}
		}
		break;
		case 3:
		{

#if defined(TIME_BY_TEST)
			if (nullptr != m_mypublisherrealtimertest)
			{
				m_mypublisherrealtimertest->slotsimGoOn();
			}
#elif defined (TIME_BY_FIRST)
			if (nullptr != m_mypublisherrealtimerfist)
			{
				m_mypublisherrealtimerfist->slotsimGoOn();
			}
#elif defined(TIME_BY_TWO)
			if (nullptr != m_mypublisherrealtimertesttwo)
			{
				m_mypublisherrealtimertesttwo->slotsimGoOn();
			}
#elif defined(TIME_BY_ONE)
			if (nullptr != m_mypublisherrealtimerone)
			{
				m_mypublisherrealtimerone->slotsimGoOn();
			}
#endif
		}
		break;
		default:
			break;
		}

	}
}

void SimCentreDDS::slot_stop_publisher()
{
	int nradio = m_buttongroup->checkedId();
	switch (nradio)
	{
	case 0:
	{//直接推进
		if (nullptr != m_mypublishertimer)
		{
			m_mypublishertimer->slotsimQuit();
		}
	}
	break;
	case 1:
	{//全速推进
		if (nullptr != m_mypublisherfullspeedthread)
		{
			m_mypublisherfullspeedthread->slotsimQuit();
		}
	}
	break;
	case 2:
	{//实时推进
		if (nullptr != m_mypublisherrealtimer)
		{
			m_mypublisherrealtimer->slotsimQuit();
		}
	}
	break;
	case 3:
	{//实时推进2

#if defined(TIME_BY_TEST)
		if (nullptr != m_mypublisherrealtimertest)
		{
			m_mypublisherrealtimertest->slotsimQuit();
		}
#elif defined(TIME_BY_FIRST)
		if (nullptr != m_mypublisherrealtimerfist)
		{
			m_mypublisherrealtimerfist->slotsimQuit();
		}
#elif defined(TIME_BY_TWO)
		if (nullptr != m_mypublisherrealtimertesttwo)
		{
			m_mypublisherrealtimertesttwo->slotsimQuit();
		}
#elif defined(TIME_BY_ONE)
		if (nullptr != m_mypublisherrealtimerone)
		{
			m_mypublisherrealtimerone->slotsimQuit();
		}
#endif
	}
	break;
	default:
		break;
	}

	//Domain::stopAll();
	//Log::Reset();
}

void SimCentreDDS::slot_cor_publisher()
{
	int nradio = m_buttongroup->checkedId();
	switch (nradio)
	{
	case 0:
	{//直接推进
		if (m_mypublishertimer == nullptr)
		{
			m_mypublishertimer = new MyPublisherTimer();
		}
	}
	break;
	case 1:
	{//全速推进
		if (m_mypublisherfullspeedthread == nullptr)
		{
			m_mypublisherfullspeedthread = new MyPublisherFullSpeedThread();
		}
	}
	break;
	case  2:
	{//实时推进
		if (m_mypublisherrealtimer == nullptr)
		{
			m_mypublisherrealtimer = new MyPublisherRealTimer();
		}
	}
	break;
	case 3:
	{//实时推进2

#if defined(TIME_BY_TEST)
		if (m_mypublisherrealtimertest == nullptr)
		{
			m_mypublisherrealtimertest = new MyPublisherRealTimerTest();
		}
#elif defined(TIME_BY_FIRST)
		if (m_mypublisherrealtimerfist == nullptr)
		{
			m_mypublisherrealtimerfist = new MyPublisherRealTimerTestfirst();
		}
#elif defined(TIME_BY_TWO)
		if (m_mypublisherrealtimertesttwo == nullptr)
		{
			m_mypublisherrealtimertesttwo = new MyPublisherRealTimerTestTwo();
		}
#elif defined(TIME_BY_ONE)
		if (m_mypublisherrealtimerone == nullptr)
		{
			m_mypublisherrealtimerone = new MyPublisherRealTimerTestone();
		}
#endif
	}
	default:
		break;
	}

	return;
}

void SimCentreDDS::slot_only_publisher()
{
	bool check = ui.checkBox_only_publisher->isChecked();
	MIddleByValueSet::instance()->setConditionCheck(check);
}



void SimCentreDDS::slot_command_pubpublisher()
{
	QPushButton* btn = dynamic_cast<QPushButton*>(sender());
	QString strname = btn->text();
	SimMessageDDs simdds;

	if (strname == QStringLiteral("查询节点步长指令"))
	{
		static unsigned int sample = 0;
		QtSettingSet::instance()->readConfig("SEARTH_NODE_STEP", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = sample++;
		//拼接数据step - stepnum - count;
		std::string step = ui.lineEdit_publisher->text().toStdString();
		for (int i = 0; i < step.length(); i++)
		{
			simdds.data.push_back(step[i]);
		}
		simdds.data.push_back('-');
		//step_num
		std::string stepnum = QString::number(simdds.count).toStdString();
		for (int n = 0; n < stepnum.length(); n++)
		{
			simdds.data.push_back(stepnum[n]);
		}
		simdds.data.push_back('-');
		//count;
		std::string num = QString::number(simdds.count).toStdString();
		for (int k = 0; k < num.length(); k++)
		{
			simdds.data.push_back(num[k]);
		}
		SimDDS::instance()->SimDDSPubPublisher(simdds);
	}
	else if (strname == QStringLiteral("查询节点状态指令"))
	{
		static unsigned int sample = 0;
		QtSettingSet::instance()->readConfig("SEARTH_NODE_STATE", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = sample++;
		//拼接数据step - stepnum - count;
		std::string step = ui.lineEdit_publisher->text().toStdString();
		for (int i = 0; i < step.length(); i++)
		{
			simdds.data.push_back(step[i]);
		}
		simdds.data.push_back('-');
		//step_num
		std::string stepnum = QString::number(simdds.count).toStdString();
		for (int n = 0; n < stepnum.length(); n++)
		{
			simdds.data.push_back(stepnum[n]);
		}
		simdds.data.push_back('-');
		//count;
		std::string num = QString::number(simdds.count).toStdString();
		for (int k = 0; k < num.length(); k++)
		{
			simdds.data.push_back(num[k]);
		}
		SimDDS::instance()->SimDDSPubPublisher(simdds);
	}
	else if (strname == QStringLiteral("协同推进指令"))
	{
		static unsigned int sample = 0;
		QtSettingSet::instance()->readConfig("COR_FORWARD", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = sample++;
		//拼接数据 step - stepnum - count;
		std::string step = ui.lineEdit_publisher->text().toStdString();
		for (int i = 0; i < step.length(); i++)
		{
			simdds.data.push_back(step[i]);
		}
		simdds.data.push_back('-');
		//step_num
		std::string stepnum = QString::number(simdds.count).toStdString();
		for (int n = 0; n < stepnum.length(); n++)
		{
			simdds.data.push_back(stepnum[n]);
		}
		simdds.data.push_back('-');
		//count;
		std::string num = QString::number(simdds.count).toStdString();
		for (int k = 0; k < num.length(); k++)
		{
			simdds.data.push_back(num[k]);
		}
		SimDDS::instance()->SimDDSPubPublisher(simdds);
	}

	TerminalPubPublisherOutput(simdds);
}


void SimCentreDDS::slot_skp_publisher()
{
	QPushButton* btn = dynamic_cast<QPushButton*>(sender());
	QString strname = btn->text();
	SimMessageDDs simdds;

	if (strname == QStringLiteral("保存节点快照指令"))
	{
		static unsigned int sample = 0;
		QtSettingSet::instance()->readConfig("SAVE_SNAPSHOOT", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = sample++;
		simdds.data.push_back('1');//10ms的步长
		simdds.data.push_back('0');
		SimDDS::instance()->SimDDSPubPublisher(simdds);
	}
	else if (strname == QStringLiteral("恢复节点快照指令"))
	{
		static unsigned int sample = 0;
		QtSettingSet::instance()->readConfig("RECOVER_SNAPSHOOT", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.count = sample++;
		//拼接数据 +step + stepnum + count;
		std::string step = ui.lineEdit_publisher->text().toStdString();
		for (int i = 0; i < step.length(); i++)
		{
			simdds.data.push_back(step[i]);
		}
		simdds.data.push_back('-');
		//step_num
		std::string stepnum = QString::number(simdds.count).toStdString();
		for (int n = 0; n < stepnum.length(); n++)
		{
			simdds.data.push_back(stepnum[n]);
		}
		simdds.data.push_back('-');
		//count;
		std::string num = QString::number(simdds.count).toStdString();
		for (int k = 0; k < num.length(); k++)
		{
			simdds.data.push_back(num[k]);
		}
		//Data
		SimpleLog::instance()->writelog();
		QString str = SimpleLog::instance()->readlog();
		std::string data = SimpleLog::instance()->readlog().toLocal8Bit();
		for (int s = 0; s < data.length(); s++)
		{
			simdds.data.push_back(data[s]);
		}
		SimDDS::instance()->SimDDSPubPublisher(simdds);
	}
	TerminalPubPublisherOutput(simdds);
}

void SimCentreDDS::slot_recv_pubsubscriber()
{
	if (m_pubsubscriberthread == NULL)
	{
		m_pubsubscriberthread = new MyPubSubscriberThread;
	}
}


void SimCentreDDS::closeEvent(QCloseEvent* event)
{
	if (m_mypublishertimer != NULL)
	{
		m_mypublishertimer->slotsimQuit();
	}
	if (m_mypublisherfullspeedthread != nullptr)
	{
		m_mypublisherfullspeedthread->slotsimQuit();
	}
	if (m_pubsubscriberthread != nullptr)
	{
		m_pubsubscriberthread->slotsimQuit();
	}
	if (m_mypublisherrealtimer != nullptr)
	{
		m_mypublisherrealtimer->slotsimQuit();
	}
	Domain::stopAll();
	Log::Reset();
}