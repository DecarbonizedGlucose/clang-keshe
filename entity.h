#pragma once

// ----- about person -----

/*ѧ��������ʦ������Ա
����id��psw��Լ��
m_Id : ѧ��10λ��׼ѧ�ţ�8λ��ְ����ţ�8λ������
m_Psw : 8-16λ��СдӢ����ĸ�����ֵ���ϣ����ó��������ַ�
*/
typedef struct {
    char m_Id[20]; // Ψһ��ʶID
    char m_Psw[20];
} Person;

Person* createEmptyPerson();

Person* personCopy(Person* p);

int isPersonInfoEqual(Person* a, Person* b);

int isPersonIdEqual(Person* a, Person* b);

int isIdValid(char* id, int type);

int isStuIdValid(char* id);

int isPasswordValid(char* psw);

void showTypePersonsListLine(Person* p, int idx);

void showSinglePerson(Person* p);

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

Room* createEmptyRoom();

Room* createRoom(int id, int capacity, int size);

void showRoomListLine(Room* r);

// ----- about order -----

// ԤԼ��
// ���ǽ�weekday��Ϊstruct tm��ԤԼʱ��Ϊ������������
// ��2025-3-12-����
// ��δ�޸�
// д���ļ���˳��order_Id stu_Id room_Id weekday state
typedef struct {
	char order_Id[20];
	char stu_Id[20];
	int room_Id;
	int weekday; // 1-10
	int state; // ״̬
	// 0 ԤԼ�ɹ�-δ�ϻ�
	// 1 ����ʹ��
	// 2 �����
	// 3 ѧ��ȡ��
	// 4 ��ʦ�ܾ�
} Order;

char* createOrderId();

Order* createEmptyOrder();

Order* createOrder(char* order_Id, int room_Id, char* stu_Id, int state, int weekday);\

void showOrderListLine(Order* o, int idx);

int isOrderInfoEqual(Order* a, Order* b);