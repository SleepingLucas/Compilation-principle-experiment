#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QPlainTextEdit>
#include <QPushButton>
#include "xlexgenerator.h"
#include "highlighter.h"

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

    void on_generateNFAButton_clicked();

    void on_regEdit_textChanged();

    void on_generateDFAButton_clicked();

    void on_generateMinDFAButton_clicked();

    void on_generateXLEXButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isRegExpChanged = false;
    XLEXGenerator xlexGenerator;

};
#endif // MAINWINDOW_H
