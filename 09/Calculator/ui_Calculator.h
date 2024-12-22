/********************************************************************************
** Form generated from reading UI file 'Calculator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *Button_0;
    QPushButton *Button_5;
    QPushButton *Button_7;
    QPushButton *Button_9;
    QPushButton *Button_4;
    QPushButton *Button_2;
    QPushButton *Button_Add;
    QPushButton *Button_8;
    QPushButton *Button_3;
    QPushButton *Button_Clear;
    QPushButton *Button_Div;
    QPushButton *Button_6;
    QPushButton *Button_Sub;
    QPushButton *Button_1;
    QPushButton *Button_Mul;
    QPushButton *Button_Result;
    QTextEdit *Num_1;
    QTextEdit *Num_2;
    QTextEdit *Result;
    QLabel *ArithmeticLabel;
    QLabel *ResultLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(412, 325);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 70, 371, 211));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        Button_0 = new QPushButton(gridLayoutWidget);
        Button_0->setObjectName(QString::fromUtf8("Button_0"));

        gridLayout_2->addWidget(Button_0, 3, 1, 1, 1);

        Button_5 = new QPushButton(gridLayoutWidget);
        Button_5->setObjectName(QString::fromUtf8("Button_5"));

        gridLayout_2->addWidget(Button_5, 1, 1, 1, 1);

        Button_7 = new QPushButton(gridLayoutWidget);
        Button_7->setObjectName(QString::fromUtf8("Button_7"));

        gridLayout_2->addWidget(Button_7, 0, 0, 1, 1);

        Button_9 = new QPushButton(gridLayoutWidget);
        Button_9->setObjectName(QString::fromUtf8("Button_9"));

        gridLayout_2->addWidget(Button_9, 0, 2, 1, 1);

        Button_4 = new QPushButton(gridLayoutWidget);
        Button_4->setObjectName(QString::fromUtf8("Button_4"));

        gridLayout_2->addWidget(Button_4, 1, 0, 1, 1);

        Button_2 = new QPushButton(gridLayoutWidget);
        Button_2->setObjectName(QString::fromUtf8("Button_2"));

        gridLayout_2->addWidget(Button_2, 2, 1, 1, 1);

        Button_Add = new QPushButton(gridLayoutWidget);
        Button_Add->setObjectName(QString::fromUtf8("Button_Add"));

        gridLayout_2->addWidget(Button_Add, 0, 3, 1, 1);

        Button_8 = new QPushButton(gridLayoutWidget);
        Button_8->setObjectName(QString::fromUtf8("Button_8"));

        gridLayout_2->addWidget(Button_8, 0, 1, 1, 1);

        Button_3 = new QPushButton(gridLayoutWidget);
        Button_3->setObjectName(QString::fromUtf8("Button_3"));

        gridLayout_2->addWidget(Button_3, 2, 2, 1, 1);

        Button_Clear = new QPushButton(gridLayoutWidget);
        Button_Clear->setObjectName(QString::fromUtf8("Button_Clear"));

        gridLayout_2->addWidget(Button_Clear, 3, 0, 1, 1);

        Button_Div = new QPushButton(gridLayoutWidget);
        Button_Div->setObjectName(QString::fromUtf8("Button_Div"));

        gridLayout_2->addWidget(Button_Div, 3, 3, 1, 1);

        Button_6 = new QPushButton(gridLayoutWidget);
        Button_6->setObjectName(QString::fromUtf8("Button_6"));

        gridLayout_2->addWidget(Button_6, 1, 2, 1, 1);

        Button_Sub = new QPushButton(gridLayoutWidget);
        Button_Sub->setObjectName(QString::fromUtf8("Button_Sub"));

        gridLayout_2->addWidget(Button_Sub, 1, 3, 1, 1);

        Button_1 = new QPushButton(gridLayoutWidget);
        Button_1->setObjectName(QString::fromUtf8("Button_1"));

        gridLayout_2->addWidget(Button_1, 2, 0, 1, 1);

        Button_Mul = new QPushButton(gridLayoutWidget);
        Button_Mul->setObjectName(QString::fromUtf8("Button_Mul"));

        gridLayout_2->addWidget(Button_Mul, 2, 3, 1, 1);

        Button_Result = new QPushButton(gridLayoutWidget);
        Button_Result->setObjectName(QString::fromUtf8("Button_Result"));

        gridLayout_2->addWidget(Button_Result, 3, 2, 1, 1);

        Num_1 = new QTextEdit(centralwidget);
        Num_1->setObjectName(QString::fromUtf8("Num_1"));
        Num_1->setGeometry(QRect(20, 20, 91, 31));
        Num_1->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        Num_2 = new QTextEdit(centralwidget);
        Num_2->setObjectName(QString::fromUtf8("Num_2"));
        Num_2->setGeometry(QRect(160, 20, 91, 31));
        Num_2->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        Result = new QTextEdit(centralwidget);
        Result->setObjectName(QString::fromUtf8("Result"));
        Result->setGeometry(QRect(300, 20, 91, 31));
        Result->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        ArithmeticLabel = new QLabel(centralwidget);
        ArithmeticLabel->setObjectName(QString::fromUtf8("ArithmeticLabel"));
        ArithmeticLabel->setGeometry(QRect(110, 20, 51, 31));
        ArithmeticLabel->setAlignment(Qt::AlignCenter);
        ResultLabel = new QLabel(centralwidget);
        ResultLabel->setObjectName(QString::fromUtf8("ResultLabel"));
        ResultLabel->setGeometry(QRect(250, 20, 51, 31));
        ResultLabel->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 412, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Button_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        Button_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        Button_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        Button_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        Button_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        Button_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        Button_Add->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        Button_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        Button_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        Button_Clear->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        Button_Div->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        Button_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        Button_Sub->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        Button_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        Button_Mul->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        Button_Result->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        ArithmeticLabel->setText(QString());
        ResultLabel->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
