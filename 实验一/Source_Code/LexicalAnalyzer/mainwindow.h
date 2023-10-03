#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "Parser.h"
#include "highlighter.h"
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFileButton_clicked();

    void on_saveFileButton_clicked();

    void on_analyseButton_clicked();

    void on_styleButton_clicked();

    void on_XCInstruction_triggered();

private:
    Ui::MainWindow *ui;
    Highlighter *highlighter;
    Highlighter *highlighter2;
};
#endif // MAINWINDOW_H
