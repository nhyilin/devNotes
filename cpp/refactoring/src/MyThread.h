//
// Created by 裴奕霖 on 2022/11/18.
//

#ifndef REFACTORING_SRC_MYTHREAD_H_
#define REFACTORING_SRC_MYTHREAD_H_
#include "../StdAfx.h"

class MyThread : public QThread {
    Q_OBJECT
   public:
    explicit MyThread(QObject* parent = 0);
    void stop();

   protected:
    void run() override;

   private:
    volatile bool stopped;
};

#endif  // REFACTORING_SRC_MYTHREAD_H_
