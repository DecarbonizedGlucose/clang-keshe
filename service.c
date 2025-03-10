#define _CRT_SECURE_NO_WARNINGS
#include "entity.h"
#include "DAL.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "globalfile.h"
#include "UI.h"
#include <string.h>

// 优化什么的, 有空再写
// 改进时间存储机制
// 添加展示大量数据时的翻页功能
// 添加图形界面

// ----- about student -----

// 签到
void signIn(Person* stu) {
	
}

// 签退
void signOut(Person* stu) {

}

void applyOrder(Person* stu) {
	system("cls");
	introduceRooms();
	int weekday = 0;
	int room_Id = 0;
	printf("自动匹配为次日起的第一个周*。\n");
	digitInput(&weekday, 3, "请输入预约时间：", 1, 10);
	if (weekday == 0) {
		return;
	}
	digitInput(&room_Id, 3, "请输入机房号：", 1, 10);
	if (room_Id == 0) {
		return;
	}
	Order* newOrder = createEmptyOrder();
	if (newOrder == NULL) {
		printf("[ERROR] 内存分配错误，无法预约。\n");
		return;
	}
	newOrder->weekday = weekday;
	newOrder->room_Id = room_Id;
	strcpy(newOrder->stu_Id, stu->m_Id);
	strcpy(newOrder->order_Id, createOrderId());
	newOrder->state = 0;
	addNewOrder(newOrder);
	roomInfoUpdate(room_Id, 1);
}

void showMyOrder(Person* stu) {
	system("cls");
	showOrderLogs(stu);
}

void cancelOrder(Person* stu) {
	showMyOrder(stu);
	List* orderList = readOrderFromFile();
	if (orderList == NULL) {
		printf("[ERROR] 无法读取文件，无法取消预约。\n");
		return;
	}
	char order_Id[20] = { 0 };
	strInput(order_Id, 3, strAlnumDetect, "请输入要取消的预约号：");
	if (order_Id[0] == '\0') {
		return;
	}
	Order* order = createEmptyOrder();
	strcpy(order->order_Id, order_Id);
	strcpy(order->stu_Id, stu->m_Id);
	Node* del = findListElem(orderList, order, isOrderInfoEqual);
	if (del == NULL) {
		printf("[INFO] 未找到该预约。\n");
		destroyList(orderList);
		return;
	}
	orderLogUpdate((Order*)(del->data), 3);
	roomInfoUpdate(((Order*)(del->data))->room_Id, -1);
	if (writeOrderToFile(orderList) == 0) {
		printf("[ERROR] 无法写入文件，无法取消预约。\n");
	}
	destroyList(orderList);
	printf("[INFO] 取消预约成功。\n");
}

// ----- about teacher -----

void showAllOrder(Person* tea) {
	system("cls");
	showOrderLogs(NULL);
}

void showOnesOrder(Person* tea) {
	system("cls");
	char* stu_Id[20] = { 0 };
	strInput(stu_Id, 3, isStuIdValid, "请输入学生账号：");
	if (stu_Id[0] == '\0') {

	}
}

// 这何尝不是一种loop
void validOrder(Person* tea) {
	system("cls");
	
}

// ----- about admin -----

int secondSafetyVerify(Person* admin) {
	int res = 0;
	char psw[20];
	printf("[Input> 请再次输入您的密码以验证身份：");
	fgets(psw, 19, stdin);
	clearReturn(psw, 20);
	fflush(stdin);
	if (!strcmp(psw, admin->m_Psw)) {
		res = 1;
		printf("身份验证成功。\n");
	}
	else {
		printf("身份验证失败。\n");
	}
	return res;
}

void addPerson(Person* admin) {
	system("cls");
	int type = 0;
	printf("选择类型。\n");
	printf("1   -----   学生\n");
	printf("2   -----   教师\n");
	printf("0   -----   退出\n");
	digitInput(&type, 3, "请输入添加账号的类型：", 0, 2);
	if (!type) {
		return;
	}
	List* personList = readPersonFromFile(type);
	if (personList == NULL) {
		printf("[ERROR] 无法读取文件，无法添加账号。\n");
		return;
	}
	Person* newPerson = createEmptyPerson();
	if (newPerson == NULL) {
		printf("[ERROR] 内存分配错误，无法添加账号。\n");
		return;
	}
	printf("[Input> 帐号：");
	fgets(newPerson->m_Id, 19, stdin);
	clearReturn(newPerson->m_Id, 20);
	fflush(stdin);
	printf("[Input> 密码：");
	fgets(newPerson->m_Psw, 19, stdin);
	clearReturn(newPerson->m_Psw, 20);
	fflush(stdin);
	if (!secondSafetyVerify(admin)) {
		free(newPerson);
		destroyList(personList);
		return;
	}
	if (!(isIdValid(newPerson->m_Id, type) && isPasswordValid(newPerson->m_Psw))) {
		printf("[INFO] 输入不符合规则，无法添加账号。\n");
		free(newPerson);
		destroyList(personList);
		return;
	}
	if (findListElem(personList, newPerson, isPersonIdEqual) != NULL) {
		printf("[INFO] 该账号已存在。\n"); // 这里可以加个询问是否覆盖（修改密码）
		// 什么鲁棒性，不知道喵
		free(newPerson);
		destroyList(personList);
		return;
	}
	if (addListLast(personList, newPerson) == NULL) {
		printf("[ERROR] 数据处理错误，无法添加账号。\n");
		free(newPerson);
		destroyList(personList);
		return;
	}
	if (writePersonToFile(personList, type) == 0) {
		printf("[ERROR] 无法写入文件，无法添加账号。\n");
		free(newPerson);
		destroyList(personList);
		return;
	}
	free(newPerson);
	destroyList(personList);
	printf("[INFO] 添加账号成功。\n");
}

