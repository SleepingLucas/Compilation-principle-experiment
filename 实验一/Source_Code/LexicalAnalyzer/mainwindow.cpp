#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    highlighter = new Highlighter(ui->sourceCodeText->document());
    highlighter2 = new Highlighter(ui->analysisText->document());

    ui->openFileButton->setStatusTip(tr("打开文件"));
    ui->saveFileButton->setStatusTip(tr("保存分析结果"));
    ui->analyseButton->setStatusTip(tr("将源代码中各类 Token 进行拼装分类"));
    ui->styleButton->setStatusTip(tr("将原 C++ 风格变为 XC++ 风格"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete highlighter;
}


void MainWindow::on_openFileButton_clicked()
{
    ui->fileText->clear();
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                 ".",
                                                tr("*.c *.cpp *.h *.txt"));
    if (!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("注意"), tr("无法打开文件：\n%1").arg(path));
            return;
        }
        ui->fileText->setText(path);
        QTextStream in(&file);
        ui->sourceCodeText->setPlainText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("注意"), tr("你还没选择文件"));
    }

}


void MainWindow::on_saveFileButton_clicked()
{
    auto content = ui->analysisText->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("分析结果为空"));
        return;
    }
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt *.md)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("注意"), tr("无法打开文件：\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << content;
        file.close();
    } else {
        QMessageBox::warning(this, tr("注意"), tr("你还没选择文件"));
    }
}


void MainWindow::on_analyseButton_clicked()
{
    auto content = ui->sourceCodeText->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("源代码为空，请先打开文件"));
        return;
    }
    Parser p(content.toStdString());
    p.analyse();
    auto result = QString::fromStdString(p.print());
    ui->analysisText->setPlainText(result);
}


void MainWindow::on_styleButton_clicked()
{
    auto content = ui->sourceCodeText->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("源代码为空，请先打开文件"));
        return;
    }
    Parser p(content.toStdString());
    auto result = QString::fromStdString(p.changeToX());
    ui->analysisText->setPlainText(result);
}

void MainWindow::on_XCInstruction_triggered()
{
    QDialog *dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    dialog->setMinimumSize(555, 500);
//    dialog->resize(500,600);

    QLabel *text = new QLabel(dialog);
    text->setText(tr("以下为XC++单词替换说明:"));
    text->setFont(QFont("宋体", 12));
    text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QTableWidget *tableWidget = new QTableWidget(12, 2, dialog);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableWidget->setFont(QFont("宋体", 15));
    tableWidget->setHorizontalHeaderLabels(QStringList() << "原C++风格" << "XC++风格");
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setColumnWidth(0, 250);
    tableWidget->setColumnWidth(1, 250);

    tableWidget->setItem(0, 0, new QTableWidgetItem("="));
    tableWidget->setItem(0, 1, new QTableWidgetItem("<:="));
    tableWidget->setItem(1, 0, new QTableWidgetItem("float"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("f32"));
    tableWidget->setItem(2, 0, new QTableWidgetItem("double"));
    tableWidget->setItem(2, 1, new QTableWidgetItem("f64"));
    tableWidget->setItem(3, 0, new QTableWidgetItem("int"));
    tableWidget->setItem(3, 1, new QTableWidgetItem("i32"));
    tableWidget->setItem(4, 0, new QTableWidgetItem("auto"));
    tableWidget->setItem(4, 1, new QTableWidgetItem("var"));
    tableWidget->setItem(5, 0, new QTableWidgetItem("cin"));
    tableWidget->setItem(5, 1, new QTableWidgetItem("Read"));
    tableWidget->setItem(6, 0, new QTableWidgetItem("cout"));
    tableWidget->setItem(6, 1, new QTableWidgetItem("Write"));
    tableWidget->setItem(7, 0, new QTableWidgetItem("!"));
    tableWidget->setItem(7, 1, new QTableWidgetItem(" not "));
    tableWidget->setItem(8, 0, new QTableWidgetItem("||"));
    tableWidget->setItem(8, 1, new QTableWidgetItem(" or "));
    tableWidget->setItem(9, 0, new QTableWidgetItem("&&"));
    tableWidget->setItem(9, 1, new QTableWidgetItem(" and "));
    tableWidget->setItem(10, 0, new QTableWidgetItem("{"));
    tableWidget->setItem(10, 1, new QTableWidgetItem("BEGIN:"));
    tableWidget->setItem(11, 0, new QTableWidgetItem("}"));
    tableWidget->setItem(11, 1, new QTableWidgetItem("END"));


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(text);
    layout->addWidget(tableWidget);

    dialog->setLayout(layout);
    dialog->exec();
}

