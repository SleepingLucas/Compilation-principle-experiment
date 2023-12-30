#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString VR2QString(vector<Rule> v) {
    QString res = "";
    for (auto &it:v) {
        QString s = QString(QChar(it.first)) + " -> " + QString::fromStdString(it.second);
        if (!(it == *v.rbegin())) s += "\n";
        res += s;
    }
    return res;
};

void MainWindow::updateGrammar()
{
    if (analyzed) return;
    analyzed = true;
    sentenceChanged = true;
    solution.clear();
    solution.setStr(ui->codeEdit->toPlainText().toStdString());
    solution.init();
    solution.Debug();
}

void MainWindow::showFirstFollow(QTableWidget *tableWidget, Solution &solution)
{
    auto first = solution.getFirst();
    auto follow = solution.getFollow();
    auto non_terminal = solution.getNonTerminal();
    int n = non_terminal.size();

    for(int i = 0; i < tableWidget->rowCount(); i++)
        for(int j = 0; j < tableWidget->columnCount(); j++)
            tableWidget->setSpan(i, j, 1, 1);

    tableWidget->clear();
    tableWidget->setRowCount(n);
    tableWidget->setColumnCount(3);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑
    tableWidget->verticalHeader()->setVisible(true);   // 显示第一列
    tableWidget->horizontalHeader()->setVisible(true);   // 显示第一行
    // ui->tableWidget->horizontalHeader()->setFont(QFont("Microsoft YaHei UI", 11));
    // ui->tableWidget->setFont(QFont("Microsoft YaHei UI", 11));

    QStringList header;
    header << "非终结符号" << "first集合" << "follow集合";
    ui->tableWidget->setHorizontalHeaderLabels(header);

    // 文法开始符号
    tableWidget->setItem(0, 0, new QTableWidgetItem(QString(QChar(solution.getStart())) + " *"));
    tableWidget->setItem(0, 1, new QTableWidgetItem(set2QString(first[solution.getStart()])));
    tableWidget->setItem(0, 2, new QTableWidgetItem(set2QString(follow[solution.getStart()])));


    int i = 1;
    for (auto &c:non_terminal) {    // 填入非终结符号
        if (c == solution.getStart()) continue;
        tableWidget->setItem(i++, 0, new QTableWidgetItem(QString(QChar(c))));
    }
    i = 1;
    for (auto &c:non_terminal) {    // 填入 first
        if (c == solution.getStart()) continue;
        tableWidget->setItem(i++, 1, new QTableWidgetItem(set2QString(first[c])));
    }
    i = 1;
    for (auto &c:non_terminal) {    // 填入 follow
        if (c == solution.getStart()) continue;
        tableWidget->setItem(i++, 2, new QTableWidgetItem(set2QString(follow[c])));
    }

    // 居中显示
    for(int i = 0; i < tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *item = tableWidget->item(i, j);
            if(item) item->setTextAlignment(Qt::AlignCenter);
        }
    }

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tableWidget->show();
}

void MainWindow::showDFA(QTableWidget *tableWidget, Solution &solution)
{
    auto DFA = solution.getDFA();
    auto states = solution.getStateMap();
    auto charSet = solution.getCharSet();
    vector<char> usedChar;
    usedChar.assign(charSet.begin(), charSet.end());

    for(int i = 0; i < tableWidget->rowCount(); i++)
        for(int j = 0; j < tableWidget->columnCount(); j++)
            tableWidget->setSpan(i, j, 1, 1);

    tableWidget->clear();
    tableWidget->setRowCount(states.size());
    tableWidget->setColumnCount(usedChar.size() + 1);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑
    // ui->tableWidget->horizontalHeader()->setFont(QFont("Microsoft YaHei UI", 11));
    // ui->tableWidget->setFont(QFont("Microsoft YaHei UI", 11));
    tableWidget->verticalHeader()->setVisible(false);   // 隐藏第一列
    tableWidget->horizontalHeader()->setVisible(true);   // 显示第一行

    QStringList header;
    header << "LR(0)DFA状态";
    for (auto c : usedChar) {
        header << QString(c);
    }
    tableWidget->setHorizontalHeaderLabels(header);

    for (auto &[idx, v]:states) {
        qDebug() << QString::number(idx) + "\n" + VR2QString(v);
        tableWidget->setItem(idx, 0, new QTableWidgetItem(QString::number(idx) + "\n" + VR2QString(v)));
    }

    qDebug() << usedChar << DFA;

    for (auto &[idx, m]:DFA) {
        for (auto &[c, to]:m) {
            tableWidget->setItem(idx, std::find(usedChar.begin(), usedChar.end(), c)-usedChar.begin() + 1, new QTableWidgetItem(QString::number(to)));
        }
    }

    // 居中显示
    for(int i = 0; i < tableWidget->rowCount(); i++)
    {
        for(int j = 1; j < tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *item = tableWidget->item(i, j);
            if(item) item->setTextAlignment(Qt::AlignCenter);
        }
    }

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);        // 列宽
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // 行高
    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tableWidget->show();
}

