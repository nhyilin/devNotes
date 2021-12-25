#pragma once

#include <QTextEdit>
#include "SimMessageDDs.h"
class QtMyTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	QtMyTextEdit(QWidget *parent);
	~QtMyTextEdit();
	void setOut(SimMessageDDs sim,QString &message);
	uint32_t m_sample;
};
