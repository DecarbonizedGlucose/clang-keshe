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

void applyOrder(struct Student* stu) {

}

void showMyOrder(struct Student* stu) {

}

void showAllOrder_stu(struct Student* stu) {

}

void cancelOrder(struct Student* stu) {

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

void showAllOrder_tea(struct Teacher* tea) {

}

void validOrder(struct Teacher* tea) {

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

void addPerson() {

}

void showPerson() {

}

void showRooms() {

}

void cleanRecords() {

}

// ----- about room -----

// ----- about order -----