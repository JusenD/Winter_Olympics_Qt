#include"CMD.h"
#include"Calculator.h"
#include"Administrator.h"
#include"User.h"
#include"Data.h"
#include"SQL.h"

void Administrator_Module() {
	Administrator a;
	a.log_in();
}
void Register() {
	User a;
	a.regist();
}
void User_Module() {
	User a;
	a.log_in();
}
void CMD::init() {
	system("chcp 65001");
    string folderPath = ".\\Winter_temp";
    string command;
    command = "mkdir " + folderPath;
    system(command.c_str());
    system("cls");
	Commodity::init();
	Order::init();
	User::init();
}
void CMD::circle() {
	while (true) {
		char choice[10];
		cout << "=============================================" << endl;
		cout << "1.管理员登陆 2.用户注册 3.用户登录 4.退出程序" << endl;
		cout << "=============================================" << endl;
		cout << "请输入操作：";
		cin.getline(choice, 10);									//防止出现错误输入
		if (strcmp(choice, "1") == 0) Administrator_Module();
		else if (strcmp(choice, "2") == 0) Register();
		else if (strcmp(choice, "3") == 0) User_Module();
		else if (strcmp(choice, "4") == 0) exit(0);
		else cout << "输入错误\n";
	}
}
