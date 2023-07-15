//
// Created by 裴奕霖 on 2023/6/9.
//

#ifndef AATOOLS_SRC_MAINWINDOW_H_
#define AATOOLS_SRC_MAINWINDOW_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private:
  Ui::MainWindow *ui;
};

#endif //AATOOLS_SRC_MAINWINDOW_H_
