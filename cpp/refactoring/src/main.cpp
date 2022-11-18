#include <QCoreApplication>
#include <QDebug>
#include <QApplication>
#include "./mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();
    return QCoreApplication::exec();
}
