#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "../include/stack.h"
#include "../include/vector.h"

int iter_eq(Iter lhs, Iter rhs) {
    if (lhs.vec == rhs.vec && lhs.pos == rhs.pos) {
        return 1;
    }
    else {
        return 0;
    }
}

Iter vector_begin(Vector *vec) {
    Iter temp;
    temp.vec = vec;
    temp.pos = vec->first;  
    return temp;
}

Iter vector_end(Vector *vec) {
    Iter temp;
    temp.vec = vec;
    temp.pos = -1;  
    return temp;
}

void iter_next(Iter *iter) {
    //assert(iter->pos != -1);
    if (iter->pos == -1) {
        return;
    }
    iter->pos = iter->vec->buff[iter->pos].next;
}

int iter_get(Iter iter) {
    return iter.vec->buff[iter.pos].data;
}

void iter_change(Iter iter, int data) {
    iter.vec->buff[iter.pos].data = data;
}

int vector_size(Vector *vec) {
    return vec->size;
}

void vector_print(Vector *vec) {
    for (Iter iter = vector_begin(vec); !iter_eq(iter, vector_end(vec)); iter_next(&iter)) {
        printf("%d ", iter.vec->buff[iter.pos].data);
    }
    printf("\n");
}

void _vector_grow(Vector *vec) {
    Elem *temp = realloc(vec->buff, sizeof(Elem) * vec->size * SIZE_MULTIPLIER);
    if (temp == NULL) {
        perror("realloc");
        return;
    }
    vec->buff = temp;
    for (int i = vec->size; i < vec->size * SIZE_MULTIPLIER; ++i) {
        stack_push(&vec->stack, i);
    }
}

void vector_add(Iter iter, int data) {
    Iter temp = vector_begin(iter.vec);
    if (temp.pos == -1 || temp.pos == iter.pos) {
        int free_pos = stack_pop(&iter.vec->stack);
        iter.vec->buff[free_pos].data = data;
        iter.vec->size++;
        iter.vec->first = free_pos;
        iter.vec->buff[free_pos].next = iter.pos;
        return;
    }
    while(temp.vec->buff[temp.pos].next != iter.pos) {
        iter_next(&temp);
    }
    int free_pos = stack_pop(&iter.vec->stack);
    if (free_pos == -1) {
        _vector_grow(iter.vec);
        free_pos = stack_pop(&iter.vec->stack);
    }
    iter.vec->buff[free_pos].data = data;
    iter.vec->buff[free_pos].next = iter.pos;
    iter.vec->buff[temp.pos].next = free_pos;
    iter.vec->size++;
}

void vector_del(Iter iter) {
    if (iter.pos == iter.vec->first) {
        return;
    }
    Iter temp = vector_begin(iter.vec);
    while(temp.vec->buff[temp.pos].next != iter.pos) {
        iter_next(&temp);
    }
    if (temp.pos == iter.vec->first) {
        stack_push(&iter.vec->stack, temp.pos);
        iter.vec->first = iter.pos;
    }
    else {
        int del_pos = temp.pos;
        temp = vector_begin(iter.vec);
        while(temp.vec->buff[temp.pos].next != del_pos) {
            iter_next(&temp);
        }
        temp.vec->buff[temp.pos].next = iter.pos;
        stack_push(&iter.vec->stack, del_pos);
    }
    iter.vec->size--;
}

Vector *vector_new() {
    Vector *temp = malloc(sizeof(Vector));
    temp->size = 0;
    temp->first = -1;
    temp->buff = malloc(sizeof(Elem) * DEFAULT_CAPACITY);
    temp->stack = NULL;
    for (int i = 0; i < DEFAULT_CAPACITY; ++i) {
        stack_push(&temp->stack, i);
    }
    return temp;
}

void vector_free(Vector *vec) {
    free(vec->buff);
    while (stack_pop(&vec->stack) != -1) {}
    free(vec);
}

void vector_task(Vector *vec, int k) {
    if (vec->first == -1) {
        return;
    }
    Iter last = vector_begin(vec);
    while (last.vec->buff[last.pos].next != -1) {
        iter_next(&last);
    }
    Iter first = vector_begin(vec);
    for (int i = 0; i < k; ++i) {
        vector_add(first, iter_get(last));
    }
}
