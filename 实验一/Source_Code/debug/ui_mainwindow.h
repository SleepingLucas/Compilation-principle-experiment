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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "codeeditor.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openFile;
    QAction *saveFile;
    QAction *XCInstruction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *fileText;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *openFileButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *saveFileButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *analyseButton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *styleButton;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *sourceLabel;
    CodeEditor *sourceCodeText;
    QVBoxLayout *verticalLayout_2;
    QLabel *analysisLabel;
    CodeEditor *analysisText;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuXCpp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1138, 627);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        openFile = new QAction(MainWindow);
        openFile->setObjectName("openFile");
        saveFile = new QAction(MainWindow);
        saveFile->setObjectName("saveFile");
        XCInstruction = new QAction(MainWindow);
        XCInstruction->setObjectName("XCInstruction");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        fileText = new QLineEdit(centralwidget);
        fileText->setObjectName("fileText");
        fileText->setMinimumSize(QSize(0, 28));
        fileText->setReadOnly(true);

        horizontalLayout->addWidget(fileText);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName("openFileButton");
        openFileButton->setMinimumSize(QSize(0, 28));

        horizontalLayout->addWidget(openFileButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        saveFileButton = new QPushButton(centralwidget);
        saveFileButton->setObjectName("saveFileButton");
        saveFileButton->setMinimumSize(QSize(0, 28));

        horizontalLayout->addWidget(saveFileButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 16);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 3);
        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(5, 3);
        horizontalLayout->setStretch(6, 2);

        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        analyseButton = new QPushButton(centralwidget);
        analyseButton->setObjectName("analyseButton");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(analyseButton->sizePolicy().hasHeightForWidth());
        analyseButton->setSizePolicy(sizePolicy1);
        analyseButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_3->addWidget(analyseButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        styleButton = new QPushButton(centralwidget);
        styleButton->setObjectName("styleButton");
        sizePolicy1.setHeightForWidth(styleButton->sizePolicy().hasHeightForWidth());
        styleButton->setSizePolicy(sizePolicy1);
        styleButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_3->addWidget(styleButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        horizontalLayout_3->setStretch(0, 7);
        horizontalLayout_3->setStretch(1, 8);
        horizontalLayout_3->setStretch(2, 7);
        horizontalLayout_3->setStretch(3, 7);
        horizontalLayout_3->setStretch(4, 9);
        horizontalLayout_3->setStretch(5, 7);

        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, -1, 3, -1);
        sourceLabel = new QLabel(centralwidget);
        sourceLabel->setObjectName("sourceLabel");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sourceLabel->sizePolicy().hasHeightForWidth());
        sourceLabel->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(sourceLabel);

        sourceCodeText = new CodeEditor(centralwidget);
        sourceCodeText->setObjectName("sourceCodeText");
        QFont font;
        font.setPointSize(10);
        sourceCodeText->setFont(font);
        sourceCodeText->setFrameShadow(QFrame::Plain);
        sourceCodeText->setReadOnly(false);

        verticalLayout->addWidget(sourceCodeText);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        analysisLabel = new QLabel(centralwidget);
        analysisLabel->setObjectName("analysisLabel");
        sizePolicy2.setHeightForWidth(analysisLabel->sizePolicy().hasHeightForWidth());
        analysisLabel->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(analysisLabel);

        analysisText = new CodeEditor(centralwidget);
        analysisText->setObjectName("analysisText");
        analysisText->setFont(font);
        analysisText->setFrameShadow(QFrame::Plain);
        analysisText->setReadOnly(true);

        verticalLayout_2->addWidget(analysisText);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalLayout_2->setStretch(0, 8);
        horizontalLayout_2->setStretch(1, 9);

        verticalLayout_4->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1138, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuXCpp = new QMenu(menubar);
        menuXCpp->setObjectName("menuXCpp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuXCpp->menuAction());
        menuFile->addAction(openFile);
        menuFile->addAction(saveFile);
        menuXCpp->addAction(XCInstruction);

        retranslateUi(MainWindow);
        QObject::connect(openFile, &QAction::triggered, openFileButton, qOverload<>(&QPushButton::click));
        QObject::connect(saveFile, &QAction::triggered, saveFileButton, qOverload<>(&QPushButton::click));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openFile->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        openFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        saveFile->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\210\206\346\236\220\347\273\223\346\236\234", nullptr));
#if QT_CONFIG(shortcut)
        saveFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        XCInstruction->setText(QCoreApplication::translate("MainWindow", "\351\243\216\346\240\274\350\257\264\346\230\216", nullptr));
#if QT_CONFIG(statustip)
        openFileButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        openFileButton->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(statustip)
        saveFileButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        saveFileButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\210\206\346\236\220\347\273\223\346\236\234", nullptr));
#if QT_CONFIG(statustip)
        analyseButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        analyseButton->setText(QCoreApplication::translate("MainWindow", "\350\257\215\346\263\225\345\210\206\346\236\220", nullptr));
#if QT_CONFIG(statustip)
        styleButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        styleButton->setText(QCoreApplication::translate("MainWindow", "\346\233\264\346\224\271\351\243\216\346\240\274", nullptr));
        sourceLabel->setText(QCoreApplication::translate("MainWindow", "  \346\272\220\344\273\243\347\240\201\357\274\232", nullptr));
        analysisLabel->setText(QCoreApplication::translate("MainWindow", "  \345\210\206\346\236\220\347\273\223\346\236\234\357\274\232", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuXCpp->setTitle(QCoreApplication::translate("MainWindow", "XC++", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
