#include "themewidget.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMainWindow window;
    ThemeWidget *widget = new ThemeWidget();
    window.setCentralWidget(widget);
    window.resize(900, 600);
    window.setWindowTitle("电梯健康评估监测");
    window.show();
    return a.exec();
}
