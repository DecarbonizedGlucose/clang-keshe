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
//#include <conio.h>
//优化的事以后再说罢

void mainLoop() {
	int running = 1;
	int option;
	showMainMenu();
	while (running) {
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
		/*case 0:
			running = 0;
			goodbye();
			break;*/
		default:
			printf("[ERROR] 程序bug出现了 !\n");
		}
	}
}

Person* login(int type) {
	Person* person = NULL;
	List* personList = readFromPerson(type);
	if (personList == NULL) {
		printf("[ERROR] 现在无法登录。\n");
		return NULL;
	}
	Person tmp;
	int count = 3;
	while (count--) {
		printf("[INPUT] 帐号：");
		fgets(tmp.m_Id, 19, stdin);
		clearReturn(tmp.m_Id, 20);
		fflush(stdin);
		printf("[INPUT] 密码：");
		fgets(tmp.m_Psw, 19, stdin);
		clearReturn(tmp.m_Psw, 20);
		fflush(stdin);
		Node* res = findElem(personList, &tmp, isPersonEqual);
		//printf("m_Id:%s m_Psw:%s\n", ((Person*)(res->data))->m_Id, 
		// ((Person*)(res->data))->m_Psw);
		if (res == NULL) {
			printf("[INFO] 账号或密码错误，\n");
			printf("[INFO] 你还有%d次机会。\n", count);
		}
		else {
			person = (Person*)malloc(sizeof(Person));
			if (person == NULL) {
				printf("[ERROR] 内存分配错误，登录失败。\n");
				return NULL;
			}
			strcpy(person->m_Id, tmp.m_Id);
			strcpy(person->m_Psw, tmp.m_Psw);
			printf("[INFO] 登录成功。\n");
			break;
		}
	}
	return person;
}

void studentLoop(Person* me) {
	//printf("欢迎学生代表：%s登录！\n", me->m_Id);
	int running = 1;
	int option;
	showStudentMenu();
	while (running) {
		digitInput(&option, -1, "请选择操作：", 0, 4);
		if (!option) {
			running = 0;
			break;
		}
		switch (option) {
		case 1:
			applyOrder(me);
			break;
		case 2:
			showMyOrder(me);
			break;
		case 3:
			showAllOrder_stu(me);
			break;
		case 4:
			cancelOrder(me);
			break;
		default:
			printf("[ERROR] 程序bug出现了 !\n");
		}
	}
}

void teacherLoop(Person* me) {
	//printf("欢迎教师：%s登录！\n", me->m_Id);
	int running = 1;
	int option;
	showTeacherMenu();
	while (running) {
		digitInput(&option, -1, "请选择操作：", 0, 2);
		if (!option) {
			running = 0;
			break;
		}
		switch (option) {
		case 1:
			showAllOrder_tea(me);
			break;
		case 2:
			validOrder(me);
			break;
		default:
			printf("[ERROR] 程序bug出现了 !\n");
		}
	}
}

void adminLoop(Person* me) {
	//printf("欢迎管理员：%s登录！\n", me->m_Id);
	int running = 1;
	int option;
	showAdminMenu();
	while (running) {
		digitInput(&option, -1, "请选择操作：", 0, 4);
		if (!option) {
			running = 0;
			break;
		}
		switch (option) {
		case 1:
			addPerson();
			break;
		case 2:
			showPerson();
			break;
		case 3:
			showRooms();
			break;
		case 4:
			cleanRecords();
			break;
		default:
			printf("[ERROR] 程序bug出现了 !\n");
		}
	}
}
