#include "BLL.h"
#include "UI.h"
#include "DAL.h"
#include "globalfile.h"
#include <stdio.h>
#include <ctype.h>

void mainLoop() {
	int running = 1;
	int option;
	while (running) {
		digitInput(&option, -1, "��ѡ����ݣ�", 0, 3);
		switch (option) {
		case 1: // student DaiBiao

			break;
		case 2: // teacher
			break;
		case 3: // admin
			break;
		case 0:
			running = 0;
			goodbye();
			break;
		default:
			printf("! ����bug������ !\n");
		}
	}
}

void login(int type, char* file) {
	;
}

void studentLoop() {

}

void teacherLoop() {

}

void adminLoop() {

}
