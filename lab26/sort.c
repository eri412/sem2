#include "list.h"

int partition(list *subj, size_t first_indx, size_t last_indx) {
	int pivot = list_get(subj, first_indx);
	size_t i = first_indx - 1;
	size_t j = last_indx + 1;
	while (1) {
		do {
			i++;
		} while (list_get(subj, i) < pivot);
		
		do {
			j--;
		} while (list_get(subj, j) > pivot);
		
		if (i >= j) {
			return j;
		}
		
		list_swap(subj, i, j);
	}
}

void quicksort(list *subj, size_t first_indx, size_t last_indx) {
	if (first_indx >= last_indx) {
		return;
	}
	
	int pivot = partition(subj, first_indx, last_indx);
	
	quicksort(subj, first_indx, pivot);
	quicksort(subj, pivot + 1, last_indx);
}

int in_order(list *subj) {
	if (!list_is_empty(subj)) {
		list *temp = subj;
		while (temp->next != NULL) {
			if (temp->val > temp->next->val) {
				return 0;
			}
			temp = temp->next;
		}
	}
	return 1;
}

int main() {
	srand(time(NULL));
	list *test = NULL;
	
	for (int i = 0; i < 100000; i++) {
		for (int j = 0; j < 16; j++) {
			list_push(&test, rand() % 1000);
		}
		quicksort(test, 0, list_size(test) - 1);
		if (!in_order(test)) {
			printf("! ");
		}
		list_delete(&test);
	}
	printf(".\n");
	
	return 0;
}