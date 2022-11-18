//
// Created by 裴奕霖 on 2022/5/27.
//

#pragma once

#include <QKeyEvent>
#include <QWidget>

#include "Controller.h"
#include "MyThread.h"
#include "Student.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

   private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void myslot();
    void checkConflict(std::vector<Student> &);
    // 线程demo槽函数，方式一
    void on_StartThread_btn_clicked();
    void on_EndThread_btn_clicked();
    // 线程demo槽函数，方式二
    void on_StartThread_btn_2_clicked();
    void on_EndThread_btn_2_clicked();


   private:
    Ui::MainWindow *ui;
    QTimer *timer;
    static int getRandomNum(int total);
    MyThread thread;

    Controller *controller_;

   protected:
    bool eventFilter(QObject *target, QEvent *event) override;  // 事件过滤器
};
