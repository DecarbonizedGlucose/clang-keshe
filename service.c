#define _CRT_SECURE_NO_WARNINGS
#include "entity.h"
#include "DAL.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "globalfile.h"
#include "UI.h"
#include <string.h>
#include "service.h"
#include "iohelper.h"

// ---------- student ----------

void applyOrder(Person* stu) {
	system("cls");
	introduceRooms();
	int weekday = 0;
	int room_Id = 0;
	printf("\033[33m[Info] 自动匹配为次日起的第一个周*。\033[0m\n");
	digitInput(&weekday, 3, "请输入预约时间(输入0退出)：", 0, 10);
	if (weekday == 0) {
		system("pause");
		return;
	}
	digitInput(&room_Id, 3, "请输入机房号：", 1, 10);
	if (room_Id == 0) {
		system("pause");
		return;
	}
	Order* newOrder = createEmptyOrder();
	if (newOrder == NULL) {
		printf("\033[31;1m[Error] Var \"newOrder\" is a nullptr in func \"applyOrder\".\033[0m\n");
		system("pause");
		return;
	}
	newOrder->weekday = weekday;
	newOrder->room_Id = room_Id;
	strcpy(newOrder->stu_Id, stu->m_Id);
	char* newOrderId = createOrderId();
	strcpy(newOrder->order_Id, newOrderId);
	newOrder->state = 4;
	addNewOrder(newOrder);//这里浅拷贝
	//roomInfoUpdate(room_Id, 1); // 这个功能要是真加上 就不是预约系统了
	free(newOrder); // 析构两次报错 newOrder added in list then destroy list
	free(newOrderId);
	newOrder = NULL;
	newOrderId = NULL;
	printf("\033[33m[Info] 预约提交成功。\033[0m\n");
	system("pause");
}

void showMyOrder(Person* stu) {
	system("cls");
	showOrderLogs(stu);
}

void cancelOrder(Person* stu) {
	manageOrderLoop(stu, 1);
}

// ---------- teacher ----------

void showOnesOrder(Person* tea) {
	system("cls");
	char stu_Id[20] = { 0 };
	strInput(stu_Id, 3, isPasswordValid, "请输入学生账号：");
	if (stu_Id[0] == '\0') {
		system("pause");
		return;
	}
	Person* found = findPerson(1, stu_Id);
	if (found == NULL) {
		printf("\033[33[Info] 未找到该账号。\033[0m\n");
		system("pause");
		return;
	}
	showOrderLogs(found);
	system("pause");
}

void checkOrder(Person* tea) {
	manageOrderLoop(tea, 2);
}

// ---------- administrator ----------

int secondSafetyVerify(Person* admin) {
	int res = 0;
	char psw[20];
	printf("\033[36m[Input] 请再次输入您的密码以验证身份：\033[0m");
	fgets(psw, 19, stdin);
	clearReturn(psw, 20);
	fflush(stdin);
	if (!strcmp(psw, admin->m_Psw)) {
		res = 1;
		printf("\033[32m[Info] 身份验证成功。\033[0m\n");
	}
	else {
		printf("\033[31m[Info] 身份验证失败。\033[0m\n");
	}
	system("pause");
	return res;
}

void addPerson(Person* admin) {
	system("cls");
	int type = 0;
	printf("\033[33m选择类型。\033[0m\n");
	printf("\033[33m1   -----   学生\033[0m\n");
	printf("\033[33m2   -----   教师\033[0m\n");
	printf("\033[33m0   -----   退出\033[0m\n");
	digitInput(&type, 3, "请输入添加账号的类型：", 0, 2);
	if (!type) {
		system("pause");
		return;
	}
	if (!secondSafetyVerify(admin)) {
		return;
	}
	Person* newPerson = createEmptyPerson();
	if (newPerson == NULL) {
		printf("\033[31;1m[Error] Var \"newPerson\" is a nullptr in func \"addPerson\".\033[0m\n");
		system("pause");
		return;
	}
	strInput(newPerson->m_Id, 1, (type == 1 ? isStuIdValid : isTeaIdValid), "帐号：");
	if (newPerson->m_Id[0] == '\0') {
		system("pause");
		return;
	}
	strInput(newPerson->m_Psw, 1, isPasswordValid, "密码：");
	if (newPerson->m_Psw[0] == '\0') {
		system("pause");
		return;
	}
	int acc = 1;
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("\033[31;1m[Error] Var \"personList\" is a nullptr in func \"addPerson\".\033[0m\n");
		acc = 0;
	}
	if (findListElemNode(personList, newPerson, isPersonIdEqual) != NULL) {
		printf("\033[31m[Info] 该账号已存在。\033[0m\n"); // 这里可以加个询问是否覆盖（修改密码）
		// 什么鲁棒性，不知道
		acc = 0;
	}
	if (addListLast(personList, newPerson) == NULL) {
		printf("\033[31;1m[Error] Failed to add node to list in func \"addPerson\".\033[0m\n");
		acc = 0;
	}
	if (acc && writePersonToFile_Bin(personList, type) == 0) {
		printf("\033[31;1m[Error] Failed to write order to file in func \"addPerson\".\033[0m\n");
	}
	//free(newPerson); // 哈哈，浅拷贝 折如磨
	destroyList(personList);
	personList = NULL;
	printf("\033[32m[Info] 添加账号成功。\033[0m\n");
	system("pause");
}

