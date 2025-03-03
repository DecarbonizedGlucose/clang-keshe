#define _CRT_SECURE_NO_WARNINGS
#include "entity.h"
#include <stdlib.h>
#include <string.h>

// ----- about person -----

Person* createPerson(char id[20], char psw[20]) {
    Person* newpsn = malloc(sizeof(Person));
    if (newpsn == NULL) {
        return NULL;
    }
    strcpy(newpsn->m_Id, id);
    strcpy(newpsn->m_Psw, psw);
    return newpsn;
}

int isPersonEqual(Person* a, Person* b) {
    return !strcmp(a->m_Id, b->m_Id) && !strcmp(a->m_Psw, b->m_Psw);
}

// ----- about room -----

// ----- about order -----
