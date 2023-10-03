#include "Parser.h"

void Parser::init() {
    /* 关键字 */
    mp["asm"] = 21,  mp["auto"] = 22,  mp["bool"] = 23,  mp["break"] = 24,  mp["case"] = 25,
    mp["catch"] = 26,  mp["char"] = 27,  mp["class"] = 28,  mp["const"] = 29,  mp["const_cast"] = 30,
    mp["continue"] = 31,  mp["default"] = 32,  mp["delete"] = 33,  mp["do"] = 34,  mp["double"] = 35,
    mp["dynamic_cast"] = 36,  mp["else"] = 37,  mp["enum"] = 38,  mp["explicit"] = 39,  mp["export"] = 40,
    mp["extern"] = 41,  mp["false"] = 42,  mp["float"] = 43,  mp["for"] = 44,  mp["friend"] = 45,
    mp["goto"] = 46,  mp["if"] = 47,  mp["inline"] = 48,  mp["int"] = 49,  mp["long"] = 50,
    mp["mutable"] = 51,  mp["namespace"] = 52,  mp["new"] = 53,  mp["operator"] = 54,  mp["private"] = 55,
    mp["protected"] = 56,  mp["public"] = 57,  mp["register"] = 58,  mp["reinterpret_cast"] = 59,  mp["return"] = 60,
    mp["short"] = 61,  mp["signed"] = 62,  mp["sizeof"] = 63,  mp["static"] = 64,  mp["static_cast"] = 65,
    mp["struct"] = 66,  mp["switch"] = 67,  mp["template"] = 68,  mp["this"] = 69,  mp["throw"] = 70,
    mp["true"] = 71,  mp["try"] = 72,  mp["typedef"] = 73,  mp["typeid"] = 74,  mp["typename"] = 75,
    mp["union"] = 76,  mp["unsigned"] = 77,  mp["using"] = 78,  mp["virtual"] = 79,  mp["void"] = 80,
    mp["volatile"] = 81,  mp["wchar_t"] = 82,  mp["while"] = 83;

    /* 运算符 */
    // 算术运算符
    mp["+"] = 91,  mp["-"] = 92,  mp["*"] = 93,  mp["/"] = 94,  mp["%"] = 95,  mp["++"] = 96,  mp["--"] = 97;
    // 关系运算符
    mp["=="] = 98,  mp["!="] = 99,  mp[">"] = 100,  mp["<"] = 101,  mp[">="] = 102,  mp["<="] = 103;
    // 逻辑运算符
    mp["&&"] = 104,  mp["||"] = 105,  mp["!"] = 106;
    // 位运算符
    mp["&"] = 107,  mp["|"] = 108,  mp["^"] = 109,  mp["~"] = 110,  mp["<<"] = 111,  mp[">>"] = 112;
    // 赋值运算符
    mp["="] = 113,  mp["+="] = 114,  mp["-="] = 115,  mp["*="] = 116,  mp["/="] = 117,
    mp["%="] = 118,  mp["<<="] = 119,  mp[">>="] = 120,  mp["&="] = 121,  mp["^="] = 122,  mp["|="] = 123;
    // 杂项运算符
    mp["."] = 124,  mp["->"] = 125,  mp[","] = 126,  mp["::"] = 127;

    /* 特殊符号 */
    mp["?"] = 131,  mp[":"] = 132,  mp["["] = 133,  mp["]"] = 134,  mp[";"] = 135,
    mp["{"] = 136,  mp["}"] = 137,  mp["("] = 138,  mp[")"] = 139,  mp["#"] = 140,  mp["\\"] = 141;


    mp["#COMMENT"] = 151;	// 注释
    mp["#IDENTIFIER"] = 152;	// 标识符
    mp["#STRING"] = 153;		// 字符串
    mp["#CHARACTER"] = 154;	// 字符常量
    mp["#NUMBER"] = 155;		// 数字

    /* XC++风格 */
    my_style["="] = "<:=",  my_style["float"] = "f32",  my_style["double"] = "f64",  my_style["cin"] = "Read",
    my_style["cout"] = "Write",  my_style["int"] = "i32",  my_style["auto"] = "var",  my_style["!"] = " not ",
    my_style["||"] = " or ",  my_style["&&"] = " and ",  my_style["{"] = "BEGIN:",  my_style["}"] = "END";
}

