//
// Created by 裴奕霖 on 2022/11/18.
//

#ifndef REFACTORING_SRC_CONTROLLER_H_
#define REFACTORING_SRC_CONTROLLER_H_

#include "../StdAfx.h"
#include "Worker.h"
class Controller : public QObject {
    Q_OBJECT
    QThread workerThread;

   public:
    Controller() {
        Worker *worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, SIGNAL(finished()), worker,
                SLOT(deleterLater()));
        connect(this, SIGNAL(operate(QString)), worker, SLOT(doWork()));
        connect(worker, SIGNAL(resultReady(QString)), this,
                SLOT(handleResults(QString)));

        workerThread.start();
    }
    ~Controller() {
        workerThread.quit();
        workerThread.wait();
    }
   public slots:
    void handleResults(const QString &){};
   signals:
    void operate(const QString &);
};

#endif  // REFACTORING_SRC_CONTROLLER_H_
