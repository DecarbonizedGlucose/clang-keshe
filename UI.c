#include <stdio.h>
#include <stdlib.h>
#include "entity.h"

void showMainMenu() {
	system("cls");
	printf("============  ��ӭ���������ܿմ�ѧ����ԤԼϵͳ  ===========\n\n");
	printf("\t\t+-------------------------------+\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          1.ѧ������           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          2.��    ʦ           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          3.�� �� Ա           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          0.��    ��           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t+-------------------------------+\n");
}

void goodbye() {
	system("cls");
	printf("��ӭ�´�ʹ�á�\n");
	system("pause");
}

void showStudentMenu() {
	system("cls");
	printf("\t\t+----------------------------------+\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          1.����ԤԼ              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          2.�鿴�ҵ�ԤԼ          |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          3.�鿴����ԤԼ          |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          4.ȡ��ԤԼ              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          0.ע����¼              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t+----------------------------------+\n");
}

void showTeacherMenu() {
	system("cls");
	printf("\t\t+----------------------------------+\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          1.�鿴����ԤԼ          |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          2.���ԤԼ              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t|          0.ע����¼              |\n");
	printf("\t\t|                                  |\n");
	printf("\t\t+----------------------------------+\n");
}

void showAdminMenu() {
	system("cls");
	printf("\t\t+---------------------------------+\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          1.����˺�             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          2.�鿴�˺�             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          3.�鿴����             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          4.���ԤԼ             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          0.ע����¼             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t+---------------------------------+\n");
}