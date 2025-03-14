#define _CRT_SECURE_NO_WARNINGS
#include "DAL.h"
#include "list.h"
#include "globalfile.h"
#include "entity.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// ---------- person ----------

List* readPersonFromFile_Bin(int type) {
	char fileName[20] = { 0 };
	switch (type) {
	case 1: // 学生
		strcpy(fileName, STUFILE_BIN);
		break;
	case 2: // 教师
		strcpy(fileName, TEACHERFILE_BIN);
		break;
	case 3: // 管理员
		strcpy(fileName, ADMINFILE_BIN);
		break;
	default:
		printf("[ERROR] bug出现了呃呃\n");
	}
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) {
		printf("[ERROR] 无法读取文件。\n");
		return NULL;
	}
	List* personList = createEmptyList();
	if (personList == NULL) {
		printf("[ERROR] 未能创建人员列表\n");
		return NULL;
	}
	while (1) {
		Person* new_person = createEmptyPerson();
		if (new_person == NULL) {
			printf("[ERROR] 内存分配错误，无法读取账号。\n");
			destroyList(personList);
			return NULL;
		}
		if (fread(new_person, sizeof(Person), 1, fp) <= 0) {
			free(new_person);
			new_person = NULL;
			break;
		}
		addListLast(personList, new_person);
	}
	fclose(fp);
	return personList;
}

int writePersonToFile_Bin(List* list, int type) {
	char fileName[20] = { 0 };
	switch (type) {
	case 1: // 学生
		strcpy(fileName, STUFILE_BIN);
		break;
	case 2: // 教师
		strcpy(fileName, TEACHERFILE_BIN);
		break;
	case 3: // 管理员
		strcpy(fileName, ADMINFILE_BIN);
		break;
	default:
		printf("[ERROR] bug出现了呃呃\n");
	}
	FILE* fp = fopen(fileName, "wb");
	if (fp == NULL) {
		printf("[ERROR] 无法写入文件。\n");
		return 0;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		Person* p = (Person*)cur->data;
		fwrite(p, sizeof(Person), 1, fp);
		cur = cur->next;
	}
	fclose(fp);
	return 1;
}

// --------- room ----------

List* readRoomFromFile_Bin() {
	FILE* fp = fopen(ROOMFILE_BIN, "rb");
	if (fp == NULL) {
		printf("[ERROR] 无法读取文件。\n");
		return NULL;
	}
	List* roomList = createEmptyList();
	if (roomList == NULL) {
		printf("[ERROR] 未能创建机房列表\n");
		return NULL;
	}
	while (1) {
		Room* new_room = createEmptyRoom();
		if (new_room == NULL) {
			printf("[ERROR] 内存分配错误，无法读取账号。\n");
			destroyList(roomList);
			return NULL;
		}
		if (fread(new_room, sizeof(Room), 1, fp) <= 0) {
			free(new_room);
			new_room = NULL;
			break;
		}
		addListLast(roomList, new_room);
	}
	fclose(fp);
	return roomList;
}

int writeRoomToFile_Bin(List* list) {
	FILE* fp = fopen(ROOMFILE_BIN, "wb");
	if (fp == NULL) {
		printf("[ERROR] 无法写入文件。\n");
		return 0;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		Room* r = (Room*)cur->data;
		fwrite(r, sizeof(Room), 1, fp);
		cur = cur->next;
	}
	fclose(fp);
	return 1;
}

// ---------- order ----------

List* readOrderFromFile_Bin() {
	FILE* fp = fopen(ORDERFILE_BIN, "rb");
	if (fp == NULL) {
		printf("[ERROR] 无法读取文件。\n");
		return NULL;
	}
	List* orderList = createEmptyList();
	if (orderList == NULL) {
		printf("[ERROR] 未能创建机房列表\n");
		return NULL;
	}
	while (1) {
		Order* new_order = createEmptyOrder();
		if (new_order == NULL) {
			printf("[ERROR] 内存分配错误，无法读取账号。\n");
			destroyList(orderList);
			return NULL;
		}
		if (fread(new_order, sizeof(Order), 1, fp) <= 0) {
			free(new_order);
			new_order = NULL;
			break;
		}
		addListLast(orderList, new_order);
	}
	fclose(fp);
	return orderList;
}

int writeOrderToFile_Bin(List* list) {
	FILE* fp = fopen(ORDERFILE_BIN, "wb");
	if (fp == NULL) {
		printf("[ERROR] 无法写入文件。\n");
		return 0;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		Order* o = (Order*)cur->data;
		fwrite(o, sizeof(Order), 1, fp);
		cur = cur->next;
	}
	fclose(fp);
	return 1;
}

void addNewOrder(Order* order) {
	List* orderList = readOrderFromFile_Bin();
	if (orderList == NULL) {
		printf("[ERROR] 无法添加预约。\n");
		return;
	}
	Order* newOrder = orderCopy(order);
	// 这样就深拷贝了
	addListLast(orderList, newOrder);
	if (writeOrderToFile_Bin(orderList)) {
		printf("[INFO] 预约已添加。\n");
		showOrderInLine(order);
	}
	else {
		printf("[ERROR] 无法添加预约。\n");
	}
	destroyList(orderList);
}

// 程序启动后自动更新数据 还没写
void orderLogRealtimeUpdate() {

}

// ---------- all ----------

int clearFile_Bin(char* fileName) {
	FILE* fp = fopen(fileName, "wb");
	if (fp == NULL) {
		printf("[ERROR] 无法清空文件。\n");
		return 0;
	}
	fclose(fp);
	return 1;
}
