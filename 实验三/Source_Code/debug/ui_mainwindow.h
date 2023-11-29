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
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <codeeditor.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *fileText;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *openFileButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *saveFileButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *createTreeButton;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    CodeEditor *tinyEdit;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *treeWidget;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *errorTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(939, 553);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
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

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 8);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName("openFileButton");
        openFileButton->setMinimumSize(QSize(0, 28));

        horizontalLayout_3->addWidget(openFileButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        saveFileButton = new QPushButton(centralwidget);
        saveFileButton->setObjectName("saveFileButton");
        saveFileButton->setMinimumSize(QSize(0, 28));

        horizontalLayout_3->addWidget(saveFileButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        createTreeButton = new QPushButton(centralwidget);
        createTreeButton->setObjectName("createTreeButton");

        horizontalLayout_3->addWidget(createTreeButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
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
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tinyEdit = new CodeEditor(groupBox);
        tinyEdit->setObjectName("tinyEdit");
        QFont font;
        font.setPointSize(11);
        tinyEdit->setFont(font);

        verticalLayout_2->addWidget(tinyEdit);


        horizontalLayout_2->addWidget(groupBox);

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
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        treeWidget = new QTreeWidget(groupBox_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setFont(font);

        verticalLayout_3->addWidget(treeWidget);


        horizontalLayout_2->addWidget(groupBox_2);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 3);

        verticalLayout_4->addLayout(horizontalLayout_2);

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
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setObjectName("verticalLayout_5");
        errorTable = new QTableWidget(groupBox_3);
        errorTable->setObjectName("errorTable");
        QFont font1;
        font1.setPointSize(10);
        errorTable->setFont(font1);

        verticalLayout_5->addWidget(errorTable);


        verticalLayout_4->addWidget(groupBox_3);

        verticalLayout_4->setStretch(0, 12);
        verticalLayout_4->setStretch(1, 5);

        verticalLayout->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 939, 21));
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
        openFileButton->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200Tiny\347\250\213\345\272\217", nullptr));
#if QT_CONFIG(statustip)
        saveFileButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        saveFileButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230Tiny\347\250\213\345\272\217", nullptr));
        createTreeButton->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\350\257\255\346\263\225\346\240\221", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Tiny\346\272\220\344\273\243\347\240\201", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\350\257\255\346\263\225\345\210\206\346\236\220", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\351\227\256\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
