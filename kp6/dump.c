#include "students.h"

void usage() {
	printf("Usage: program <inputfile> <outputfile>\n");
	exit(1);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		usage();
	}
	FILE *fileread = fopen(argv[1], "r");
	FILE *filewrite = fopen(argv[2], "wb");
	if (fileread == NULL || filewrite == NULL) {
		printf("Cannot open file\n");
		return 1;
	}
	
	student temp;
	while (fscanf(fileread, "%[^ ] %[^ ] %c %u %u %u %u %u\n", temp.lastname,
													           temp.initials, 
													           &(temp.sex), 
													           &(temp.group), 
													           &(temp.exam1), 
													           &(temp.exam2), 
													           &(temp.exam3), 
													           &(temp.exam4)) == 8) {
		
		fwrite(&temp, sizeof(temp), 1, filewrite);
	}
	
	fclose(fileread);
	fclose(filewrite);
	
	return 0;
}