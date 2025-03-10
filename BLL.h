#pragma once
#include "entity.h"

void mainLoop();

Person* login(int type);

void studentLoop(Person*);

void teacherLoop(Person*);

void adminLoop(Person*);
