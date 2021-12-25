#include "SimDataAnalysis.h"
#include <QTime>
#include <QDateTime>

QString currentTime()
{
	return QString("%1:%2:%3:%4").arg(QTime::currentTime().hour())
		.arg(QTime::currentTime().minute())
		.arg(QTime::currentTime().second())
		.arg(QTime::currentTime().minute());
}

QString currentDataTime()
{
	QDateTime data = QDateTime::currentDateTime();
	QString timer = data.toString("yyyy-MM-dd hh:mm:ss.zzz");
	return timer;
}

QString currentData()
{
	QDateTime data = QDateTime::currentDateTime();
	QString timer = data.toString("yyyy-MM-dd");
	return timer;
}