#ifndef simcentre_h__
#define simcentre_h__

#include <QtWidgets/QWidget>
#include "ui_simcentre.h"
#include <QEvent> 
#include <QTextEdit>
#include <QButtonGroup>

class  MyPublisherTimer;
class  MyPubSubscriberThread;
class  MyPublisherFullSpeedThread;
class  MyPublisherRealTimer;
class  MyPublisherRealTimerTest;
class  MyPublisherRealTimerTestTwo;
class SimCentre : public QWidget
{
	Q_OBJECT

public:
	SimCentre(QWidget *parent = Q_NULLPTR);
	void Init();
	void Inconnect();
	virtual void closeEvent(QCloseEvent *event);
public slots:
	void slot_publisher();
	void slot_pause_publisher();
	void slot_stop_publisher();

	void slot_cor_publisher();

	void slot_recv_pubsubscriber();

	void slot_command_pubpublisher();

	void slot_skp_publisher();

	void slot_only_publisher();

private:
	Ui::SimCentreClass ui;
	MyPubSubscriberThread * m_pubsubscriberthread;
	MyPublisherTimer *m_mypublishertimer;
	MyPublisherFullSpeedThread *m_mypublisherfullspeedthread;
	MyPublisherRealTimer* m_mypublisherrealtimer;
	MyPublisherRealTimerTest* m_mypublisherrealtimertest;
	MyPublisherRealTimerTestTwo* m_mypublisherrealtimertesttwo;
	QButtonGroup * m_buttongroup;
};

#endif // simcentre_h__