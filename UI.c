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
	printf("\t\t|          3.ȡ��ԤԼ              |\n");
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
	printf("\t\t|          3.�����˺�             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          4.ɾ���˺�             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          5.�޸��˺�             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          6.�鿴����             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          7.���ԤԼ             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t|          0.ע����¼             |\n");
	printf("\t\t|                                 |\n");
	printf("\t\t+---------------------------------+\n");
}

void introduceRooms() {
	system("cls");
	printf("��������ʱ��Ϊ��һ������8:00-11:30��13:30-22:30�������������\n");
	printf("       ����    ����\n");
	printf("��һ     1      2\n");
	printf("�ܶ�     3      4\n");
	printf("����     5      6\n");
	printf("����     7      8\n");
	printf("����     9     10\n");
	printf("��������\n");
	printf("С����(20)��1-5\n");
	printf("�л���(50)��6-8\n");
	printf("�����(100)��9-10\n");
	system("pause");
}