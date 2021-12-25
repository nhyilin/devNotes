/********************************************************************************
** Form generated from reading UI file 'SimCentreDDS.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMCENTREDDS_H
#define UI_SIMCENTREDDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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

class Ui_SimCentreDDSClass
{
public:
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_publisher;
    QCheckBox *checkBox_only_publisher;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *lineEdit_publishernum;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_node_search;
    QPushButton *pushButton_node_statesearch;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_publisher;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_direct_push;
    QRadioButton *radioButton_fullspeed_push;
    QRadioButton *radioButton_real_push;
    QRadioButton *radioButton_real_pushtest;
    QPushButton *pushButton_advance_publisher;
    QPushButton *pushButton_cor_publisher;
    QPushButton *pushButton_pause_publisher;
    QPushButton *pushButton_stop_publisher;
    QGroupBox *groupBox_;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_recover_snapshoot;
    QtMyTextEdit *textEdit_publisher;

    void setupUi(QWidget *SimCentreDDSClass)
    {
        if (SimCentreDDSClass->objectName().isEmpty())
            SimCentreDDSClass->setObjectName(QString::fromUtf8("SimCentreDDSClass"));
        SimCentreDDSClass->resize(638, 663);
        verticalLayout_6 = new QVBoxLayout(SimCentreDDSClass);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox = new QGroupBox(SimCentreDDSClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_publisher = new QPushButton(groupBox);
        pushButton_publisher->setObjectName(QString::fromUtf8("pushButton_publisher"));

        horizontalLayout_5->addWidget(pushButton_publisher);

        checkBox_only_publisher = new QCheckBox(groupBox);
        checkBox_only_publisher->setObjectName(QString::fromUtf8("checkBox_only_publisher"));

        horizontalLayout_5->addWidget(checkBox_only_publisher);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineEdit_publishernum = new QLineEdit(groupBox);
        lineEdit_publishernum->setObjectName(QString::fromUtf8("lineEdit_publishernum"));

        horizontalLayout_3->addWidget(lineEdit_publishernum);


        verticalLayout_5->addLayout(horizontalLayout_3);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        pushButton_node_search = new QPushButton(groupBox_3);
        pushButton_node_search->setObjectName(QString::fromUtf8("pushButton_node_search"));

        verticalLayout_4->addWidget(pushButton_node_search);

        pushButton_node_statesearch = new QPushButton(groupBox_3);
        pushButton_node_statesearch->setObjectName(QString::fromUtf8("pushButton_node_statesearch"));

        verticalLayout_4->addWidget(pushButton_node_statesearch);


        horizontalLayout_6->addLayout(verticalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_publisher = new QLineEdit(groupBox_3);
        lineEdit_publisher->setObjectName(QString::fromUtf8("lineEdit_publisher"));

        horizontalLayout->addWidget(lineEdit_publisher);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);


        horizontalLayout_6->addLayout(horizontalLayout);


        verticalLayout_5->addWidget(groupBox_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton_direct_push = new QRadioButton(groupBox_4);
        radioButton_direct_push->setObjectName(QString::fromUtf8("radioButton_direct_push"));

        verticalLayout->addWidget(radioButton_direct_push);

        radioButton_fullspeed_push = new QRadioButton(groupBox_4);
        radioButton_fullspeed_push->setObjectName(QString::fromUtf8("radioButton_fullspeed_push"));

        verticalLayout->addWidget(radioButton_fullspeed_push);

        radioButton_real_push = new QRadioButton(groupBox_4);
        radioButton_real_push->setObjectName(QString::fromUtf8("radioButton_real_push"));

        verticalLayout->addWidget(radioButton_real_push);

        radioButton_real_pushtest = new QRadioButton(groupBox_4);
        radioButton_real_pushtest->setObjectName(QString::fromUtf8("radioButton_real_pushtest"));

        verticalLayout->addWidget(radioButton_real_pushtest);

        pushButton_advance_publisher = new QPushButton(groupBox_4);
        pushButton_advance_publisher->setObjectName(QString::fromUtf8("pushButton_advance_publisher"));

        verticalLayout->addWidget(pushButton_advance_publisher);

        pushButton_cor_publisher = new QPushButton(groupBox_4);
        pushButton_cor_publisher->setObjectName(QString::fromUtf8("pushButton_cor_publisher"));

        verticalLayout->addWidget(pushButton_cor_publisher);

        pushButton_pause_publisher = new QPushButton(groupBox_4);
        pushButton_pause_publisher->setObjectName(QString::fromUtf8("pushButton_pause_publisher"));

        verticalLayout->addWidget(pushButton_pause_publisher);

        pushButton_stop_publisher = new QPushButton(groupBox_4);
        pushButton_stop_publisher->setObjectName(QString::fromUtf8("pushButton_stop_publisher"));

        verticalLayout->addWidget(pushButton_stop_publisher);


        verticalLayout_3->addWidget(groupBox_4);

        groupBox_ = new QGroupBox(groupBox);
        groupBox_->setObjectName(QString::fromUtf8("groupBox_"));
        verticalLayout_2 = new QVBoxLayout(groupBox_);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton = new QPushButton(groupBox_);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_recover_snapshoot = new QPushButton(groupBox_);
        pushButton_recover_snapshoot->setObjectName(QString::fromUtf8("pushButton_recover_snapshoot"));

        verticalLayout_2->addWidget(pushButton_recover_snapshoot);


        verticalLayout_3->addWidget(groupBox_);


        horizontalLayout_2->addLayout(verticalLayout_3);

        textEdit_publisher = new QtMyTextEdit(groupBox);
        textEdit_publisher->setObjectName(QString::fromUtf8("textEdit_publisher"));

        horizontalLayout_2->addWidget(textEdit_publisher);


        verticalLayout_5->addLayout(horizontalLayout_2);


        verticalLayout_6->addWidget(groupBox);


        retranslateUi(SimCentreDDSClass);

        QMetaObject::connectSlotsByName(SimCentreDDSClass);
    } // setupUi

    void retranslateUi(QWidget *SimCentreDDSClass)
    {
        SimCentreDDSClass->setWindowTitle(QApplication::translate("SimCentreDDSClass", "SimCentreDDS", nullptr));
        groupBox->setTitle(QApplication::translate("SimCentreDDSClass", "\345\215\217\345\220\214\346\216\247\345\210\266", nullptr));
        pushButton_publisher->setText(QApplication::translate("SimCentreDDSClass", "\345\274\200\345\247\213", nullptr));
        checkBox_only_publisher->setText(QApplication::translate("SimCentreDDSClass", "\345\217\252\345\217\221\351\200\201", nullptr));
        label_5->setText(QApplication::translate("SimCentreDDSClass", "\345\217\221\351\200\201\346\225\260\351\207\217", nullptr));
        groupBox_3->setTitle(QApplication::translate("SimCentreDDSClass", "\346\237\245\350\257\242", nullptr));
        pushButton_node_search->setText(QApplication::translate("SimCentreDDSClass", "\346\237\245\350\257\242\350\212\202\347\202\271\346\255\245\351\225\277\346\214\207\344\273\244", nullptr));
        pushButton_node_statesearch->setText(QApplication::translate("SimCentreDDSClass", "\346\237\245\350\257\242\350\212\202\347\202\271\347\212\266\346\200\201\346\214\207\344\273\244", nullptr));
        label->setText(QApplication::translate("SimCentreDDSClass", "\346\255\245\351\225\277", nullptr));
        label_4->setText(QApplication::translate("SimCentreDDSClass", "\346\257\253\347\247\222", nullptr));
        groupBox_4->setTitle(QApplication::translate("SimCentreDDSClass", "\345\215\217\345\220\214\346\216\247\345\210\266", nullptr));
        radioButton_direct_push->setText(QApplication::translate("SimCentreDDSClass", "\347\233\264\346\216\245\346\216\250\350\277\233", nullptr));
        radioButton_fullspeed_push->setText(QApplication::translate("SimCentreDDSClass", "\345\205\250\351\200\237\346\216\250\350\277\233", nullptr));
        radioButton_real_push->setText(QApplication::translate("SimCentreDDSClass", "\345\256\236\346\227\266\346\216\250\350\277\2331", nullptr));
        radioButton_real_pushtest->setText(QApplication::translate("SimCentreDDSClass", "\345\256\236\346\227\266\346\216\250\350\277\2332", nullptr));
        pushButton_advance_publisher->setText(QApplication::translate("SimCentreDDSClass", "\345\215\217\345\220\214\346\216\250\350\277\233\346\214\207\344\273\244", nullptr));
        pushButton_cor_publisher->setText(QApplication::translate("SimCentreDDSClass", "\345\215\217\345\220\214\345\274\200\345\247\213\346\214\207\344\273\244", nullptr));
        pushButton_pause_publisher->setText(QApplication::translate("SimCentreDDSClass", "\345\215\217\345\220\214\346\232\202\345\201\234\346\214\207\344\273\244", nullptr));
        pushButton_stop_publisher->setText(QApplication::translate("SimCentreDDSClass", "\345\215\217\345\220\214\347\273\210\346\255\242\346\214\207\344\273\244", nullptr));
        groupBox_->setTitle(QApplication::translate("SimCentreDDSClass", "\350\267\263\350\275\254", nullptr));
        pushButton->setText(QApplication::translate("SimCentreDDSClass", "\344\277\235\345\255\230\350\212\202\347\202\271\345\277\253\347\205\247\346\214\207\344\273\244", nullptr));
        pushButton_recover_snapshoot->setText(QApplication::translate("SimCentreDDSClass", "\346\201\242\345\244\215\350\212\202\347\202\271\345\277\253\347\205\247\346\214\207\344\273\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimCentreDDSClass: public Ui_SimCentreDDSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMCENTREDDS_H
