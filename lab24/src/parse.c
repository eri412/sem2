#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "token_vec.h"
#include "token_tree.h"
#include "parse.h"

int _check_str(char *str) {
    int num_flag = NUM_OUT;
    int braces = 0;
    int last_expr = PARSE_EXPR_NONE;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i])) {
            num_flag = NUM_OUT;
        }
        if (str[i] == ' ') {
            
        }
        else if (str[i] == '(') {
            if (last_expr != PARSE_EXPR_L_BRACE && last_expr != PARSE_EXPR_NONE &&
                last_expr != PARSE_EXPR_UNBIN)
            {
                return i;
            }
            ++braces;
            last_expr = PARSE_EXPR_L_BRACE;
        }
        else if (str[i] == ')') {
            if (last_expr != PARSE_EXPR_R_BRACE && last_expr != PARSE_EXPR_VARNUM) {
                return i;
            }
            if (--braces < 0) {
                return i;
            }
            last_expr = PARSE_EXPR_R_BRACE;
        }
        else if (isdigit(str[i])) {
            if (num_flag == NUM_IN) {
                continue;
            }
            else {
                if (last_expr != PARSE_EXPR_L_BRACE && last_expr != PARSE_EXPR_NONE && 
                    last_expr != PARSE_EXPR_UNBIN)
                {
                    return i;
                }
                num_flag = NUM_IN;
            }
            last_expr = PARSE_EXPR_VARNUM;
        }
        else if (isalpha(str[i])) {
            if (last_expr != PARSE_EXPR_L_BRACE && last_expr != PARSE_EXPR_NONE && 
                last_expr != PARSE_EXPR_UNBIN)
            {
                return i;
            }
            last_expr = PARSE_EXPR_VARNUM;
        }
        else if (str[i] == '+' || str[i] == '-') {
            if (last_expr != PARSE_EXPR_L_BRACE && last_expr != PARSE_EXPR_NONE && 
                last_expr != PARSE_EXPR_R_BRACE && last_expr != PARSE_EXPR_VARNUM) 
            {
                return i;
            }
            last_expr = PARSE_EXPR_UNBIN;
        }
        else if (str[i] == '*' || str[i] == '/' || str[i] == '^') {
            if (last_expr != PARSE_EXPR_R_BRACE && last_expr != PARSE_EXPR_VARNUM) {
                return i;
            }
            last_expr = PARSE_EXPR_UNBIN;
        }
        else {
            return i;
        }
    }
    if (braces != 0) {
        for (size_t i = 0; i < strlen(str); ++i) {
            if (str[i] == '(') {
                return i;
            }
        }
    }
    char last = str[strlen(str) - 1];
    if (!isalnum(last) && last != ')' && last != ' ') {
        return strlen(str) - 1;
    }

    return -1;
}

token_vec *split2toks(char *str) {
    int str_check_res;
    if ((str_check_res = _check_str(str)) != -1) {
        printf("%s\n", str);
        for (int i = 0; i < str_check_res; ++i) {
            printf(" ");
        }
        printf("^ error here\n");
        return NULL;
    }
    token_vec *vec = token_vec_create();
    unsigned int temp_num = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (i != 0 && !isdigit(str[i]) && isdigit(str[i-1])) {
            token temp_stack_tok = {EXPR_NUM, '\0', temp_num};
            token_vec_push(vec, temp_stack_tok);
            temp_num = 0;
        }
        if (str[i] == ' ') {

        }
        else if (str[i] == '(') {
            token temp_stack_tok = {EXPR_L_BRACE};
            token_vec_push(vec, temp_stack_tok);
        }
        else if (str[i] == ')') {
            token temp_stack_tok = {EXPR_R_BRACE};
            token_vec_push(vec, temp_stack_tok);
        }
        else if (str[i] == '+') {
            token *temp_tok = token_vec_get(vec, token_vec_size(vec) - 1);
            if (temp_tok == NULL || temp_tok->expression == EXPR_L_BRACE) {
                token temp_stack_tok = {EXPR_UN_PLUS};
                token_vec_push(vec, temp_stack_tok);
            }
            else {
                token temp_stack_tok = {EXPR_BIN_PLUS};
                token_vec_push(vec, temp_stack_tok);
            }
        }
        else if (str[i] == '-') {
            token *temp_tok = token_vec_get(vec, token_vec_size(vec) - 1);
            if (temp_tok == NULL || temp_tok->expression == EXPR_L_BRACE) {
                token temp_stack_tok = {EXPR_UN_MINUS};
                token_vec_push(vec, temp_stack_tok);
            }
            else {
                token temp_stack_tok = {EXPR_BIN_MINUS};
                token_vec_push(vec, temp_stack_tok);
            }
        }
        else if (str[i] == '*') {
            token temp_stack_tok = {EXPR_BIN_MULT};
            token_vec_push(vec, temp_stack_tok);
        }
        else if (str[i] == '/') {
            token temp_stack_tok = {EXPR_BIN_DIV};
            token_vec_push(vec, temp_stack_tok);
        }
        else if (str[i] == '^') {
            token temp_stack_tok = {EXPR_BIN_POW};
            token_vec_push(vec, temp_stack_tok);
        }
        else if (isdigit(str[i])) {
            temp_num = temp_num*10 + (str[i] - '0');
        }
        else if (isalpha(str[i])) {
            token temp_stack_tok = {EXPR_VAR, str[i]};
            token_vec_push(vec, temp_stack_tok);
        }
        else {
            fprintf(stderr, "%s\n", str);
            for (size_t j = 0; j < i; ++j) {
                fprintf(stderr, " ");
            }
            fprintf(stderr, "^ error here\n");
            token_vec_delete(vec);
            return NULL;
        }
    }
    if (isdigit(str[strlen(str) - 1])) {
        token temp_stack_tok = {EXPR_NUM, '\0', temp_num};
        token_vec_push(vec, temp_stack_tok);
    }
    return vec;
}

