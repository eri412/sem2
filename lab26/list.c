#include "list.h"

int list_is_empty(list *subj) {
	if (subj == NULL) {
		return 1;
	}
	return 0;
}

void list_push(list **subj, int val) {
	if (!list_is_empty(*subj)) {
		list *iter = *subj;
		while (iter->next != NULL) {
			iter = iter->next;
		}
		list *temp = malloc(sizeof(list));
		temp->val = val;
		temp->next = NULL;
		iter->next = temp;
	}
	else {
		(*subj) = malloc(sizeof(list));
		(*subj)->val = val;
		(*subj)->next = NULL;
	}
}

void list_print(list *subj) {
	if (!list_is_empty(subj)) {
		list *iter = subj;
		while (iter != NULL) {
			printf("%d ", iter->val);
			iter = iter->next;
		}
	}
	printf("\n");
}

int list_get(list *subj, size_t indx) {
	if (!list_is_empty(subj)) {
		size_t i = 0;
		list *temp = subj;
		while (i != indx && temp != NULL) {
			i++;
			temp = temp->next;
		}
		if (temp != NULL) {
			return temp->val;
		}
	}
	
	return INT_MAX;
}

size_t list_size(list *subj) {
	size_t n = 0;
	list *temp = subj;
	while(temp != NULL) {
		temp = temp->next;
		n++;
	}
	
	return n;
}

void list_set(list *subj, size_t indx, int val) {
	if (!list_is_empty(subj)) {
		int i = 0;
		list *temp = subj;
		while (i != indx && temp != NULL) {
			i++;
			temp = temp->next;
		}
		if (temp != NULL) {
			temp->val = val;
		}
	}
}

void list_swap(list *subj, size_t indx1, size_t indx2) {
	if (!list_is_empty(subj)) {
		int temp = list_get(subj, indx1);
		list_set(subj, indx1, list_get(subj, indx2));
		list_set(subj, indx2, temp);
	}
}

void list_pop(list **subj) {
	if (!list_is_empty(*subj)) {
		if ((*subj)->next != NULL) {
			list *temp = *subj;
			while (temp->next->next != NULL) {
				temp = temp->next;
			}
			free(temp->next);
			temp->next = NULL;
		}
		else {
			free(*subj);
			*subj = NULL;
		}
	}
}

void list_delete(list **subj) {
	while (!list_is_empty(*subj)) {
		list_pop(subj);
	}
}