#include "SimNode.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimNode w;
	w.show();
	return a.exec();
}
