#define _CRT_SECURE_NO_WARNINGS
#include "entity.h"
#include "DAL.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "globalfile.h"
#include "UI.h"
#include <string.h>

// �Ż�ʲô��, �п���д
// �Ľ�ʱ��洢����
// ���չʾ��������ʱ�ķ�ҳ����
// ���ͼ�ν���

// ----- about student -----

// ǩ��
void signIn(Person* stu) {
	
}

// ǩ��
void signOut(Person* stu) {

}

void applyOrder(Person* stu) {
	system("cls");
	introduceRooms();
	int weekday = 0;
	int room_Id = 0;
	printf("�Զ�ƥ��Ϊ������ĵ�һ����*��\n");
	digitInput(&weekday, 3, "������ԤԼʱ�䣺", 1, 10);
	if (weekday == 0) {
		return;
	}
	digitInput(&room_Id, 3, "����������ţ�", 1, 10);
	if (room_Id == 0) {
		return;
	}
	Order* newOrder = createEmptyOrder();
	if (newOrder == NULL) {
		printf("[ERROR] �ڴ��������޷�ԤԼ��\n");
		return;
	}
	newOrder->weekday = weekday;
	newOrder->room_Id = room_Id;
	strcpy(newOrder->stu_Id, stu->m_Id);
	strcpy(newOrder->order_Id, createOrderId());
	newOrder->state = 0;
	addNewOrder(newOrder);
	roomInfoUpdate(room_Id, 1);
}

void showMyOrder(Person* stu) {
	system("cls");
	showOrderLogs(stu);
}

void cancelOrder(Person* stu) {
	showMyOrder(stu);
	List* orderList = readOrderFromFile();
	if (orderList == NULL) {
		printf("[ERROR] �޷���ȡ�ļ����޷�ȡ��ԤԼ��\n");
		return;
	}
	char order_Id[20] = { 0 };
	strInput(order_Id, 3, strAlnumDetect, "������Ҫȡ����ԤԼ�ţ�");
	if (order_Id[0] == '\0') {
		return;
	}
	Order* order = createEmptyOrder();
	strcpy(order->order_Id, order_Id);
	strcpy(order->stu_Id, stu->m_Id);
	Node* del = findListElem(orderList, order, isOrderInfoEqual);
	if (del == NULL) {
		printf("[INFO] δ�ҵ���ԤԼ��\n");
		destroyList(orderList);
		return;
	}
	orderLogUpdate((Order*)(del->data), 3);
	roomInfoUpdate(((Order*)(del->data))->room_Id, -1);
	if (writeOrderToFile(orderList) == 0) {
		printf("[ERROR] �޷�д���ļ����޷�ȡ��ԤԼ��\n");
	}
	destroyList(orderList);
	printf("[INFO] ȡ��ԤԼ�ɹ���\n");
}

// ----- about teacher -----

void showAllOrder(Person* tea) {
	system("cls");
	showOrderLogs(NULL);
}

void showOnesOrder(Person* tea) {
	system("cls");
	char* stu_Id[20] = { 0 };
	strInput(stu_Id, 3, isStuIdValid, "������ѧ���˺ţ�");
	if (stu_Id[0] == '\0') {

	}
}

// ��γ�����һ��loop
void validOrder(Person* tea) {
	system("cls");
	
}

// ----- about admin -----

int secondSafetyVerify(Person* admin) {
	int res = 0;
	char psw[20];
	printf("[Input> ���ٴ�����������������֤��ݣ�");
	fgets(psw, 19, stdin);
	clearReturn(psw, 20);
	fflush(stdin);
	if (!strcmp(psw, admin->m_Psw)) {
		res = 1;
		printf("�����֤�ɹ���\n");
	}
	else {
		printf("�����֤ʧ�ܡ�\n");
	}
	return res;
}

void addPerson(Person* admin) {
	system("cls");
	int type = 0;
	printf("ѡ�����͡�\n");
	printf("1   -----   ѧ��\n");
	printf("2   -----   ��ʦ\n");
	printf("0   -----   �˳�\n");
	digitInput(&type, 3, "����������˺ŵ����ͣ�", 0, 2);
	if (!type) {
		return;
	}
	List* personList = readPersonFromFile(type);
	if (personList == NULL) {
		printf("[ERROR] �޷���ȡ�ļ����޷�����˺š�\n");
		return;
	}
	Person* newPerson = createEmptyPerson();
	if (newPerson == NULL) {
		printf("[ERROR] �ڴ��������޷�����˺š�\n");
		return;
	}
	printf("[Input> �ʺţ�");
	fgets(newPerson->m_Id, 19, stdin);
	clearReturn(newPerson->m_Id, 20);
	fflush(stdin);
	printf("[Input> ���룺");
	fgets(newPerson->m_Psw, 19, stdin);
	clearReturn(newPerson->m_Psw, 20);
	fflush(stdin);
	if (!secondSafetyVerify(admin)) {
		free(newPerson);
		destroyList(personList);
		return;
	}
	if (!(isIdValid(newPerson->m_Id, type) && isPasswordValid(newPerson->m_Psw))) {
		printf("[INFO] ���벻���Ϲ����޷�����˺š�\n");
		free(newPerson);
		destroyList(personList);
		return;
	}
	if (findListElem(personList, newPerson, isPersonIdEqual) != NULL) {
		printf("[INFO] ���˺��Ѵ��ڡ�\n"); // ������ԼӸ�ѯ���Ƿ񸲸ǣ��޸����룩
		// ʲô³���ԣ���֪����
		free(newPerson);
		destroyList(personList);
		return;
	}
	if (addListLast(personList, newPerson) == NULL) {
		printf("[ERROR] ���ݴ�������޷�����˺š�\n");
		free(newPerson);
		destroyList(personList);
		return;
	}
	if (writePersonToFile(personList, type) == 0) {
		printf("[ERROR] �޷�д���ļ����޷�����˺š�\n");
		free(newPerson);
		destroyList(personList);
		return;
	}
	free(newPerson);
	destroyList(personList);
	printf("[INFO] ����˺ųɹ���\n");
}

