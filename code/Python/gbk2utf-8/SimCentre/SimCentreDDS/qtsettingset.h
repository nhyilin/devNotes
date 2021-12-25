#ifndef qtsettingset_h__
#define qtsettingset_h__

#include <QObject>
#include <SimMessageDDs.h>
class QSettings;
class QtSettingSet : public QObject
{
	Q_OBJECT

public:
	QtSettingSet(QObject *parent = nullptr);
	~QtSettingSet();
	void readConfig(QString group,SimMessageDDs& dds);
	void writeConfig(QString group,SimMessageDDs dds);
	void writeConfig(QString group,QString key,QString value);
	void readConfig(QString group, QString key, QString& value);
	static QtSettingSet* instance();
	static void destroy();
private:
	static QtSettingSet* m_pInstance;
	QSettings *settings;
};
#endif // qtsettingset_h__