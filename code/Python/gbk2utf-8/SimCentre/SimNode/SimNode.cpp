#include "SimNode.h"
#include "MIddleByValueSet.h"
#include "qtsettingset.h"
#include <iostream>
#include <QDateTime>
#include <fastrtps/Domain.h>
#include <fastrtps/log/Log.h>
#include "simdds.h"
#include "MyFeedSubscrivberThread.h"
#include "MySubscriberThread.h"
#include "SimDataAnalysis.h"
#include "qttestout.hpp"
#include "simplelog.h"

using namespace std;
using namespace eprosima;
using namespace fastrtps;
using namespace rtps;
SimNode::SimNode(QWidget *parent)
	: QWidget(parent)
	, m_myfeedsubscriverthread(NULL)
	, m_mysubscriberthread(NULL)
	, m_feedbackbuttongroup(new QButtonGroup)
{
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("节点"));
	init();
	inconnect();
}

void SimNode::init()
{
	MIddleByValueSet::instance()->setSubTextEdit(ui.textEdit_subscriber);
	ui.lineEdit_subscriber_step->setText(QStringLiteral("10"));
	m_feedbackbuttongroup->setExclusive(true);
	m_feedbackbuttongroup->addButton(ui.radioButton_sub_init, 0);
	m_feedbackbuttongroup->addButton(ui.radioButton_sub_run, 1);
	m_feedbackbuttongroup->addButton(ui.radioButton_sub_pause, 2);
	m_feedbackbuttongroup->addButton(ui.radioButton_sub_error, 3);
	QString str;
	QtSettingSet::instance()->readConfig("FEEDBACK_NODE_STEP", "src", str);
	ui.comboBox_subscriber->setCurrentText(str);
	MIddleByValueSet::instance()->setnodename(str);
	ui.radioButton_sub_init->setChecked(true);
}

void SimNode::inconnect()
{
	connect(ui.pushButton_subscriber, SIGNAL(clicked()), this, SLOT(slot_subscriber()));
	//反馈
	connect(ui.pushButton_feed_pause, SIGNAL(clicked()), this, SLOT(slot_feedpause_buttongroup()));
	connect(ui.pushButton_feed_stop, SIGNAL(clicked()), this, SLOT(slot_feedstop_buttongroup()));
	connect(ui.pushButton_feed_run, SIGNAL(clicked()), this, SLOT(slot_command_subpublisher()));
	connect(ui.pushButton_feed_nodesearch, SIGNAL(clicked()), this, SLOT(slot_command_subpublisher()));
	connect(ui.pushButton_feed_nodesearchstate, SIGNAL(clicked()), this, SLOT(slot_command_subpublisher()));
	connect(ui.pushButton_feed_snapshoot, SIGNAL(clicked()), this, SLOT(slot_command_subpublisher()));

	connect(ui.comboBox_subscriber, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[=](int index) {
		QString str = ui.comboBox_subscriber->currentText();
		QtSettingSet::instance()->writeConfig("FEEDBACK_NODE_STEP", "src", str);
		QtSettingSet::instance()->writeConfig("FEEDBACK_NODE_STATE", "src", str);
		QtSettingSet::instance()->writeConfig("FEEDBACK_COR_RUN", "src", str);
		QtSettingSet::instance()->writeConfig("FEEDBACK_SNAPSHOOT", "src", str);
	});
}

void SimNode::slot_subscriber()
{
	std::cout << "节点" << std::endl;
	QString temp = ui.comboBox_subscriber->currentText();
	long sleep = ui.lineEdit_subscriber_step->text().toLong();
	this->setWindowTitle(QStringLiteral("节点") + temp);
	MIddleByValueSet::instance()->setsubscribersleep(sleep);
	bool only = ui.checkBox_only_subscriber->isChecked();
	SimDDS::instance()->SimDDSSubscriberInit(only);//只作为收端
	slot_recv_subsubscriber();
	return;
}

void SimNode::slot_only_subscriber()
{
	bool check = ui.checkBox_only_subscriber->isChecked();
	MIddleByValueSet::instance()->setConditionCheck(check);
}

