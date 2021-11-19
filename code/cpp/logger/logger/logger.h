#ifndef LOGGER_H
#define LOGGER_H

#include <QtWidgets/QWidget>
#include "ui_logger.h"

class logger : public QWidget
{
	Q_OBJECT

public:
	logger(QWidget *parent = 0);
	~logger();

private:
	Ui::loggerClass ui;
};

#endif // LOGGER_H
