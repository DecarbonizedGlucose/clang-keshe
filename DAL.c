#define _CRT_SECURE_NO_WARNINGS
#include "DAL.h"
#include "list.h"
#include "globalfile.h"
#include "entity.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

//int strAlnumDetect(char* str) {
//	for (int i = 0; i < strlen(str); ++i) {
//		if (!isalnum(str[i])) {
//			return 0;
//		}
//	}
//	return 1;
//}

int digitInput(int* data, unsigned triles, char* start, int min, int max) {
	unsigned times = 0;
	int state = 0;
	int cur = 1;
	int temp_data = 0;
	while (times < triles) {
		cur = 1;
		printf("[Input> %s", start);
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
			sscanf(line, "%d", &temp_data);
			cur = (min <= temp_data && temp_data <= max) ? 1 : 0;
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
			*data = temp_data;
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
		printf("[Input> %s", start);
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

List* readPersonFromFile(int type) {
	char fileName[20] = { 0 };
	switch (type) {
	case 1: // 学生
		strcpy(fileName, STUFILE);
		break;
	case 2: // 教师
		strcpy(fileName, TEACHERFILE);
		break;
    case 3: // 管理员
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
	List* personList = createEmptyList();
	if (personList == NULL) {
		printf("[ERROR] 未能创建人员列表\n");
		return NULL;
	}
	char line[40], id[20], psw[20];
	while (1) {
		char* t = fgets(line, 39, fp);
		if (t == NULL) {
			break;
		}
		sscanf(line, "%s %s", id, psw);
		Person* new_person = createEmptyPerson();
		if (new_person == NULL) {
			printf("[ERROR] 内存分配错误，无法读取账号。\n");
			destroyList(personList);
			return NULL;
		}
		strcpy(new_person->m_Id, id);
		strcpy(new_person->m_Psw, psw);
		addListLast(personList, new_person);
	}
	return personList;
}

int writePersonToFile(List* list, int type) {
	char fileName[20] = { 0 };
	switch (type) {
	case 1: // 学生
		strcpy(fileName, STUFILE);
		break;
	case 2: // 教师
		strcpy(fileName, TEACHERFILE);
		break;
	case 3: // 管理员
		strcpy(fileName, ADMINFILE);
		break;
	default:
		printf("[ERROR] bug出现了呃呃\n");
	}
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("[ERROR] 无法写入文件。\n");
		return 0;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		Person* p = (Person*)cur->data;
		fprintf(fp, "%s %s\n", p->m_Id, p->m_Psw);
		cur = cur->next;
	}
	fclose(fp);
	return 1;
}

List* readRoomFromFile() {
	FILE* fp = fopen(ROOMFILE, "r");
	if (fp == NULL) {
		printf("[ERROR] 无法读取文件。\n");
		return NULL;
	}
	List* roomList = createEmptyList();
	if (roomList == NULL) {
		printf("[ERROR] 未能创建机房列表\n");
		return NULL;
	}
	char line[20];
	while (1) {
		char* t = fgets(line, 19, fp);
		if (t == NULL) {
			break;
		}
		int id, capacity, size;
		sscanf(line, "%d %d %d", &id, &capacity, &size);
		Room* newRoom = createRoom(id, capacity, size);
		if (newRoom == NULL) {
			printf("[ERROR] 内存分配错误，无法读取机房。\n");
			destroyList(roomList);
			return NULL;
		}
		addListLast(roomList, newRoom);
	}
	return roomList;
}

int writeRoomToFile(List* list) {
	FILE* fp = fopen(ROOMFILE, "w");
	if (fp == NULL) {
		printf("[ERROR] 无法写入文件。\n");
		return 0;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		Room* r = (Room*)cur->data;
		fprintf(fp, "%d %d %d\n", r->m_Id, r->m_Capacity, r->m_Size);
		cur = cur->next;
	}
	fclose(fp);
	return 1;
}

List* readOrderFromFile() {
	FILE* fp = fopen(ORDERFILE, "r");
	if (fp == NULL) {
		printf("[ERROR] 无法读取文件。\n");
		return NULL;
	}
	List* orderList = createEmptyList();
	if (orderList == NULL) {
		printf("[ERROR] 未能创建预约列表\n");
		return NULL;
	}
	char line[100];
	while (1) {
		char* t = fgets(line, 99, fp);
		if (t == NULL) {
			break;
		}
		Order* newOrder = createEmptyOrder();
		if (newOrder == NULL) {
			printf("[ERROR] 内存分配错误，无法读取预约。\n");
			destroyList(orderList);
			return NULL;
		}
		sscanf(line, "%s %s %d %d %d",
			newOrder->order_Id, newOrder->stu_Id, newOrder->room_Id,
			newOrder->weekday, newOrder->state);
		addListLast(orderList, newOrder);
	}
	return orderList;
}

int writeOrderToFile(List* list) {
	FILE* fp = fopen(ORDERFILE, "w");
	if (fp == NULL) {
		printf("[ERROR] 无法写入文件。\n");
		return 0;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		Order* o = (Order*)cur->data;
		fprintf(fp, "%s %s %d %d %d\n",
			o->order_Id, o->stu_Id, o->room_Id, o->weekday, o->state);
		cur = cur->next;
	}
	fclose(fp);
	return 1;
}

int clearFile(char* fileName) {
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("[ERROR] 无法清空文件。\n");
		return 0;
	}
	fclose(fp);
	return 1;
}

void roomInfoUpdate(int id, int delta_size) {
	List* roomList = readRoomFromFile();
	if (roomList == NULL) {
		printf("[ERROR] 无法更新机房信息。\n");
		return;
	}
	Node* cur = roomList->head;
	while (cur != NULL) {
		Room* r = (Room*)cur->data;
		if (r->m_Id == id) {
			r->m_Size += delta_size;
			break;
		}
		cur = cur->next;
	}
	if (writeRoomToFile(roomList)) {
		printf("[INFO] 机房信息已更新。\n");
	}
	else {
		printf("[ERROR] 无法更新机房信息。\n");
	}
	destroyList(roomList);
}

void addNewOrder(Order* order) {
	List* orderList = readOrderFromFile();
	if (orderList == NULL) {
		printf("[ERROR] 无法添加预约。\n");
		return;
	}
	addListLast(orderList, order);
	if (writeOrderToFile(orderList)) {
		printf("[INFO] 预约已添加。\n");
	}
	else {
		printf("[ERROR] 无法添加预约。\n");
	}
	destroyList(orderList);
}

// 待定
void orderLogUpdate(Order* order, int state) { 
	order->state = state;
}