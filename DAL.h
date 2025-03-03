#pragma once
#include "list.h"

int digitInput(int* data, unsigned triles, char* start, int min, int max);

int strInput(char** data, int triles, int det(char*), char* start);

void clearReturn(char* str, int size);

List* readFromPerson(int type);