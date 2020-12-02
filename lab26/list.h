#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

typedef struct struct_list{
	int val;
	struct struct_list *next;
} list;


int list_is_empty(list *subj);
void list_push(list **subj, int val);
void list_print(list *subj);
int list_get(list *subj, size_t indx);
size_t list_size(list *subj);
void list_set(list *subj, size_t indx, int val);
void list_swap(list *subj, size_t indx1, size_t indx2);
void list_pop(list **subj);
void list_delete(list **subj);

#endif