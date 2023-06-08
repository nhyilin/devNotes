//
// Created by 裴奕霖 on 2023/4/21.
//

#ifndef MARKDOWN2LATEX__MAINWINDOW_H_
#define MARKDOWN2LATEX__MAINWINDOW_H_

#include <QWidget>
#include "MdFile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

//  MdFile *mdFile;


 private slots:
  void OpenFile();
  void HandleMdFile(const std::string &file_path);

 private:
  Ui::MainWindow *ui;
};

#endif //MARKDOWN2LATEX__MAINWINDOW_H_
