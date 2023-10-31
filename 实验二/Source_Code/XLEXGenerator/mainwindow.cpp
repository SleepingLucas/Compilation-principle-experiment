#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->regEdit->setPlaceholderText("输入多行正则表达式时，默认将每行表达式用'|'连接");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFileButton_clicked()
{
    ui->regEdit->clear();
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("*.txt"));
    if (!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("注意"), tr("无法打开文件：\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        ui->regEdit->setPlainText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("注意"), tr("你还没选择文件"));
    }

}


void MainWindow::on_saveFileButton_clicked()
{
    auto content = ui->regEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("正则表达式为空"));
        return;
    }
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));
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


void MainWindow::on_regEdit_textChanged()
{
    // 若正则表达式改变，则将isRegExpChanged置为true
    isRegExpChanged = true;
}


void MainWindow::on_generateNFAButton_clicked()
{
    auto content = ui->regEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("正则表达式为空"));
        return;
    }
    if (isRegExpChanged) {
        content.replace("\n", "|");
        content.replace(" ", "");
        xlexGenerator.setRegExp(content.toStdString());
        xlexGenerator.init();
        isRegExpChanged = false;
    }
    // 将NFA表示展示到showTable中
    auto NFA = xlexGenerator.getNFA();
    vector<char> charSet;
    auto charset = xlexGenerator.getCharset();
    charSet.assign(charset.begin(), charset.end());
    ui->showTable->clear();
    ui->showTable->setRowCount(xlexGenerator.getNFASize());
    ui->showTable->setColumnCount(xlexGenerator.getCharset().size() + 3);
    // 隐藏第一列
    ui->showTable->verticalHeader()->setVisible(false);
    for (int i=1;i<=xlexGenerator.getNFASize();i++) {
        ui->showTable->setItem(i-1, 0, new QTableWidgetItem(QString::number(i)));
    }
    QStringList header;
    header << "" << "状态";
    for (auto c : xlexGenerator.getCharset()) {
        header << QString(c);
    }
    header << QString("#");
    ui->showTable->setHorizontalHeaderLabels(header);
    ui->showTable->setItem(xlexGenerator.getStart()-1, 1, new QTableWidgetItem("初态"));
    ui->showTable->item(xlexGenerator.getStart()-1, 1)->setTextAlignment(Qt::AlignCenter);
    ui->showTable->setItem(xlexGenerator.getEnd()-1, 1, new QTableWidgetItem("终态"));
    ui->showTable->item(xlexGenerator.getEnd()-1, 1)->setTextAlignment(Qt::AlignCenter);
    for (auto& [node, ma] : NFA) {
        for (auto& [c, se] : ma) {
            QString s;
            for (auto& i : se) {
                s += QString::number(i) + ", ";
            }
            s = s.mid(0, s.size() - 2);
            ui->showTable->setItem(node - 1,
                                   c=='#'? xlexGenerator.getCharset().size() + 2:lower_bound(charSet.begin(), charSet.end(), c) - charSet.begin() + 2,
                                   new QTableWidgetItem(s));
        }
    }
//    ui->showTable->resizeColumnsToContents();
//    ui->showTable->resizeRowsToContents();
    ui->showTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->showTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->showTable->show();
}


void MainWindow::on_generateDFAButton_clicked()
{
    auto content = ui->regEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("正则表达式为空"));
        return;
    }
    if (isRegExpChanged) {
        content.replace("\n", "|");
        content.replace(" ", "");
        xlexGenerator.setRegExp(content.toStdString());
        xlexGenerator.init();
        isRegExpChanged = false;
    }
    // 将DFA表示展示到showTable中
    auto DFA = xlexGenerator.getDFA();
    vector<char> charSet;
    auto charset = xlexGenerator.getCharset();
    charSet.assign(charset.begin(), charset.end());
    ui->showTable->clear();
    ui->showTable->setRowCount(xlexGenerator.getDFASize());
    ui->showTable->setColumnCount(xlexGenerator.getCharset().size() + 2);
    ui->showTable->verticalHeader()->setVisible(true);
    QStringList header;
    header << "状态集合" << "状态";
    for (auto c : xlexGenerator.getCharset()) {
        header << QString(c);
    }
    auto set2QString = [](set<int> s) {
        QString res = "{ ";
        for (auto& i : s) {
            res += QString::number(i) + ", ";
        }
        res = res.mid(0, res.size() - 2);
        res += " }";
        return res;
    };
    ui->showTable->setHorizontalHeaderLabels(header);
    auto stateMapReverse = xlexGenerator.getStateMapReverse();
    for (int i=1;i<=xlexGenerator.getDFASize();i++) {
        ui->showTable->setItem(i-1, 0, new QTableWidgetItem(set2QString(stateMapReverse[i])));
    }
    ui->showTable->setItem(0, 1, new QTableWidgetItem("初态 "));
    ui->showTable->item(0, 1)->setTextAlignment(Qt::AlignCenter);
    for (auto& it:xlexGenerator.getDFAendSet()) {
//        QDebug() << (ui->showTable->item(it-1, 1)->text().isEmpty()? "":ui->showTable->item(it-1, 1)->text() + "终态");
        ui->showTable->setItem(it-1, 1, new QTableWidgetItem(
                                              (ui->showTable->item(it-1, 1) == nullptr? "":ui->showTable->item(it-1, 1)->text()) + "终态"));
        ui->showTable->item(it-1, 1)->setTextAlignment(Qt::AlignCenter);
    }
    for (auto& [node, ma] : DFA) {
        for (auto& [c, i] : ma) {
            ui->showTable->setItem(node - 1,
                                   lower_bound(charSet.begin(), charSet.end(), c) - charSet.begin() + 2,
                                   new QTableWidgetItem(set2QString(stateMapReverse[i])));
        }
    }
    ui->showTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->showTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->showTable->show();
}


