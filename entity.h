#pragma once

// 学生代表
// 申请使用机房
struct Student {
	char m_Id[20]; // 学号
	char m_Psw[20];
};

// 审核学生的预约申请
struct Teacher {
	char m_Id[20]; // 教职工编号
	char m_Psw[20];
};

// 管理账号
struct Admin {
	char m_Id[20]; // 管理员工号
	char m_Psw[20];
};

// 机房
// 小机房容量20人 * 5 (1~5)
// 中机房 50 * 3 (6~8)
// 大机房 100 * 2 (9~10)
struct Room {
	int m_Id; // 门牌号
	int m_Capacity; // 总容量
	int m_Size; // 已占用（预约状态0-1）
};

// 预约类
struct Order {
	char order_id[20];
	int room_Id;
	char stu_Id[20];
	int state; // 状态
	// 0 预约成功-未上机
	// 1 正在使用
	// 2 已完成
	// 3 学生取消
	// 4 教师拒绝
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