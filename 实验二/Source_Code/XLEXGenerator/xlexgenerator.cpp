#include "xlexgenerator.h"

int XLEXGenerator::priority(char op) {
    switch (op) {
        case '*':
        case '+':
        case '?': return 3;
        case '.': return 2;
        case '|': return 1;
        default:  return 0;
    }
}

void XLEXGenerator::addConnector() {
    for (int i = 0; i < regExp.length() - 1; i++) {
        char it = regExp[i], next = regExp[i + 1];
        if (it == '(' || it == '|')
            continue;
        if (next == ')' || next == '|' || next == '*' || next == '+' || next == '?')
            continue;
        regExp.insert(i + 1, ".");
        i++;
    }
}

pii XLEXGenerator::opConnect(pii a, pii b) {
    NFA[a.second]['#'].insert(b.first);
    return {a.first, b.second};
}

pii XLEXGenerator::opUnion(pii a, pii b) {
    NFA[idNFA]['#'].insert(a.first);
    NFA[idNFA++]['#'].insert(b.first);
    NFA[a.second]['#'].insert(idNFA);
    NFA[b.second]['#'].insert(idNFA++);
    return {idNFA - 2, idNFA - 1};
}

pii XLEXGenerator::opClosure(pii a) {
    NFA[idNFA]['#'].insert(a.first);
    NFA[idNFA]['#'].insert(idNFA + 1);
    NFA[a.second]['#'].insert(a.first);
    NFA[a.second]['#'].insert(idNFA + 1);
    return {idNFA++, idNFA++};
}

pii XLEXGenerator::opOption(pii a) {
    // NFA[idNFA]['#'].insert(idNFA + 1);
    // NFA[idNFA+2]['#'].insert(a.first);
    // NFA[idNFA+2]['#'].insert(idNFA);
    // NFA[a.second]['#'].insert(idNFA + 3);
    // NFA[idNFA+1]['#'].insert(idNFA + 3);
    // idNFA += 4;
    // return {idNFA - 2, idNFA - 1};
    NFA[a.first]['#'].insert(a.second);
    return {a.first, a.second};
}

pii XLEXGenerator::opPosClosure(pii a) {
    NFA[idNFA]['#'].insert(a.first);
    NFA[a.second]['#'].insert(a.first);
    NFA[a.second]['#'].insert(idNFA + 1);
    return {idNFA++, idNFA++};
}

pii XLEXGenerator::binOp(char op, pii a, pii b) {
    switch (op) {
        case '.': return opConnect(a, b);
        case '|': return opUnion(a, b);
    } return {};
}

pii XLEXGenerator::monOp(char op, pii a) {
    switch (op) {
        case '*': return opClosure(a);
        case '?': return opOption(a);
        case '+': return opPosClosure(a);
    } return {};
}

set<int> XLEXGenerator::getClosure(set<int> states) {
    set<int> res = states;
    function<void(set<int>)> dfs = [&](set<int> states) {   // 递归获取空集闭包
        for (auto state : states) {
            if (!NFA.count(state)) continue;    // 不存在转移的状态不处理
            if (!NFA[state].count('#')) continue;   // 不存在空转移的状态不处理
            for (auto next : NFA[state]['#']) {
                if (!res.count(next)) {
                    res.insert(next);
                    dfs({next});
                }
            }
        }
    };
    dfs(states);
    return res;
}

set<int> XLEXGenerator::move(set<int> states, char c) {
    set<int> res;
    for (auto state : states) {
        if (!NFA.count(state)) continue;    // 不存在转移的状态不处理
        if (!NFA[state].count(c)) continue; // 不存在字符c的转移不处理
        for (auto next : NFA[state][c]) {
            res.insert(next);
        }
    }
    return res;
}

// 使用Thompson构造法，通过双栈操作，将正则表达式转换为NFA
void XLEXGenerator::reg2NFA() {
    addConnector();	// 为正则表达式添加连接符
    stack<pii> nodeStack;	// 操作数栈 <起始状态, 终止状态>
    stack<char> opStack;	// 操作符栈
    for (int i = 0; i < regExp.length(); i++) {
        char it = regExp[i];
        if (it == '(') {
            opStack.push(it);
        } else if (it == ')') {	// 遇到右括号，弹出操作符栈中的操作符，直到遇到左括号
            while (opStack.top() != '(') {
                char op = opStack.top(); opStack.pop();
                pii a = nodeStack.top(); nodeStack.pop();
                if (op == '*' || op == '?' || op == '+') {
                    nodeStack.push(monOp(op, a));
                } else {
                    pii b = nodeStack.top(); nodeStack.pop();
                    nodeStack.push(binOp(op, b, a));
                }
            }
            opStack.pop();	// 弹出左括号
        } else if (it == '*' || it == '.' || it == '|' || it == '?' || it == '+') {	// 遇到操作符，弹出操作符栈中优先级大于等于当前操作符的操作符
            while (!opStack.empty() && priority(opStack.top()) >= priority(it)) {
                char op = opStack.top(); opStack.pop();
                pii a = nodeStack.top(); nodeStack.pop();
                if (op == '*' || op == '?' || op == '+') {
                    nodeStack.push(monOp(op, a));
                } else {
                    pii b = nodeStack.top(); nodeStack.pop();
                    nodeStack.push(binOp(op, b, a));
                }
            }
            opStack.push(it);	// 将当前操作符压入操作符栈
        } else {	// 遇到操作数，创建一个新的节点，将其压入操作数栈
            NFA[idNFA][it].insert(idNFA + 1);
            nodeStack.push({idNFA++, idNFA++});
            charset.insert(it);
        }
    }
    while (!opStack.empty()) {	// 将操作符栈中剩余的操作符弹出
        char op = opStack.top(); opStack.pop();
        pii a = nodeStack.top(); nodeStack.pop();
        if (op == '*' || op == '?' || op == '+') {
            nodeStack.push(monOp(op, a));
        } else {
            pii b = nodeStack.top(); nodeStack.pop();
            nodeStack.push(binOp(op, b, a));
        }
    }
    // 获取起始状态和终止状态
    start = nodeStack.top().first;
    end = nodeStack.top().second;
}