void showTypePersons(Person* admin) {
	system("cls");
	int type = 0;
	printf("选择类型。\n");
	printf("1   -----   学生\n");
	printf("2   -----   教师\n");
	printf("0   -----   退出\n");
	digitInput(&type, 3, "请输入查看账号的类型：", 0, 2);
	if (!type) {
		return;
	}
	if (!secondSafetyVerify(admin)) {
		return;
	}
	List* personList = readPersonFromFile(type);
	if (personList == NULL) {
		printf("[ERROR] 无法读取文件，无法查看账号。\n");
		return;
	}
	int count = 0;
	Node* cur = personList->head;
	printf("     ID                  Password\n");
	for (int i = 1; i <= personList->length; ++i) {
		showTypePersonsListLine((Person*)(cur->data), i);
		cur = cur->next;
		++count;
	}
	printf("[INFO] 共找到%d个账号。\n", count);
	destroyList(personList);
	system("pause");
}

void findOnePerson(Person* admin) {
	system("cls");
	int type = 0;
	char person_Id[20] = { 0 };
	printf("选择类型。\n");
	printf("1   -----   学生\n");
	printf("2   -----   教师\n");
	printf("0   -----   退出\n");
	digitInput(&type, 3, "请输入查找账号的类型：", 0, 2);
	if (!type) {
		return;
	}
	strInput(person_Id, 3, isStuIdValid, "请输入要查找的账号：");
	if (person_Id[0] == '\0') {
		return;
	}	
	if (!secondSafetyVerify(admin)) {
		return;
	}
	Person* p = findPerson(type, person_Id);
	if (p == NULL) {
		return;
	}
	showSinglePerson(p);
	free(p);
	system("pause");
}

void delOnePerson(Person* admin) {

}

void changePersonInfo(Person* admin) {

}

void showRooms(Person* admin) {
	system("cls");
	if (!secondSafetyVerify(admin)) {
		return;
	}
	List* roomList = readRoomFromFile();
	if (roomList == NULL) {
		printf("[ERROR] 无法读取文件，无法查看机房。\n");
		return;
	}
	Node* cur = roomList->head;
	printf("房号     容量                已占用\n");
	for (int i = 1; i <= roomList->length; ++i) {
		showRoomListLine((Room*)(cur->data));
		cur = cur->next;
	}
	destroyList(roomList);
	system("pause");
}

void cleanRecords(Person* admin) {
	system("cls");
	if (!secondSafetyVerify(admin)) {
		return;
	}
	if (clearFile(ROOMFILE)) {
		printf("[INFO] 机房记录已清空。\n");
	}
	else {
		printf("[ERROR] 无法清空机房记录。\n");
	}
}

// ----- all -----

void showOrderLogs(Person* p) {
	system("cls");
	List* orderList = readOrderFromFile();
	if (orderList == NULL) {
		printf("[ERROR] 无法读取文件，无法查看预约记录。\n");
		return;
	}
	int count = 0;
	printf("          请求标号            \
学生账号            \
房间 时间      状态\n");
	Node* cur = orderList->head;
	while (cur != NULL) {
		if (p == NULL || !strcmp(p->m_Id, ((Order*)(cur->data))->stu_Id)) {
			count++;
			showOrderListLine(cur->data, count);
		}
	}
	printf("\n[INFO] 共找到%d条记录。\n", count);
	destroyList(orderList);
}

Person* findPerson(int type, char* id) {
	List* personList = readPersonFromFile(type);
	if (personList == NULL) {
		printf("[ERROR] 无法查找账号。\n");
	}
	Node* res = findListElem(personList, id, isPersonIdEqual);
	if (res == NULL) {
		printf("[INFO] 未找到该账号。\n");
		destroyList(personList);
		return NULL;
	}
	Person* p = personCopy(res->data);
	destroyList(personList);
	return p;
}