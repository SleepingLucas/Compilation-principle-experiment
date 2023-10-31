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
#include <QtWidgets/QLabel>
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
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    CodeEditor *regEdit;
    QVBoxLayout *verticalLayout_2;
    QPushButton *openFileButton;
    QPushButton *saveFileButton;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *generateNFAButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *generateDFAButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *generateMinDFAButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *generateXLEXButton;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_5;
    QTableWidget *showTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(916, 542);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        regEdit = new CodeEditor(groupBox);
        regEdit->setObjectName("regEdit");
        QFont font;
        font.setPointSize(12);
        regEdit->setFont(font);

        verticalLayout->addWidget(regEdit);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        openFileButton = new QPushButton(groupBox);
        openFileButton->setObjectName("openFileButton");

        verticalLayout_2->addWidget(openFileButton);

        saveFileButton = new QPushButton(groupBox);
        saveFileButton->setObjectName("saveFileButton");

        verticalLayout_2->addWidget(saveFileButton);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalLayout_4->setStretch(0, 8);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        generateNFAButton = new QPushButton(groupBox);
        generateNFAButton->setObjectName("generateNFAButton");

        horizontalLayout_3->addWidget(generateNFAButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        generateDFAButton = new QPushButton(groupBox);
        generateDFAButton->setObjectName("generateDFAButton");

        horizontalLayout_3->addWidget(generateDFAButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        generateMinDFAButton = new QPushButton(groupBox);
        generateMinDFAButton->setObjectName("generateMinDFAButton");

        horizontalLayout_3->addWidget(generateMinDFAButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        generateXLEXButton = new QPushButton(groupBox);
        generateXLEXButton->setObjectName("generateXLEXButton");

        horizontalLayout_3->addWidget(generateXLEXButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalLayout_4->setStretch(0, 9);
        verticalLayout_4->setStretch(1, 2);

        verticalLayout_5->addLayout(verticalLayout_4);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        horizontalLayout_5 = new QHBoxLayout(groupBox_2);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        showTable = new QTableWidget(groupBox_2);
        showTable->setObjectName("showTable");

        horizontalLayout_5->addWidget(showTable);


        verticalLayout_3->addWidget(groupBox_2);

        verticalLayout_3->setStretch(0, 8);
        verticalLayout_3->setStretch(1, 11);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 916, 21));
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
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234\351\235\242\346\235\277", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\345\215\225\350\241\214\346\210\226\345\244\232\350\241\214\346\255\243\345\210\231\350\241\250\350\276\276\345\274\217\357\274\232", nullptr));
        regEdit->setPlaceholderText(QString());
        openFileButton->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        saveFileButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\344\273\266", nullptr));
        generateNFAButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220NFA", nullptr));
        generateDFAButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220DFA", nullptr));
        generateMinDFAButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\234\200\345\260\217\345\214\226DFA", nullptr));
        generateXLEXButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\350\257\215\346\263\225\345\210\206\346\236\220\347\250\213\345\272\217", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\345\261\225\347\244\272\351\235\242\346\235\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
