#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

#define SIZE_MULTIPLIER 2
#define DEFAULT_CAPACITY 8

typedef struct {
    int data;
    int next;
} Elem;

typedef struct {
    int size;
    int first;
    Stack *stack;
    Elem *buff;
} Vector;

typedef struct {
    Vector *vec;
    int pos;
} Iter;

int iter_eq(Iter lhs, Iter rhs); // checks if iterators are equal
Iter vector_begin(Vector *vec); // iterator for the list first element
Iter vector_end(Vector *vec); // iterator for the list NULL element
void iter_next(Iter *iter); // moves iterator forward
int iter_get(Iter iter); // returns data contained in current iterator position
void iter_change(Iter iter, int data); // changes data
int vector_size(Vector *vec); // returns size of a vector
void vector_print(Vector *vec); // prints vector
void _vector_grow(Vector *vec); // does realloc for vector
void vector_add(Iter iter, int data); // adds element before iterator position
void vector_del(Iter iter); // deletes element on iterator position
Vector *vector_new(); // creates list
void vector_free(Vector *vec); // deletes list
void vector_task(Vector *vec, int k); // does the individual task

#endif
