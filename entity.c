#define _CRT_SECURE_NO_WARNINGS
#include "entity.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>

// ----- about person -----

Person* createEmptyPerson() {
    Person* newPerson = malloc(sizeof(Person));
    if (newPerson == NULL) {
        return NULL;
    }
    return newPerson;
}

Person* personCopy(Person* p) {
	Person* newPerson = createEmptyPerson();
	if (newPerson == NULL) {
		printf("[ERROR] 内存分配错误，无法复制。\n");
		return NULL;
	}
	strcpy(newPerson->m_Id, p->m_Id);
	strcpy(newPerson->m_Psw, p->m_Psw);
	return newPerson;
}

int isPersonInfoEqual(Person* a, Person* b) {
    return !strcmp(a->m_Id, b->m_Id) && !strcmp(a->m_Psw, b->m_Psw);
}

int isPersonIdEqual(Person* a, Person* b) {
	return !strcmp(a->m_Id, b->m_Id);
}

int isIdValid(char* id, int type) {
    int len = strlen(id);
    switch (type) {
	case 1: // 学生
		if (len != 10) {
			return 0;
		}
		for (int i = 0; i < len; ++i) {
			if (!isdigit(id[i])) {
				return 0;
			}
		}
		break;
    case 2: // 教师
	case 3: // 管理员
        if (len != 8) {
            return 0;
        }
		for (int i = 0; i < len; ++i) {
			if (!isalnum(id[i])) {
				return 0;
			}
		}
		break;
    default:
		printf("[ERROR] bug出现了呃呃\n");
		return 0;
	}
	return 1;
}

int isStuIdValid(char* id) {
	int len = strlen(id);
	if (len != 10) {
		return 0;
	}
	for (int i = 0; i < len; ++i) {
		if (!isdigit(id[i])) {
			return 0;
		}
	}
	return 1;
}

int isPasswordValid(char* psw) {
    int len = strlen(psw);
    if (len < 8 || len > 16) {
        return 0;
    }
    for (int i = 0; i < len; ++i) {
        if (!isalnum(psw[i])) {
            return 0;
        }
    }
    return 1;
}

void showSinglePerson(Person* p) {
    printf("ID: %s\n", p->m_Id);
    printf("Password: %s\n", p->m_Psw);
}

// 5d --- -20s-20s
void showTypePersonsListLine(Person* p, int idx) {
    printf("%5d --- %-20s%-20s\n", idx, p->m_Id, p->m_Psw);
}

// ----- about room -----

Room* createEmptyRoom() {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) {
        printf("内存分配错误，无法创建实体。");
        return NULL;
    }
	newRoom->m_Id = 0;
	newRoom->m_Capacity = 0;
	newRoom->m_Size = 0;
	return newRoom;
}

Room* createRoom(int id, int capacity, int size) {
	Room* newRoom = (Room*)malloc(sizeof(Room));
	if (newRoom == NULL) {
		printf("内存分配错误，无法创建实体。");
		return NULL;
	}
	newRoom->m_Id = id;
	newRoom->m_Capacity = capacity;
	newRoom->m_Size = size;
	return newRoom;
}

// -5门牌号-5容量-5人数
void showRoomListLine(Room* r) {
	printf("%-5d%-5d%-5d\n", r->m_Id, r->m_Capacity, r->m_Size);
}

// ----- about order -----

char* createOrderId() {
	char* orderId = (char*)calloc(20, sizeof(char));
	if (orderId == NULL) {
		printf("内存分配错误，无法生成标号。");
		return NULL;
	}
	time_t now = time(NULL);
	struct tm* ltm = localtime(&now);
	char* code = (char*)calloc(20, sizeof(char));
	char* idx = code;
	int temp;
	sprintf(code, "R%d", 1900 + ltm->tm_year);
	temp = ltm->tm_mon + 1;
	while (*idx != '\0' && idx < code + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	temp = ltm->tm_mday;
	while (*idx != '\0' && idx < code + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	temp = ltm->tm_hour;
	while (*idx != '\0' && idx < code + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	temp = ltm->tm_min;
	while (*idx != '\0' && idx < code + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	temp = ltm->tm_sec;
	while (*idx != '\0' && idx < code + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d\0", temp);
	return orderId;
}

Order* createEmptyOrder() {
	Order* newOrder = (Order*)malloc(sizeof(Order));
	if (newOrder == NULL) {
		printf("内存分配错误，无法创建实体。");
		return NULL;
	}
	newOrder->order_Id[0] = '\0';
	newOrder->stu_Id[0] = '\0';
	newOrder->room_Id = 0;
	newOrder->state = 0;
	newOrder->weekday = 0;
	return newOrder;
}

Order* createOrder(char* order_Id, int room_Id, char* stu_Id, int state, int weekday) {
	Order* newOrder = (Order*)malloc(sizeof(Order));
	if (newOrder == NULL) {
		printf("内存分配错误，无法创建实体。");
		return NULL;
	}
	strcpy(newOrder->order_Id, order_Id);
	strcpy(newOrder->stu_Id, stu_Id);
	newOrder->room_Id = room_Id;
	newOrder->state = state;
	newOrder->weekday = weekday;
	return newOrder;
}

char* changeNumToWeekday(int num) {
	char* weekday = (char*)calloc(10, sizeof(char));
	switch (num) {
	case 1:
		strcpy(weekday, "周一上午");
		break;
	case 2:
		strcpy(weekday, "周一下午");
		break;
	case 3:
		strcpy(weekday, "周二上午");
		break;
	case 4:
		strcpy(weekday, "周二下午");
		break;
	case 5:
		strcpy(weekday, "周三上午");
		break;
	case 6:
		strcpy(weekday, "周三下午");
		break;
	case 7:
		strcpy(weekday, "周四上午");
		break;
	case 8:
		strcpy(weekday, "周四下午");
		break;
	case 9:
		strcpy(weekday, "周五上午");
		break;
	case 10:
		strcpy(weekday, "周五下午");
		break;
	default:
		printf("[ERROR] 程序bug出现了 !\n");
		break;
	}
	return weekday;
}

// -5idx-20请求标号-20人-5房-10时间-5状态
void showOrderListLine(Order* o, int idx) {
	char* weekday = changeNumToWeekday(o->weekday);
	printf("%5d --- %-20s%-20s%-5d%-10s%-5d\n", idx, o->order_Id, o->stu_Id, o->room_Id, weekday, o->state);
	free(weekday);
}

int isOrderInfoEqual(Order* a, Order* b) {
	return !strcmp(a->order_Id, b->order_Id) && !strcmp(a->stu_Id, b->stu_Id);
}