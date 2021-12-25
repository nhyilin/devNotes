#ifndef simplelog_h__
#define simplelog_h__

#include <QObject>
#include "SimMessageDDs.h"

class SimpleLog : public QObject
{
	Q_OBJECT

private:
	SimpleLog(QObject *parent = nullptr);
	~SimpleLog();
public:
	void writelog(SimMessageDDs simdds);
	QString readlog();
	void writelog();
	void writelogStartTime();
	void wrtielogEndTime();
	static SimpleLog* instance();
	static void destroy();
private:
	static SimpleLog * m_pInstance;
};
#endif // simplelog_h__