// 使用子集构造法，将NFA转换为DFA
void XLEXGenerator::NFA2DFA() {
    set<int> startSet = getClosure({start});    // 获取起始状态的闭包
    stateMap[startSet] = idDFA;
    stateMapReverse[idDFA++] = startSet;
    queue<set<int>> q;  // BFS队列
    q.push(startSet);
    while (!q.empty()) {    // BFS
        set<int> u = q.front(); q.pop();
        for (char c : charset) {
            auto v = getClosure(move(u, c));    // 获取状态集合u通过字符c转换后的状态集合的闭包
            if (v.empty()) continue;        // 空集不处理
            if (!stateMap.count(v)) {
                stateMap[v] = idDFA;    // 添加新状态
                stateMapReverse[idDFA++] = v;
                q.push(v);
            }
            DFA[stateMap[u]][c] = stateMap[v];    // 添加状态转换
        }
    }
    for (auto& [k, v]:stateMapReverse) {   // 获取终止状态集合
        if (v.count(end)) {
            DFAendSet.insert(k);
        }
    }
}

// 使用合并的方法，将DFA最小化
void XLEXGenerator::minimizeDFA() {
    DSU dsu(idDFA);
    map<int, int> DFA2minDFA;
    for (int i=1;i<idDFA;i++) {
        if (!DFA.count(i))    // 空集不处理
            goto CREATE;
        if (i != dsu.find(i))   // 如果已经合并则不处理
            continue;
        for (int j=i+1;j<idDFA;j++) {
            if (!DFA.count(j)) {    // 空集不处理
                continue;
            }
            // 终态只能与终态合并，非终态只能与非终态合并
            if (DFAendSet.count(i) ^ DFAendSet.count(j))
                continue;
            if (j != dsu.find(j))   // 如果已经合并则不处理
                continue;
            bool flag = true;
            for (char c : charset) {
                if (!DFA[i].count(c) && !DFA[j].count(c))    // 如果两个状态都不存在转移则不处理
                    continue;
                if (DFA[i].count(c) ^ DFA[j].count(c)) { // 如果两个状态只有一个存在转移则不合并
                    flag = false;
                    break;
                }
                if (!dsu.same(DFA[i][c], DFA[j][c])) { // 如果两个状态转移后的状态不在同一个集合则不合并
                    flag = false;
                    break;
                }
            }
            if (flag) { // 合并两个状态
                dsu.merge(i, j);
                j = i+1;    // 重新开始合并
            }
        }
        minDFA[idMinDFA] = DFA[i];    // 记录合并后的状态转移
CREATE: DFA2minDFA[i] = idMinDFA++;   // 记录合并后的状态
        // 记录合并后的终态
        if (DFAendSet.count(i)) {
            minDFAendSet.insert(DFA2minDFA[i]);
        }
    }
    for (auto& [node, ma]:minDFA) {
        for (auto& [k, v]:ma) {
            v = DFA2minDFA[dsu.find(v)];
        }
    }
}

// 根据最小化DFA生成c++词法分析程序
void XLEXGenerator::DFA2XLEX() {
    stringstream ss;
    ss << "#include<iostream>\n";
    ss << "#include<string>\n";
    ss << "using namespace std;\n";
    ss << "int main() {\n";
    ss << "    string s;\n";
    ss << "    cin>>s;\n";
    ss << "    int state = 1;\n";
    ss << "    for (char c : s) {\n";
    ss << "        switch (state) {\n";
    for (auto& [node, ma]:minDFA) {
        ss << "            case " << node << ":\n";
        ss << "                switch (c) {\n";
        for (auto& [k, v]:ma) {
            ss << "                    case '" << k << "': state = " << v << "; break;\n";
        }
        ss << "                    default: state = 0;\n";
        ss << "                }\n";
        ss << "                break;\n";
    }
    ss << "            default: state = 0;\n";
    ss << "        }\n";
    ss << "    }\n";
    ss << "    switch (state) {\n";
    for (auto it : minDFAendSet) {
        ss << "        case " << it << ": cout<<\"匹配成功\"<<endl; break;\n";
    }
    ss << "        default: cout<<\"匹配失败\"<<endl;\n";
    ss << "    }\n";
    ss << "}\n";
    xlex = ss.str();
}

// 初始化
void XLEXGenerator::init() {
    idNFA = 1;
    idDFA = 1;
    idMinDFA = 1;
    charset.clear();
    NFA.clear();
    DFA.clear();
    stateMap.clear();
    stateMapReverse.clear();
    DFAendSet.clear();
    minDFA.clear();
    minDFAendSet.clear();
    xlex.clear();

    reg2NFA();
    NFA2DFA();
    minimizeDFA();
    DFA2XLEX();
}
