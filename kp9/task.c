#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define N 12
#define E 0.001

typedef struct {
	char *buff;
	long long prim_key;
	float sec_key;
} elem;

void usage() {
	printf("Usage: program <filename> <order(1-3)>\n");
	exit(1);
}

elem elem_init() {
	elem temp;
	temp.prim_key = 0;
	temp.sec_key = 0;
	temp.buff = malloc(sizeof(char));
	temp.buff[0] = '\0';
	return temp;
}

void elem_push(elem *subj, char ch) {
	subj->buff = realloc(subj->buff, sizeof(char) * (strlen(subj->buff) + 2));
	if (subj->buff == NULL) {
		printf("Error while allocating\n");
		exit(1);
	}
	subj->buff[strlen(subj->buff) + 1] = '\0';
	subj->buff[strlen(subj->buff)] = ch;
}

void parse(char *filename, elem *arr, int *n) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Couldn't open the file\n");
		exit(1);
	}
	int ch;
	arr[*n] = elem_init();
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n') {
			(*n)++;
			if (*n == N) {
				fclose(fp);
				return;
			}
			arr[*n] = elem_init();
		}
		else {
			elem_push(&(arr[*n]), ch);
		}
	}
	(*n)++;
	fclose(fp);
}

void print(elem *arr, int n) {
	printf("_______________________________________\n"
		   "| primary key | secondary key | value |\n"
		   "---------------------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("| %-11lld | %-13.3f | %-7s |\n", arr[i].prim_key, arr[i].sec_key, arr[i].buff);
		printf("---------------------------------------\n");
	}	
}

void fill(elem *arr, int n, char *order) {
	if (strcmp(order, "1") == 0) {
		for (int i = 0; i < n; i++) {
			arr[i].prim_key = i;
			arr[i].sec_key = i;
		}
	}
	else if (strcmp(order, "2") == 0) {
		for (int i = 0; i < n; i++) {
			arr[i].prim_key = n - i - 1;
			arr[i].sec_key = n - i - 1;
		}
	}
	else {
		srand(time(0));
		for (int i = 0; i < n; i++) {
			arr[i].prim_key = rand() % 10;
			arr[i].sec_key = ((float) rand()) / ((float) RAND_MAX);
		}
	}
}

void swap(elem *arr, int a, int b) {
	elem temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void sift_down(elem *arr, int n, int i) {
	if (i*2 + 1 >= n) {
		return;
	}
	
	long long i_prim = arr[i].prim_key;
	float i_sec = arr[i].sec_key;
	long long left_prim = arr[i*2 + 1].prim_key;
	float left_sec = arr[i*2 + 1].sec_key;
	long long right_prim = LLONG_MIN;
	float right_sec = -1;
	if (i*2 + 2 < n) {
		right_prim = arr[i*2 + 2].prim_key;
		right_sec = arr[i*2 + 2].sec_key;
	}
	
	int max_ind;
	if (left_prim > right_prim || (left_prim == right_prim && left_sec > right_sec)) {
		max_ind = i*2 + 1;
	}
	else {
		max_ind = i*2 + 2;
	}
	
	if (arr[i].prim_key < arr[max_ind].prim_key || (arr[i].prim_key == arr[max_ind].prim_key && arr[i].sec_key < arr[max_ind].sec_key)) {
		swap(arr, i, max_ind);
		sift_down(arr, n, max_ind);
	}
	
}

void build_heap(elem *arr, int n) {
	for (int start = n/2 - 1; start >= 0; start--) {
		sift_down(arr, n, start);
	}
}

void heapsort(elem *arr, int n) {
	build_heap(arr, n);
	int temp = n;
	while (temp > 1) {
		swap(arr, 0, temp-1);
		temp--;
		sift_down(arr, temp, 0);
	}
}

void bin_search(elem *arr, int n, long long prim_key, float sec_key) {
	int start = 0;
	int end = n - 1;
	int temp;
	while (start <= end) {
		temp = (end + start)/2;
		if (arr[temp].prim_key > prim_key || (arr[temp].prim_key == prim_key && arr[temp].sec_key - sec_key > E)) {
			end = temp - 1;
		}
		else if (arr[temp].prim_key < prim_key || (arr[temp].prim_key == prim_key && sec_key - arr[temp].sec_key > E)) {
			start = temp + 1;
		}
		else {
			printf("%s\n", arr[temp].buff);
			return;
		}
	}
	printf("No such element\n");
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		usage();
	}
	elem arr[N];
	int n = 0;
	
	parse(argv[1], arr, &n);
	fill(arr, n, argv[2]);
	print(arr, n);
	heapsort(arr, n);
	print(arr, n);
	
	long long prim_key;
	float sec_key;
	while (scanf("%lld %f", &prim_key, &sec_key) == 2) {
		bin_search(arr, n, prim_key, sec_key);
	}
	
	return 0;
}