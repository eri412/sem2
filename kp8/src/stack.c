#include <stdlib.h>
#include <stdio.h>

#include "../include/stack.h"

void stack_push(Stack **stack, const size_t data) {
    Stack *temp = *stack;
    *stack = malloc(sizeof(Stack));
    if (*stack == NULL) {
        perror("malloc");
        *stack = temp;
        return;
    }
    (*stack)->data = data;
    (*stack)->next = temp;
}

int stack_pop(Stack **stack) {
    if (*stack == NULL) {
        return -1;
    }
    Stack *temp = *stack;
    *stack = (*stack)->next;
    int ret_val = temp->data;
    free(temp);
    return ret_val;
}

/*
int main() {
    Stack *test = NULL;
    for (int i = 0; i < 20; ++i) {
        stack_push(&test, i);
    }
    for (int i = 0; i < 22; ++i) {
        printf("%d ", stack_pop(&test));
    }
    printf("\n");

    return 0;
}
*/
