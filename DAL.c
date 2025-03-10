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
			printf("[INFO] �����������������롣\n");
			if (triles != -1) {
				printf("[INFO] �㻹��%d�λ��ᡣ\n", triles - times);
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
			printf("[INFO] �����������������롣\n");
			if (triles != -1) {
				printf("[INFO] �㻹��%d�λ��ᡣ\n", triles - times);
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
	case 1: // ѧ��
		strcpy(fileName, STUFILE);
		break;
	case 2: // ��ʦ
		strcpy(fileName, TEACHERFILE);
		break;
    case 3: // ����Ա
		strcpy(fileName, ADMINFILE);
		break;
	default:
		printf("[ERROR] bug����������\n");
	}
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("[ERROR] �޷���ȡ�ļ���\n");
		return NULL;
	}
	List* personList = createEmptyList();
	if (personList == NULL) {
		printf("[ERROR] δ�ܴ�����Ա�б�\n");
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
			printf("[ERROR] �ڴ��������޷���ȡ�˺š�\n");
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
	case 1: // ѧ��
		strcpy(fileName, STUFILE);
		break;
	case 2: // ��ʦ
		strcpy(fileName, TEACHERFILE);
		break;
	case 3: // ����Ա
		strcpy(fileName, ADMINFILE);
		break;
	default:
		printf("[ERROR] bug����������\n");
	}
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("[ERROR] �޷�д���ļ���\n");
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
		printf("[ERROR] �޷���ȡ�ļ���\n");
		return NULL;
	}
	List* roomList = createEmptyList();
	if (roomList == NULL) {
		printf("[ERROR] δ�ܴ��������б�\n");
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
			printf("[ERROR] �ڴ��������޷���ȡ������\n");
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
		printf("[ERROR] �޷�д���ļ���\n");
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
		printf("[ERROR] �޷���ȡ�ļ���\n");
		return NULL;
	}
	List* orderList = createEmptyList();
	if (orderList == NULL) {
		printf("[ERROR] δ�ܴ���ԤԼ�б�\n");
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
			printf("[ERROR] �ڴ��������޷���ȡԤԼ��\n");
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
		printf("[ERROR] �޷�д���ļ���\n");
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
		printf("[ERROR] �޷�����ļ���\n");
		return 0;
	}
	fclose(fp);
	return 1;
}

void roomInfoUpdate(int id, int delta_size) {
	List* roomList = readRoomFromFile();
	if (roomList == NULL) {
		printf("[ERROR] �޷����»�����Ϣ��\n");
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
		printf("[INFO] ������Ϣ�Ѹ��¡�\n");
	}
	else {
		printf("[ERROR] �޷����»�����Ϣ��\n");
	}
	destroyList(roomList);
}

void addNewOrder(Order* order) {
	List* orderList = readOrderFromFile();
	if (orderList == NULL) {
		printf("[ERROR] �޷����ԤԼ��\n");
		return;
	}
	addListLast(orderList, order);
	if (writeOrderToFile(orderList)) {
		printf("[INFO] ԤԼ����ӡ�\n");
	}
	else {
		printf("[ERROR] �޷����ԤԼ��\n");
	}
	destroyList(orderList);
}

// ����
void orderLogUpdate(Order* order, int state) { 
	order->state = state;
}