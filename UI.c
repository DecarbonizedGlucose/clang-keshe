#include <stdio.h>

void showMainMenu() {
	printf("============  欢迎来到西安架空大学机房预约系统  ===========\n");
	printf("\n请输入您的身份\n");
	printf("\t\t -------------------------------\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          1.学生代表           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          2.老    师           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          3.管 理 员           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          0.退    出           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t -------------------------------\n");
}

void goodbye() {
	printf("欢迎下次使用。\n");
	system("pause");
}