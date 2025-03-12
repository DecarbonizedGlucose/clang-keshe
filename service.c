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

// 优化什么的, 有空再写
// 改进时间存储机制
// 添加展示大量数据时的翻页功能(√)
// 添加图形界面

// ---------- student ----------

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
		printf("[ERROR] 内存分配错误，无法预约。\n");
		system("pause");
		return;
	}
	newOrder->weekday = weekday;
	newOrder->room_Id = room_Id;
	strcpy(newOrder->stu_Id, stu->m_Id);
	char* newOrderId = createOrderId();
	printf("order_Id=%s\n", newOrderId);
	strcpy(newOrder->order_Id, newOrderId);
	newOrder->state = 4;
	addNewOrder(newOrder);
	//roomInfoUpdate(room_Id, 1);
	free(newOrder);
	free(newOrderId);
	printf("[INFO] 预约提交成功。\n");
	system("pause");
}

void showMyOrder(Person* stu) {
	system("cls");
	showOrderLogs(stu);
}

//void cancelOrder(Person* stu) {
//	showMyOrder(stu);
//	List* orderList = readOrderFromFile();
//	if (orderList == NULL) {
//		printf("[ERROR] 无法读取文件，无法取消预约。\n");
//		system("pause");
//		return;
//	}
//	char order_Id[20] = { 0 };
//	strInput(order_Id, 3, strAlnumDetect, "请输入要取消的预约号：");
//	if (order_Id[0] == '\0') {
//		system("pause");
//		return;
//	}
//	Order* order = createEmptyOrder();
//	strcpy(order->order_Id, order_Id);
//	strcpy(order->stu_Id, stu->m_Id);
//	Node* del = findListElemNode(orderList, order, isOrderIdEqual);
//	if (del == NULL) {
//		printf("[INFO] 未找到该预约。\n");
//		destroyList(orderList);
//		system("pause");
//		return;
//	}
//	orderLogUpdate((Order*)(del->data), 3);
//	roomInfoUpdate(((Order*)(del->data))->room_Id, -1);
//	if (writeOrderToFile(orderList) == 0) {
//		printf("[ERROR] 无法写入文件，无法取消预约。\n");
//	}
//	destroyList(orderList);
//	printf("[INFO] 取消预约成功。\n");
//	system("pause");
//}

void cancelOrder(Person* stu) {
	manageOrderLoop(stu, 1);
}

// ---------- teacher ----------

void showAllOrder(Person* tea) {
	system("cls");
	showOrderLogs(NULL);
}

void showOnesOrder(Person* tea) {
	system("cls");
	char* stu_Id[20] = { 0 };
	strInput(stu_Id, 3, isPasswordValid, "请输入学生账号：");
	if (stu_Id[0] == '\0') {
		system("pause");
		return;
	}
	Person* found = findPerson(1, stu_Id);
	if (found == NULL) {
		printf("[INFO] 未找到该账号。\n");
		system("pause");
		return;
	}
	showOrderLogs(found);
	system("pause");
}

//// 这何尝不是一种loop
//void checkOrder(Person* tea) {
//	List* orderList = readOrderFromFile();
//	// 这个不能提前销毁！！
//	if (orderList == NULL) {
//		printf("[ERROR] 列表为空指针 in func \"checkOrder\".\n");
//		system("pause");
//		return;
//	}
//	Order tmp;
//	tmp.state = 4;
//	List* sub = generateSublist_Ref(
//		orderList,
//		&tmp,
//		isOrderStateEqual,
//		orderCopy
//	);
//	if (sub == NULL) {
//		printf("[ERROR] 列表为空指针 in func \"checkOrder\".\n\n");
//		system("pause");
//		return;
//	}
//	// 下面进入loop
//	int running = 1;
//	int lastpage = 0;
//	while (running) {
//		showListInPages(
//			sub,
//			showOrderHeader,
//			showOrderInLine,
//			15,
//			1,
//			1
//		);
//		int subidx = 0;
//		digitInput(&subidx, 3,
//			"请输入要审核的预约序号：（输入‘0’退出）",
//			0, sub->length);
//		if (subidx = 0) {
//			break;
//		}
//		Node* full_idx = findListElemNode(
//			orderList,
//			getListIdxNode(sub, subidx)->data,
//			isOrderIdEqual
//		);
//		if (full_idx == -1) {
//			printf("[ERROR] 父列表中找不到子列表的元素 in func \"checkOrder\"\n");
//			break;
//		}
//		printf("[INFO] 这是你选择的预约：\n\t");
//		showOrderInLine(getListIdxNode(orderList, full_idx));
//		int adj = -1;
//		digitInput(&adj, 3, "1:同意 0:驳回 >>> ", 0, 1);
//		if (adj == -1) {
//			printf("[INFO] 未能审批。\n");
//			break;
//		}
//		else if (adj == 1) {
//			((Order*)(getListIdxNode(orderList, full_idx)->data))->state = 0;
//			delListIdx(sub, subidx);
//		}
//		else if (adj == 0) {
//			((Order*)(getListIdxNode(orderList, full_idx)->data))->state = 5;
//			delListIdx(sub, subidx);
//		}
//		else {
//			printf("[ERROR] 变量\"adj\"出现意外的值 in func \"checkOrder\".\n");
//			break;
//		}
//		printf("[INFO] 该项处理成功。\n");
//	}
//	system("pause");
//}
//
void checkOrder(Person* tea) {
	manageOrderLoop(tea, 2);
}

