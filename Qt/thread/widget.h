//
// Created by 裴奕霖 on 2022/11/16.
//

#ifndef THREAD__WIDGET_H_
#define THREAD__WIDGET_H_

#include <QPushButton>
#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget() override;

 private:
  Ui::Widget *ui;
  QPushButton Btn_1;

 signals:

 public slots:
  void slots_1();
};

#endif//THREAD__WIDGET_H_
