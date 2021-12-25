#include "SimCentreDDS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimCentreDDS w;
	w.show();
	return a.exec();
}
