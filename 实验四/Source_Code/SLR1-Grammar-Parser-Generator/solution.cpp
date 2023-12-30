#include "solution.h"

void Solution::init() {
    istream *input = &cin;
    #if defined(INQT)
        stringstream ss(str);
        input = &ss;
    #endif
    string s;
    while (getline(*input, s)) {
        if (s == "#") break;
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        if (s.empty()) continue;
        char left = s[0];
        if (start == ' ') start = left;
        non_terminal.insert(left);
        charSet.insert(left);
        s = s.substr(3);
        // 处理可能存在的 |
        do {
            int idx = s.find('|');
            if (idx == string::npos) {
                grammar[left].insert(s);
                for (auto &c:s) if (c != '@') charSet.insert(c);
                break;
            }
            for (auto &c:s.substr(0, idx)) if (c != '@') charSet.insert(c);
            grammar[left].insert(s.substr(0, idx));
            s = s.substr(idx + 1);
        } while (true);
    }
    if (grammar[start].size() > 1) {	// 文法规则的扩充
        char new_start = 'Z';
        if (!non_terminal.count('S')) new_start = 'S';
        else while (non_terminal.count(new_start)) new_start--;
        non_terminal.insert(new_start);
        grammar[new_start].insert(string(1, start));
        start = new_start;
    }
}

void Solution::clear() {
    grammar.clear();
    start = ' ';
    non_terminal.clear();
    charSet.clear();
    first.clear();
    follow.clear();
    DFA.clear();
    stateMap.clear();
    stateMapReverse.clear();
    conflict.clear();
    idDFA = 0;
    inputAnalysisTable.clear();
    gotoAnalysisTable.clear();
    isSLR1 = false;
    analysisStack.clear();
    analysisLog.clear();
}

void Solution::clearAnalysis() {
    sentence.clear();
    analysisStack.clear();
    analysisLog.clear();
}

void Solution::Debug() {
    calcFirst();
    calcFollow();
    calcDFA();
    judgeSLR1();
    if (isSLR1) {
        calcAnalysisTable();
        // analysis();
    }
#ifdef DE_BUG
    SEP = "\n";
    debug(grammar, first, follow, DFA, stateMap, "\n", isSLR1, conflict)
    if (isSLR1) {
        debug(inputAnalysisTable, gotoAnalysisTable)
        NEWLINE = true;
        debug("\n", analysisLog)   
    }
#endif
}

void Solution::calcFirst() {
    for (auto &it:non_terminal) {
        first[it] = set<char>();
    }
    bool flag = true;
    while (flag) {  // 直到 first 集合不再变化
        flag = false;
        for (auto &[left, right]:grammar) {     // 遍历每个非终结符号
            for (auto &s:right) {               // 遍历每个产生式
                int k = 0, n = s.size();
                bool continue_flag = true;
                while (continue_flag && k < n) {
                    if (s[k] == '@') ;
                    else if (!isupper(s[k])) {	// 终结符号
                        flag |= first[left].insert(s[k]).second;
                        continue_flag = false;
                    } else {	// 非终结符号
                        for (auto &c:first[s[k]]) {     // 将 first[s[k]] 中的元素加入 first[left]
                            if (c != '@') {
                                flag |= first[left].insert(c).second;
                            }
                        }
                        if (first[s[k]].count('@') == 0) {	// 如果该非终结符号不含空串，则不再继续
                            continue_flag = false;
                        }
                    }
                    k++;
                }
                if (continue_flag) {    // 如果该产生式的每个符号都含有空串，则将空串加入 first[left]
                    flag |= first[left].insert('@').second;
                }
            }
        }
    }
}

void Solution::calcFollow() {
    for (auto &it:non_terminal) {
        follow[it] = set<char>();
    }
    follow[start].insert('$');      // 将 $ 加入 follow[start]
    bool flag = true;
    while (flag) {
        flag = false;
        for (auto &[left, right]:grammar) {     // 遍历每个非终结符号
            for (auto &s:right) {               // 遍历每个产生式
                // left -> X1 X2 ... Xn
                int k = 0, n = s.size();
                while (k < n) {
                    if (!isupper(s[k])) {k++; continue;}
                    // 非终结符号
                    int j = k + 1;
                    // Xk+1 Xk+2 ... Xn
                    while (j < n && isupper(s[j]) && first[s[j]].count('@')) {	// 该非终结符号的first集合含空串
                        for (auto &c:first[s[j]]) {
                            if (c != '@') {
                                flag |= follow[s[k]].insert(c).second;
                            }
                        }
                        j++;
                    }
                    if (j == n) {	// 该非终结符号的first集合含空串
                        for (auto &c:follow[left]) {
                            flag |= follow[s[k]].insert(c).second;
                        }
                    } else {	// 该非终结符号的first集合不含空串
                        if (!isupper(s[j])) {	// 终结符号
                            flag |= follow[s[k]].insert(s[j]).second;
                        } else {
                            for (auto &c:first[s[j]]) {
                                if (c != '@') {
                                    flag |= follow[s[k]].insert(c).second;
                                }
                            }
                        }
                    }
                    k++;
                }
            }
        }
    }
}

