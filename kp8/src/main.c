#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/vector.h"

#define BUFFSIZE 256

Vector *global_vec;

void execute(char *command) {
    char dup[BUFFSIZE + 2];
    strcpy(dup + 1, command);
    dup[0] = '\0';
    size_t len = strlen(command);
    int argc = 0;
    for (int i = 1; i < (int) len; ++i) {
        if (!isspace(dup[i]) && isspace(dup[i+1])) {
            ++argc;
        }
    }
    char *argv[argc];
    int cur = 0;
    for (int i = 1; i < (int) len + 1; ++i) {
        if (isspace(dup[i])) {
            dup[i] = '\0';
        }
        else if (dup[i-1] == '\0') {
            argv[cur] = &dup[i];
            ++cur;
        }
    }
    
    if (argc == 0) {
        printf("no input given\n");
        return;
    }

    if (strcmp(argv[0], "help") == 0) {
        printf(" * help - prints help\n"
               " * print - prints list\n"
               " * add <num> - adds <num> at the end of the list\n"
               " * insert <num> <pos> - inserts <num> at pos <pos> of the list\n"
               " * delete <pos> - deletes element from pos <pos> of the list\n"
               " * length - prints length of the list\n"
               " * task <k> - inserts last element <k> times at the beginning of the list\n");
    }
    else if (strcmp(argv[0], "print") == 0) {
        vector_print(global_vec);
    }
    else if (strcmp(argv[0], "add") == 0) {
        if (argc != 2) {
            printf("wrong number of arguments\n");
            return;
        }
        Iter it = vector_end(global_vec);
        vector_add(it, atoi(argv[1]));
    }
    else if (strcmp(argv[0], "insert") == 0) {
        if (argc != 3) {
            printf("wrong number of arguments\n");
            return;
        }
        Iter it = vector_begin(global_vec);
        for (int i = 0; i < atoi(argv[2]); ++i) {
            iter_next(&it);
        }
        vector_add(it, atoi(argv[1]));
    }
    else if (strcmp(argv[0], "delete") == 0) {
        if (argc != 2) {
            printf("wrong number of arguments\n");
            return;
        }
        Iter it = vector_begin(global_vec);
        for (int i = 0; i < atoi(argv[1]) + 1; ++i) {
            iter_next(&it);
        }
        vector_del(it);
    }
    else if (strcmp(argv[0], "length") == 0) {
        printf("%d\n", vector_size(global_vec));
    }
    else if (strcmp(argv[0], "task") == 0) {
        if (argc != 2) {
            printf("wrong number of arguments\n");
            return;
        }
        vector_task(global_vec, atoi(argv[1]));
    }
    else {
        printf("no such command, use \"help\"\n");
    }
}

int main() {
    global_vec = vector_new();
    char command[BUFFSIZE + 1];
    while (fgets(command, BUFFSIZE + 1, stdin) != NULL) {
        execute(command);
    }
    vector_free(global_vec);

    return 0;
}