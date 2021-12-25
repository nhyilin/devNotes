#include "QtMyTextEdit.h"
#include "SimDataAnalysis.h"

QtMyTextEdit::QtMyTextEdit(QWidget *parent)
	: QTextEdit(parent)
	, m_sample(0)
{
	this->document()->setMaximumBlockCount(200);
}

QtMyTextEdit::~QtMyTextEdit()
{
}

void QtMyTextEdit::setOut(SimMessageDDs sim, QString &message)
{
	message = QStringLiteral("tastID")
		+ QString::fromLocal8Bit(sim.tastID.c_str())
		+ QStringLiteral(" src")
		+ QString::fromLocal8Bit(sim.src.c_str())
		+ QStringLiteral(" dest")
		+ QString::fromLocal8Bit(sim.dest.c_str())
		+ QStringLiteral(" time")
		+ QString::fromLocal8Bit(sim.time.c_str())
		+ QStringLiteral(" 接收时间")
		+ currentDataTime()
		+ QStringLiteral(" step")
		+ QString::fromLocal8Bit(sim.step.c_str())
		+ QStringLiteral(" type")
		+ QString::fromLocal8Bit(sim.type.c_str())
		+ QStringLiteral(" subtype")
		+ QString::fromLocal8Bit(sim.subtype.c_str())
		+ QStringLiteral(" count")
		+ QString::number(sim.count)
		+ QStringLiteral(" 接收的总数量")
		+ QString::number(m_sample++)
		+ QString(" ");
	//this->append(message);
	QString str;
	for (int i = 0; i < sim.data.size(); i++)
	{
		str = str + sim.data[i];
	}
	message = message + str;
}