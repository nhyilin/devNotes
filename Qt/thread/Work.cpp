//
// Created by 裴奕霖 on 2022/11/16.
//

#include "Work.h"
#include <QThread>
Work::Work() {
  thread = new QThread;
  this->moveToThread(thread);
  connect(thread, SIGNAL(finished(),thread,SLOT(quit())));
}