void Solution::calcDFA() {
    auto addDependency = [&](vector<Rule> &v) {	// 添加依赖
        bool flag = true;
        while (flag) {
            flag = false;
            vector<Rule> tmp;
            for (auto &[left, right, idx]:v) {
                // int idx = right.find('.');
                if (idx == right.size() - 1) continue;	// .在最后
                if (!isupper(right[idx + 1])) continue;	// .后面是终结符号
                char c = right[idx + 1];
                for (auto &s:grammar[c]) {
                    if (s == "@") tmp.push_back({c, "."});
                    else tmp.push_back({c, "." + s});
                }
            }
            for (auto &it:tmp) {
                if (find(v.begin(), v.end(), it) == v.end()) {
                    v.push_back(it);
                    flag = true;
                }
            }
        }
    };
    // DFA 初态
    DFA[idDFA] = map<char, int>();
    stateMap[idDFA] = {{start, "." + *grammar[start].begin()}};
    addDependency(stateMap[idDFA]);
    stateMapReverse[stateMap[idDFA]] = idDFA;

    queue<int> q;
    q.push(idDFA++);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        auto status = stateMap[u];
        map<char, vector<Rule>> temp;   // 临时存储
        for (auto &[left, right, idx]:status) {
            // int idx = right.find('.');
            if (idx == right.size() - 1) continue;	// .在最后
            char nextC = right[idx+1];
            string shifted = right;
            swap(shifted[idx], shifted[idx+1]);
            temp[nextC].push_back({left, shifted, idx+1});
        }
        for (auto &[nextC, needToAdd]:temp) {   
            addDependency(needToAdd);   // 添加依赖
            if (!stateMapReverse.count(needToAdd)) {	// 如果不存在该状态，则新建一个状态
                stateMap[idDFA] = needToAdd;
                stateMapReverse[needToAdd] = idDFA;
                q.push(idDFA++);
            }
            DFA[u][nextC] = stateMapReverse[needToAdd];
        }
    }
}

void Solution::judgeSLR1() {
    isSLR1 = true;
    for (auto &[DFAidx, status]:stateMap) {
        map<char, vector<Rule>> shifting;	// 移进项
        vector<Rule> reduction;	// 归约项
        for (auto &[left, right, idx]:status) {
            // int idx = right.find('.');
            if (idx == right.size() - 1) {	// 归约项
                reduction.emplace_back(left, right);
            } else {	// 移进项
                if (!isupper(right[idx+1]))	// 终结符号
                    shifting[right[idx+1]].emplace_back(left, right);
            }
        }
        if (reduction.empty()) continue;
        // 移进-归约冲突
        for (auto &[left, right, idx]:reduction) {
            auto Follow = follow[left];
            for (auto [c, v]:shifting) {
                if (Follow.count(c)) {
                    isSLR1 = false;
                    v.emplace_back(left, right);
                    conflict.emplace_back(DFAidx, SHIFT_REDUCE_CONFLICT, v);
                }
            }
        }
        // 归约-归约冲突
        for (int i = 0; i < reduction.size(); i++) {
            for (int j = i + 1; j < reduction.size(); j++) {
                set<char> result;
                set_intersection(follow[reduction[i].first].begin(), follow[reduction[i].first].end(),
                                 follow[reduction[j].first].begin(), follow[reduction[j].first].end(),
                                 inserter(result, result.begin()));
                if (result.empty()) continue;
                isSLR1 = false;
                conflict.emplace_back(DFAidx, REDUCE_REDUCE_CONFLICT, vector<Rule>{reduction[i], reduction[j]});
            }
        }
    }
}

void Solution::calcAnalysisTable() {
    // 填入移进项
    for (auto &[idx, m]:DFA) {
        for (auto &[c, next]:m) {
            if (isupper(c)) {
                gotoAnalysisTable[idx][c] = next;
            } else {
                inputAnalysisTable[idx][c].type = SHIFT;
                inputAnalysisTable[idx][c].num = next;
            }
        }
    }

    // 填入归约项
    for (auto &[DFAidx, status]:stateMap) {
        for (auto &[left, right, idx]:status) {
            if (idx == right.size() - 1) {	// 归约项
                if (left == start) {
                    inputAnalysisTable[DFAidx]['$'].type = ACCEPT;
                } else {
                    auto temp = right.substr(0, right.size() - 1);
                    if (temp.empty()) temp = "@";    // 空串
                    for (auto &c:follow[left]) {
                        inputAnalysisTable[DFAidx][c].type = REDUCE;
                        inputAnalysisTable[DFAidx][c].rule = {left, temp};
                    }
                }
            }
        }
    }
}

void Solution::analysis() {
    int nowStep = 1;            // 当前步骤
    int analysisIdx = 0;        // 当前分析的位置 
    sentence.push_back('$');
    analysisStack.emplace_back(0, '$');

    auto stack2str = [](const vector<StackNode> &v) {   // 分析栈转字符串
        string s;
        for (auto &[DFAidx, c]:v) {
            s += string(1, c) + " " + to_string(DFAidx) + " ";
        }
        return s;
    };

    while (true) {
        LogNode node(nowStep++, stack2str(analysisStack), sentence.substr(analysisIdx), " ");
        int nowstate = analysisStack.back().state;
        char nowchar = sentence[analysisIdx];

        if (!inputAnalysisTable[nowstate].count(nowchar)) {
            node.action = "错误, 该句子不符合文法规则";
            analysisLog.push_back(node);
            break;
        }
        
        auto todo = inputAnalysisTable[nowstate][nowchar];
        if (todo.type == SHIFT) {    // 移进
            node.action = "移进" + to_string(todo.num);
            analysisStack.emplace_back(todo.num, nowchar);
            analysisIdx++;
        } else if (todo.type == REDUCE) {    // 归约
            node.action = "用 " + string(1, todo.rule.first) + "->" + todo.rule.second + " 归约";
            int len = todo.rule.second.size();
            if (len == 1 && todo.rule.second[0] == '@') len = 0;
            while (len--) analysisStack.pop_back();
            analysisStack.emplace_back(gotoAnalysisTable[analysisStack.back().state][todo.rule.first], todo.rule.first);
        } else {
            node.action = "接受";
        }
        analysisLog.push_back(node);
        if (todo.type == ACCEPT) break;
    }
}
