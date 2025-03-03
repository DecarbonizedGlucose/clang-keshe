#pragma once

// ----- about person -----

/*ѧ��������ʦ������Ա
����id��psw��Լ��
m_Id : ѧ��10λ��׼ѧ�ţ�8λ��ְ����ţ�8λ������
m_Psw : 8-16λ��СдӢ����ĸ�����ֵ���ϣ�ȱһ�����Ҳ��ó��������ַ�
*/
typedef struct {
    char m_Id[20]; // Ψһ��ʶID
    char m_Psw[20];
} Person;

Person* createPerson(char id[20], char psw[20]);

int isPersonEqual(Person* a, Person* b);

// ----- about room -----

// ����
// С��������20�� * 5 (1~5)
// �л��� 50 * 3 (6~8)
// ����� 100 * 2 (9~10)
typedef struct {
	int m_Id; // ���ƺ�
	int m_Capacity; // ������
	int m_Size; // ��ռ�ã�ԤԼ״̬0-1��
} Room;

// ----- about order -----

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
