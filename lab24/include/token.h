#ifndef _TOKEN_H_
#define _TOKEN_H_

#define EXPR_VAR 0
#define EXPR_NUM 1
#define EXPR_L_BRACE 2
#define EXPR_R_BRACE 3
#define EXPR_UN_PLUS 4
#define EXPR_UN_MINUS 5
#define EXPR_BIN_PLUS 6
#define EXPR_BIN_MINUS 7
#define EXPR_BIN_MULT 8
#define EXPR_BIN_DIV 9
#define EXPR_BIN_POW 10

#define PRECEDENCE_EMPTY -1

typedef struct {
    int expression;
    char variable;
    unsigned int number;
} token;

int op_precedence(token *tok);
void op_print(token tok);

#endif