void MainWindow::showAnalysisSheet(QTableWidget *tableWidget, Solution &solution)
{
    auto DFA = solution.getDFA();
    auto states = solution.getStateMap();
    auto charSet = solution.getCharSet();
    auto non_terminal = solution.getNonTerminal();
    set<char> inputSet;
    set_difference(charSet.begin(), charSet.end(),
                   non_terminal.begin(), non_terminal.end(),
                   inserter(inputSet, inputSet.begin()));
    vector<char> inputV, gotoV;
    inputV.assign(inputSet.begin(), inputSet.end());
    inputV.push_back('$');
    non_terminal.erase(solution.getStart());
    gotoV.assign(non_terminal.begin(), non_terminal.end());
    qDebug() << inputV << gotoV << DFA;

    for(int i = 0; i < tableWidget->rowCount(); i++)
        for(int j = 0; j < tableWidget->columnCount(); j++)
            tableWidget->setSpan(i, j, 1, 1);

    tableWidget->clear();
    tableWidget->setRowCount(states.size() + 2);
    tableWidget->setColumnCount(1+inputV.size()+gotoV.size());
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑
    // ui->tableWidget->horizontalHeader()->setFont(QFont("Microsoft YaHei UI", 11));
    // ui->tableWidget->setFont(QFont("Microsoft YaHei UI", 11));
    tableWidget->verticalHeader()->setVisible(false);   // 隐藏第一列
    tableWidget->horizontalHeader()->setVisible(false);   // 隐藏第一行

    tableWidget->setItem(0, 0, new QTableWidgetItem(QString("状态")));
    tableWidget->setSpan(0, 1, 1, inputV.size()); //合并单元格
    tableWidget->setItem(0, 1, new QTableWidgetItem(QString("输入")));
    tableWidget->setSpan(0, inputV.size() + 1, 1, gotoV.size()); //合并单元格
    tableWidget->setItem(0, 1 + inputV.size(), new QTableWidgetItem(QString("Goto")));

    for (int i=0;i<inputV.size();i++) {
        tableWidget->setItem(1, i+1, new QTableWidgetItem(QString(QChar(inputV[i]))));
    }
    for (int i=0;i<gotoV.size();i++) {
        tableWidget->setItem(1, i+1+inputV.size(), new QTableWidgetItem(QString(QChar(gotoV[i]))));
    }
    for (auto &[idx, _]:states) {
        tableWidget->setItem(idx+2, 0, new QTableWidgetItem(QString::number(idx)));
    }

    auto inputAnalysisTable = solution.getInputAnalysisTable();
    auto gotoAnalysisTable = solution.getGotoAnalysisTable();
    for (auto &[idx, m]:inputAnalysisTable) {
        for (auto &[c, to]:m) {
            int x = idx + 2, y = std::find(inputV.begin(), inputV.end(), c)-inputV.begin()+1;
            if (to.type == SHIFT) { // 移进
                tableWidget->setItem(x, y, new QTableWidgetItem("S" + QString::number(to.num)));
            } else if (to.type == REDUCE) { // 归约
                tableWidget->setItem(x, y, new QTableWidgetItem("r( " + QString(QChar(to.rule.first)) + " -> " + QString::fromStdString(to.rule.second) + " )"));
            } else if (to.type == ACCEPT) {
                tableWidget->setItem(x, y, new QTableWidgetItem("接受"));
            }
            // tableWidget->setItem(idx+2, std::find(inputV.begin(), inputV.end(), c)-inputV.begin()+1, new QTableWidgetItem(QString::fromStdString(to)));
        }
    }
    for (auto &[idx, m]:gotoAnalysisTable) {
        for (auto &[c, to]:m) {
            int x = idx + 2, y = std::find(gotoV.begin(), gotoV.end(), c)-gotoV.begin()+1+inputV.size();
            tableWidget->setItem(x, y, new QTableWidgetItem(QString::number(to)));
            // tableWidget->setItem(idx+2, std::find(gotoV.begin(), gotoV.end(), c)-gotoV.begin()+1+inputV.size(), new QTableWidgetItem(QString::fromStdString(to)));
        }
    }


    // // 填入移进项
    // for (auto &[idx, m]:DFA) {
    //     for (auto &[c, to]:m) {
    //         if (isupper(c)) {
    //             tableWidget->setItem(idx+2, std::find(gotoV.begin(), gotoV.end(), c)-gotoV.begin()+1+inputV.size(), new QTableWidgetItem(QString::number(to)));
    //         } else {
    //             tableWidget->setItem(idx+2, std::find(inputV.begin(), inputV.end(), c)-inputV.begin()+1, new QTableWidgetItem("S" + QString::number(to)));
    //         }
    //     }
    // }

    // auto follow = solution.getFollow();
    // // 填入归约项
    // for (auto &[DFAidx, status]:states) {
    //     vector<Rule> reduction;	// 归约项
    //     for (auto &[left, right, idx]:status) {
    //         if (idx == right.size() - 1) {	// 归约项
    //             reduction.emplace_back(left, right);
    //         }
    //     }
    //     for (auto &[left, right, idx]:reduction) {
    //         if (left == solution.getStart()) {
    //             tableWidget->setItem(DFAidx+2, inputV.size(), new QTableWidgetItem("接受"));
    //         } else {
    //             for (auto &c:follow[left]) {
    //                 auto temp = QString::fromStdString(right.substr(0, right.size()-1));
    //                 if (temp == "") temp = "@";	// 空串
    //                 tableWidget->setItem(DFAidx+2, std::find(inputV.begin(), inputV.end(), c)-inputV.begin()+1, new QTableWidgetItem("r( " + QString(QChar(left)) + "->" + temp + " )"));
    //             }
    //         }
    //     }
    // }

    // 居中显示
    for(int i = 0; i < tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *item = tableWidget->item(i, j);
            if(item) item->setTextAlignment(Qt::AlignCenter);
        }
    }

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i=1;i<inputV.size()+1;i++) {
        tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    // tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tableWidget->show();
}


