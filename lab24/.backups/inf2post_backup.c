#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_CAPACITY 8
#define CAPACITY_MULTIPLIER 2

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

#define PARSE_EXPR_NONE 0
#define PARSE_EXPR_VARNUM 1
#define PARSE_EXPR_L_BRACE 2
#define PARSE_EXPR_R_BRACE 3
#define PARSE_EXPR_UNBIN 4

#define NUM_OUT 0
#define NUM_IN 1

typedef struct {
    int expression;
    char variable;
    unsigned int number;
} token;

typedef struct {
    size_t size;
    size_t capacity;
    token *buff;
} token_vec;

token_vec *token_vec_create() {
    token_vec *vec;
    if ((vec = malloc(sizeof(token_vec))) == NULL) {
        perror("malloc");
        return NULL;
    }
    vec->size = 0;
    vec->capacity = DEFAULT_CAPACITY;
    if ((vec->buff = malloc(sizeof(token) * DEFAULT_CAPACITY)) == NULL) {
        free(vec);
        perror("malloc");
        return NULL;
    }
   return vec; 
}

size_t token_vec_size(token_vec *vec) {
    return vec->size;
}

token *token_vec_get(token_vec *vec, int pos) {
    if (pos < 0 || pos >= (int) vec->size) {
        return NULL;
    }
    return vec->buff + pos;
}

int _token_vec_grow(token_vec *vec) {
    token *temp_buff;
    if ((temp_buff = realloc(vec->buff, sizeof(token) * vec->capacity * CAPACITY_MULTIPLIER)) == NULL) {
        perror("realloc");
        return 0;
    }
    vec->buff = temp_buff;
    vec->capacity *= CAPACITY_MULTIPLIER;
    return 1;
}

int token_vec_push(token_vec *vec, token tok) {
    assert(vec->size <= vec->capacity);
    if (vec->size == vec->capacity) {
        if (!_token_vec_grow(vec)) {
            return 0;
        }
    }
    vec->buff[token_vec_size(vec)] = tok;
    vec->size++;
    return 1;
}

int _token_vec_shrink(token_vec *vec) {
    if (vec->capacity / CAPACITY_MULTIPLIER < DEFAULT_CAPACITY) {
        return 0;
    }
    token *temp_buff;
    if ((temp_buff = realloc(vec->buff, sizeof(token) * vec->capacity / CAPACITY_MULTIPLIER)) == NULL) {
        perror("realloc");
        return 0;
    }
    vec->buff = temp_buff;
    vec->capacity /= CAPACITY_MULTIPLIER;
    return 1;
}

token token_vec_pop(token_vec *vec) {
    assert(vec->size <= vec->capacity);
    vec->size--;
    token temp_tok = vec->buff[vec->size];
    if (vec->capacity / CAPACITY_MULTIPLIER == vec->size) {
        _token_vec_shrink(vec);
    }
    return temp_tok;
}

void token_vec_delete(token_vec *vec) {
    free(vec->buff);
    free(vec);
}

token_vec *split2toks(char *str) {
    token_vec *vec = token_vec_create();
    unsigned int temp_num = 0;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i]) && temp_num != 0) {
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
    if (temp_num != 0) {
        token temp_stack_tok = {EXPR_NUM, '\0', temp_num};
        token_vec_push(vec, temp_stack_tok);
    }
    return vec;
}

int op_precedence(token *tok) {
    if (tok == NULL) {
        return -1;
    }
    if (tok->expression == EXPR_UN_PLUS || tok->expression == EXPR_UN_MINUS) {
        return 3;
    }
    else if (tok->expression == EXPR_BIN_POW) {
        return 2;
    }
    else if (tok->expression == EXPR_BIN_MULT || tok->expression == EXPR_BIN_DIV) {
        return 1;
    }
    else if (tok->expression == EXPR_L_BRACE) {
        return -2;
    }
    else {
        return 0;
    }
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
    while (op_precedence(token_vec_get(op_vec, token_vec_size(op_vec) - 1)) != -1) {
        token_vec_push(output_vec, token_vec_pop(op_vec));
    }
    token_vec_delete(op_vec);
    return output_vec;
}

void token_vec_print(token_vec *vec) {
    for (size_t i = 0; i < token_vec_size(vec); ++i) {
        token cur_tok = *(token_vec_get(vec, i));
        if (cur_tok.expression == EXPR_VAR) {
            printf("%c ", cur_tok.variable);
        }
        else if (cur_tok.expression == EXPR_NUM) {
            printf("%d ", cur_tok.number);
        }
        else if (cur_tok.expression == EXPR_UN_PLUS) {
            printf("# ");
        }
        else if (cur_tok.expression == EXPR_UN_MINUS) {
            printf("! ");
        }
        else if (cur_tok.expression == EXPR_BIN_PLUS) {
            printf("+ ");
        }
        else if (cur_tok.expression == EXPR_BIN_MINUS) {
            printf("- ");
        }
        else if (cur_tok.expression == EXPR_BIN_MULT) {
            printf("* ");
        }
        else if (cur_tok.expression == EXPR_BIN_DIV) {
            printf("/ ");
        }
        else if (cur_tok.expression == EXPR_BIN_POW) {
            printf("^ ");
        }
    }
    printf("\n");
}

int check_str(char *str) {
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


int main() {
    char str[257];
    /*
    while ((fgets(str, 257, stdin)) != NULL) {
        str[strlen(str) - 1] = '\0';
        token_vec *vec, *post_vec;
        if ((vec = split2toks(str)) == NULL) {
            return 1;
        }
        if ((post_vec = inf2post(vec)) == NULL) {
            return 1;
        }
        token_vec_delete(vec);
        token_vec_print(post_vec);
        token_vec_delete(post_vec);
    }
    */
    while ((fgets(str, 257, stdin)) != NULL) {
        str[strlen(str) - 1] = '\0';
        int res;
        if ((res = check_str(str)) != -1) {
            printf("%s\n", str);
            for (int i = 0; i < res; ++i) {
                printf(" ");
            }
            printf("^ error here\n");
        }
    }

    return 0;
}

