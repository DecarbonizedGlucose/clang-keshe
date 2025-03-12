#pragma once
#include "list.h"

int strAlnumDetect(char* str);

int digitInput(int* data,unsigned triles,char* start,int min,int max);

int strInput(char* data,int triles,int det(char*),char* start);

int isQuitSign(char* str);

void clearReturn(char* str,int size);

int showListInPages(
	List* list,
	void showDataHeader(),
	void showDataInLine(void* data),
	int lpp,
	int startpage,
	int showIndex
);
