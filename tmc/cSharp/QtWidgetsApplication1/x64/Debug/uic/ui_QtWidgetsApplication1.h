/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplication1.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION1_H
#define UI_QTWIDGETSAPPLICATION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplication1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsApplication1Class)
    {
        if (QtWidgetsApplication1Class->objectName().isEmpty())
            QtWidgetsApplication1Class->setObjectName(QStringLiteral("QtWidgetsApplication1Class"));
        QtWidgetsApplication1Class->resize(600, 400);
        menuBar = new QMenuBar(QtWidgetsApplication1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtWidgetsApplication1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtWidgetsApplication1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtWidgetsApplication1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtWidgetsApplication1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtWidgetsApplication1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtWidgetsApplication1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtWidgetsApplication1Class->setStatusBar(statusBar);

        retranslateUi(QtWidgetsApplication1Class);

        QMetaObject::connectSlotsByName(QtWidgetsApplication1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsApplication1Class)
    {
        QtWidgetsApplication1Class->setWindowTitle(QApplication::translate("QtWidgetsApplication1Class", "QtWidgetsApplication1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplication1Class: public Ui_QtWidgetsApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION1_H
