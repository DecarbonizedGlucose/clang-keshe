#include "entity.h"
#include <stdlib.h>
#include <string.h>

// ----- about student -----

struct Student* createStudent(char id[20], char psw[20]) {
	struct Student* newstu = malloc(sizeof(struct Student));
	if (newstu == NULL) {
		return NULL;
	}
	strcpy(newstu->m_Id, id);
	strcpy(newstu->m_Psw, psw);
	return newstu;
}

// ----- about teacher -----

// ----- about admin -----

// ----- about room -----