void showTypePersons(Person* admin) {
	system("cls");
	int type = 0;
	printf("\033[33m选择类型。\033[0m\n");
	printf("\033[33m1   -----   学生\033[0m\n");
	printf("\033[33m2   -----   教师\033[0m\n");
	printf("\033[33m0   -----   退出\033[0m\n");
	digitInput(&type, 3, "请输入查看账号的类型：", 0, 2);
	if (!type) {
		system("pause");
		return;
	}
	if (!secondSafetyVerify(admin)) {
		return;
	}
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("\033[31;1m[Error] Var \"personList\" is a nullptr in func \"showTypePersons\".\033[0m\n");
		system("pause");
		return;
	}
	int shift;
	PF cmp = personListSortAdvice(&shift);
	if (cmp != NULL) {
		sortForList(personList, cmp);
		if (shift == 2) {
			reverseList(personList);
		}
		showListInPages(
			personList,
			showPersonHeader,
			showPersonInLine,
			15,
			1,
			1
		);
	}
	destroyList(personList);
	personList = NULL;
	system("pause");
}

void findOnePerson(Person* admin) {
	system("cls");
	int type = 0;
	char person_Id[20] = { 0 };
	printf("\033[33m选择类型。\033[0m\n");
	printf("\033[33m1   -----   学生\033[0m\n");
	printf("\033[33m2   -----   教师\033[0m\n");
	printf("\033[33m0   -----   退出\033[0m\n");
	digitInput(&type, 3, "请输入查找账号的类型：", 0, 2);
	if (!type) {
		system("pause");
		return;
	}
	strInput(person_Id, 3, isPasswordValid, "请输入要查找的账号：");
	if (person_Id[0] == '\0') {
		system("pause");
		return;
	}	
	if (!secondSafetyVerify(admin)) {
		return;
	}
	Person* p = findPerson(type, person_Id);
	if (p == NULL) {
		printf("\033[31m[Info] 未找到该账号。\033[0m\n");
		system("pause");
		return;
	}
	showSinglePerson(p);
	free(p);
	p = NULL;
	system("pause");
}

void delOnePerson(Person* admin) {
	system("cls");
	int type = 0;
	printf("\033[33m选择类型。\033[0m\n");
	printf("\033[33m1   -----   学生\033[0m\n");
	printf("\033[33m2   -----   教师\033[0m\n");
	printf("\033[33m0   -----   退出\033[0m\n");
	digitInput(&type, 3, "请输入查找账号的类型：", 0, 2);
	if (!type) {
		system("pause");
		return;
	}
	char person_Id[20] = { 0 };
	if (type == 1) {
		strInput(person_Id, 3, isPasswordValid, "请输入学生账号：");
	}
	else if (type == 2) {
		strInput(person_Id, 3, isTeaIdValid, "请输入教师账号：");
	}
	else {
		printf("\033[31;1m[Error] Unexpected value of var \"type\" = %d in func \"delOnePerson\".\033[0m\n", type);
		system("pause");
		return;
	}
	if (person_Id[0] == '\0') {
		system("pause");
		return;
	}
	if (!secondSafetyVerify(admin)) {
		return;
	}
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("\033[31;1m[Error] Var \"personList\" is a nullptr in func \"delOnePerson\".\033[0m\n");
		system("pause");
		return;
	}
	Person todel;
	strcpy(todel.m_Id, person_Id);
	int idx = findListElemIdx(personList, &todel, isPersonIdEqual);
	if (idx == -1) {
		printf("\033[31m[Info] 未找到该账号。\033[0m\n");
		destroyList(personList);
		personList = NULL;
		system("pause");
		return;
	}
	delListIdx(personList, idx);
	writePersonToFile_Bin(personList, 1);
	destroyList(personList);
	personList = NULL;
	printf("\033[32m[Info] 删除成功！\033[0m\n");
	system("pause");
}

