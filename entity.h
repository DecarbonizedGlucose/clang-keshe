#pragma once

// ----- about person -----

/*学生代表，教师，管理员
关于id和psw的约定
m_Id : 学生10位标准学号，8位教职工编号，8位管理工号
m_Psw : 8-16位大小写英文字母和数字的组合，不得出现其他字符
*/
typedef struct {
    char m_Id[20]; // 唯一标识ID
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

// 机房
// 小机房容量20人 * 5 (1~5)
// 中机房 50 * 3 (6~8)
// 大机房 100 * 2 (9~10)
typedef struct {
	int m_Id; // 门牌号
	int m_Capacity; // 总容量
	int m_Size; // 已占用（预约状态0-1）
} Room;

Room* createEmptyRoom();

Room* createRoom(int id, int capacity, int size);

void showRoomListLine(Room* r);

// ----- about order -----

// 预约类
// 考虑将weekday改为struct tm，预约时间为年月日上下午
// 如2025-3-12-上午
// 暂未修改
// 写入文件的顺序：order_Id stu_Id room_Id weekday state
typedef struct {
	char order_Id[20];
	char stu_Id[20];
	int room_Id;
	int weekday; // 1-10
	int state; // 状态
	// 0 预约成功-未上机
	// 1 正在使用
	// 2 已完成
	// 3 学生取消
	// 4 教师拒绝
} Order;

char* createOrderId();

Order* createEmptyOrder();

Order* createOrder(char* order_Id, int room_Id, char* stu_Id, int state, int weekday);\

void showOrderListLine(Order* o, int idx);

int isOrderInfoEqual(Order* a, Order* b);