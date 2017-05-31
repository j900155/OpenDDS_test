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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *Topic1;
    QLineEdit *Topic1Text;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *Topic2;
    QLineEdit *Topic2Text;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *Topic4;
    QLineEdit *Topic4Text;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *Topic3;
    QLineEdit *Topic3Text;
    QPushButton *Send;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 492);
        horizontalLayoutWidget = new QWidget(Dialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 10, 311, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Topic1 = new QRadioButton(horizontalLayoutWidget);
        Topic1->setObjectName(QString::fromUtf8("Topic1"));

        horizontalLayout->addWidget(Topic1);

        Topic1Text = new QLineEdit(horizontalLayoutWidget);
        Topic1Text->setObjectName(QString::fromUtf8("Topic1Text"));

        horizontalLayout->addWidget(Topic1Text);

        horizontalLayoutWidget_2 = new QWidget(Dialog);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 100, 311, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Topic2 = new QRadioButton(horizontalLayoutWidget_2);
        Topic2->setObjectName(QString::fromUtf8("Topic2"));

        horizontalLayout_2->addWidget(Topic2);

        Topic2Text = new QLineEdit(horizontalLayoutWidget_2);
        Topic2Text->setObjectName(QString::fromUtf8("Topic2Text"));

        horizontalLayout_2->addWidget(Topic2Text);

        horizontalLayoutWidget_3 = new QWidget(Dialog);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 280, 311, 80));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        Topic4 = new QRadioButton(horizontalLayoutWidget_3);
        Topic4->setObjectName(QString::fromUtf8("Topic4"));

        horizontalLayout_3->addWidget(Topic4);

        Topic4Text = new QLineEdit(horizontalLayoutWidget_3);
        Topic4Text->setObjectName(QString::fromUtf8("Topic4Text"));

        horizontalLayout_3->addWidget(Topic4Text);

        horizontalLayoutWidget_4 = new QWidget(Dialog);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(20, 190, 311, 80));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        Topic3 = new QRadioButton(horizontalLayoutWidget_4);
        Topic3->setObjectName(QString::fromUtf8("Topic3"));

        horizontalLayout_4->addWidget(Topic3);

        Topic3Text = new QLineEdit(horizontalLayoutWidget_4);
        Topic3Text->setObjectName(QString::fromUtf8("Topic3Text"));

        horizontalLayout_4->addWidget(Topic3Text);

        Send = new QPushButton(Dialog);
        Send->setObjectName(QString::fromUtf8("Send"));
        Send->setGeometry(QRect(260, 420, 95, 31));

        retranslateUi(Dialog);
        QObject::connect(Send, SIGNAL(clicked()), Dialog, SLOT(SendButtonClicked()));
        QObject::connect(Topic1, SIGNAL(clicked(bool)), Dialog, SLOT(Topic1Enable()));
        QObject::connect(Topic2, SIGNAL(clicked(bool)), Dialog, SLOT(Topic2Enable()));
        QObject::connect(Topic3, SIGNAL(clicked(bool)), Dialog, SLOT(Topic3Enable()));
        QObject::connect(Topic4, SIGNAL(clicked(bool)), Dialog, SLOT(Topic4Enable()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        Topic1->setText(QApplication::translate("Dialog", "Topic1", 0, QApplication::UnicodeUTF8));
        Topic2->setText(QApplication::translate("Dialog", "Topic2", 0, QApplication::UnicodeUTF8));
        Topic4->setText(QApplication::translate("Dialog", "Topic4", 0, QApplication::UnicodeUTF8));
        Topic3->setText(QApplication::translate("Dialog", "Topic3", 0, QApplication::UnicodeUTF8));
        Send->setText(QApplication::translate("Dialog", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi
};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UI_H