void resetPersonPassword(Person* admin) {
	system("cls");
	int type = 0;
	printf("\033[33m选择类型。\033[0m\n");
	printf("\033[33m1   -----   学生\033[0m\n");
	printf("\033[33m2   -----   教师\033[0m\n");
	printf("\033[33m3   -----   管理员\33[0m\n");
	printf("\033[33m0   -----   退出\033[0m\n");
	digitInput(&type, 3, "请输入查找账号的类型：", 0, 3);
	if (!type) {
		system("pause");
		return;
	}
	char person_Id[20] = { 0 };
	if (type == 1) {
		strInput(person_Id, 3, isPasswordValid, "请输入学生账号：");
	}
	else if (type == 2) {
		strInput(person_Id, 3, isTeaIdValid, "请输入教师账号：");
	}
	else if (type == 3) {
		strInput(person_Id, 3, isTeaIdValid, "请输入管理员账号：");
	}
	else {
		printf("\033[31;1m[Error] Unexpected value of var \"type\" = %d in func \"resetPersonPassword\".\033[0m\n", type);
		system("pause");
		return;
	}
	if (person_Id[0] == '\0') {
		system("pause");
		return;
	}
	if (!secondSafetyVerify(admin)) {
		return;
	}
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("\033[31;1m[Error] Var \"personList\" is a nullptr in func \"resetPersonPassword\".\033[0m\n");
		system("pause");
		return;
	}
	Person tochange;
	strcpy(tochange.m_Id, person_Id);
	Node* pnode = findListElemNode(personList, &tochange, isPersonIdEqual);
	if (pnode == NULL) {
		printf("\033[31m[Info] 未找到该账号。\033[0m\n");
		destroyList(personList);
		system("pause");
		return;
	}
	char new_psw[20] = { 0 };
	strInput(new_psw, 3, isPasswordValid, "请输入新的密码：");
	if (new_psw[0] == '\0') {
		printf("\033[31m[Info] 修改失败。\033[0m\n");
		destroyList(personList);
		personList = NULL;
		system("pause");
		return;
	}
	strcpy(((Person*)(pnode->data))->m_Psw, new_psw);
	writePersonToFile_Bin(personList, 1);
	destroyList(personList);
	personList = NULL;
	printf("\033[32m[Info] 修改成功！\033[0m\n");
	system("pause");
}

void showRooms(Person* admin) {
	system("cls");
	List* roomList = readRoomFromFile_Bin();
	if (roomList == NULL) {
		printf("\033[31;1m[Error] Var \"roomList\" is a nullptr in func \"showRooms\".\033[0m\n");
		system("pause");
		return;
	}
	showListInPages(
		roomList,
		showRoomHeader,
		showRoomInLine,
		15,
		1,
		1
	);
	destroyList(roomList);
	roomList = NULL;
	system("pause");
}

void clearOrderLogs(Person* admin) {
	system("cls");
	if (!secondSafetyVerify(admin)) {
		return;
	}
	if (clearFile_Bin(ORDERFILE_BIN)) {
		printf("\033[32m[Info] 预约记录已清空。\033[0m\n");
	}
	else {
		printf("\033[31;1m[Error] Failed to clear file in func \"clearOrderLogs\".\033[0m\n");
	}
	system("pause");
}

// ---------- all ----------

void showAllOrder(Person* me) {
	system("cls");
	showOrderLogs(NULL);
}

void showOrderLogs(Person* p) {
	system("cls");
	List* curlist = NULL;
	List* full_list = readOrderFromFile_Bin();
	if (full_list == NULL) {
		printf("\033[31;1m[Error] Var \"full_list\" is a nullptr in func \"showOrderLogs\".\033[0m\n");
		return;
	}
	if (p != NULL) {
		Order tmp;
		strcpy(tmp.stu_Id, p->m_Id);
		List* sub_list = generateSublist_Ref(
			full_list,
			&tmp,
			isOrderPersonEqual,
			orderCopy
		);
		destroyList(full_list);
		full_list = NULL;
		if (sub_list == NULL) {
			printf("\033[31;1m[Error] Var \"sub_list\" is a nullptr in func \"showOrderLogs\".\033[0m\n");
			system("pause");
			return;
		}
		curlist = sub_list;
	}
	else {
		curlist = full_list;
	}
	int shift;
	PF cmp = orderListSortAdvice(&shift);
	if (cmp != NULL) {
		sortForList(curlist, cmp);
		if (shift == 2) {
			reverseList(curlist);
		}
		showListInPages(
			curlist,
			showOrderHeader,
			showOrderInLine,
			15,
			1,
			1
		);
	}
	destroyList(curlist);
	curlist = NULL;
	system("pause");
}

