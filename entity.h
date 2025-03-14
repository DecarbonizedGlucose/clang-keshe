#pragma once

typedef int (*PF)(void*, void*, int);

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

int isTeaIdValid(char* id);

int isPasswordValid(char* psw);

void showPersonHeader();

void showPersonInLine(Person* p);

void showSinglePerson(Person* p);

PF personListSortAdvice(int*);

int cmpPersonWithId(Person* a, Person* b);

// ---------- room ----------

// 机房
// 小机房容量20人 * 5 (1~5)
// 中机房 50 * 3 (6~8)
// 大机房 100 * 2 (9~10)
typedef struct {
	int m_Id; // 门牌号
	int m_Capacity; // 总容量
	//int m_Size; // 已占用（预约状态0-1）
} Room;

Room* createEmptyRoom();

Room* createRoom(int id, int capacity);

void showRoomHeader();

void showRoomInLine(Room* r);

// ---------- order ----------

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
	// 0 审批通过-未上机(可以取消)
	// 1 正在使用
	// 2 已签退
	// 3 学生取消
	// 4 未审批(可以取消，可以审批)
	// 5 驳回
	// 6 过期(无论是否审批)
} Order;

char* createOrderId();

Order* createEmptyOrder();

Order* createOrder(char* order_Id,int room_Id,char* stu_Id,int state,int weekday);\

char* changeNumToWeekday(int num);

char* changeNumToState(int num);

void showOrderHeader();

void showOrderInLine(Order* o);

int isOrderIdEqual(Order* a, Order* b);

int isOrderPersonEqual(Order* a, Order* b);

int isOrderStateEqual(Order* a,Order* b);

Order* orderCopy(Order* prev);

int isOrderUnchecked(Order* o);

int canOrderBeCanceled(Order* listdata, Order* ref);

PF orderListSortAdvice(int*);

int cmpOrderWithOrderId(Order* a, Order* b);

int cmpOrderWithStuId(Order* a,Order* b);

int cmpOrderWithTime(Order* a, Order* b);

int cmpOrderWithState(Order* a, Order* b);
