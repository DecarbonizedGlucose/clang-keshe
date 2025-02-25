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
	int m_Capacity;
	int m_Size;
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

// ----- about teacher -----

// ----- about admin -----

// ----- about room -----

// ----- about order -----