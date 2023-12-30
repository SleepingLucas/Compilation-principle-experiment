#ifndef SOLUTION_H
#define SOLUTION_H

#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
#include<sstream>
using namespace std;

#define INQT

#ifndef INQT
    #define DE_BUG
#endif
#ifdef DE_BUG
#include "D:\c++\DEBUG.h"
using namespace DEBUG_;
#endif

struct Rule;
struct Conflict;
struct Action;
struct StackNode;
struct LogNode;

// 大写英文字母为非终结符号，小写英文字母为终结符号，@表示空串
class Solution {
public:
    Solution() = default;
    Solution(string str):str(str) {}
    void init();		// 初始化文法
    void clear();        // 清空文法
    void clearAnalysis();   // 清空分析栈和日志
    void Debug();
    void calcFirst();	// 求first集
    void calcFollow();	// 求follow集
    void calcDFA();		// 求DFA
    void judgeSLR1();	// 判断是否为 SLR(1) 文法
    void calcAnalysisTable();	// 求分析表
    void analysis();	// 分析句子

public:
    void setStr(string str) { this->str = str; }
    void setSentence(string sentence) { this->sentence = sentence; }
    bool getIsSLR1() { return isSLR1; }
    map<char, set<char>> getFirst() { return first; }
    map<char, set<char>> getFollow() { return follow; }
    set<char> getNonTerminal() { return non_terminal; }
    set<char> getCharSet() { return charSet; }
    char getStart() { return start; }
    map<int, map<char, int>> getDFA() { return DFA; }
    map<int, vector<Rule>> getStateMap() { return stateMap; }
    vector<Conflict> getConflict() { return conflict; }
    map<int, map<char, Action>> getInputAnalysisTable() { return inputAnalysisTable; }
    map<int, map<char, int>> getGotoAnalysisTable() { return gotoAnalysisTable; }
    vector<LogNode> getAnalysisLog() { return analysisLog; }

private:
    string str;	// 输入的文法
    map<char, set<string>> grammar;	// 文法
    char start = ' ';	// 文法开始符号
    set<char> non_terminal;		// 非终结符号
    set<char> charSet;          // 出现过的符号
    map<char, set<char>> first;		// first 集合
    map<char, set<char>> follow;	// follow 集合

    int idDFA = 0;	// DFA 状态编号
    map<int, map<char, int>> DFA;	// DFA
    map<int, vector<Rule>> stateMap;	// 状态映射
    map<vector<Rule>, int> stateMapReverse;		// 状态逆映射
    bool isSLR1 = false;    // 判断是否为 SLR(1) 文法
    vector<Conflict> conflict;	// 冲突信息

    map<int, map<char, Action>> inputAnalysisTable;	// 输入分析表
    map<int, map<char, int>> gotoAnalysisTable;	// GOTO 分析表

    string sentence;            // 待分析的句子  
    vector<StackNode> analysisStack;	// 分析栈
    vector<LogNode> analysisLog;	    // 日志
};

struct Rule {
    char first;	// 文法规则左部
    string second;	// 文法规则右部
    int idx;		// 运行位置

    Rule() = default;
    Rule(char first, string second, int idx = 0):first(first), second(second), idx(idx) {}

    bool operator<(const Rule &r) const {
        return make_pair(first, second) < make_pair(r.first, r.second);
    }

    bool operator==(const Rule &r) const {
        return make_pair(first, second) == make_pair(r.first, r.second);
    }

    friend ostream& operator<<(ostream &os, const Rule &r) {
        #ifdef DE_BUG
            os << make_pair(r.first, r.second);
        #else
            os << "<" << r.first << ", " << r.second << ">";
        #endif
        
        return os;
    }
};

enum ConflictType {
    SHIFT_REDUCE_CONFLICT,	// 移进-归约冲突
    REDUCE_REDUCE_CONFLICT	// 归约-归约冲突
};

struct Conflict {
    int num;	// DFA 状态编号
    ConflictType type;	// 冲突类型
    vector<Rule> rule;	// 冲突的规则

    Conflict() = default;
    Conflict(int num, ConflictType type, vector<Rule> rule):num(num), type(type), rule(rule) {}


    friend ostream& operator<<(ostream &os, const Conflict &c) {
        os << "DFA 状态编号: " << c.num << "\n";
                                          os << "冲突类型: " << (c.type == SHIFT_REDUCE_CONFLICT ? "移进-归约冲突" : "归约-归约冲突") << "\n";
                                       os << "冲突的规则: \n";
        for (auto &it:c.rule) {
            os << it.first << " -> " << it.second << "\n";
        }
        return os;
    }
};

enum ActionType {
    SHIFT,	// 移进
    REDUCE,	// 归约
    ACCEPT	// 接受
};

struct Action {
    ActionType type;	// 动作类型
    int num;	// 移进的 DFA 状态编号
    Rule rule;	// 归约的规则

    Action() = default;
    Action(ActionType type, int num):type(type), num(num) {}
    Action(ActionType type, Rule rule):type(type), rule(rule) {}

    friend ostream& operator<<(ostream &os, const Action &a) {
        os << "动作类型: " << (a.type == SHIFT ? "移进" : (a.type == REDUCE ? "归约" : "接受")) << "\t";
        if (a.type == SHIFT) {
            os << "移进的 DFA 状态编号: " << a.num << "\t";
        } else if (a.type == REDUCE) {
            os << "归约的规则: " << a.rule << "\t";
        }
        return os;
    }
};

// 分析栈内的元素
struct StackNode {
    int state;      // DFA 状态编号
    char symbol;    // 符号

    StackNode() = default;
    StackNode(int state, char symbol):state(state), symbol(symbol) {}
};

struct LogNode {
    int step;                   // 步骤
    string analysisStackData;   // 分析栈
    string inputData;           // 输入串
    string action;              // 动作

    LogNode() = default;
    LogNode(int step, string analysisStackData, string inputData, string action = ""):
        step(step), analysisStackData(analysisStackData), inputData(inputData), action(action) {}

    friend ostream& operator<<(ostream &os, const LogNode &l) {
        os << "步骤: " << l.step << "\t";
        os << "分析栈: " << l.analysisStackData << "\t";
        os << "输入串: " << l.inputData << "\t";
        os << "动作: " << l.action << "\t";
        return os;
    }
};

#endif // SOLUTION_H
