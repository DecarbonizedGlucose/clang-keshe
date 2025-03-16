#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "iohelper.h"
#include <stdlib.h>

int strAlnumDetect(char* str) {
	for (int i = 0; i < strlen(str); ++i) {
		if (!isalnum(str[i])) {
			return 0;
		}
	}
	return 1;
}

int digitInput(int* data, unsigned triles, char* start, int min, int max) {
	unsigned times = 0;
	int state = 0;
	int cur = 1;
	int temp_data = 0;
	while (times < triles) {
		cur = 1;//合法状态
		printf("\033[36m[Input] %s\033[0m", start);
		char line[300];
		fgets(line, 299, stdin);
		fflush(stdin);
		for (int i = 0; i < 80 && line[i] != '\0'; ++i) {
			if (line[0] == '\n') {
				cur = 0;
				break;
			}
			if (line[i] == '\n') {
				line[i] = '\0';
			}
			if (!isdigit(line[i]) && line[i] != '\0') {
				cur = 0;
				break;
			}
		}
		if (cur) {
			sscanf(line, "%d", &temp_data);
			cur = (min <= temp_data && temp_data <= max) ? 1 : 0;
		}
		times++;
		if (!cur) {
			printf("\033[33m[Info] 输入有误，请重新输入。\033[0m\n");
			if (triles != -1) {
				printf("\033[33m[Info] 你还有%d次机会。\033[0m\n", (triles - times));
			}
		}
		else {
			state = 1;
			*data = temp_data;
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
		printf("\033[36m[Input] %s\033[0m", start);
		char line[20];
		fgets(line, 19, stdin);
		fflush(stdin);
		clearReturn(line, 20);
		cur = det(line);
		times++;
		if (!cur) {
			printf("\033[33m[Info] 输入有误，请重新输入。\033[0m\n");
			if (triles != -1) {
				printf("\033[33m[Info] 你还有%d次机会。\033[0m\n", (triles - times));
			}
		}
		else {
			state = 1;
			strcpy(data, line);
			break;
		}
	}
	return state;
}

int isQuitSign(char* str) {
	return !strcmp(str, "0\0");
}

void clearReturn(char* str, int size) {
	for (int i = 0; i < size && str[i] != '\0'; ++i) {
		if (str[i] == '\n') {
			str[i] = '\0';
		}
	}
	// line[strcspn(line, "\n")] = '\0';
}

// 翻页展示数据功能
// 仅展示
int showListInPages(
	List* list,
	void showDataHeader(),
	void showDataInLine(void* data),
	int lpp, // line per page 每页的行数
	int startpage, // 这里不做检查
	int showIndex
) {
	if (list == NULL) {
		system("cls");
		printf("\033[31;1m[Error] Param \"list\" is a nullptr in func \"showListInLine\".\033[0m\n");
		system("pause");
		return 0;
	}
	// num of pages 页数
	int nop = list->length / lpp;
	if (lpp * nop < list->length) {
		nop++;
	}
	int cur_idx = 0;
	Node* cur = NULL;
	int running = 1;
	int option;
	while (running) {
		system("cls");
		printf("\033[36m共%d页%d项，每页%d项.\033[0m\n", nop, list->length, lpp);
		if (showIndex) {
			printf("      ");
		}
		showDataHeader();
		cur_idx = (startpage - 1) * lpp + 1;
		cur = getListIdxNode(list, cur_idx);
		for (int i = 0; i < lpp; ++i) {
			if (cur != NULL) {
				if (showIndex) {
					printf("\033[36m%5d\033[0m ", cur_idx);
				}
				showDataInLine(cur->data);
				cur = cur->next;
				cur_idx++;
			}
			else {
				printf("\033[32m~\033[0m\n");
			}
		}
		printf("\033[36m第%d页，共%d页    [0]退出翻页查看 [1]上页 [2]下页 [3]排序选项\033[0m\n", startpage, nop);
		digitInput(&option, -1, "", 0, 2);
		if (!option) {
			running = 0;
		}
		else if (option == 1 && startpage > 1) {
			startpage--;
		}
		else if (option == 2 && startpage < nop) {
			startpage++;
		}
	}
	return startpage;
}