/* 解析一个可带符号整数或浮点数
 */
string Parser::getIntorFloat() {
    int state = 0;
    vector<int> finals = {0, 0, 0, 1, 0, 1, 1, 0, 1};

    vector<vector<int>> transfer = {
            {0, 1, 6, 2, -1, -1},
            {-1, -1, 6, 2, -1, -1},
            {-1, -1, 3, -1, -1, -1},
            {8, -1, 3, -1, 4, -1},
            {-1, 7, 5, -1, -1, -1},
            {8, -1, 5, -1, -1, -1},
            {8, -1, 6, 3, 4, -1},
            {-1, -1, 5, -1, -1, -1},
            {8, -1, -1, -1, -1, -1}
    };

    auto make = [](char c) -> int {
        switch(c) {
            case ' ': return 0;
            case '+':
            case '-': return 1;
            case '.': return 3;
            case 'E':
            case 'e': return 4;
            default:
                int code = static_cast<int>(c);
                if (code >= 48 && code <= 57) {
                    return 2;
                } else {
                    return 5;
                }
        }
    };
    string s;
    for (int i=pc;i<text.size();i++) {
        char c = text[i];
        state = transfer[state][make(c)];
        if (state < 0) {
            pc = i;
            return s;
        } else {
            s += c;
        }
    }
    pc = text.size();
    return s;
}

/* 解析一个数字
 */
string Parser::getNum() {
    string s;
    if (text[pc] == '0') {
        // 八进制或十六进制
        if (text[pc+1] == 'x' || text[pc+1] == 'X') {	// 十六进制
            s += text.substr(pc, 2);
            pc += 2;
            while (isdigit(text[pc]) || ('a' <= text[pc] && text[pc] <= 'f') || ('A' <= text[pc] && text[pc] <= 'F'))
                s += text[pc++];
        } else if (isdigit(text[pc+1]) && text[pc+1] < '8') {	// 八进制
            while ('0' <= text[pc] && text[pc] <= '7')
                s += text[pc++];
        } else {	// 0 或含前导零的数
            s = getIntorFloat();
        }
    } else {
        s = getIntorFloat();
    }
    return s;
}

/* 根据全局变量 text, pc, cur_line 解析出一个 Token
 */
