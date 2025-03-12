#pragma once
#include "entity.h"

// ---------- student ----------

void signIn(Person* stu); 

void signOut(Person* stu);

void applyOrder(Person* stu);

void showMyOrder(Person* stu);

void cancelOrder(Person* stu);

// ---------- teacher ----------

void showOnesOrder(Person* tea);

void checkOrder(Person* tea);

// ---------- administrator ----------

int secondSafetyVerify(Person* admin);

void addPerson(Person* admin);

void showTypePersons(Person* admin);

void findOnePerson(Person* admin);

void delOnePerson(Person* admin);

void resetPersonPassword(Person* admin);

void showRooms(Person* admin);

void clearOrderLogs(Person* admin);

// ----- all -----

void showAllOrder(Person* me);

void showOrderLogs(Person* p);

Person* findPerson(int type, char* id);

void manageOrderLoop(Person* person,int type);
