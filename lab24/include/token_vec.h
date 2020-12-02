#ifndef _TOKEN_VEC_H_
#define _TOKEN_VEC_H_

#include <stdlib.h>

#include "token.h"

#define DEFAULT_CAPACITY 8
#define CAPACITY_MULTIPLIER 2

typedef struct {
    size_t size;
    size_t capacity;
    token *buff;
} token_vec;

token_vec *token_vec_create();
size_t token_vec_size(token_vec *vec);
token *token_vec_get(token_vec *vec, int pos);
int _token_vec_grow(token_vec *vec);
int token_vec_push(token_vec *vec, token tok);
int _token_vec_shrink(token_vec *vec);
token token_vec_pop(token_vec *vec);
void token_vec_delete(token_vec *vec);
void token_vec_print(token_vec *vec);

#endif
