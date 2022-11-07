/********************************************************************************
** Form generated from reading UI file 'logger.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGGER_H
#define UI_LOGGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loggerClass
{
public:

    void setupUi(QWidget *loggerClass)
    {
        if (loggerClass->objectName().isEmpty())
            loggerClass->setObjectName(QStringLiteral("loggerClass"));
        loggerClass->resize(600, 400);

        retranslateUi(loggerClass);

        QMetaObject::connectSlotsByName(loggerClass);
    } // setupUi

    void retranslateUi(QWidget *loggerClass)
    {
        loggerClass->setWindowTitle(QApplication::translate("loggerClass", "logger", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loggerClass: public Ui_loggerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGGER_H
