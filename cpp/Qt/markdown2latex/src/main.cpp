
#include "pch.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  InitLog::Init(InitLog::LogPath);
  LOG_TRACE << InitLog::InitFile;

  MainWindow *mywidget=new MainWindow();
  mywidget->show();
  return QApplication::exec();
}
