//
// Created by 裴奕霖 on 2023/4/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "pch.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Markdown2LaTeX");

  QMenuBar *menu_bar = new QMenuBar(this);             //创建一个菜单栏
  this->setMenuBar(menu_bar);
  QToolBar *tool_bar = new QToolBar(this);                    //创建一个工具栏
  this->addToolBar(tool_bar);                                            //添加工具栏到MainWindow
  QStatusBar *status_bar = new QStatusBar(this);            //创建一个状态栏
  this->setStatusBar(status_bar);                                        //设置为MainWindow的状态栏

//创建菜单
  QMenu *file_menu = new QMenu("文件(&F)", menu_bar);
  QMenu *edit_menu = new QMenu("编辑(&E)", menu_bar);
  QMenu *help_menu = new QMenu("帮助(&H)", menu_bar);

  //创建动作
  QAction *new_action = new QAction("新建(&N)");
  QAction *open_action = new QAction("打开(&O)");
  QAction *save_action = new QAction("保存(&S)");

  //添加状态栏提示
  new_action->setStatusTip("新建一个文件或项目");
  open_action->setStatusTip("打开一个文件或项目");
  save_action->setStatusTip("保存");

  //添加动作到新建菜单，QAction就会自动变成子菜单
  file_menu->addAction(new_action);
  file_menu->addAction(open_action);
  file_menu->addSeparator();                      //添加菜单分隔符
  file_menu->addAction(save_action);

  //给编辑菜单添加子菜单
  edit_menu->addAction("剪切(&T)");
  //给帮助菜单添加子菜单
  help_menu->addAction("关于(&A)");

  //把菜单添加到菜单栏
  menu_bar->addMenu(file_menu);
  menu_bar->addMenu(edit_menu);
  menu_bar->addMenu(help_menu);

  QObject::connect(open_action, SIGNAL(triggered()), this, SLOT(OpenFile()));
}

void MainWindow::OpenFile() {
  //同时打开多个文件
  QStringList str_path_list =
      QFileDialog::getOpenFileNames(this,
                                    tr("选择md文件"),
                                    tr("/Users/peiyilin/dev/xxxxxx"),
                                    tr("markdown文件(*.md);;其他文件(*.*)"));

  QString str_path = "";
  for (int i = 0; i < str_path_list.size(); i++)
    str_path = str_path_list[i];

  std::string StrPath = str_path.toStdString();
  std::cout << "path=" << StrPath << std::endl;

  HandleMdFile(StrPath);
}

void MainWindow::HandleMdFile(const std::string &file_path) {
  MdFile *mdFile = new MdFile(file_path);

}

MainWindow::~MainWindow() {
  delete ui;
}
