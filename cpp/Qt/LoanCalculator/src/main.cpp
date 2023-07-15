#include <QApplication>
#include <QPushButton>
#include <QStyleFactory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  qApp->setStyle(QStyleFactory::create("Windows")); //将Fusion样式设置为当前样式

  QPushButton button("Hello world!", nullptr);
  button.resize(200, 100);
  button.show();
  return QApplication::exec();
}
