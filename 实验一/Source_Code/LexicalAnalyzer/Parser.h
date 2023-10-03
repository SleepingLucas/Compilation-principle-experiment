#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include <sstream>
using namespace std;

using TokenType = int;	// Token 的类型

struct Token {
    TokenType type;		// Token 的类型
    string val;			// Token 的值
    int line;			// Token 所在行数
};

class Parser {
public:
    Parser() {init();}
    Parser(string s):text(s) {init();}
    void setText(string s) {text = s;}
    string getText() {return text;}
    void analyse();				// 分析 text
    string print();				// 打印分析结果
    string changeToX();         // 变成XC++风格

private:
    /* 成员变量 */
    map<string, TokenType> mp;	    // Token 映射表
    int pc, cur_line;			    // 字符串当前遍历指针、当前遍历行数
    string text;				    // 待分析字符串
    vector<Token> tokens;		    // 已分析的 Token 流
    map<string, string> my_style;   // XC++

private:
    /* 工具函数 */
    void init();				// 初始化 Token 映射表
    string getIntorFloat();		// 根据 text 与当前遍历指针 pc 解析出一个整数或浮点数
    string getNum();			// 根据 text 与当前遍历指针 pc 解析出一个数字
    Token parse();				// 根据 text 与当前遍历指针 pc 解析出一个 Token
};

#endif // PARSER_H
