#include "entity.h"
#include "DAL.h"

// ----- about student -----

void applyOrder(Person* stu) {

}

void showMyOrder(Person* stu) {

}

void showAllOrder_stu(Person* stu) {

}

void cancelOrder(Person* stu) {

}

// ----- about teacher -----

void showAllOrder_tea(Person* tea) {

}

void validOrder(Person* tea) {

}

// ----- about admin -----

void addPerson() { // 没写完，
	int type = 0;
	printf("选择类型。\n");
	printf("1   -----   学生\n");
	printf("2   -----   教师\n");
	printf("3   -----   退出\n");
	digitInput(&type, 3, "请输入添加账号的类型：", 0, 2);
}

void showPerson() {

}

void showRooms() {

}

void cleanRecords() {

}

// ----- about room -----

// ----- about order -----
