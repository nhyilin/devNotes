//
// Created by 裴奕霖 on 2022/11/18.
//

#include "MyThread.h"

#include <QDebug>
MyThread::MyThread(QObject *parent) : QThread(parent) { stopped = false; }
void MyThread::run() {
    qreal i = 0;
    while (!stopped) {
        qDebug() << QString("in MyThread: ") << i;
        msleep(1000);
        i++;
    }

}
void MyThread::stop() { stopped = false; }