// 只有person有专门的搜索函数
Person* findPerson(int type, char* id) {
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("\033[31;1m[Error] Var \"personList\" is a nullptr in func \"findPerson\".\033[0m\n");
	}
	Node* res = findListElemNode(personList, id, isPersonIdEqual);
	if (res == NULL) {
		printf("\033[31m[Info] 未找到该账号。\033[0m\n");
		destroyList(personList);
		personList = NULL;
		return NULL;
	}
	Person* p = personCopy(res->data);
	destroyList(personList);
	personList = NULL;
	return p;
}

void manageOrderLoop(Person* person, int type) {
	List* orderList = readOrderFromFile_Bin();
	if (orderList == NULL) {
		printf("\033[31;1m[Error] Var \"orderList\" is a nullptr in func \"manageOrderLoop\".\033[0m\n");
		system("pause");
		return;
	}
	Order tmp;
	List* sub = NULL;
	if (type == 1) {
		strcpy(tmp.stu_Id, person->m_Id);
		sub = generateSublist_Ref(
			orderList,
			&tmp,
			canOrderBeCanceled,
			orderCopy
		);
	}
	else {
		sub = generateSublist_Det(
			orderList,
			isOrderUnchecked,
			orderCopy
		);
	}
	if (sub == NULL) {
		printf("\033[31;1m[Error] Var \"sub\" is a nullptr in func \"checkOrder\".\033[0m\n");
		system("pause");
		return;
	}
	// 下面进入loop
	int running = 1;
	int lastpage = 0;
	while (running) {
		system("cls");
		int shift;
		PF cmp = orderListSortAdvice(&shift);
		if (cmp != NULL) {
			if (shift == 2) {
				reverseList(sub);
			}
			sortForList(sub, cmp);
			showListInPages(
				sub,
				showOrderHeader,
				showOrderInLine,
				15,
				1,
				1
			);
			int subidx = 0;
			char message1[80] = { 0 };
			sprintf(message1, "请输入要%s的预约序号：（输入‘0’退出）", (type == 1 ? "取消" : "审核"));
			digitInput(&subidx, 3, message1, 0, sub->length);
			if (subidx == 0) {
				break;
			}
			Node* full_node = findListElemNode(
				orderList,
				getListIdxNode(sub, subidx)->data,
				isOrderIdEqual
			);
			if (full_node == NULL) {
				printf("\033[31;1m[Error] Var \"full_node\" is a nullptr in func \"checkOrder\"\033[0m\n");
				break;
			}
			printf("\033[33m[Info] 这是你选择的预约：\033[0m\n\t");
			showOrderInLine(full_node->data);
			int adj = -1;
			char message2[80] = { 0 };
			sprintf(message2, "%s", (type == 1 ? "确定要取消吗？\n1:是   0:否   >>> " : "1:同意 0:驳回 >>> "));
			digitInput(&adj, 3, message2, 0, 1);
			if (adj == -1) {
				printf("\033[31m[Info] 未能%s。\033[0m\n", (type == 1 ? "取消" : "审核"));
				break;
			}
			else if (adj == 1) {
				((Order*)(full_node->data))->state = (type == 1 ? 3 : 0);
				delListIdx(sub, subidx);
			}
			else if (adj == 0) {
				if (type == 2) {
					((Order*)(full_node->data))->state = 5;
					delListIdx(sub, subidx);
				}
			}
			else {
				printf("\033[31;1m[Error] Unexpected value of var \"adj\" = %d in func \"checkOrder\".\033[0m\n", adj);
				break;
			}
			printf("\033[32m[Info] 该项处理成功。\033[0m\n");
			system("pause");
		}
	}
	writeOrderToFile_Bin(orderList);
	destroyList(orderList);
	orderList = NULL;
	destroyList(sub);
	sub = NULL;
	system("pause");
}
