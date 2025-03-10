#pragma once
#include "entity.h"

// ----- about student -----

void signIn(Person* stu); 

void signOut(Person* stu);

void applyOrder(Person* stu);

void showMyOrder(Person* stu);

void cancelOrder(Person* stu);

// ----- about teacher -----

void showAllOrder(Person* tea);

void showOnesOrder(Person* tea);

void validOrder(Person* tea);

// ----- about admin -----

int secondSafetyVerify(Person* admin);

void addPerson(Person* admin);

void showTypePersons(Person* admin);

void findOnePerson(Person* admin);

void delOnePerson(Person* admin);

void changePersonInfo(Person* admin);

void showRooms(Person* admin);

void cleanRecords(Person* admin);

// ----- all -----

List* showOrderLogs(Person* p);

Person* findPerson(int type, char* id);