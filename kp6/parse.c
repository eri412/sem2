#include "students.h"

void usage() {
	printf("Usage:\nprogram -f <inputfile>\n"
	       "program -p <arg> <inputfile>\n");
	//exit(1);
}

void printfile(FILE *fp) {
	student temp;
	printf("_________________________________________________________________________\n"
	       "|   lastname   | initials | sex | group | exam1 | exam2 | exam3 | exam4 |\n"
		   "-------------------------------------------------------------------------\n");
	while (fread(&temp, sizeof(student), 1, fp) == 1) {
		printf("|%-14s|%-10s|%-5c|%-7d|%-7d|%-7d|%-7d|%-7d|\n", temp.lastname, temp.initials, temp.sex, temp.group, temp.exam1, temp.exam2, temp.exam3, temp.exam4);
		printf("-------------------------------------------------------------------------\n");
	}
	fclose(fp);
}

int fivenum(student subj) {
	int n = 0;
	if (subj.exam1 == 5) {
		n++;
	}
	if (subj.exam2 == 5) {
		n++;
	}
	if (subj.exam3 == 5) {
		n++;
	}
	if (subj.exam4 == 5) {
		n++;
	}
	return n;
}

void parse(FILE *fp, int group) {
	student temp;
	int n = 0;
	while (fread(&temp, sizeof(student), 1, fp) == 1) {
		if (temp.sex == 'f' && temp.group == group && fivenum(temp) == 1) {
			n++;
		}
	}
	printf("Female students with only one 5: %d\n", n);
	fclose(fp);
}

int main(int argc, char *argv[]) {
	int group;
	if (argc == 3 && strcmp(argv[1], "-f") == 0) { //print
		FILE *fp = fopen(argv[2], "rb");
		if (fp == NULL) {
			printf("Cannot open file\n");
			return 1;
		}
		printfile(fp);
	}
	else if(argc == 4 && strcmp(argv[1], "-p") == 0 && (group = atoi(argv[2])) != 0) { //task
		FILE *fp = fopen(argv[3], "rb");
		if (fp == NULL) {
			printf("Cannot open file\n");
			return 1;
		}
		parse(fp, group);
	}
	else {
		usage();
	}
	
	return 0;
}