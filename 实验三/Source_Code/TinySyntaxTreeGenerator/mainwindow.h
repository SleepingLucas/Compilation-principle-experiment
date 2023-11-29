#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QTreeWidgetItem>
#include <QTextStream>
#include <QStyleFactory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TreeNode * syntaxTree;
    FILE* output;

private:
    FILE* QString2FILE(QString s);
    void createTreeItem(TreeNode* tree, QTreeWidgetItem* parent);
    QString Token2QString(TokenType token);

private slots:
    void on_openFileButton_clicked();

    void on_createTreeButton_clicked();

    void on_saveFileButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