Token Parser::parse() {
    if (pc >= text.length()) {
        return {0, "", 0};
    }
    Token token;
    string s;
    if (isdigit(text[pc]) || (text[pc] == '+' || text[pc] == '-') && isdigit(text[pc+1])) { // 数字
        token.type = mp["#NUMBER"];
        token.val = getNum();
        token.line = cur_line;
    } else if (isalpha(text[pc]) || text[pc] == '_') {	// 标识符或关键字
        s += text[pc++];
        while (isalnum(text[pc]) || text[pc] == '_')
            s += text[pc++];
        if (mp.count(s)) {	// 关键字
            token.type = mp[s];
        } else {
            token.type = mp["#IDENTIFIER"];
        }
        token.val = s;
        token.line = cur_line;
    } else if (text[pc] == '\'') { // 字符常量
        token.type = mp["#CHARACTER"];
        s += text[pc++];
        while (text[pc] != '\'') {
            if (text[pc] == '\\')
                s += text[pc++];
            s += text[pc++];
        }
        s += text[pc++];
        token.val = s;
        token.line = cur_line;
    } else if (text[pc] == '"') {	// 字符串
        token.type = mp["#STRING"];
        s += text[pc++];
        while (text[pc] != '"') {
            if (text[pc] == '\\')
                s += text[pc++];
            s += text[pc++];
        }
        s += text[pc++];
        token.val = s;
        token.line = cur_line;
    } else if (text[pc] == '/' && text[pc+1] == '/') {	// 单行注释
        token.type = mp["#COMMENT"];
        while (text[pc] != '\n')
            s += text[pc++];
        pc++;
        token.val = s;
        token.line = cur_line++;
    } else if (text[pc] == '/' && text[pc+1] == '*') {	// 多行注释
        token.type = mp["#COMMENT"];
        token.line = cur_line;
        while (text[pc] != '*' || text[pc+1] != '/') {
            if (text[pc] == '\n') cur_line++;
            s += text[pc++];
        }
        s += text.substr(pc, 2);
        pc += 2;
        token.val = s;
    } else {	// 运算符或其他符号
        switch (text[pc]) {
            case '+': {
                if (text[pc+1] == '+') {
                    token = {mp["++"], "++", cur_line}; pc += 2;
                } else if (text[pc+1] == '=') {
                    token = {mp["+="], "+=", cur_line}; pc += 2;
                } else {
                    token = {mp["+"], "+", cur_line}; pc++;
                } break;
            } case '-': {
                if (text[pc+1] == '-') {
                    token = {mp["--"], "--", cur_line}; pc += 2;
                } else if (text[pc+1] == '=') {
                    token = {mp["-="], "-=", cur_line}; pc += 2;
                } else if (text[pc+1] == '>') {
                    token = {mp["->"], "->", cur_line}; pc += 2;
                } else {
                    token = {mp["-"], "-", cur_line}; pc++;
                } break;
            } case '*': {
                if (text[pc+1] == '=') {
                    token = {mp["*="], "*=", cur_line}; pc += 2;
                } else {
                    token = {mp["*"], "*", cur_line}; pc++;
                } break;
            } case '/': {
                if (text[pc+1] == '=') {
                    token = {mp["/="], "/=", cur_line}; pc += 2;
                } else {
                    token = {mp["/"], "/", cur_line}; pc++;
                } break;
            } case '%': {
                if (text[pc+1] == '=') {
                    token = {mp["%="], "%=", cur_line}; pc += 2;
                } else {
                    token = {mp["%"], "%", cur_line}; pc++;
                } break;
            } case '=': {
                if (text[pc+1] == '=') {
                    token = {mp["=="], "==", cur_line}; pc += 2;
                } else {
                    token = {mp["="], "=", cur_line}; pc++;
                } break;
            } case '!': {
                if (text[pc+1] == '=') {
                    token = {mp["!="], "!=", cur_line}; pc += 2;
                } else {
                    token = {mp["!"], "!", cur_line}; pc++;
                } break;
            } case '>': {
                if (text[pc+1] == '>') {
                    if (text[pc+2] == '=') {
                        token = {mp[">>="], ">>=", cur_line}; pc += 3;
                    } else {
                        token = {mp[">>"], ">>", cur_line}; pc += 2;
                    }
                } else if (text[pc+1] == '=') {
                    token = {mp[">="], ">=", cur_line}; pc += 2;
                } else {
                    token = {mp[">"], ">", cur_line}; pc++;
                } break;
            } case '<': {
                if (text[pc+1] == '<') {
                    if (text[pc+2] == '=') {
                        token = {mp["<<="], "<<=", cur_line}; pc += 3;
                    } else {
                        token = {mp["<<"], "<<", cur_line}; pc += 2;
                    }
                } else if (text[pc+1] == '=') {
                    token = {mp["<="], "<=", cur_line}; pc += 2;
                } else {
                    token = {mp["<"], "<", cur_line}; pc++;
                } break;
            } case '&': {
                if (text[pc+1] == '&') {
                    token = {mp["&&"], "&&", cur_line}; pc += 2;
                } else if (text[pc+1] == '=') {
                    token = {mp["&="], "&=", cur_line}; pc += 2;
                } else {
                    token = {mp["&"], "&", cur_line}; pc++;
                } break;
            } case '|': {
                if (text[pc+1] == '|') {
                    token = {mp["||"], "||", cur_line}; pc += 2;
                } else if (text[pc+1] == '=') {
                    token = {mp["|="], "|=", cur_line}; pc += 2;
                } else {
                    token = {mp["|"], "|", cur_line}; pc++;
                } break;
            } case '^': {
                if (text[pc+1] == '=') {
                    token = {mp["^="], "^=", cur_line}; pc += 2;
                } else {
                    token = {mp["^"], "^", cur_line}; pc++;
                } break;
            } case '~': {
                if (text[pc+1] == '=') {
                    token = {mp["~="], "~=", cur_line}; pc += 2;
                } else {
                    token = {mp["~"], "~", cur_line}; pc++;
                } break;
            } case ':': {
                if (text[pc+1] == ':') {
                    token = {mp["::"], "::", cur_line}; pc += 2;
                } else {
                    token = {mp[":"], ":", cur_line}; pc++;
                } break;
            } case '.': {
                token = {mp["."], ".", cur_line}; pc++;
                break;
            } case '?': {
                token = {mp["?"], "?", cur_line}; pc++;
                break;
            } case ',': {
                token = {mp[","], ",", cur_line}; pc++;
                break;
            } case '[': {
                token = {mp["["], "[", cur_line}; pc++;
                break;
            } case ']': {
                token = {mp["]"], "]", cur_line}; pc++;
                break;
            } case ';': {
                token = {mp[";"], ";", cur_line}; pc++;
                break;
            } case '{': {
                token = {mp["{"], "{", cur_line}; pc++;
                break;
            } case '}': {
                token = {mp["}"], "}", cur_line}; pc++;
                break;
            } case '(': {
                token = {mp["("], "(", cur_line}; pc++;
                break;
            } case ')': {
                token = {mp[")"], ")", cur_line}; pc++;
                break;
            } case '#': {
                token = {mp["#"], "#", cur_line}; pc++;
                break;
            } case '\\': {
                token = {mp["\\"], "\\", cur_line}; pc++;
                break;
            }
        }
    }
    return token;
}

