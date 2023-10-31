#ifndef XLEXGENERATOR_H
#define XLEXGENERATOR_H
#include<iostream>
#include <numeric>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<queue>
#include<functional>
using namespace std;

using pii = pair<int, int>;

class XLEXGenerator {
public:
    XLEXGenerator() {}
    XLEXGenerator(string reg) {regExp = reg;}
    void init();	// 初始化
    void reg2NFA(); // Thompson构造法
    void NFA2DFA();	// 子集构造法
    void minimizeDFA();	// 最小化DFA
    void DFA2XLEX();	// DFA转换为词法分析程序

public:
    /* 成员函数 */
    void setRegExp(string reg) {regExp = reg;}  // 设置正则表达式
    string getRegExp() {return regExp;} // 获取正则表达式
    int getStart() {return start;}  // 获取起始状态
    int getEnd() {return end;}  // 获取终止状态
    set<char> getCharset() {return charset;}    // 获取字符集
    map<int, map<char, set<int>>> getNFA() {return NFA;}    // 获取NFA
    int getNFASize() {return idNFA-1;}  // 获取NFA节点数

    map<int, map<char, int>> getDFA() {return DFA;}   // 获取DFA
    int getDFASize() {return idDFA-1;}  // 获取DFA节点数
    map<int, set<int>> getStateMapReverse() {return stateMapReverse;}   // 获取状态映射集合
    set<int> getDFAendSet() {return DFAendSet;}   // 获取DFA终止状态集合

    map<int, map<char, int>> getMinDFA() {return minDFA;}   // 获取最小化DFA
    int getMinDFASize() {return idMinDFA-1;}    // 获取最小化DFA节点数
    string getXLEX() {return xlex;} // 获取词法分析程序
    set<int> getMinDFAendSet() {return minDFAendSet;}   // 获取最小化DFA终止状态集合

private:
    /* 成员变量 */
    /* reg to NFA */
    int idNFA = 1;			// 节点编号
    int start;		// 起始状态
    int end;		// 终止状态
    string regExp;	// 正则表达式
    set<char> charset;	// 字符集
    map<int, map<char, set<int>>> NFA;	// NFA

    /* NFA to DFA */
    int idDFA = 1;	// DFA节点编号
    map<int, map<char, int>> DFA;		// DFA
    map<set<int>, int> stateMap;			// 状态集合映射
    map<int, set<int>> stateMapReverse;		// 状态映射集合
    set<int> DFAendSet;	// DFA终止状态集合

    /* 最小化 DFA */
    int idMinDFA = 1;	// 最小化DFA节点编号
    map<int, map<char, int>> minDFA;	// 最小化DFA
    set<int> minDFAendSet;  // minDFA终止状态集合

    /* DFA to 词法分析程序 */
    string xlex;    // 词法分析程序

private:
    /* 工具函数 */
    int priority(char op);				// 优先级
    void addConnector();				// 添加连接符
    pii opConnect(pii a, pii b);		// 连接操作
    pii opUnion(pii a, pii b);			// 并操作
    pii opClosure(pii a);				// 闭包操作
    pii opOption(pii a);				// 可选操作
    pii opPosClosure(pii a);			// 正闭包操作
    pii binOp(char op, pii a, pii b);	// 双目运算符
    pii monOp(char op, pii a);			// 单目运算符
    set<int> getClosure(set<int> states);	// 获取状态集合states的闭包
    set<int> move(set<int> states, char c);	// 获取状态集合states通过字符c转换后的状态集合
};

struct DSU {
    vector<int> fa, siz;
    DSU(int n) : fa(n), siz(n, 1) { iota(fa.begin(), fa.end(), 0); }
    int find(int x) {
        return fa[x] == x? x:(fa[x] = find(fa[x]));
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (x > y) swap(x, y);
        siz[x] += siz[y];
        fa[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};

#endif // XLEXGENERATOR_H
