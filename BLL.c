#include "BLL.h"
#include "UI.h"
#include "DAL.h"
#include "globalfile.h"
#include <stdio.h>
#include <ctype.h>

void mainLoop() {
	int running = 1;
	int option;
	while (running) {
		digitInput(&option, -1, "请选择身份：", 0, 3);
		switch (option) {
		case 1: // student DaiBiao

			break;
		case 2: // teacher
			break;
		case 3: // admin
			break;
		case 0:
			running = 0;
			goodbye();
			break;
		default:
			printf("! 程序bug出现了 !\n");
		}
	}
}

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

void login(int type, char* file) {

}

void studentLoop() {

}

void teacherLoop() {

}

void adminLoop() {

}