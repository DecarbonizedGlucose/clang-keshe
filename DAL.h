#pragma once
#include "list.h"
#include "entity.h"

// ---------- person ----------

//List* readPersonFromFile(int type);

List* readPersonFromFile_Bin(int type);

//int writePersonToFile(List* list, int type);

int writePersonToFile_Bin(List* list,int type);

// --------- room ----------

//List* readRoomFromFile();

List* readRoomFromFile_Bin();

//int writeRoomToFile(List* list);

int writeRoomToFile_Bin(List* list);

void roomInfoUpdate(int id,int delta_size);

// ---------- order ----------

//List* readOrderFromFile();

List* readOrderFromFile_Bin();

//int writeOrderToFile(List* list);

int writeOrderToFile_Bin(List* list);

void addNewOrder(Order* order);

void orderLogUpdate(Order* order,int state);

void orderLogRealtimeUpdate();

// ---------- all ----------

//int clearFile(char* fileName);

int clearFile_Bin(char* fileName);
