#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QFont>
#include <QFileInfo>
#include "solution.h"

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
    Solution solution;
    bool analyzed = false;
    bool sentenceChanged = false;

private slots:
    void on_codeEdit_textChanged();

    void on_openFileButton_clicked();

    void on_saveFileButton_clicked();

    void on_showSetButton_clicked();

    void on_showDFAButton_clicked();

    void on_judgeButton_clicked();

    void on_showTableButton_clicked();

    void on_sentenceEdit_textChanged();

    void on_sentenceAnalysisButton_clicked();

private:
    void updateGrammar();
    void showFirstFollow(QTableWidget *tableWidget, Solution &solution);
    void showDFA(QTableWidget *tableWidget, Solution &solution);
    void showAnalysisSheet(QTableWidget *tableWidget, Solution &solution);

private:
    Ui::MainWindow *ui;

private:
    QString set2QString(set<char> s) {
        QString res = "{ ";
        for (auto& i : s) {
            res += QString(QChar(i)) + " , ";
        }
        res = res.mid(0, res.size() - 2);
        res += " }";
        return res;
    }
};
#endif // MAINWINDOW_H