void MainWindow::on_generateMinDFAButton_clicked()
{
    auto content = ui->regEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("正则表达式为空"));
        return;
    }
    if (isRegExpChanged) {
        content.replace("\n", "|");
        content.replace(" ", "");
        xlexGenerator.setRegExp(content.toStdString());
        xlexGenerator.init();
        isRegExpChanged = false;
    }
    // 将minDFA表示展示到showTable中
    auto minDFA = xlexGenerator.getMinDFA();
    vector<char> charSet;
    auto charset = xlexGenerator.getCharset();
    charSet.assign(charset.begin(), charset.end());
    ui->showTable->clear();
    ui->showTable->setRowCount(xlexGenerator.getMinDFASize());
    ui->showTable->setColumnCount(xlexGenerator.getCharset().size() + 2);
    ui->showTable->verticalHeader()->setVisible(false);
    for (int i=1;i<=xlexGenerator.getMinDFASize();i++) {
        ui->showTable->setItem(i-1, 0, new QTableWidgetItem(QString::number(i)));
    }
    QStringList header;
    header << "" << "状态";
    for (auto c : xlexGenerator.getCharset()) {
        header << QString(c);
    }
    ui->showTable->setHorizontalHeaderLabels(header);
    ui->showTable->setItem(0, 1, new QTableWidgetItem("初态 "));
    ui->showTable->item(0, 1)->setTextAlignment(Qt::AlignCenter);
    for (auto& it:xlexGenerator.getMinDFAendSet()) {
        ui->showTable->setItem(it-1, 1, new QTableWidgetItem(
                                              (ui->showTable->item(it-1, 1) == nullptr? "":ui->showTable->item(it-1, 1)->text()) + "终态"));
        ui->showTable->item(it-1, 1)->setTextAlignment(Qt::AlignCenter);
    }
    for (auto& [node, ma] : minDFA) {
        for (auto& [c, i] : ma) {
            ui->showTable->setItem(node - 1,
                                   lower_bound(charSet.begin(), charSet.end(), c) - charSet.begin() + 2,
                                   new QTableWidgetItem(QString::number(i)));
        }
    }
    ui->showTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->showTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->showTable->show();
}


void MainWindow::on_generateXLEXButton_clicked()
{
    auto content = ui->regEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("正则表达式为空"));
        return;
    }
    if (isRegExpChanged) {
        content.replace("\n", "|");
        content.replace(" ", "");
        xlexGenerator.setRegExp(content.toStdString());
        xlexGenerator.init();
        isRegExpChanged = false;
    }
    // 弹出一个对话框，对话框内放置一个CodeEditor文本框，文本框内为生成的词法分析程序，以及一个保存文件按钮，能将文本框内的c++代码保存到文件中
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("XLEX");
    dialog->resize(800, 600);
    CodeEditor* editor = new CodeEditor(dialog);
    new Highlighter(editor->document());
    editor->setPlainText(QString::fromStdString(xlexGenerator.getXLEX()));
    QPushButton* saveCodeButton = new QPushButton("保存", dialog);
    saveCodeButton->move(700, 0);
    connect(saveCodeButton, &QPushButton::clicked, [=](){
        QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("C++ Files(*.cpp)"));
        if(!path.isEmpty()) {
            QFile file(path);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(this, tr("注意"), tr("无法打开文件：\n%1").arg(path));
                return;
            }
            QTextStream out(&file);
            out << editor->toPlainText();
            file.close();
        } else {
            QMessageBox::warning(this, tr("注意"), tr("你还没选择文件"));
        }
    });
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(editor);
    layout->addWidget(saveCodeButton);
    dialog->setLayout(layout);
    dialog->show();
}

