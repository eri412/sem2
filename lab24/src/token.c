#include <stdlib.h>
#include <stdio.h>

#include "token.h"

int op_precedence(token *tok) {
    if (tok == NULL) {
        return PRECEDENCE_EMPTY;
    }
    if (tok->expression == EXPR_UN_PLUS || tok->expression == EXPR_UN_MINUS) {
        return 4;
    }
    else if (tok->expression == EXPR_BIN_POW) {
        return 3;
    }
    else if (tok->expression == EXPR_BIN_MULT || tok->expression == EXPR_BIN_DIV) {
        return 2;
    }
    else if (tok->expression == EXPR_L_BRACE) {
        return 0;
    }
    else if (tok->expression == EXPR_NUM || tok->expression == EXPR_VAR) {
        return 6;
    }
    else {
        return 1;
    }
}

void op_print(token tok) {
    if (tok.expression == EXPR_NUM) {
        printf("%d", tok.number);
    }
    else if (tok.expression == EXPR_VAR) {
        printf("%c", tok.variable);
    }
    else if (tok.expression == EXPR_VAR) {
        printf("%c", tok.variable);
    }
    else if (tok.expression == EXPR_UN_MINUS || tok.expression == EXPR_BIN_MINUS) {
        printf("-");
    }
    else if (tok.expression == EXPR_BIN_PLUS) {
        printf("+");
    }
    else if (tok.expression == EXPR_BIN_MULT) {
        printf("*");
    }
    else if (tok.expression == EXPR_BIN_DIV) {
        printf("/");
    }
    else if (tok.expression == EXPR_BIN_POW) {
        printf("^");
    }
    else {
        printf("\nsomething gone terribly wrong here\n");
    }
}
