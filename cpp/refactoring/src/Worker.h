//
// Created by 裴奕霖 on 2022/11/18.
//

#ifndef REFACTORING_SRC_WORKER_H_
#define REFACTORING_SRC_WORKER_H_
//
// Created by 裴奕霖 on 2022/11/18.
//
#include "../StdAfx.h"
#include "Controller.h"
class Worker : public QObject {
    Q_OBJECT
   public slots:
    void doWork(const QString &parameter) {
        QString result;
        emit resultReady(result);
    }
   signals:
    void resultReady(const QString &result);
};

#endif  // REFACTORING_SRC_WORKER_H_
