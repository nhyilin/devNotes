#pragma once

#include <QtWidgets/QWidget>
#include "ui_SimNode.h"
#include <QButtonGroup>
class  MyFeedSubscriverThread;
class  MySubscriberThread;

class SimNode : public QWidget
{
	Q_OBJECT

public:
	SimNode(QWidget *parent = Q_NULLPTR);
	void init();
	void inconnect();
	virtual void closeEvent(QCloseEvent *event);
public slots:
	void slot_subscriber();
	void slot_only_subscriber();
	void slot_recv_subsubscriber();
	void slot_command_subpublisher();
	void slot_feedbutton_group(int id);
	void slot_feedpause_buttongroup();
	void slot_feedstop_buttongroup();
private:
	QButtonGroup * m_feedbackbuttongroup;
	MyFeedSubscriverThread *m_myfeedsubscriverthread;
	MySubscriberThread *m_mysubscriberthread;
	Ui::SimNodeClass ui;
};
