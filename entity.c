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

int isStudentEqual(struct Student* a, struct Student* b) {
	return !strcmp(a->m_Id, b->m_Id) && !strcmp(a->m_Psw, b->m_Psw);
}

// ----- about teacher -----

struct Teacher* createTeacher(char id[20], char psw[20]) {
	struct Teacher* newtea = malloc(sizeof(struct Teacher));
	if (newtea == NULL) {
		return NULL;
	}
	strcpy(newtea->m_Id, id);
	strcpy(newtea->m_Psw, psw);
	return newtea;
}

int isTeacherEqual(struct Teacher* a, struct Teacher* b) {
	return !strcmp(a->m_Id, b->m_Id) && !strcmp(a->m_Psw, b->m_Psw);
}

// ----- about admin -----

struct Student* createAdmin(char id[20], char psw[20]) {
	struct Admin* newadm = malloc(sizeof(struct Admin));
	if (newadm == NULL) {
		return NULL;
	}
	strcpy(newadm->m_Id, id);
	strcpy(newadm->m_Psw, psw);
	return newadm;
}

int isAdminEqual(struct Admin* a, struct Admin* b) {
	return !strcmp(a->m_Id, b->m_Id) && !strcmp(a->m_Psw, b->m_Psw);
}

// ----- about room -----

// ----- about order -----