#ifndef _STACK_H_
#define _STACK_H_

typedef struct _struct_Stack {
    int data;
    struct _struct_Stack *next;
} Stack;

void stack_push(Stack **stack, const size_t data);
int stack_pop(Stack **stack);

#endif