// ---------- administrator ----------

int secondSafetyVerify(Person* admin) {
	int res = 0;
	char psw[20];
	printf("[Input] 请再次输入您的密码以验证身份：");
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
	printf("3   -----   管理员\n");
	printf("0   -----   退出\n");
	digitInput(&type, 3, "请输入添加账号的类型：", 0, 3);
	if (!type) {
		system("pause");
		return;
	}
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("[ERROR] 无法读取文件，无法添加账号。\n");
		system("pause");
		return;
	}
	Person* newPerson = createEmptyPerson();
	if (newPerson == NULL) {
		printf("[ERROR] 内存分配错误，无法添加账号。\n");
		system("pause");
		return;
	}
	printf("[Input] 帐号：");
	fgets(newPerson->m_Id, 19, stdin);
	clearReturn(newPerson->m_Id, 20);
	fflush(stdin);
	printf("[Input] 密码：");
	fgets(newPerson->m_Psw, 19, stdin);
	clearReturn(newPerson->m_Psw, 20);
	fflush(stdin);
	if (!secondSafetyVerify(admin)) {
		free(newPerson);
		destroyList(personList);
		system("pause");
		return;
	}
	if (!(isIdValid(newPerson->m_Id, type) && isPasswordValid(newPerson->m_Psw))) {
		printf("[INFO] 输入不符合规则，无法添加账号。\n");
		free(newPerson);
		destroyList(personList);
		system("pause");
		return;
	}
	if (findListElemNode(personList, newPerson, isPersonIdEqual) != NULL) {
		printf("[INFO] 该账号已存在。\n"); // 这里可以加个询问是否覆盖（修改密码）
		// 什么鲁棒性，不知道喵
		free(newPerson);
		destroyList(personList);
		system("pause");
		return;
	}
	if (addListLast(personList, newPerson) == NULL) {
		printf("[ERROR] 数据处理错误，无法添加账号。\n");
		free(newPerson);
		destroyList(personList);
		system("pause");
		return;
	}
	if (writePersonToFile_Bin(personList, type) == 0) {
		printf("[ERROR] 无法写入文件，无法添加账号。\n");
		free(newPerson);
		destroyList(personList);
		system("pause");
		return;
	}
	free(newPerson);
	destroyList(personList);
	printf("[INFO] 添加账号成功。\n");
	system("pause");
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
		system("pause");
		return;
	}
	if (!secondSafetyVerify(admin)) {
		system("pause");
		return;
	}
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("[ERROR] 无法读取文件，无法查看账号。\n");
		system("pause");
		return;
	}
	showListInPages(
		personList,
		showPersonHeader,
		showPersonInLine,
		15,
		1,
		1
	);
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
		system("pause");
		return;
	}
	strInput(person_Id, 3, isPasswordValid, "请输入要查找的账号：");
	if (person_Id[0] == '\0') {
		system("pause");
		return;
	}	
	if (!secondSafetyVerify(admin)) {
		system("pause");
		return;
	}
	Person* p = findPerson(type, person_Id);
	if (p == NULL) {
		printf("[INFO] 未找到该账号，\n");
		system("pause");
		return;
	}
	showSinglePerson(p);
	free(p);
	system("pause");
}

void delOnePerson(Person* admin) {
	system("cls");
	int type = 0;
	printf("选择类型。\n");
	printf("1   -----   学生\n");
	printf("2   -----   教师\n");
	printf("0   -----   退出\n");
	digitInput(&type, 3, "请输入查找账号的类型：", 0, 2);
	if (!type) {
		system("pause");
		return;
	}
	char* person_Id[20] = { 0 };
	if (type == 1) {
		strInput(person_Id, 3, isPasswordValid, "请输入学生账号：");
	}
	else if (type == 2) {
		strInput(person_Id, 3, isTeaIdValid, "请输入教师账号：");
	}
	else {
		printf("[ERROR] bug出现了\n");
		system("pause");
		return;
	}
	if (person_Id[0] == '\0') {
		system("pause");
		return;
	}
	if (!secondSafetyVerify(admin)) {
		system("pause");
		return;
	}
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("[ERROR] 无法读取文件。\n");
		system("pause");
		return;
	}
	Person todel;
	strcpy(todel.m_Id, person_Id);
	int idx = findListElemIdx(personList, &todel, isPersonIdEqual);
	if (idx == -1) {
		printf("[INFO] 未找到该账号。\n");
		destroyList(personList);
		system("pause");
		return;
	}
	delListIdx(personList, idx);
	writePersonToFile_Bin(personList, 1);
	destroyList(personList);
	printf("[INFO] 删除成功！\n");
	system("pause");
}