void showTypePersons(Person* admin) {
	system("cls");
	int type = 0;
	printf("ѡ�����͡�\n");
	printf("1   -----   ѧ��\n");
	printf("2   -----   ��ʦ\n");
	printf("0   -----   �˳�\n");
	digitInput(&type, 3, "������鿴�˺ŵ����ͣ�", 0, 2);
	if (!type) {
		return;
	}
	if (!secondSafetyVerify(admin)) {
		return;
	}
	List* personList = readPersonFromFile(type);
	if (personList == NULL) {
		printf("[ERROR] �޷���ȡ�ļ����޷��鿴�˺š�\n");
		return;
	}
	int count = 0;
	Node* cur = personList->head;
	printf("     ID                  Password\n");
	for (int i = 1; i <= personList->length; ++i) {
		showTypePersonsListLine((Person*)(cur->data), i);
		cur = cur->next;
		++count;
	}
	printf("[INFO] ���ҵ�%d���˺š�\n", count);
	destroyList(personList);
	system("pause");
}

void findOnePerson(Person* admin) {
	system("cls");
	int type = 0;
	char person_Id[20] = { 0 };
	printf("ѡ�����͡�\n");
	printf("1   -----   ѧ��\n");
	printf("2   -----   ��ʦ\n");
	printf("0   -----   �˳�\n");
	digitInput(&type, 3, "����������˺ŵ����ͣ�", 0, 2);
	if (!type) {
		return;
	}
	strInput(person_Id, 3, isStuIdValid, "������Ҫ���ҵ��˺ţ�");
	if (person_Id[0] == '\0') {
		return;
	}	
	if (!secondSafetyVerify(admin)) {
		return;
	}
	Person* p = findPerson(type, person_Id);
	if (p == NULL) {
		return;
	}
	showSinglePerson(p);
	free(p);
	system("pause");
}

void delOnePerson(Person* admin) {

}

void changePersonInfo(Person* admin) {

}

void showRooms(Person* admin) {
	system("cls");
	if (!secondSafetyVerify(admin)) {
		return;
	}
	List* roomList = readRoomFromFile();
	if (roomList == NULL) {
		printf("[ERROR] �޷���ȡ�ļ����޷��鿴������\n");
		return;
	}
	Node* cur = roomList->head;
	printf("����     ����                ��ռ��\n");
	for (int i = 1; i <= roomList->length; ++i) {
		showRoomListLine((Room*)(cur->data));
		cur = cur->next;
	}
	destroyList(roomList);
	system("pause");
}

void cleanRecords(Person* admin) {
	system("cls");
	if (!secondSafetyVerify(admin)) {
		return;
	}
	if (clearFile(ROOMFILE)) {
		printf("[INFO] ������¼����ա�\n");
	}
	else {
		printf("[ERROR] �޷���ջ�����¼��\n");
	}
}

// ----- all -----

void showOrderLogs(Person* p) {
	system("cls");
	List* orderList = readOrderFromFile();
	if (orderList == NULL) {
		printf("[ERROR] �޷���ȡ�ļ����޷��鿴ԤԼ��¼��\n");
		return;
	}
	int count = 0;
	printf("          ������            \
ѧ���˺�            \
���� ʱ��      ״̬\n");
	Node* cur = orderList->head;
	while (cur != NULL) {
		if (p == NULL || !strcmp(p->m_Id, ((Order*)(cur->data))->stu_Id)) {
			count++;
			showOrderListLine(cur->data, count);
		}
	}
	printf("\n[INFO] ���ҵ�%d����¼��\n", count);
	destroyList(orderList);
}

Person* findPerson(int type, char* id) {
	List* personList = readPersonFromFile(type);
	if (personList == NULL) {
		printf("[ERROR] �޷������˺š�\n");
	}
	Node* res = findListElem(personList, id, isPersonIdEqual);
	if (res == NULL) {
		printf("[INFO] δ�ҵ����˺š�\n");
		destroyList(personList);
		return NULL;
	}
	Person* p = personCopy(res->data);
	destroyList(personList);
	return p;
}