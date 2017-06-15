/********************************************************************************
** Form generated from reading UI file 'Ui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UI_H
#define UI_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Topic1Text;
    QLabel *label_8;
    QLabel *time1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *Topic2Text;
    QLabel *label_6;
    QLabel *time2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *Topic3Text;
    QLabel *label_7;
    QLabel *time3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *Topic4Text;
    QLabel *label_5;
    QLabel *time4;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(646, 492);
        verticalLayoutWidget = new QWidget(Dialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 601, 441));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        Topic1Text = new QLineEdit(verticalLayoutWidget);
        Topic1Text->setObjectName(QString::fromUtf8("Topic1Text"));

        horizontalLayout->addWidget(Topic1Text);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout->addWidget(label_8);

        time1 = new QLabel(verticalLayoutWidget);
        time1->setObjectName(QString::fromUtf8("time1"));

        horizontalLayout->addWidget(time1);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        Topic2Text = new QLineEdit(verticalLayoutWidget);
        Topic2Text->setObjectName(QString::fromUtf8("Topic2Text"));

        horizontalLayout_2->addWidget(Topic2Text);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        time2 = new QLabel(verticalLayoutWidget);
        time2->setObjectName(QString::fromUtf8("time2"));

        horizontalLayout_2->addWidget(time2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        Topic3Text = new QLineEdit(verticalLayoutWidget);
        Topic3Text->setObjectName(QString::fromUtf8("Topic3Text"));

        horizontalLayout_4->addWidget(Topic3Text);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        time3 = new QLabel(verticalLayoutWidget);
        time3->setObjectName(QString::fromUtf8("time3"));

        horizontalLayout_4->addWidget(time3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        Topic4Text = new QLineEdit(verticalLayoutWidget);
        Topic4Text->setObjectName(QString::fromUtf8("Topic4Text"));

        horizontalLayout_3->addWidget(Topic4Text);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        time4 = new QLabel(verticalLayoutWidget);
        time4->setObjectName(QString::fromUtf8("time4"));

        horizontalLayout_3->addWidget(time4);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "Topic1", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Dialog", "Time", 0, QApplication::UnicodeUTF8));
        time1->setText(QApplication::translate("Dialog", "00:00", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "Topic2", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Dialog", "Time", 0, QApplication::UnicodeUTF8));
        time2->setText(QApplication::translate("Dialog", "00:00", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "Topic3", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Dialog", "Time", 0, QApplication::UnicodeUTF8));
        time3->setText(QApplication::translate("Dialog", "00:00", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "Topic4", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog", "Time", 0, QApplication::UnicodeUTF8));
        time4->setText(QApplication::translate("Dialog", "00:00", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_H