void resetPersonPassword(Person* admin) {
	system("cls");
	int type = 0;
	printf("选择类型。\n");
	printf("1   -----   学生\n");
	printf("2   -----   教师\n");
	printf("3   -----   管理员\n");
	printf("0   -----   退出\n");
	digitInput(&type, 3, "请输入查找账号的类型：", 0, 3);
	if (!type) {
		system("pause");
		return;
	}
	char* person_Id[20] = { 0 };
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
		printf("[ERROR] bug出现了\n");
		system("pause");
		return;
	}
	if (person_Id[0] == '\0') {
		system("pause");
		return;
	}
	if (!secondSafetyVerify(admin)) {
		system("pause");
		return;
	}
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("[ERROR] 无法读取文件。\n");
		system("pause");
		return;
	}
	Person tochange;
	strcpy(tochange.m_Id, person_Id);
	Node* pnode = findListElemNode(personList, &tochange, isPersonIdEqual);
	if (pnode == NULL) {
		printf("[INFO] 未找到该账号。\n");
		destroyList(personList);
		system("pause");
		return;
	}
	char new_psw[20] = { 0 };
	strInput(new_psw, 3, isPasswordValid, "请输入新的密码：");
	if (new_psw[0] == '\0') {
		printf("[INFO] 修改失败。\n");
		destroyList(personList);
		system("pause");
		return;
	}
	writePersonToFile_Bin(personList, 1);
	destroyList(personList);
	printf("[INFO] 修改成功！\n");
	system("pause");
}

void showRooms(Person* admin) {
	system("cls");
	if (!secondSafetyVerify(admin)) {
		system("pause");
		return;
	}
	List* roomList = readRoomFromFile_Bin();
	if (roomList == NULL) {
		printf("[ERROR] 无法读取文件，无法查看机房。\n");
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
	system("pause");
}

void cleanRecords(Person* admin) {
	system("cls");
	if (!secondSafetyVerify(admin)) {
		return;
	}
	if (clearFile_Bin(ROOMFILE)) {
		printf("[INFO] 机房记录已清空。\n");
	}
	else {
		printf("[ERROR] 无法清空机房记录。\n");
	}
	system("pause");
}

// ---------- all ----------

void showOrderLogs(Person* p) {
	system("cls");
	List* curlist = NULL;
	List* full_list = readOrderFromFile_Bin();
	if (full_list == NULL) {
		printf("[ERROR] 获取数据失败。\n");
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
		curlist = sub_list;
	}
	else {
		curlist = full_list;
	}
	if (curlist == NULL) {
		printf("[ERROR] 内存分配错误。\n");
		return NULL;
	}
	showListInPages(
		curlist,
		showOrderHeader,
		showOrderInLine,
		15,
		1,
		1
	);
	destroyList(curlist);
	system("pause");
}

// 只有person有专门的搜索函数
Person* findPerson(int type, char* id) {
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("[ERROR] 无法查找账号。\n");
	}
	Node* res = findListElemNode(personList, id, isPersonIdEqual);
	if (res == NULL) {
		printf("[INFO] 未找到该账号。\n");
		destroyList(personList);
		return NULL;
	}
	Person* p = personCopy(res->data);
	destroyList(personList);
	return p;
}

void manageOrderLoop(Person* person, int type) {
	List* orderList = readOrderFromFile_Bin();
	if (orderList == NULL) {
		printf("[ERROR] 列表为空指针 in func \"checkOrder\".\n");
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
		printf("[ERROR] 列表为空指针 in func \"checkOrder\".\n\n");
		system("pause");
		return;
	}
	// 下面进入loop
	int running = 1;
	int lastpage = 0;
	while (running) {
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
			printf("[ERROR] 父列表中找不到子列表的元素 in func \"checkOrder\"\n");
			break;
		}
		printf("[INFO] 这是你选择的预约：\n\t");
		showOrderInLine(full_node);
		int adj = -1;
		char message2[80] = { 0 };
		sprintf(message2, "%s", (type == 1 ? "确定要取消吗？\n1:是   0:否   >>> " : "1:同意 0:驳回 >>> "));
		digitInput(&adj, 3, message2, 0, 1);
		if (adj == -1) {
			printf("[INFO] 未能%s。\n", (type == 1 ? "取消" : "审核"));
			break;
		}
		else if (adj == 1) {
			((Order*)(full_node->data))->state = (type == 1 ? 3 : 0);
			//roomInfoUpdate(((Order*)(full_node->data))->room_Id, )
			delListIdx(sub, subidx);
		}
		else if (adj == 0) {
			if (type == 2) {
				((Order*)(full_node->data))->state = 5;
				delListIdx(sub, subidx);
			}
		}
		else {
			printf("[ERROR] 变量\"adj\"出现意外的值 in func \"checkOrder\".\n");
			break;
		}
		printf("[INFO] 该项处理成功。\n");
	}
	destroyList(orderList);
	destroyList(sub);
	system("pause");
}