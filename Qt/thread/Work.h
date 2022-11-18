//
// Created by 裴奕霖 on 2022/11/16.
//

#ifndef THREAD__WORK_H_
#define THREAD__WORK_H_
#include <QObject>
class Work : public QObject {
  Q_OBJECT
 public:
  Work();
  ~Work();

 private:
  QThread *thread;
};

#endif//THREAD__WORK_H_
