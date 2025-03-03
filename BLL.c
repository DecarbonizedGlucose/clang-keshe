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
//#include <conio.h>

void mainLoop() {
	int running = 1;
	int option;
	showMainMenu();
	while (running) {
		digitInput(&option, -1, "请选择身份：", 0, 3);
		if (!option) {
			running = 0;
			goodbye();
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

}

void teacherLoop(Person* me) {

}

void adminLoop(Person* me) {

}
