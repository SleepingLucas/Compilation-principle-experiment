/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "codeeditor.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *fileText;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *openFileButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *saveFileButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    CodeEditor *codeEdit;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    CodeEditor *sentenceEdit;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *showSetButton;
    QPushButton *showDFAButton;
    QPushButton *judgeButton;
    QPushButton *showTableButton;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *sentenceAnalysisButton;
    QTableWidget *sentenceAnalysisTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1163, 630);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        fileText = new QLineEdit(centralwidget);
        fileText->setObjectName("fileText");
        fileText->setMinimumSize(QSize(0, 28));
        fileText->setStyleSheet(QString::fromUtf8(""));
        fileText->setFrame(false);
        fileText->setReadOnly(true);

        horizontalLayout_2->addWidget(fileText);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName("openFileButton");
        openFileButton->setMinimumSize(QSize(0, 28));

        horizontalLayout_2->addWidget(openFileButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        saveFileButton = new QPushButton(centralwidget);
        saveFileButton->setObjectName("saveFileButton");
        saveFileButton->setMinimumSize(QSize(0, 28));

        horizontalLayout_2->addWidget(saveFileButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 15);
        horizontalLayout_2->setStretch(2, 2);
        horizontalLayout_2->setStretch(3, 3);
        horizontalLayout_2->setStretch(4, 2);
        horizontalLayout_2->setStretch(5, 3);
        horizontalLayout_2->setStretch(6, 2);

        verticalLayout_6->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border-width: 0.5px;\n"
"	border-color: #aaaaaa;\n"
"	border-style: solid;\n"
"	margin-top:8px\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"	font: 14px \"Microsoft YaHei\";\n"
"	color: #000000;\n"
"	subcontrol-origin: margin;\n"
"	left:20px;\n"
"	padding: 0px 5px 0px 5px;\n"
"}"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        codeEdit = new CodeEditor(groupBox);
        codeEdit->setObjectName("codeEdit");

        verticalLayout->addWidget(codeEdit);


        verticalLayout_5->addWidget(groupBox);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border-width: 0.5px;\n"
"	border-color: #aaaaaa;\n"
"	border-style: solid;\n"
"	margin-top:8px\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"	font: 14px \"Microsoft YaHei\";\n"
"	color: #000000;\n"
"	subcontrol-origin: margin;\n"
"	left:20px;\n"
"	padding: 0px 5px 0px 5px;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        sentenceEdit = new CodeEditor(groupBox_4);
        sentenceEdit->setObjectName("sentenceEdit");

        verticalLayout_3->addWidget(sentenceEdit);


        verticalLayout_5->addWidget(groupBox_4);

        verticalLayout_5->setStretch(0, 9);
        verticalLayout_5->setStretch(1, 3);

        horizontalLayout_3->addLayout(verticalLayout_5);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border-width: 0.5px;\n"
"	border-color: #aaaaaa;\n"
"	border-style: solid;\n"
"	margin-top:8px\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"	font: 14px \"Microsoft YaHei\";\n"
"	color: #000000;\n"
"	subcontrol-origin: margin;\n"
"	left:20px;\n"
"	padding: 0px 5px 0px 5px;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        showSetButton = new QPushButton(groupBox_2);
        showSetButton->setObjectName("showSetButton");

        horizontalLayout->addWidget(showSetButton);

        showDFAButton = new QPushButton(groupBox_2);
        showDFAButton->setObjectName("showDFAButton");

        horizontalLayout->addWidget(showDFAButton);

        judgeButton = new QPushButton(groupBox_2);
        judgeButton->setObjectName("judgeButton");

        horizontalLayout->addWidget(judgeButton);

        showTableButton = new QPushButton(groupBox_2);
        showTableButton->setObjectName("showTableButton");

        horizontalLayout->addWidget(showTableButton);


        verticalLayout_2->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(groupBox_2);
        tableWidget->setObjectName("tableWidget");

        verticalLayout_2->addWidget(tableWidget);


        horizontalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border-width: 0.5px;\n"
"	border-color: #aaaaaa;\n"
"	border-style: solid;\n"
"	margin-top:8px\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"	font: 14px \"Microsoft YaHei\";\n"
"	color: #000000;\n"
"	subcontrol-origin: margin;\n"
"	left:20px;\n"
"	padding: 0px 5px 0px 5px;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        sentenceAnalysisButton = new QPushButton(groupBox_3);
        sentenceAnalysisButton->setObjectName("sentenceAnalysisButton");

        verticalLayout_4->addWidget(sentenceAnalysisButton);

        sentenceAnalysisTable = new QTableWidget(groupBox_3);
        sentenceAnalysisTable->setObjectName("sentenceAnalysisTable");

        verticalLayout_4->addWidget(sentenceAnalysisTable);

        verticalLayout_4->setStretch(1, 15);

        horizontalLayout_3->addWidget(groupBox_3);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 6);
        horizontalLayout_3->setStretch(2, 4);

        verticalLayout_6->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1163, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(statustip)
        openFileButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        openFileButton->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\346\263\225\350\247\204\345\210\231", nullptr));
#if QT_CONFIG(statustip)
        saveFileButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        saveFileButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\346\263\225\350\247\204\345\210\231", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\346\263\225\347\274\226\350\276\221\345\231\250", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\345\217\245\345\255\220\347\274\226\350\276\221\345\231\250", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\346\263\225\345\210\206\346\236\220", nullptr));
        showSetButton->setText(QCoreApplication::translate("MainWindow", "\345\261\225\347\244\272first/follow\351\233\206\345\220\210", nullptr));
        showDFAButton->setText(QCoreApplication::translate("MainWindow", "\345\261\225\347\244\272LR(0)DFA\345\233\276", nullptr));
        judgeButton->setText(QCoreApplication::translate("MainWindow", "\345\210\244\346\226\255\346\226\207\346\263\225", nullptr));
        showTableButton->setText(QCoreApplication::translate("MainWindow", "\345\261\225\347\244\272SLR(1)\345\210\206\346\236\220\350\241\250", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\345\217\245\345\255\220\345\210\206\346\236\220", nullptr));
        sentenceAnalysisButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\345\210\206\346\236\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
