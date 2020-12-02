#ifndef _PARSE_H_
#define _PARSE_H_

#include "token_vec.h"
#include "token_tree.h"

#define PARSE_EXPR_NONE 0
#define PARSE_EXPR_VARNUM 1
#define PARSE_EXPR_L_BRACE 2
#define PARSE_EXPR_R_BRACE 3
#define PARSE_EXPR_UNBIN 4

#define NUM_OUT 0
#define NUM_IN 1

int _check_str(char *str);
token_vec *split2toks(char *str);
token_vec *inf2post(token_vec *input_vec);
token_tree *post2tree(token_vec *post_vec);

#endif
