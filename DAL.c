#include "DAL.h"
#include "list.h"
#include "globalfile.h"
#include <string.h>
#include <stdio.h>

int digitInput(int* data, int triles, char* start, int min, int max) {
	int times = 0;
	int state = 0;
	int cur = 1;
	while (times < triles) {
		cur = 1;
		printf("%s", start);
		char line[80];
		fgets(line, 79, stdin);
		fflush(stdin);
		for (int i = 0; i < 80 && line[i] != '\0'; ++i) {
			if (line[i] == '\n') {
				line[i] = '\0';
			}
			if (!isdigit(line[i])) {
				cur = 0;
				break;
			}
		}
		if (cur) {
			sscanf_s(line, "%d", data);
			cur = (min <= *data && *data <= max) ? 1 : 0;
		}
		times++;
		if (!cur) {
			printf("输入有误，请重新输入。\n");
			if (triles != -1) {
				printf("你还有%d次机会。\n", triles - times);
			}
		}
		else {
			state = 1;
			break;
		}
	}
	return state;
}

int strInput(char* data, int triles, int det(char*), char* start) {
	int times = 0;
	int state = 0;
	int cur = 1;
	while (times < triles) {
		cur = 1;
		printf("%s", start);
		char line[20];
		fgets(line, 19, stdin);
		for (int i = 0; i < 20 && line[i] != '\0'; ++i) {
			if (line[i] == '\n') {
				line[i] = '\0';
			}
		}
		cur = det(line);
		times++;
		if (!cur) {
			printf("输入有误，请重新输入。\n");
			if (triles != -1) {
				printf("你还有%d次机会。\n", triles - times);
			}
		}
		else {
			state = 1;
			break;
		}
	}
}

struct List* readFromPerson(int type) {
    char fileName[20];
    switch (type) {
    case 1:
        strcpy(fileName, STUDENTFILE);
        break;
    case 2:
        strcpy(fileName, TEACHERFILE);
        break;
    case 3:
        strcpy(fileName, ADMINFILE);
        break;
    default:
        printf("program bug appears\n");
    }
    FILE* fp = fopen(fileName, "r");
    List* personList = createList();
    if (personList == NULL) {
        printf("[ERROR] fail creating list\n");
        return NULL;
    }
    while (1) {
        char line[40], name[20], psw[20];
        if (fgets(line, 39, fp) == NULL) {
            break;
        }
        sscanf(line, "%s %s", name, psw);
        addListLast(personList, createPerson(name, psw));
    }
    return personList;
}
