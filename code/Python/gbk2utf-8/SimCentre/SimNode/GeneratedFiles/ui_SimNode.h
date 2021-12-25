/********************************************************************************
** Form generated from reading UI file 'SimNode.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMNODE_H
#define UI_SIMNODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtMyTextEdit.h"

QT_BEGIN_NAMESPACE

class Ui_SimNodeClass
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_13;
    QComboBox *comboBox_subscriber;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_subscriber;
    QCheckBox *checkBox_only_subscriber;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_12;
    QPushButton *pushButton_feed_nodesearch;
    QPushButton *pushButton_feed_nodesearchstate;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButton_sub_init;
    QRadioButton *radioButton_sub_run;
    QVBoxLayout *verticalLayout_11;
    QRadioButton *radioButton_sub_pause;
    QRadioButton *radioButton_sub_error;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *lineEdit_subscriber_step;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pushButton_feed_run;
    QCheckBox *checkBox_feedbackalway;
    QPushButton *pushButton_feed_pause;
    QPushButton *pushButton_feed_stop;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pushButton_feed_snapshoot;
    QtMyTextEdit *textEdit_subscriber;

    void setupUi(QWidget *SimNodeClass)
    {
        if (SimNodeClass->objectName().isEmpty())
            SimNodeClass->setObjectName(QString::fromUtf8("SimNodeClass"));
        SimNodeClass->resize(605, 552);
        verticalLayout = new QVBoxLayout(SimNodeClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(SimNodeClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_13 = new QVBoxLayout(groupBox_2);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        comboBox_subscriber = new QComboBox(groupBox_2);
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->addItem(QString());
        comboBox_subscriber->setObjectName(QString::fromUtf8("comboBox_subscriber"));

        verticalLayout_13->addWidget(comboBox_subscriber);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pushButton_subscriber = new QPushButton(groupBox_2);
        pushButton_subscriber->setObjectName(QString::fromUtf8("pushButton_subscriber"));

        horizontalLayout_9->addWidget(pushButton_subscriber);

        checkBox_only_subscriber = new QCheckBox(groupBox_2);
        checkBox_only_subscriber->setObjectName(QString::fromUtf8("checkBox_only_subscriber"));

        horizontalLayout_9->addWidget(checkBox_only_subscriber);


        verticalLayout_13->addLayout(horizontalLayout_9);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_6);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        pushButton_feed_nodesearch = new QPushButton(groupBox_6);
        pushButton_feed_nodesearch->setObjectName(QString::fromUtf8("pushButton_feed_nodesearch"));

        verticalLayout_12->addWidget(pushButton_feed_nodesearch);

        pushButton_feed_nodesearchstate = new QPushButton(groupBox_6);
        pushButton_feed_nodesearchstate->setObjectName(QString::fromUtf8("pushButton_feed_nodesearchstate"));

        verticalLayout_12->addWidget(pushButton_feed_nodesearchstate);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        radioButton_sub_init = new QRadioButton(groupBox_6);
        radioButton_sub_init->setObjectName(QString::fromUtf8("radioButton_sub_init"));

        verticalLayout_6->addWidget(radioButton_sub_init);

        radioButton_sub_run = new QRadioButton(groupBox_6);
        radioButton_sub_run->setObjectName(QString::fromUtf8("radioButton_sub_run"));

        verticalLayout_6->addWidget(radioButton_sub_run);


        horizontalLayout_7->addLayout(verticalLayout_6);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        radioButton_sub_pause = new QRadioButton(groupBox_6);
        radioButton_sub_pause->setObjectName(QString::fromUtf8("radioButton_sub_pause"));

        verticalLayout_11->addWidget(radioButton_sub_pause);

        radioButton_sub_error = new QRadioButton(groupBox_6);
        radioButton_sub_error->setObjectName(QString::fromUtf8("radioButton_sub_error"));

        verticalLayout_11->addWidget(radioButton_sub_error);


        horizontalLayout_7->addLayout(verticalLayout_11);


        verticalLayout_12->addLayout(horizontalLayout_7);


        horizontalLayout_10->addLayout(verticalLayout_12);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(groupBox_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        lineEdit_subscriber_step = new QLineEdit(groupBox_6);
        lineEdit_subscriber_step->setObjectName(QString::fromUtf8("lineEdit_subscriber_step"));

        horizontalLayout_2->addWidget(lineEdit_subscriber_step);


        verticalLayout_10->addLayout(horizontalLayout_2);


        horizontalLayout_10->addLayout(verticalLayout_10);

        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_10->addWidget(label_3);


        verticalLayout_13->addWidget(groupBox_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        groupBox_7 = new QGroupBox(groupBox_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        verticalLayout_7 = new QVBoxLayout(groupBox_7);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        pushButton_feed_run = new QPushButton(groupBox_7);
        pushButton_feed_run->setObjectName(QString::fromUtf8("pushButton_feed_run"));

        verticalLayout_7->addWidget(pushButton_feed_run);

        checkBox_feedbackalway = new QCheckBox(groupBox_7);
        checkBox_feedbackalway->setObjectName(QString::fromUtf8("checkBox_feedbackalway"));

        verticalLayout_7->addWidget(checkBox_feedbackalway);

        pushButton_feed_pause = new QPushButton(groupBox_7);
        pushButton_feed_pause->setObjectName(QString::fromUtf8("pushButton_feed_pause"));

        verticalLayout_7->addWidget(pushButton_feed_pause);

        pushButton_feed_stop = new QPushButton(groupBox_7);
        pushButton_feed_stop->setObjectName(QString::fromUtf8("pushButton_feed_stop"));

        verticalLayout_7->addWidget(pushButton_feed_stop);


        verticalLayout_9->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(groupBox_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        verticalLayout_8 = new QVBoxLayout(groupBox_8);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        pushButton_feed_snapshoot = new QPushButton(groupBox_8);
        pushButton_feed_snapshoot->setObjectName(QString::fromUtf8("pushButton_feed_snapshoot"));

        verticalLayout_8->addWidget(pushButton_feed_snapshoot);


        verticalLayout_9->addWidget(groupBox_8);


        horizontalLayout_8->addLayout(verticalLayout_9);

        textEdit_subscriber = new QtMyTextEdit(groupBox_2);
        textEdit_subscriber->setObjectName(QString::fromUtf8("textEdit_subscriber"));

        horizontalLayout_8->addWidget(textEdit_subscriber);


        verticalLayout_13->addLayout(horizontalLayout_8);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(SimNodeClass);

        QMetaObject::connectSlotsByName(SimNodeClass);
    } // setupUi

    void retranslateUi(QWidget *SimNodeClass)
    {
        SimNodeClass->setWindowTitle(QApplication::translate("SimNodeClass", "SimNode", nullptr));
        groupBox_2->setTitle(QApplication::translate("SimNodeClass", "\350\212\202\347\202\271", nullptr));
        comboBox_subscriber->setItemText(0, QApplication::translate("SimNodeClass", "01", nullptr));
        comboBox_subscriber->setItemText(1, QApplication::translate("SimNodeClass", "02", nullptr));
        comboBox_subscriber->setItemText(2, QApplication::translate("SimNodeClass", "03", nullptr));
        comboBox_subscriber->setItemText(3, QApplication::translate("SimNodeClass", "04", nullptr));
        comboBox_subscriber->setItemText(4, QApplication::translate("SimNodeClass", "05", nullptr));
        comboBox_subscriber->setItemText(5, QApplication::translate("SimNodeClass", "06", nullptr));
        comboBox_subscriber->setItemText(6, QApplication::translate("SimNodeClass", "07", nullptr));
        comboBox_subscriber->setItemText(7, QApplication::translate("SimNodeClass", "08", nullptr));
        comboBox_subscriber->setItemText(8, QApplication::translate("SimNodeClass", "09", nullptr));
        comboBox_subscriber->setItemText(9, QApplication::translate("SimNodeClass", "10", nullptr));

        pushButton_subscriber->setText(QApplication::translate("SimNodeClass", "\345\274\200\345\247\213", nullptr));
        checkBox_only_subscriber->setText(QApplication::translate("SimNodeClass", "\345\217\252\346\216\245\346\224\266", nullptr));
        groupBox_6->setTitle(QApplication::translate("SimNodeClass", "\346\237\245\350\257\242\345\217\215\351\246\210", nullptr));
        pushButton_feed_nodesearch->setText(QApplication::translate("SimNodeClass", "\345\217\215\351\246\210\350\212\202\347\202\271\346\255\245\351\225\277\346\266\210\346\201\257", nullptr));
        pushButton_feed_nodesearchstate->setText(QApplication::translate("SimNodeClass", "\345\217\215\351\246\210\350\212\202\347\202\271\347\212\266\346\200\201\346\266\210\346\201\257", nullptr));
        radioButton_sub_init->setText(QApplication::translate("SimNodeClass", "\345\210\235\345\247\213\346\200\201", nullptr));
        radioButton_sub_run->setText(QApplication::translate("SimNodeClass", "\350\277\220\350\241\214\346\200\201", nullptr));
        radioButton_sub_pause->setText(QApplication::translate("SimNodeClass", "\346\232\202\345\201\234\346\200\201", nullptr));
        radioButton_sub_error->setText(QApplication::translate("SimNodeClass", "\346\225\205\351\232\234\346\200\201", nullptr));
        label_6->setText(QApplication::translate("SimNodeClass", "\346\255\245\351\225\277", nullptr));
        label_3->setText(QApplication::translate("SimNodeClass", "\346\257\253\347\247\222", nullptr));
        groupBox_7->setTitle(QApplication::translate("SimNodeClass", "\345\215\217\345\220\214\346\216\247\345\210\266\345\217\215\351\246\210", nullptr));
        pushButton_feed_run->setText(QApplication::translate("SimNodeClass", "\345\215\217\345\220\214\346\216\250\350\277\233\345\233\236\344\273\244", nullptr));
        checkBox_feedbackalway->setText(QApplication::translate("SimNodeClass", "\350\207\252\345\212\250", nullptr));
        pushButton_feed_pause->setText(QApplication::translate("SimNodeClass", "\345\215\217\345\220\214\346\232\202\345\201\234\345\233\236\344\273\244", nullptr));
        pushButton_feed_stop->setText(QApplication::translate("SimNodeClass", "\345\215\217\345\220\214\347\273\210\346\255\242\345\233\236\344\273\244", nullptr));
        groupBox_8->setTitle(QApplication::translate("SimNodeClass", "\350\267\263\350\275\254\345\217\215\351\246\210", nullptr));
        pushButton_feed_snapshoot->setText(QApplication::translate("SimNodeClass", "\345\217\215\351\246\210\350\212\202\347\202\271\345\277\253\347\205\247\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimNodeClass: public Ui_SimNodeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMNODE_H
