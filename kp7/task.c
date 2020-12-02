#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	int *buff;
	size_t size;
	size_t capacity;
} vector;

typedef struct {
	vector val;
	vector col_ind;
	vector row_ptr;
	size_t width;
} matrice;

void usage() {
	printf("Usage: program <filename>");
	exit(1);
}

void vector_grow(vector *subj) {
	subj->buff = realloc(subj->buff, subj->capacity * 2 * sizeof(int));
	if (subj->buff == NULL) {
		printf("Error while allocating\n");
		exit(1);
	}
	subj->capacity *= 2;
}

void vector_push(vector *subj, int val) {
	if (subj->size == subj->capacity) {
		vector_grow(subj);
	}
	subj->buff[subj->size] = val;
	subj->size++;
}

int vector_get(vector subj, size_t indx) {
	return subj.buff[indx];
}

vector vector_init() {
	vector temp;
	temp.capacity = 10;
	temp.size = 0;
	temp.buff = malloc(10 * sizeof(int));
	if (temp.buff == NULL) {
		printf("Error while allocating\n");
		exit(1);
	}
	return temp;
}

size_t vector_size(vector subj) {
	return subj.size;
}

matrice matrice_init() {
	matrice temp;
	temp.val = vector_init();
	temp.col_ind = vector_init();
	temp.row_ptr = vector_init();
	temp.width = 0;
	return temp;
}

matrice matrice_parse(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Couldn't open the file\n");
		exit(1);
	}
	matrice temp = matrice_init();
	int ch;
	size_t current_col = 0;
	size_t row_end = 0;
	int current_val = 0;
	int sign = 1;
	vector_push(&(temp.row_ptr), row_end);
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n') {
			if (current_val != 0) {
				current_val *= sign;
				vector_push(&(temp.val), current_val);
				vector_push(&(temp.col_ind), current_col);
				current_val = 0;
				row_end++;
			}
			vector_push(&(temp.row_ptr), row_end);
			current_col = 0;
			sign = 1;
		}
		else if (ch == ' ') {
			if (current_val != 0) {
				current_val *= sign;
				vector_push(&(temp.val), current_val);
				vector_push(&(temp.col_ind), current_col);
				current_val = 0;
				row_end++;
			}
			current_col++;
			sign = 1;
		}
		else if (ch == '-') {
			sign = -1;
		}
		else {
			current_val = current_val*10 + (ch - '0');
		}
	}
	if (current_val != 0) {
				current_val *= sign;
				vector_push(&(temp.val), current_val);
				vector_push(&(temp.col_ind), current_col);
				current_val = 0;
				row_end++;
	}
	vector_push(&(temp.row_ptr), row_end);
	temp.width = ++current_col;
	
	return temp;
}

void matrice_print(matrice subj) {
	for (int i = 0; i < vector_size(subj.val); i++) {
		printf("%d ", vector_get(subj.val, i));
	}
	printf("\n");
	for (int i = 0; i < vector_size(subj.col_ind); i++) {
		printf("%d ", vector_get(subj.col_ind, i));
	}
	printf("\n");
	for (int i = 0; i < vector_size(subj.row_ptr); i++) {
		printf("%d ", vector_get(subj.row_ptr, i));
	}
	printf("\n\n");
	
	size_t temp = 0;
	for (int i = 0; i < vector_size(subj.row_ptr) - 1; i++) {
		size_t row_start = vector_get(subj.row_ptr, i);
		size_t row_end = vector_get(subj.row_ptr, i+1);
		for (int j = 0; j < subj.width; j++) {
			if (row_start + temp == row_end) {
				temp = 0;
			}
			if (j == vector_get(subj.col_ind, row_start + temp) && row_start != row_end) {
				printf("%-4d ", vector_get(subj.val, row_start + temp));
				temp++;
			}
			else {
				printf("%-4d ", 0);
			}
		}
		temp = 0;
		printf("\n\n");
	} 
}

void task(matrice subj) {
	int elemnum[subj.width];
	int elemmult[subj.width];
	for (int i = 0; i < subj.width; i++) {
		elemnum[i] = 0;
		elemmult[i] = 1;
	}
	for (int i = 0; i < vector_size(subj.val); i++) {
		elemnum[vector_get(subj.col_ind, i)]++;
		elemmult[vector_get(subj.col_ind, i)] *= vector_get(subj.val, i);
	}
	
	int max1, max2 = elemnum[0];
	int max1n, max2n = 0;
	for (int i = 0; i < subj.width; i++) {
		if (elemnum[i] >= max2) {
			max1 = max2;
			max1n = max2n;
			
			max2 = elemnum[i];
			max2n = i;
		}
	}
	if (max1 == max2) {
		max2n = max1n;
	}
	if (max2 == 0) {
		elemmult[max2n] = 0;
	}
	printf("i = %d; mult = %d\n", max2n, elemmult[max2n]);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		usage();
	}
	
	matrice subj = matrice_parse(argv[1]);
	matrice_print(subj);
	task(subj);
	
	return 0;
}

matrice matrice_init(); // creates matrice
matrice matrice_parse(char *filename); // parses matrice from file
void matrice_print(matrice subj); // prints matrice in human-readable form
void task(matrice subj); // does the task itself