void MainWindow::on_codeEdit_textChanged()
{
    analyzed = false;
}


void MainWindow::on_openFileButton_clicked()
{
    ui->fileText->clear();
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("(*.txt, *.slr1)"));
    if (path.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("你还没选择文件"));
    }
    ui->fileText->setText(path);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("注意"), tr("无法打开文件：\n%1").arg(path));
        return;
    }
    auto fileSuffix = QFileInfo(file).suffix();
    if (fileSuffix == "txt") {
        QTextStream in(&file);
        ui->codeEdit->setPlainText(in.readAll());
    } else if (fileSuffix == "slr1") {
        QTextStream in(&file);
        auto str = in.readAll();
        auto pos = str.indexOf("$$$");
        if (pos == -1) {
            QMessageBox::warning(this, tr("注意"), tr("文件格式错误"));
            return;
        }
        ui->codeEdit->setPlainText(str.mid(0, pos).trimmed());
        ui->sentenceEdit->setPlainText(str.mid(pos+3).trimmed());
    } else {
        QMessageBox::warning(this, tr("注意"), tr("文件格式错误"));
        return;
    }
    file.close();
}


void MainWindow::on_saveFileButton_clicked()
{
    auto content = ui->codeEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("文法规则为空"));
        return;
    }
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("SLR1 Files(*.slr1)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("注意"), tr("无法打开文件：\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << content.trimmed();
        out << "\n$$$\n";
        out << ui->sentenceEdit->toPlainText().trimmed();
        file.close();
    } else {
        QMessageBox::warning(this, tr("注意"), tr("你还没选择文件"));
    }
}


void MainWindow::on_showSetButton_clicked()
{
    if (ui->codeEdit->toPlainText().isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("文法规则为空"));
        return;
    }
    updateGrammar();
    showFirstFollow(ui->tableWidget, solution);
}


void MainWindow::on_showDFAButton_clicked()
{
    if (ui->codeEdit->toPlainText().isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("文法规则为空"));
        return;
    }
    updateGrammar();
    showDFA(ui->tableWidget, solution);
}


void MainWindow::on_judgeButton_clicked()
{
    // 弹出一个对话框显示是否为 SLR(1) 文法，如果不是，在对话框显示冲突项，调用solution.getIsSLR1()获取是否为 SLR(1) 文法，调用solution.getConflict()获取冲突项
    if (ui->codeEdit->toPlainText().isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("文法规则为空"));
        return;
    }
    updateGrammar();
    bool ok = solution.getIsSLR1();
    if (ok) {
        QMessageBox::information(this,
                                 tr("判断文法"),
                                 tr("该文法为SLR(1)文法"));
    } else {
        auto conflicts = solution.getConflict();
        QString res = "";
        for (auto &[idx, type, rules]:conflicts) {
            res += QString("在状态 %1 存在 %2\n").arg(idx).arg(type==SHIFT_REDUCE_CONFLICT? "移进-归约冲突":"归约-归约冲突");
            res += VR2QString(rules) + "\n";
        }
        QMessageBox::information(this,
                                 tr("判断文法"),
                                 "该文法不是SLR(1)文法\n" + res);
    }
}


