#pragma once
#include "list.h"
#include "entity.h"

// ---------- person ----------

List* readPersonFromFile_Bin(int type);

int writePersonToFile_Bin(List* list,int type);

// --------- room ----------

List* readRoomFromFile_Bin();

int writeRoomToFile_Bin(List* list);

void roomInfoUpdate(int id,int delta_size);

// ---------- order ----------

List* readOrderFromFile_Bin();

int writeOrderToFile_Bin(List* list);

void addNewOrder(Order* order);

void orderLogUpdate(Order* order,int state);

void orderLogRealtimeUpdate();

// ---------- all ----------

int clearFile_Bin(char* fileName);
