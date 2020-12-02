#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 101

typedef enum {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE} num;

typedef struct struct_node {
	num val;
	struct struct_node *son;
	struct struct_node *bro;
} node;

/* add path val
   delete path
   print
   nonterminal */
   
void exec(node **root, char *command);
void add(node **root, char *path, num val);
num strtonum(char *str);
void print(node *root, int level);
int pathok(char *path);
int numok(char *num);
void delete(node **root, char *path);
void nonterminal(node *root, int *res);

   
void input(node **root) {
	char command[N];
	int ch;
	int n = 0;
	while ((ch = getchar()) != EOF) {
		if (ch != '\n') {
			command[n] = ch;
			n++;
		}
		else {
			command[n] = '\0';
			exec(root, command);
			n = 0;
		}
	}
}

void exec(node **root, char *command) {
	char argc = 0;
	char argv[N/2 + 1][N/2 + 1];
	int j = 0;
	for (int i = 0; i < strlen(command); i++) {
		if (command[i] == ' ') {
			argv[argc][j] = '\0';
			j = 0;
			argc++;
			continue;
		}
		argv[argc][j] = command[i];
		j++;
	}
	argv[argc][j] = '\0';
	argc++;
	if (strcmp(argv[0], "print") == 0) {
		if (argc != 1) {
			printf("wrong arguments\n");
		}
		else {
			print(*root, 0);
		}
	}
	else if (strcmp(argv[0], "nonterminal") == 0) {
		if (argc != 1) {
			printf("wrong arguments\n");
		}
		else {
			int res = 0;
			nonterminal(*root, &res);
			printf("%d\n", res);
		}
	}
	else if (strcmp(argv[0], "delete") == 0) {
		if (argc != 2) {
			printf("wrong arguments\n");
		}
		else {
			if (pathok(argv[1])) {
				delete(root, argv[1]);
			}
			else {
				printf("bad path\n");
			}
		}
	}
	else if (strcmp(argv[0], "add") == 0) {
		if (argc != 3) {
			printf("wrong arguments\n");
		}
		else {
			if (pathok(argv[1]) && numok(argv[2])) {
				add(root, argv[1], strtonum(argv[2]));
			}
			else {
				printf("bad path or value\n");
			}
		}
	}
	else {
		printf("no such command\n");
	}
}

void add(node **root, char *path, num val) {
	if (*root == NULL && path[0] == '\0') {
		*root = malloc(sizeof(node));
		(*root)->val = val;
		(*root)->son = NULL;
		(*root)->bro = NULL;
		return;
	}
	//else if (*root == NULL && strcmp(path, '\0') != 0) {
	else if (*root == NULL) {
		printf("no such parent\n");
		return;
	}
	node *temp = *root;
	for (int i = 0; i < strlen(path); i++) {
		if (path[i] == 's' && temp->son != NULL) {
			temp = temp->son;
		}
		else if (path[i] == 'b' && temp->bro != NULL) {
			temp = temp->bro;
		}
		else {
			printf("no such parent\n");
			return;
		}
	}
	if (temp->son == NULL) {
		temp->son = malloc(sizeof(node));
		temp->son->val = val;
		temp->son->son = NULL;
		temp->son->bro = NULL;
	}
	else {
		temp = temp->son;
		while (temp->bro != NULL) {
			temp = temp->bro;
		}
		temp->bro = malloc(sizeof(node));
		temp->bro->val = val;
		temp->bro->son = NULL;
		temp->bro->bro = NULL;
	}
}

num strtonum(char *str) {
	if (strcmp(str, "ZERO") == 0) {
		return 0;
	}
	else if (strcmp(str, "ONE") == 0) {
		return 1;
	}
	else if (strcmp(str, "TWO") == 0) {
		return 2;
	}
	else if (strcmp(str, "THREE") == 0) {
		return 3;
	}
	else if (strcmp(str, "FOUR") == 0) {
		return 4;
	}
	else if (strcmp(str, "FIVE") == 0) {
		return 5;
	}
	else if (strcmp(str, "SIX") == 0) {
		return 6;
	}
	else if (strcmp(str, "SEVEN") == 0) {
		return 7;
	}
	else if (strcmp(str, "EIGHT") == 0) {
		return 8;
	}
	else {
		return 9;
	}
}

char *numtostr(num numb) {
	if (numb == 0) {
		return "ZERO";
	}
	else if (numb == 1) {
		return "ONE";
	}
	else if (numb == 2) {
		return "TWO";
	}
	else if (numb == 3) {
		return "THREE";
	}
	else if (numb == 4) {
		return "FOUR";
	}
	else if (numb == 5) {
		return "FIVE";
	}
	else if (numb == 6) {
		return "SIX";
	}
	else if (numb == 7) {
		return "SEVEN";
	}
	else if (numb == 8) {
		return "EIGHT";
	}
	else if (numb == 9) {
		return "NINE";
	}
}

void print(node *root, int level) {
	if (root != NULL) {
		print(root->bro, level);
		for (int i = 0; i < level; i++) {
			printf("\t");
		}
		printf("%s\n", numtostr(root->val));
		print(root->son, level + 1);
	}
}

int pathok(char *path) {
	for (int i = 0; i < strlen(path); i++) {
		if (path[i] != 's' && path[i] != 'b') {
			return 0;
		}
	}
	return 1;
}

int numok(char *num) {
	if (strcmp(num, "ZERO") != 0 && strcmp(num, "ONE") != 0 && strcmp(num, "TWO") != 0 && strcmp(num, "THREE") != 0 && strcmp(num, "FOUR") != 0 && strcmp(num, "FIVE") != 0 && strcmp(num, "SIX") != 0 && strcmp(num, "SEVEN") != 0 && strcmp(num, "EIGHT") != 0 && strcmp(num, "NINE") != 0) {
		return 0;
	}
	return 1;
}

void deletenode(node *delnode) {
	if (delnode != NULL) {
		deletenode(delnode->bro);
		deletenode(delnode->son);
		free(delnode);
	}
}

void delete(node **root, char *path) {
	if (*root != NULL){
		node *prev = *root;
		node *temp = *root;
		char ch = path[strlen(path) - 1];
		for (int i = 0; i < strlen(path); i++) {
			prev = temp;
			if (path[i] == 's' && temp->son != NULL) {
				temp = temp->son;
			}
			else if (path[i] == 'b' && temp->bro != NULL) {
				temp = temp->bro;
			}
			else {
				printf("no such path\n");
				return;
			}
		}
		deletenode(temp);
		if (temp == *root) {
			*root = NULL;
		}
		else {
			if (ch == 's') {
				prev->son = NULL;
			}
			else {
				prev->bro = NULL;
			}
		}
	}
}

void nonterminal(node *root, int *res) {
	if (root != NULL) {
		if (root->son != NULL) {
			(*res)++;
		}
		nonterminal(root->bro, res);
		nonterminal(root->son, res);
	}
}

int main() {
	node *root = NULL;
	input(&root);
	
	return 0;
}
