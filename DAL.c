#define _CRT_SECURE_NO_WARNINGS
#include "DAL.h"
#include "list.h"
#include "globalfile.h"
#include "entity.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int digitInput(int* data, unsigned triles, char* start, int min, int max) {
	unsigned times = 0;
	int state = 0;
	int cur = 1;
	while (times < triles) {
		cur = 1;
		printf("[INPUT] %s", start);
		char line[80];
		fgets(line, 79, stdin);
		fflush(stdin);
		for (int i = 0; i < 80 && line[i] != '\0'; ++i) {
			if (line[i] == '\n') {
				line[i] = '\0';
			}
			if (!isdigit(line[i]) && line[i] != '\0') {
				cur = 0;
				break;
			}
		}
		if (cur) {
			sscanf(line, "%d", data);
			//printf("data=%d\n", *data);
			cur = (min <= *data && *data <= max) ? 1 : 0;
		}
		times++;
		if (!cur) {
			printf("[INFO] 输入有误，请重新输入。\n");
			if (triles != -1) {
				printf("[INFO] 你还有%d次机会。\n", triles - times);
			}
		}
		else {
			state = 1;
			break;
		}
	}
	return state;
}

int strInput(char** data, int triles, int det(char*), char* start) {
	int times = 0;
	int state = 0;
	int cur = 1;
	while (times < triles) {
		cur = 1;
		printf("[INPUT] %s", start);
		char line[20];
		fgets(line, 19, stdin);
		fflush(stdin);
		clearReturn(line, 20);
		cur = det(line);
		times++;
		if (!cur) {
			printf("[INFO] 输入有误，请重新输入。\n");
			if (triles != -1) {
				printf("[INFO] 你还有%d次机会。\n", triles - times);
			}
		}
		else {
			state = 1;
			strcmp(*data, line);
			break;
		}
	}
	return state;
}

void clearReturn(char* str, int size) {
	for (int i = 0; i < size && str[i] != '\0'; ++i) {
		if (str[i] == '\n') {
			str[i] = '\0';
		}
	}
}

List* readFromPerson(int type) {
	char fileName[20] = { 0 };
	switch (type) {
	case 1:
		strcpy(fileName, STUFILE);
		break;
	case 2:
		strcpy(fileName, TEACHERFILE);
		break;
    case 3:
		strcpy(fileName, ADMINFILE);
		break;
	default:
		printf("[ERROR] bug出现了呃呃\n");
	}
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("[ERROR] 无法读取文件。\n");
		return NULL;
	}
	List* personList = createList();
	if (personList == NULL) {
		printf("[ERROR] 未能创建人员列表\n");
		return NULL;
	}
	char line[40], id[20], psw[20];
	while (1) {
		char* t = fgets(line, 39, fp);
		//clearerr(fp);
		if (t == NULL) {
			break;
		}
		sscanf(line, "%s %s", id, psw);
		addListLast(personList, createPerson(id, psw));
	}
	//clearerr(fp);
	return personList;
}