void Parser::analyse() {
    tokens.clear();
    pc = 0, cur_line = 1;
    while (pc < text.length()) {
        while (pc < text.length() && (text[pc] == ' ' || text[pc] == '\n' || text[pc] == '\t')) {
            if (text[pc] == '\n') cur_line++;
            pc++;
        }
        auto temp = parse();
        if (temp.type != 0) tokens.emplace_back(temp);
        while (pc < text.length() && (text[pc] == ' ' || text[pc] == '\n' || text[pc] == '\t')) {
            if (text[pc] == '\n') cur_line++;
            pc++;
        }
    }
}

string Parser::print() {
    stringstream ss;
    for (auto &[type, val, line]:tokens) {
        ss<<val<<"\t\t";
        if (type >= 21 && type <= 83) ss<<"关键字"<<"\t";
        else if (type >= 91 && type <= 127) ss<<"运算符"<<"\t";
        else if (type >= 31 && type <= 141) ss<<"特殊符号"<<"\t";
        else if (type == 151) ss<<"注释"<<"\t";
        else if (type == 152) ss<<"标识符"<<"\t";
        else if (type == 153) ss<<"字符串"<<"\t";
        else if (type == 154) ss<<"字符常量"<<"\t";
        else if (type == 155) ss<<"数字"<<"\t";
        ss<<"Typeid: "<<type<<"\t";
        ss<<"行数 "<<line<<endl;
    }
    return ss.str();
}

string Parser::changeToX() {
    string XCpp;
    pc = 0;
    while (pc < text.length()) {
        while (pc < text.length() && (text[pc] == ' ' || text[pc] == '\n' || text[pc] == '\t')) {
            XCpp += text[pc++];
        }
        auto [_, temp, __] = parse();
        if (my_style.count(temp)) {
            XCpp += my_style[temp];
        } else {
            XCpp += temp;
            if (temp[0] == '/' && temp[1] == '/') XCpp += "\n";
        }
        while (pc < text.length() && (text[pc] == ' ' || text[pc] == '\n' || text[pc] == '\t')) {
            XCpp += text[pc++];
        }
    }
    return XCpp;
}
