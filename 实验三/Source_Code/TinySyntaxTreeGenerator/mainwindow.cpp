#include "mainwindow.h"
#include "scan.h"
#include "ui_mainwindow.h"
#include <iostream>

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setStyle(QStyleFactory::create("windows"));
    ui->treeWidget->header()->setVisible(false);

    ui->errorTable->setColumnCount(2);
    ui->errorTable->setHorizontalHeaderLabels(QStringList() << "说明" << "行");
    ui->errorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->errorTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->errorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

FILE *MainWindow::QString2FILE(QString s)
{
    FILE* fp = tmpfile();
    fputs(s.toStdString().c_str(), fp);
    rewind(fp);
    return fp;
}

void MainWindow::createTreeItem(TreeNode *tree, QTreeWidgetItem *parent)
{
    // 参考printTree函数，将语法树转换为QTreeWidgetItem
    while (tree != NULL) {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicatorWhenChildless);
        switch (tree->nodekind) {
        case StmtK:
            switch (tree->kind.stmt) {
            case IfK:
                item->setText(0, "If");
                break;
            case RepeatK:
                item->setText(0, "Repeat");
                break;
            case ForK: {
                QString s = "For: ";
                if (tree->attr.op == TO) {
                    s += "upto";
                } else if (tree->attr.op == DOWNTO) {
                    s += "downto";
                }
                item->setText(0, s);
                break;
            }
            case AssignK:
                item->setText(0, "Assign to: " + QString(tree->attr.name));
                break;
            case Add_AssignK:
                item->setText(0, "Add_Assign to: " + QString(tree->attr.name));
                break;
            case Reg_AssignK:
                item->setText(0, "Reg_Assign to: " + QString(tree->attr.name));
                break;
            case ReadK:
                item->setText(0, "Read: " + QString(tree->attr.name));
                break;
            case WriteK:
                item->setText(0, "Write");
                break;
            default:
                break;
            }
            break;
        case ExpK:
            switch (tree->kind.exp) {
            case OpK:
                item->setText(0, "Op: " + Token2QString(tree->attr.op));
                break;
            case ConstK:
                item->setText(0, "Const: " + QString::number(tree->attr.val));
                break;
            case IdK:
                item->setText(0, "Id: " + QString(tree->attr.name));
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        for (int i = 0;i < MAXCHILDREN;i++) {
            if (tree->child[i] != NULL) {
                createTreeItem(tree->child[i], item);
            }
        }
        tree = tree->sibling;
    }
}

QString MainWindow::Token2QString(TokenType token)
{
    QString s = "";
    switch (token) {
    case ASSIGN: s += ":="; break;
    case ADD_ASSIGN: s += "+="; break;
    case REG_ASSIGN: s += "::="; break;

    case EQ: s += "="; break;
    case LT: s += "<"; break;
    case GT: s += ">"; break;
    case LE: s += "<="; break;
    case NE: s += "<>"; break;
    case GE: s += ">="; break;

    case LPAREN: s += "("; break;
    case RPAREN: s += ")"; break;
    case LBRACKET: s += "["; break;
    case RBRACKET: s += "]"; break;
    case SEMI: s += ";"; break;

    case PLUS: s += "+"; break;
    case MINUS: s += "-"; break;
    case TIMES: s += "*"; break;
    case OVER: s += "/"; break;
    case MOD: s += "%"; break;
    case POWER: s += "^"; break;

    case NOT: s += "not"; break;
    case AND: s += "and"; break;
    case OR: s += "or"; break;

    case CONCAT: s += "&"; break;
    case REGOR: s += "|"; break;
    case CLOSURE: s += "#"; break;
    case OPTIONAL: s += "?"; break;

    case ENDFILE: s += "EOF"; break;
    case ERROR:
    case IF:
    case THEN:
    case ELSE:
    case END:
    case REPEAT:
    case UNTIL:
    case READ:
    case WRITE:
    case FOR:
    case TO:
    case DO:
    case DOWNTO:
    case ENDDO:
    case ID:
    case NUM:
        break;
    }
    return s;
}


void MainWindow::on_openFileButton_clicked()
{
    ui->fileText->clear();
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("*.tny, *TNY"));
    if (!path.isEmpty()) {
        ui->fileText->setText(path);
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("注意"), tr("无法打开文件：\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        ui->tinyEdit->setPlainText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, tr("注意"), tr("你还没选择文件"));
    }
}


void MainWindow::on_saveFileButton_clicked()
{
    auto content = ui->tinyEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("Tiny程序为空"));
        return;
    }
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.tny, *TNY)"));
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


void MainWindow::on_createTreeButton_clicked()
{
    output = fopen("tinyError.txt", "w+");
    // 清空语法树
    ui->treeWidget->clear();
    // 清空问题
    ui->errorTable->clearContents();
    ui->errorTable->setRowCount(0);
    clear();
    int rowNum = 0;
    QString content = ui->tinyEdit->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::warning(this, tr("注意"), tr("Tiny程序为空"));
        return;
    }
    listing = output;
    source = QString2FILE(content);
    syntaxTree = parse();
    if (syntaxTree != NULL) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, "start");
        createTreeItem(syntaxTree, item);
        ui->treeWidget->addTopLevelItem(item);
        // 默认展开所有节点
        ui->treeWidget->expandAll();
        // 不显示表头
        ui->treeWidget->setHeaderHidden(true);
    }
    // 读出output，显示在QTextEdit errorText中
    rewind(output);
    char buf[1024];
    // 上一行
    QString lastLine = "";
    while (fgets(buf, 1024, output) != NULL) {
        // 判断是否为空行
        QString s = QString(buf).trimmed();
        if (s.isEmpty()) continue;
        s = s.mid(4);
        if (s == lastLine) continue;
        lastLine = s;
        ui->errorTable->insertRow(rowNum);
        ui->errorTable->setItem(rowNum, 0, new QTableWidgetItem(s));
        auto getLine = [](QString s) -> int {
            try {
                int i = 0, len = 0;
                while (!s[i].isDigit()) i++;
                while (s[i+len].isDigit()) {
                    len++;
                }
                return s.mid(i, len).toInt();
            } catch (...) {
                return 0;
            }

        };
        ui->errorTable->setItem(rowNum, 1, new QTableWidgetItem(QString::number(getLine(s))));
        rowNum++;
    }
    ui->errorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->errorTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    fclose(output);
    fclose(source);
}

