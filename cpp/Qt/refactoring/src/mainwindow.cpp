//
// Created by 裴奕霖 on 2022/5/27.
//

#include "mainwindow.h"

#include <QMessageBox>
#include <QTimer>
#include <QtCore>

#include "seven/DataManager.h"
#include "seven/Student.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow) {
    srand((unsigned)time(nullptr));
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myslot()));

    ui->pushButton->setFocus();
    ui->pushButton->setDefault(true);
    // 设置完后自动调用其eventFilter函数
    ui->textEdit->installEventFilter(this);
    ui->textEdit_4->setPlainText("45");
    this->setWindowIcon(QIcon(":./resource/favicon.ico"));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::myslot() {
    QMessageBox::warning(this, "timer", QObject::trUtf8("时间到!"));
    timer->stop();
}

void MainWindow::on_pushButton_clicked() {
    QString str = ui->textEdit->toPlainText();
    bool OK;
    int num = str.toInt(&OK, 10);
    num *= 1000;
    timer->start(num);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event) {
    if (target == ui->textEdit) {
        if (event->type() == QEvent::KeyPress) {  // 回车键
            QKeyEvent *k = dynamic_cast<QKeyEvent *>(event);

            if (k->key() == Qt::Key_Return) {
                on_pushButton_clicked();  // 需要响应的函数事件，以这里的按钮为例
                return true;
            }
        }
    }
    return QWidget::eventFilter(target, event);
}

void MainWindow::on_pushButton_2_clicked() {
    int total = ui->textEdit_4->toPlainText().toInt();
    int selected = ui->textEdit_5->toPlainText().toInt();
    DataManager::GetInstance()->generate(total);
    std::vector<Student> person;
    //    DataManager::GetInstance()->getPersons(person);

    std::vector<Student> selectedPerson;
    for (int i = 0; i < selected; ++i) {
        int showed = getRandomNum(total);
        selectedPerson.push_back(person.at(showed));
    }

    ui->textEdit_2->clear();
    for (auto &i : selectedPerson) {
        ui->textEdit_2->append(QString::number(i.id));
    }
}

int MainWindow::getRandomNum(int total) { return (rand() % total); }

void MainWindow::checkConflict(std::vector<Student> &selecetdPerson) {
    //    DataManager::GetInstance()->getPersons(std::vector<Student>&
    //    selectedPerson);
}
void MainWindow::on_StartThread_btn_clicked() {
    thread.start();
    ui->StartThread_btn->setEnabled(false);
    ui->EndThread_btn->setEnabled(true);
}
void MainWindow::on_EndThread_btn_clicked() {
    if (thread.isRunning()) {
        thread.stop();
        ui->StartThread_btn->setEnabled(true);
        ui->EndThread_btn->setEnabled(false);
    }
}

void MainWindow::on_StartThread_btn_2_clicked() {
    Controller *controller_ = new Controller();
}
void MainWindow::on_EndThread_btn_2_clicked() {}
