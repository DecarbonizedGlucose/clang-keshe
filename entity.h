#pragma once

// Student, Teacher and Admin(istrator)
typedef struct {
    char m_Id[20]; // only-recognized id
    char m_Psw[20]; // personal password for the account
} Person;

// ����
// С��������20�� * 5 (1~5)
// �л��� 50 * 3 (6~8)
// ����� 100 * 2 (9~10)
typedef struct {
	int m_Id; // ���ƺ�
	int m_Capacity; // ������
	int m_Size; // ��ռ�ã�ԤԼ״̬0-1��
} Room;

// ԤԼ��
typedef struct {
	char order_id[20];
	int room_Id;
	char stu_Id[20];
	int state; // ״̬
	// 0 ԤԼ�ɹ�-δ�ϻ�
	// 1 ����ʹ��
	// 2 �����
	// 3 ѧ��ȡ��
	// 4 ��ʦ�ܾ�
} Order;

// ----- about student -----

/*
struct Student* createStudent(char id[20], char psw[20]);
int isStudentEqual(struct Student* a, struct Student* b);
*/

// ----- about teacher -----

/*
struct Teacher* createTeacher(char id[20], char psw[20]);
int isTeacherEqual(struct Teacher* a, struct Teacher* b);
*/

// ----- about admin -----

/*
struct Admin* createAdmin(char id[20], char psw[20]);
int isAdminEqual(struct Admin* a, struct Admin* b);
*/

// ----- about room -----

// ----- about order -----
