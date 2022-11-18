#include "Work.h"
#include "widget.h"
#include <QApplication>
#include <QPushButton>
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  //  QPushButton button("Hello world!", nullptr);
  //  button.resize(200, 100);
  //  button.show();
  //  Widget myWidget;
  //  myWidget.show();
  Work work;
  return QApplication::exec();
}