void SimNode::slot_command_subpublisher()
{
	QPushButton * btn = dynamic_cast<QPushButton*>(sender());
	QString strname = btn->text();
	SimMessageDDs simdds;
	if (SimDDS::instance()->SimDDSSubPublisherMatch() < 1) { return; }
	if (strname == QStringLiteral("反馈节点步长消息"))
	{
		static unsigned int sample = 0;
		QtSettingSet::instance()->readConfig("FEEDBACK_NODE_STEP", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.step = ui.lineEdit_subscriber_step->text().toStdString();
		simdds.count = sample++;
		////拼接数据 +step + stepnum + count;
		//std::string step = ui.lineEdit_subscriber_step->text().toStdString();
		//for (int i = 0; i < step.length(); i++)
		//{
		//	simdds.data.push_back(step[i]);
		//}
		//simdds.data.push_back('-');
		////step_num
		//std::string stepnum = QString::number(simdds.count).toStdString();
		//for (int n = 0; n < stepnum.length(); n++)
		//{
		//	simdds.data.push_back(stepnum[n]);
		//}
		//simdds.data.push_back('-');
		////count;
		//std::string num = QString::number(simdds.count).toStdString();
		//for (int k = 0; k < num.length(); k++)
		//{
		//	simdds.data.push_back(num[k]);
		//}
		SimDDS::instance()->SimDDSSubPublisher(simdds);
	}
	else if (strname == QStringLiteral("反馈节点状态消息"))
	{
		static unsigned int sample = 0;
		QtSettingSet::instance()->readConfig("FEEDBACK_NODE_STATE", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.step = ui.lineEdit_subscriber_step->text().toStdString();
		simdds.count = sample++;
		//拼接数据 +step+stepnum+count;
		//MIddleByValueSet::instance()->getfeedbackstate();
		//int nradio = m_feedbackbuttongroup->checkedId();
		//switch (nradio)
		//{
		//case 0://初始化
		//{
		//	//反馈状态
		//	simdds.data.push_back('0');
		//	simdds.data.push_back('0');
		//}
		//break;
		//case 1://运行态
		//{
		//	simdds.data.push_back('1');
		//	simdds.data.push_back('0');
		//}
		//break;
		//case 2://暂停态
		//{
		//	simdds.data.push_back('2');
		//	simdds.data.push_back('0');
		//}
		//break;
		//case 3://故障态
		//{
		//	simdds.data.push_back('3');
		//	simdds.data.push_back('0');
		//}
		//break;
		//default:
		//	break;
		//}
		//simdds.data.push_back('-');
		////count;
		//std::string num = QString::number(simdds.count).toStdString();
		//for (int k = 0; k < num.length(); k++)
		//{
		//	simdds.data.push_back(num[k]);
		//}
		SimDDS::instance()->SimDDSSubPublisher(simdds);
	}
	else if (strname == QStringLiteral("协同推进回令"))
	{
		if (ui.checkBox_feedbackalway->isChecked())
		{
			//TODO:修改自动变量
			if (m_myfeedsubscriverthread == nullptr)
			{
				m_myfeedsubscriverthread = new MyFeedSubscriverThread;
			}
		}
		else
		{
			SimpleLog::instance()->writelogStartTime();
			static unsigned int sample = 0;
			QtSettingSet::instance()->readConfig("FEEDBACK_COR_RUN", simdds);
			simdds.time = currentDataTime().toLocal8Bit();
			simdds.step = ui.lineEdit_subscriber_step->text().toStdString();
			simdds.count = sample++;
			////拼接数据 step+stepnum+count;
			//std::string step = ui.lineEdit_subscriber_step->text().toStdString();
			//for (int i = 0; i < step.length(); i++)
			//{
			//	simdds.data.push_back(step[i]);
			//}
			//simdds.data.push_back('-');
			////step_num
			//std::string stepnum = QString::number(simdds.count).toStdString();
			//for (int n = 0; n < stepnum.length(); n++)
			//{
			//	simdds.data.push_back(stepnum[n]);
			//}
			//simdds.data.push_back('-');
			////count;
			//std::string num = QString::number(simdds.count).toStdString();
			//for (int k = 0; k < num.length(); k++)
			//{
			//	simdds.data.push_back(num[k]);
			//}
			SimDDS::instance()->SimDDSSubPublisher(simdds);
		}
	}
	else if (strname == QStringLiteral("反馈节点快照信息"))
	{
		static unsigned int sample = 0;
		QtSettingSet::instance()->readConfig("FEEDBACK_SNAPSHOOT", simdds);
		simdds.time = currentDataTime().toLocal8Bit();
		simdds.step = ui.lineEdit_subscriber_step->text().toStdString();
		simdds.count = sample++;
		//拼接数据 step + stepnum+count;
		//快照信息
		SimDDS::instance()->SimDDSSubPublisher(simdds);
	}
	TerminalSubPublisherOutput(simdds);
}

void SimNode::slot_recv_subsubscriber()
{
	if (m_mysubscriberthread == NULL)
	{
		m_mysubscriberthread = new MySubscriberThread;
	}
}

void SimNode::closeEvent(QCloseEvent *event)
{
	if (m_mysubscriberthread != nullptr)
	{
		m_mysubscriberthread->slotsimQuit();
	}
	Domain::stopAll();
	Log::Reset();
}

void SimNode::slot_feedbutton_group(int id)
{
	int nradio = m_feedbackbuttongroup->checkedId();
	MIddleByValueSet::instance()->setfeedbackstate(nradio);
}

void SimNode::slot_feedpause_buttongroup()
{
	if (ui.pushButton_feed_pause->text() == QStringLiteral("协同暂停回令"))
	{
		ui.pushButton_feed_pause->setText(QStringLiteral("协同继续回令"));
		if (nullptr != m_myfeedsubscriverthread)
		{
			m_myfeedsubscriverthread->slotsimPause();
		}
	}
	else if (ui.pushButton_feed_pause->text() == QStringLiteral("协同继续回令"))
	{
		ui.pushButton_feed_pause->setText(QStringLiteral("协同暂停回令"));
		if (nullptr != m_myfeedsubscriverthread)
		{
			m_myfeedsubscriverthread->slotsimGoOn();
		}
	}
}

void SimNode::slot_feedstop_buttongroup()
{
	if (nullptr != m_myfeedsubscriverthread)
	{
		m_myfeedsubscriverthread->slotsimQuit();
	}
}