#define _CRT_SECURE_NO_WARNINGS
#include "BLL.h"
#include "UI.h"
#include "DAL.h"
#include "globalfile.h"
#include "list.h"
#include "entity.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "service.h"
#include "iohelper.h"
//#include <conio.h>
//优化的事以后再说罢

void mainLoop() {
	int running = 1;
	int option;
	while (running) {
		showMainMenu();
		digitInput(&option, -1, "请选择身份：", 0, 3);
		if (!option) {
			running = 0;
			break;
		}
		Person* pp = login(option);
		if (pp == NULL) {
			continue;
		}
		switch (option) {
		case 1: // 学生代表
			studentLoop(pp);
			break;
		case 2: // 教师
			teacherLoop(pp);
			break;
		case 3: // 管理员
			adminLoop(pp);
			break;
		default:
			printf("[ERROR] Unexpected value of var \"option\" = %d in func \"mainLoop\".\n", option);
		}
	}
}

Person* login(int type) {
	Person* person = NULL;
	List* personList = readPersonFromFile_Bin(type);
	if (personList == NULL) {
		printf("[ERROR] Failed to read person from file in func \"login\".\n");
		return NULL;
	}
	Person tmp;
	int count = 3;
	while (count--) {
		printf("[Input] 帐号：");
		fgets(tmp.m_Id, 19, stdin);
		clearReturn(tmp.m_Id, 20);
		fflush(stdin);
		printf("[Input] 密码：");
		fgets(tmp.m_Psw, 19, stdin);
		clearReturn(tmp.m_Psw, 20);
		fflush(stdin);
		Node* res = findListElemNode(personList, &tmp, isPersonInfoEqual);
		if (res == NULL) {
			printf("[INFO] 账号或密码错误，\n");
			printf("[INFO] 你还有%d次机会。\n", count);
		}
		else {
			person = createEmptyPerson();
			if (person == NULL) {
				printf("[ERROR] 内存分配错误，登录失败。\n");
				return NULL;
			}
			strcpy(person->m_Id, tmp.m_Id);
			strcpy(person->m_Psw, tmp.m_Psw);
			printf("[INFO] 登录成功。\n");
			system("pause");
			break;
		}
	}
	destroyList(personList);
	return person;
}

void studentLoop(Person* me) {
	int running = 1;
	int option;
	while (running) {
		showStudentMenu();
		digitInput(&option, -1, "请选择操作：", 0, 5);
		if (!option) {
			running = 0;
			break;
		}
		switch (option) {
		case 1:
			signIn(me);
			break;
		case 2:
			signOut(me);
			break;
		case 3:
			applyOrder(me);
			break;
		case 4:
			showMyOrder(me);
			break;
		case 5:
			cancelOrder(me);
			break;
		default:
			printf("[ERROR] Unexpected value of var \"option\" = %d in func \"studentLoop\".\n", option);
		}
	}
}

void teacherLoop(Person* me) {
	int running = 1;
	int option;
	while (running) {
		showTeacherMenu();
		digitInput(&option, -1, "请选择操作：", 0, 2);
		if (!option) {
			running = 0;
			break;
		}
		switch (option) {
		case 1:
			showAllOrder(me);
			break;
		case 2:
			checkOrder(me);
			break;
		default:
			printf("[ERROR] Unexpected value of var \"option\" = %d in func \"teacherLoop\".\n", option);
		}
	}
}

void adminLoop(Person* me) {
	int running = 1;
	int option;
	while (running) {
		showAdminMenu();
		digitInput(&option, -1, "请选择操作：", 0, 8);
		if (!option) {
			running = 0;
			break;
		}
		switch (option) {
		case 1:
			showAllOrder(me);
			break;
		case 2:
			addPerson(me);
			break;
		case 3:
			showTypePersons(me);
			break;
		case 4:
			findOnePerson(me);
			break;
		case 5:
			delOnePerson(me);
			break;
		case 6:
			resetPersonPassword(me);
			break;
		case 7:
			showRooms(me);
			break;
		case 8:
			clearOrderLogs(me);
			break;
		default:
			printf("[ERROR] Unexpected value of var \"option\" = %d in func \"adminLoop\".\n", option);
		}
	}
}
