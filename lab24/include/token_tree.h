#ifndef _TOKEN_TREE_H_
#define _TOKEN_TREE_H_

#include <stdlib.h>

#include "token.h"

typedef struct token_tree {
    token tok;
    struct token_tree *parent;
    struct token_tree *left;
    struct token_tree *right;
} token_tree;

token_tree *token_tree_create(token tok, token_tree *parent, token_tree *left, token_tree *right);
void _token_tree_print_aux(token_tree *tree, int level);
void token_tree_print(token_tree *tree);
void token_tree_simplify1(token_tree *tree);
void token_tree_simplify(token_tree *tree);
void token_tree_print_inf(token_tree *tree);
void token_tree_delete(token_tree *tree);

typedef struct {
    size_t size;
    size_t capacity;
    token_tree **buff;
} token_tree_vec;

#define DEFAULT_CAPACITY 8
#define CAPACITY_MULTIPLIER 2

token_tree_vec *token_tree_vec_create();
size_t token_tree_vec_size(token_tree_vec *vec);
int _token_tree_vec_grow(token_tree_vec *vec);
int token_tree_vec_push(token_tree_vec *vec, token_tree *tok);
int _token_tree_vec_shrink(token_tree_vec *vec);
token_tree *token_tree_vec_pop(token_tree_vec *vec);
void token_tree_vec_delete(token_tree_vec *vec);

#endif