void MainWindow::on_showTableButton_clicked()
{
    if (ui->codeEdit->toPlainText().isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("文法规则为空"));
        return;
    }
    updateGrammar();
    if (!solution.getIsSLR1()) {
        auto conflicts = solution.getConflict();
        QString res = "";
        for (auto &[idx, type, rules]:conflicts) {
            res += QString("在状态 %1 存在 %2\n").arg(idx).arg(type==SHIFT_REDUCE_CONFLICT? "移进-归约冲突":"归约-归约冲突");
            res += VR2QString(rules) + "\n";
        }
        QMessageBox::information(this,
                                 tr("判断文法"),
                                 "该文法不是SLR(1)文法\n" + res);
        return;
    }
    // 是SLR(1)文法
    showAnalysisSheet(ui->tableWidget, solution);
}


void MainWindow::on_sentenceEdit_textChanged()
{
    sentenceChanged = true;
}


void MainWindow::on_sentenceAnalysisButton_clicked()
{
    if (ui->codeEdit->toPlainText().isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("文法规则为空"));
        return;
    }
    if (ui->sentenceEdit->toPlainText().isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("待分析句子为空"));
        return;
    }
    updateGrammar();
    if (!solution.getIsSLR1()) {
        QMessageBox::information(this,
                                 tr("注意"),
                                 "该文法不是SLR(1)文法，无法对当前句子进行分析\n");
        return;
    }
    if (sentenceChanged) {
        solution.clearAnalysis();
        string s = ui->sentenceEdit->toPlainText().toStdString();
        s.erase(remove_if(s.begin(), s.end(), [](char c){return isspace(c);}), s.end());
        solution.setSentence(s);
        solution.analysis();
        sentenceChanged = false;
    }
    auto log = solution.getAnalysisLog();

    ui->sentenceAnalysisTable->clear();
    ui->sentenceAnalysisTable->setRowCount(log.size());
    ui->sentenceAnalysisTable->setColumnCount(4);
    ui->sentenceAnalysisTable->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止编辑
    // ui->ui->sentenceAnalysisTable->horizontalHeader()->setFont(QFont("Microsoft YaHei UI", 11));
    // ui->ui->sentenceAnalysisTable->setFont(QFont("Microsoft YaHei UI", 11));
    ui->sentenceAnalysisTable->verticalHeader()->setVisible(false);   // x第一列
    ui->sentenceAnalysisTable->horizontalHeader()->setVisible(true);   // 显示第一行

    QStringList header;
    header << "步骤" << "分析栈" << "输入" << "动作";
              ui->sentenceAnalysisTable->setHorizontalHeaderLabels(header);

    for (auto &[step, stack, input, action]:log) {
        ui->sentenceAnalysisTable->setItem(step - 1, 0, new QTableWidgetItem(QString::number(step)));
        ui->sentenceAnalysisTable->setItem(step - 1, 1, new QTableWidgetItem(QString::fromStdString(stack)));
        ui->sentenceAnalysisTable->setItem(step - 1, 2, new QTableWidgetItem(QString::fromStdString(input)));
        ui->sentenceAnalysisTable->setItem(step - 1, 3, new QTableWidgetItem(QString::fromStdString(action)));
    }

    for(int i = 0; i < ui->sentenceAnalysisTable->rowCount(); i++) {
        QTableWidgetItem *item = ui->sentenceAnalysisTable->item(i, 0);
        if(item) item->setTextAlignment(Qt::AlignCenter);
    }

    for(int i = 0; i < ui->sentenceAnalysisTable->rowCount(); i++) {
        QTableWidgetItem *item = ui->sentenceAnalysisTable->item(i, 1);
        if(item) item->setTextAlignment(Qt::AlignLeft);
    }

    for(int i = 0; i < ui->sentenceAnalysisTable->rowCount(); i++) {
        QTableWidgetItem *item = ui->sentenceAnalysisTable->item(i, 2);
        if(item) item->setTextAlignment(Qt::AlignRight);
    }

    for(int i = 0; i < ui->sentenceAnalysisTable->rowCount(); i++) {
        QTableWidgetItem *item = ui->sentenceAnalysisTable->item(i, 4);
        if(item) item->setTextAlignment(Qt::AlignLeft);
    }

    ui->sentenceAnalysisTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i=1;i<4;i++) {
        ui->sentenceAnalysisTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    // ui->sentenceAnalysisTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->sentenceAnalysisTable->show();
}

