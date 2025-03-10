#pragma once
#include "list.h"
#include "entity.h"

//int strAlnumDetect(char* str);

int digitInput(int* data, unsigned triles, char* start, int min, int max);

int strInput(char** data, int triles, int det(char*), char* start);

void clearReturn(char* str, int size);

List* readPersonFromFile(int type);

int writePersonToFile(List* list, int type);

List* readRoomFromFile();

int writeRoomToFile(List* list);

List* readOrderFromFile();

int writeOrderToFile(List* list);

int clearFile(char* fileName);

void roomInfoUpdate(int id, int delta_size);

void addNewOrder(Order* order);

void orderLogUpdate(Order* order, int state);