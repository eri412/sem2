#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_vec.h"
#include "token_tree.h"
#include "parse.h"

#define BUFFSIZE 256

int main() {
    char str[BUFFSIZE + 1];
    while ((fgets(str, BUFFSIZE + 1, stdin)) != NULL) {
        str[strlen(str) - 1] = '\0';
        token_vec *inf_vec, *post_vec;
        token_tree *expr_tree;
        if ((inf_vec = split2toks(str)) == NULL) {
            continue;
        }
        if ((post_vec = inf2post(inf_vec)) == NULL) {
            exit(1);
        }
        expr_tree = post2tree(post_vec);
        printf("________________________________\n");
        printf("tree before simplification:\n");
        printf("--------------------------------\n");
        token_tree_print(expr_tree);
        token_tree_simplify(expr_tree);
        printf("________________________________\n");
        printf("tree after simplification:\n");
        printf("--------------------------------\n");
        token_tree_print(expr_tree);
        printf("________________________________\n");
        printf("infix expression:\n");
        printf("--------------------------------\n");
        token_tree_print_inf(expr_tree);
        printf("\n________________________________\n");

        token_vec_delete(inf_vec);
        token_vec_delete(post_vec);
        token_tree_delete(expr_tree);
    }

    return 0;
}
