/****************************************************/
/* File: parse.c                                    */
/* The parser implementation for the TINY compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode *stmt_sequence(void);
static TreeNode *statement(void);
static TreeNode *if_stmt(void);
static TreeNode *repeat_stmt(void);
static TreeNode *for_stmt(void);
static TreeNode *assign_stmt(void);
static TreeNode *read_stmt(void);
static TreeNode *write_stmt(void);

static TreeNode *exp(void);
static TreeNode *bitand_exp(void);
static TreeNode *cmp_exp(void);
static TreeNode *simple_exp(void);
static TreeNode *term(void);
static TreeNode *power(void);
static TreeNode *bitnot_exp(void);
static TreeNode *factor(void);

static TreeNode *reg_exp(void);
static TreeNode *reg_and_exp(void);
static TreeNode *reg_term(void);
static TreeNode *reg_factor(void);

static void syntaxError(const char *message) {
    fprintf(listing, "\n>>> ");
    fprintf(listing, "Syntax error at line %d: %s", lineno, message);
    Error = TRUE;
}

static void match(TokenType expected) {
    if (token == expected) token = getToken();
    else {
        syntaxError("unexpected token -> ");
        printToken(token, tokenString);
        fprintf(listing, "      ");
    }
}

TreeNode *stmt_sequence(void) {
    TreeNode *t = statement();
    TreeNode *p = t;
    while ((token != ENDFILE) && (token != END) &&
        (token != ELSE) && (token != UNTIL) && (token != ENDDO) && (token != RBRACKET)) {
        TreeNode *q;
        match(SEMI);
        q = statement();
        if (q != NULL) {
            if (t == NULL) t = p = q;
            else /* now p cannot be NULL either */
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    return t;
}


//P394
//lineno: 961
TreeNode *statement(void) {
    TreeNode *t = NULL;
    switch (token) {
    case IF: t = if_stmt(); break;
    case REPEAT: t = repeat_stmt(); break;
    case FOR: t = for_stmt(); break;
    case ID: t = assign_stmt(); break;
    case READ: t = read_stmt(); break;
    case WRITE: t = write_stmt(); break;
    default: syntaxError("unexpected token -> ");
        printToken(token, tokenString);
        token = getToken();
        break;
    } /* end case */
    return t;
}


//P394
//lineno: 977
TreeNode *if_stmt(void) {
    TreeNode *t = newStmtNode(IfK);
    match(IF);
    match(LPAREN);  // 匹配左括号
    if (t != NULL) t->child[0] = exp();
    match(RPAREN);  // 匹配右括号

    match(LBRACKET);    // 匹配左中括号
    if (t != NULL) t->child[1] = stmt_sequence();
    match(RBRACKET);    // 匹配右中括号

    if (token == ELSE) {
        match(ELSE);
        match(LBRACKET);
        if (t != NULL) t->child[2] = stmt_sequence();
        match(RBRACKET);
    }
    return t;
}

//P394
//lineno:991
TreeNode *repeat_stmt(void) {
    TreeNode *t = newStmtNode(RepeatK);
    match(REPEAT);
    if (t != NULL) t->child[0] = stmt_sequence();
    match(UNTIL);
    if (t != NULL) t->child[1] = exp();
    return t;
}

TreeNode *for_stmt(void) {
    TreeNode *t = newStmtNode(ForK);
    match(FOR);
    if (t != NULL) {
        TreeNode *p = newStmtNode(AssignK);
        if ((p != NULL) && (token == ID))
            p->attr.name = copyString(tokenString);
        match(ID);
        if (token == ASSIGN) {
            match(ASSIGN);
            if (p != NULL) p->child[0] = simple_exp();
        }
        t->child[0] = p;    // 第一个孩子存放赋值语句
    }
    if (token == TO) {
        match(TO);
        t->attr.op = TO;
    } else if (token == DOWNTO) {
        match(DOWNTO);
        t->attr.op = DOWNTO;
    }
    if (t != NULL) t->child[1] = simple_exp();  // 第二个孩子存放表达式
    match(DO);
    if (t != NULL) t->child[2] = stmt_sequence();   // 第三个孩子存放语句序列
    match(ENDDO);
    return t;
}

TreeNode *assign_stmt(void) {
    TreeNode *t = newStmtNode(AssignK);
    if ((t != NULL) && (token == ID))
        t->attr.name = copyString(tokenString);
    match(ID);
    switch (token) {
    case ASSIGN:        // 赋值语句
        match(ASSIGN);
        if (t != NULL) t->child[0] = exp();
        break;
    case ADD_ASSIGN:    // 加法赋值语句
        t->kind.stmt = Add_AssignK;
        match(ADD_ASSIGN);
        if (t != NULL) t->child[0] = exp();
        break;
    case REG_ASSIGN:    // 正则赋值语句
        t->kind.stmt = Reg_AssignK;
        match(REG_ASSIGN);
        if (t != NULL) t->child[0] = reg_exp();
        break;
    }
    return t;
}

