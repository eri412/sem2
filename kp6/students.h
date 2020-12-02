#ifndef _STUDENTS_H_
#define _STUDENTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char lastname[21];
	char initials[3];
	char sex;
	int group;
	unsigned int exam1, exam2, exam3, exam4;
} student;

#endif