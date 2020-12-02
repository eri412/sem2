#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "token_vec.h"

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
    assert(vec->size > 0);
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
