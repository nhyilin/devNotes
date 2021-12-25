
#include "simcentre.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimCentre w;
	w.show();
	return a.exec();
}
