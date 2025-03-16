#define _CRT_SECURE_NO_WARNINGS
#include "entity.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include "iohelper.h"

// ----- about person -----

Person* createEmptyPerson() {
    Person* newPerson = malloc(sizeof(Person));
    if (newPerson == NULL) {
        return NULL;
    }
	memset(newPerson->m_Id, 0, sizeof(newPerson->m_Id));
	memset(newPerson->m_Psw, 0, sizeof(newPerson->m_Psw));
    return newPerson;
}

Person* personCopy(Person* p) {
	Person* newPerson = createEmptyPerson();
	if (newPerson == NULL) {
		printf("\033[31;1m[Error] Var \"newPerson\" is a nullptr in func \"personCopy\".\033[0m\n");
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
		printf("\033[31;1m[Error] Unexpected value of var \"type\" = %d in func \"isIdValid\".\033[0m\n", type);
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

int isTeaIdValid(char* id) {
	int len = strlen(id);
	if (len != 8) {
		return 0;
	}
	for (int i = 0; i < len; ++i) {
		if (!isalnum(id[i])) {
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
    printf("\033[36mID: %s\033[0m\n", p->m_Id);
    printf("\033[36mPassword: %s\33[0m\n", p->m_Psw);
}

void showPersonHeader() {
	printf("\033[36m     ID             Password\033[0m\n");
}

void showPersonInLine(Person* p) {
    printf("%-20s%-20s\n", p->m_Id, p->m_Psw);
}

PF personListSortAdvice(int* shift) {
	printf("\033[36m[Info] 将以学生账号字典顺序排序。\033[0m\n");
	printf("\033[36m[0] 退出\033[0m\n");
	printf("\033[36m[1] 正序(默认)\033[0m\n");
	printf("\033[36m[2] 逆序\033[0m\n");
	digitInput(shift, -1, "选择展示方式：", 0, 1);
	if (*shift == 0) {
		return NULL;
	}
	system("pause");
	return cmpPersonWithId;
}

int cmpPersonWithId(Person* a, Person* b) {
	return strcmp(a->m_Id, b->m_Id);
}

// ---------- room ----------

Room* createEmptyRoom() {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) {
        printf("\033[31;1m[Error] Var \"newRoom\" is a nullptr in func \"createEmptyRoom\".\033[0m\n");
        return NULL;
    }
	newRoom->m_Id = 0;
	newRoom->m_Capacity = 0;
	return newRoom;
}

Room* createRoom(int id, int capacity) {
	Room* newRoom = (Room*)malloc(sizeof(Room));
	if (newRoom == NULL) {
		printf("\033[31;1m[Error] Var \"newRoom\" is a nullptr in func \"personCopy\".\033[0m\n");
		return NULL;
	}
	newRoom->m_Id = id;
	newRoom->m_Capacity = capacity;
	return newRoom;
}

void showRoomHeader() {
	printf("\033[36m房号     容量\033[0m\n");
}

void showRoomInLine(Room* r) {
	printf("%-10d%-10d\n", r->m_Id, r->m_Capacity);
}

// ---------- order ----------

char* createOrderId() {
	char* orderId = (char*)malloc(40 * sizeof(char));
	if (orderId == NULL) {
		printf("\033[31;1m[Error] Var \"orderId\" is a nullptr in func \"createOrderId\".\033[0m\n");
		return NULL;
	}
	time_t now = time(NULL);
	struct tm* ltm = localtime(&now);
	char* idx = orderId;
	int temp;
	sprintf(orderId, "R%d", 1900 + ltm->tm_year);
	temp = ltm->tm_mon + 1;
	while (*idx != '\0' && idx < orderId + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	temp = ltm->tm_mday;
	while (*idx != '\0' && idx < orderId + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	temp = ltm->tm_hour;
	while (*idx != '\0' && idx < orderId + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	temp = ltm->tm_min;
	while (*idx != '\0' && idx < orderId + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	temp = ltm->tm_sec;
	while (*idx != '\0' && idx < orderId + 20) ++idx;
	if (temp < 10) sprintf(idx, "0%d", temp);
	else sprintf(idx, "%d", temp);
	for (int i = 15; i < 20; ++i) { // 有点狼狈，但是安全
		orderId[i] = '\0';
	}
	return orderId;
}

Order* createEmptyOrder() {
	Order* newOrder = (Order*)malloc(sizeof(Order));
	if (newOrder == NULL) {
		printf("\033[31;1m[Error] Var \"newOrder\" is a nullptr in func \"createEmptyOrder\".\033[0m\n");
		return NULL;
	}
	newOrder->order_Id[0] = '\0';
	newOrder->stu_Id[0] = '\0';
	newOrder->room_Id = 0;
	newOrder->state = 0;
	newOrder->weekday = 0;
	return newOrder;
}

Order* createOrder(
	char* order_Id,
	int room_Id,
	char* stu_Id,
	int state,
	int weekday
) {
	Order* newOrder = (Order*)malloc(sizeof(Order));
	if (newOrder == NULL) {
		printf("\033[31;1m[Error] Var \"newOrder\" is a nullptr in func \"createOrder\".\033[0m\n");
		return NULL;
	}
	strcpy(newOrder->order_Id, order_Id);
	strcpy(newOrder->stu_Id, stu_Id);
	newOrder->room_Id = room_Id;
	newOrder->state = state;
	newOrder->weekday = weekday;
	return newOrder;
}

// 打表の艺术
char* changeNumToWeekday(int num) {
	char* weekday = (char*)malloc(40 * sizeof(char));
	if (weekday == NULL) {
		printf("\033[31;1m[Error] Var \"weekday\" is a nullptr in func \"changeNumToWeekday\".\033[0m\n");
		return NULL;
	}
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
		printf("\033[31;1m[Error] Unexpected value of param \"num\" = %d in func \"changeNumToWeekday\".\033[0m\n", num);
		break;
	}
	return weekday;
}

char* changeNumToState(int num) {
	char* state = (char*)malloc(40 * sizeof(char));
	if (state == NULL) {
		printf("\033[31;1m[Error] Var \"state\" is a nullptr in func \"changeNumToState\".\033[0m\n");
		return NULL;
	}
	switch (num) {
	case 0:
		strcpy(state, "预约成功");
		break;
	case 1:
		strcpy(state, "正在使用");
		break;
	case 2:
		strcpy(state, "已签退");
		break;
	case 3:
		strcpy(state, "学生取消");
		break;
	case 4:
		strcpy(state, "未审批");
		break;
	case 5:
		strcpy(state, "驳回");
		break;
	case 6:
		strcpy(state, "过期");
		break;
	default:
		printf("\033[31;1m[Error] Unexpected value of param \"num\" = %d in func \"changeNumToState\".\033[0m\n", num);
		return NULL;
	}
	return state;
}

void showOrderHeader() {
	printf("\033[36m预约号              \
学生账号           \
房间    时间           状态\033[0m\n");
}

void showOrderInLine(Order* o) {
	char* weekday = changeNumToWeekday(o->weekday);
	char* state = changeNumToState(o->state);
	if (weekday == NULL || state == NULL) {
		printf("\033[31;1m[Error] Var \"weekday\" or \"state\" is a nullptr in func \"showOrderInLine\"\033[0m\n");
		return;
	}
	printf("%-20s%-20s%-5d%-20s%s\n", o->order_Id, o->stu_Id, o->room_Id, weekday, state);
	free(weekday);
	weekday = NULL;
	free(state);
	state = NULL;
}

int isOrderIdEqual(Order* a, Order* b) {
	return !strcmp(a->order_Id, b->order_Id);
}

int isOrderPersonEqual(Order* a, Order* b) {
	return !strcmp(a->stu_Id, b->stu_Id);
}

int isOrderStateEqual(Order* a, Order* b) {
	return a->state == b->state;
}

Order* orderCopy(Order* prev) {
	Order* newOrder = createOrder(
		prev->order_Id,
		prev->room_Id,
		prev->stu_Id,
		prev->state,
		prev->weekday
	);
	if (newOrder == NULL) {
		printf("\033[31;1m[Error] Var \"newOrder\" is a nullptr in func \"orderCopy\".\033[0m\n");
		return NULL;
	}
	strcpy(newOrder->order_Id, prev->order_Id);
	strcpy(newOrder->stu_Id, prev->stu_Id);
	newOrder->state = prev->state;
	newOrder->weekday = prev->weekday;
	newOrder->room_Id = prev->room_Id;
	return newOrder;
}

int isOrderUnchecked(Order* o) {
	return o->state == 4;
}

int canOrderBeCanceled(Order* ref, Order* listdata) {
	if (strcmp(listdata->stu_Id, ref->stu_Id)) {
		return 0;
	}
	return listdata->state == 0 || listdata->state == 4;
}

PF orderListSortAdvice(int* shift) {
	int option = 0;
	printf("\033[36m[0] 退出\033[0m\n");
	printf("\033[36m[1] 以提交时间排序(默认)\033[0m\n");
	printf("\033[36m[2] 以学生账号排序\033[0m\n");
	printf("\033[36m[3] 以使用时间排序\033[0m\n");
	printf("\033[36m[4] 以状态量排序\033[0m\n");
	digitInput(&option, -1, "选择一个排序策略：", 0, 4);
	if (option == 0) {
		return NULL;
	}
	printf("\033[36m[1] 正序(默认)\033[0m\n");
	printf("\033[36m[2] 逆序\033[0m\n");
	digitInput(shift, -1, "选择展示方式：", 1, 2);
	system("pause");
	switch (option) {
	case 1:
		return cmpOrderWithOrderId;
	case 2:
		return cmpOrderWithStuId;
	case 3:
		return cmpOrderWithTime;
	case 4:
		return cmpOrderWithTime;
	}
	printf("\033[31;1m[Error] Unexpected value of var \"option\" = %d in func \"OrderListSortAdvice\".\033[0m\n", option);
	return NULL;
}

int cmpOrderWithOrderId(Order* a, Order* b) {
	return strcmp(a->order_Id, b->order_Id);
}

int cmpOrderWithStuId(Order* a, Order* b) {
	return strcmp(a->stu_Id, b->stu_Id);
}

int cmpOrderWithTime(Order* a, Order* b) {
	return a->weekday - b->weekday;
}

int cmpOrderWithState(Order* a, Order* b) {
	return a->state - b->state;
}