token_vec *inf2post(token_vec *input_vec) {
    token_vec *output_vec, *op_vec;
    if ((output_vec = token_vec_create()) == NULL) {
        return NULL;
    }
    if ((op_vec = token_vec_create()) == NULL) {
        token_vec_delete(output_vec);
        return NULL;
    }
    for (size_t i = 0; i < token_vec_size(input_vec); ++i) {
        token cur_tok = *(token_vec_get(input_vec, i));
        if (cur_tok.expression == EXPR_VAR || cur_tok.expression == EXPR_NUM) {
            token_vec_push(output_vec, cur_tok);
        }
        else if (cur_tok.expression == EXPR_UN_PLUS || cur_tok.expression == EXPR_UN_MINUS) {
            token_vec_push(op_vec, cur_tok);
        }
        else if (cur_tok.expression == EXPR_BIN_PLUS || cur_tok.expression == EXPR_BIN_MINUS || 
                 cur_tok.expression == EXPR_BIN_MULT || cur_tok.expression == EXPR_BIN_DIV || 
                 cur_tok.expression == EXPR_BIN_POW) 
        {
            while (op_precedence(token_vec_get(op_vec, token_vec_size(op_vec) - 1)) >= op_precedence(&cur_tok)) {
                token_vec_push(output_vec, token_vec_pop(op_vec));
            }
            token_vec_push(op_vec, cur_tok);
        }
        else if (cur_tok.expression == EXPR_L_BRACE) {
            token_vec_push(op_vec, cur_tok);
        }
        else if (cur_tok.expression == EXPR_R_BRACE) {
            token temp_tok;
            while ((temp_tok = token_vec_pop(op_vec)).expression != EXPR_L_BRACE) {
                token_vec_push(output_vec, temp_tok);
            }
        }
    }
    while (op_precedence(token_vec_get(op_vec, token_vec_size(op_vec) - 1)) != PRECEDENCE_EMPTY) {
        token_vec_push(output_vec, token_vec_pop(op_vec));
    }
    token_vec_delete(op_vec);
    return output_vec;
}

token_tree *post2tree(token_vec *post_vec) {
    token_tree_vec *tree_vec = token_tree_vec_create();
    for (size_t i = 0; i < token_vec_size(post_vec); ++i) {
        token temp_tok = *token_vec_get(post_vec, i);
        if (temp_tok.expression == EXPR_VAR || temp_tok.expression == EXPR_NUM) {
            token_tree *temp_tree = token_tree_create(temp_tok, NULL, NULL, NULL);
            token_tree_vec_push(tree_vec, temp_tree);
        }
        else if (temp_tok.expression == EXPR_UN_PLUS) {
            continue;
        }
        else if (temp_tok.expression == EXPR_UN_MINUS) {
            token_tree *left = token_tree_vec_pop(tree_vec);
            token_tree *temp_tree = token_tree_create(temp_tok, NULL, left, NULL);
            token_tree_vec_push(tree_vec, temp_tree);
        }
        else {
            token_tree *right = token_tree_vec_pop(tree_vec);
            token_tree *left = token_tree_vec_pop(tree_vec);
            token_tree *temp_tree = token_tree_create(temp_tok, NULL, left, right);
            token_tree_vec_push(tree_vec, temp_tree);
        }
    }
    token_tree *tree = token_tree_vec_pop(tree_vec);
    token_tree_vec_delete(tree_vec);
    return tree;
}