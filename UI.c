#include <stdio.h>
#include <stdlib.h>
#include "entity.h"

void showMainMenu() {
	system("cls");
	printf("============  欢迎来到西安架空大学机房预约系统  ===========\n\n");
	printf("\t\t+-------------------------------+\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          1.学    生           |\n");
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
	printf("\t\t|          1.机房签到              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          2.机房签退              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          3.申请预约              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          4.查看我的预约          |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          5.取消预约              |\n");
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
	printf("\t\t|          3.查找账号             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          4.删除账号             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          5.修改账号             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          6.查看机房             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          7.清空预约             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          0.注销登录             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t+---------------------------------+\n");
}

void introduceRooms() {
	system("cls");
	printf("机房开放时间为周一至周五8:00-11:30、13:30-22:30，具体代号如下\n");
	printf("       上午    下午\n");
	printf("周一     1      2\n");
	printf("周二     3      4\n");
	printf("周三     5      6\n");
	printf("周四     7      8\n");
	printf("周五     9     10\n");
	printf("机房如下\n");
	printf("小机房(20)：1-5\n");
	printf("中机房(50)：6-8\n");
	printf("大机房(100)：9-10\n");
	system("pause");
}