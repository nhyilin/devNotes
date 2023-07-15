#include <QApplication>
#include <QPushButton>
#include "src/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
//  QPushButton button("Hello world!", nullptr);
//  button.resize(200, 100);
//  button.show();
  MainWindow mWindow;
  mWindow.show();
  return QApplication::exec();
}