TreeNode *read_stmt(void) {
    TreeNode *t = newStmtNode(ReadK);
    match(READ);
    if ((t != NULL) && (token == ID))
        t->attr.name = copyString(tokenString);
    match(ID);
    return t;
}

TreeNode *write_stmt(void) {
    TreeNode *t = newStmtNode(WriteK);
    match(WRITE);
    if (t != NULL) t->child[0] = exp();
    return t;
}

TreeNode *exp(void) {
    TreeNode *t = bitand_exp();
    while (token == OR) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            p->child[1] = bitand_exp();
        }
    }
    return t;
}

TreeNode *bitand_exp(void) {
    TreeNode *t = cmp_exp();
    while (token == AND) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            p->child[1] = cmp_exp();
        }
    }
    return t;
}

TreeNode *cmp_exp(void) {
    TreeNode *t = simple_exp();
    if ((token == LT) || (token == EQ) || (token == GT) || (token == LE) || (token == NE) || (token == GE)) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
        }
        match(token);
        if (t != NULL)
            t->child[1] = simple_exp();
    }
    return t;
}

TreeNode *simple_exp(void) {
    TreeNode *t = term();
    while ((token == PLUS) || (token == MINUS)) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            t->child[1] = term();
        }
    }
    return t;
}

TreeNode *term(void) {
    TreeNode *t = power();
    while ((token == TIMES) || (token == OVER) || (token == MOD)) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            p->child[1] = power();
        }
    }
    return t;
}

TreeNode *power(void) {
    TreeNode *t = bitnot_exp();
    if (token == POWER) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            p->child[1] = power();  // 右递归实现右结合运算符
        }
    }
    return t;
}

TreeNode *bitnot_exp(void) {
    if (token != NOT) {
        return factor();
    }
    TreeNode *p = newExpNode(OpK);
    if (p != NULL) {
        p->attr.op = token;
        match(token);
        p->child[0] = bitnot_exp(); // 用递归实现右结合单目运算符
    }
    return p;
}

TreeNode *factor(void) {
    TreeNode *t = NULL;
    switch (token) {
    case NUM:
        t = newExpNode(ConstK);
        if ((t != NULL) && (token == NUM))
            t->attr.val = atoi(tokenString);
        match(NUM);
        break;
    case ID:
        t = newExpNode(IdK);
        if ((t != NULL) && (token == ID))
            t->attr.name = copyString(tokenString);
        match(ID);
        break;
    case LPAREN:
        match(LPAREN);
        t = exp();
        match(RPAREN);
        break;
    default:
        syntaxError("unexpected token -> ");
        printToken(token, tokenString);
        token = getToken();
        break;
    }
    return t;
}

TreeNode *reg_exp(void) {
	TreeNode *t = reg_and_exp();
    while (token == REGOR) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            p->child[1] = reg_and_exp();
        }
    }
    return t;
}

TreeNode *reg_and_exp(void) {
	TreeNode *t = reg_term();
    while (token == CONCAT) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
            p->child[1] = reg_term();
        }
    }
    return t;
}

TreeNode *reg_term(void) {
	TreeNode *t = reg_factor();
    while ((token == CLOSURE) || (token == OPTIONAL)) {
        TreeNode *p = newExpNode(OpK);
        if (p != NULL) {
            p->child[0] = t;
            p->attr.op = token;
            t = p;
            match(token);
        }
    }
    return t;
}

TreeNode *reg_factor(void) {
	TreeNode *t = NULL;
    switch (token) {
    case LPAREN:
        match(LPAREN);
        t = reg_exp();
        match(RPAREN);
        break;
    case ID:
        if (strlen(tokenString) == 1) {
            t = newExpNode(IdK);
            if ((t != NULL) && (token == ID))
                t->attr.name = copyString(tokenString);
            match(ID);
            break;
        }
    default:
        syntaxError("unexpected token -> ");
        printToken(token, tokenString);
        token = getToken();
        break;
    }
    return t;
}

/****************************************/
/* the primary function of the parser   */
/****************************************/
/* Function parse returns the newly
 * constructed syntax tree
 */
TreeNode *parse(void) {
    TreeNode *t;
    token = getToken();
    t = stmt_sequence();
    if (token != ENDFILE)
        syntaxError("Code ends before file\n");
    return t;
}
