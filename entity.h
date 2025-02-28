#pragma once

// ѧ������
// ����ʹ�û���
struct Student {
	char m_Id[20]; // ѧ��
	char m_Psw[20];
};

// ���ѧ����ԤԼ����
struct Teacher {
	char m_Id[20]; // ��ְ�����
	char m_Psw[20];
};

// �����˺�
struct Admin {
	char m_Id[20]; // ����Ա����
	char m_Psw[20];
};

// ����
// С��������20�� * 5 (1~5)
// �л��� 50 * 3 (6~8)
// ����� 100 * 2 (9~10)
struct Room {
	int m_Id; // ���ƺ�
	int m_Capacity; // ������
	int m_Size; // ��ռ�ã�ԤԼ״̬0-1��
};

// ԤԼ��
struct Order {
	char order_id[20];
	int room_Id;
	char stu_Id[20];
	int state; // ״̬
	// 0 ԤԼ�ɹ�-δ�ϻ�
	// 1 ����ʹ��
	// 2 �����
	// 3 ѧ��ȡ��
	// 4 ��ʦ�ܾ�
};

// ----- about student -----

struct Student* createStudent(char id[20], char psw[20]);

int isStudentEqual(struct Student* a, struct Student* b);

// ----- about teacher -----

struct Teacher* createTeacher(char id[20], char psw[20]);

int isTeacherEqual(struct Teacher* a, struct Teacher* b);

// ----- about admin -----

struct Admin* createAdmin(char id[20], char psw[20]);

int isAdminEqual(struct Admin* a, struct Admin* b);

// ----- about room -----

// ----- about order -----