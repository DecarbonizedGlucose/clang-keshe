#include <stdio.h>
#include <stdlib.h>
#include "entity.h"

void showMainMenu() {
	system("cls");
	printf("============  欢迎来到西安架空大学机房预约系统  ===========\n\n");
	printf("\t\t+-------------------------------+\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          1.学生代表           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          2.老    师           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          3.管 理 员           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          0.退    出           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t+-------------------------------+\n");
}

void goodbye() {
	system("cls");
	printf("欢迎下次使用。\n");
	system("pause");
}

void showStudentMenu() {
	system("cls");
	printf("\t\t+----------------------------------+\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          1.申请预约              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          2.查看我的预约          |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          3.查看所有预约          |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          4.取消预约              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          0.注销登录              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t+----------------------------------+\n");
}

void showTeacherMenu() {
	system("cls");
	printf("\t\t+----------------------------------+\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          1.查看所有预约          |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          2.审核预约              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          0.注销登录              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t+----------------------------------+\n");
}

void showAdminMenu() {
	system("cls");
	printf("\t\t+---------------------------------+\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          1.添加账号             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          2.查看账号             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          3.查看机房             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          4.清空预约             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          0.注销登录             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t+---------------------------------+\n");
}