#include<iostream>
#include<string.h>
#include"SQL.h"
#include"Administrator.h"
using namespace std;

extern int len(string);
void Administrator::check_commodity() {
	SQL a;
	string instruction = "SELECT * FROM commodity";
	a.operate(instruction, 1, "0");
}

void Administrator::search() {
	string name, instruction;
	cout << "请输入商品名称："; cin >> name;;
	getchar();
	instruction = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
	instruction.append(name);
	SQL a;
	a.operate(instruction, 1, "0");
}

void Administrator::off_shelf() {
	string ID, instruction, choice;
	SQL a;
	cout << "请输入要下架的商品ID："; cin >> ID;
	Commodity c; int i = 0; bool whether = false;
	while (i < c.all.size()) {
		if (ID == c.all[i].commodityID) {
			whether = true;
			break;
		}
		i++;
	}
	if (whether) {
		cout << "确定要下架该商品吗?\n";
		instruction = "SELECT * FROM commodity WHERE 商品ID CONTAINS ";
		instruction.append(ID);
		a.operate(instruction, 1, "0");
		cout << "请选择(y/n): "; cin >> choice;
		while (true) {
			if (choice == "y") {
				instruction = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
				instruction.append(ID);
				a.operate(instruction, 1, "0");
				cout << "下架成功\n\n";
				break;
			}
			else if (choice == "n") {
				cout << "取消下架\n\n";
				break;
			}
			else {
				cout << "输入有误，请重新输入\n";
			}
		}
	}
	else cout << "\n商品不存在\n" << endl;
	getchar();
}

void Administrator::check_order() {
	string instruction = "SELECT * FROM order";
	SQL a;
	a.operate(instruction, 1, "0");
}

void Administrator::check_user() {
	string instruction = "SELECT * FROM user";
	SQL a;
	a.operate(instruction, 1, "0");
}

void Administrator::ban_user() {
	string ID, instruction, choice;
	SQL a;
	cout << "请输入要下架的用户ID："; cin >> ID;
	User c; int i = 0; bool whether = false;
	while (i < c.all.size()) {
		if (ID == c.all[i].userID) {
			whether = true;
			break;
		}
		i++;
	}
	if (whether) {
		cout << "确定要封禁该用户吗?\n";
		printf("********************************************************************\n");
		printf("用户ID 用户名 密码      联系方式    地址           钱包余额 用户状态\n");
		int standard = 0, j = 0;
		standard = 7;
		printf("%s", c.all[i].userID.c_str());
		j = standard - len(c.all[i].userID);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", c.all[i].username.c_str());
		j = standard - len(c.all[i].username);
		for (; j > 0; j--) printf(" ");
		standard = 10;
		printf("%s", c.all[i].password.c_str());
		j = standard - len(c.all[i].password);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", c.all[i].phoneNumber.c_str());
		j = standard - len(c.all[i].phoneNumber);
		for (; j > 0; j--) printf(" ");
		standard = 15;
		printf("%s", c.all[i].adress.c_str());
		j = standard - len(c.all[i].adress);
		for (; j > 0; j--) printf(" ");
		standard = 9;
		printf("%s", c.all[i].balance.c_str());
		j = standard - len(c.all[i].balance);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", c.all[i].userState.c_str());
		j = standard - len(c.all[i].userState);
		for (; j > 0; j--) printf(" ");
		printf("\n");
		printf("********************************************************************\n");
		cout << "请选择(y/n): "; cin >> choice;
		while (true) {
			if (choice == "y") {
				instruction = "UPDATE user SET 用户状态 = 封禁 WHERE 用户ID = ";
				instruction.append(ID);
				a.operate(instruction, 1, "0");
				instruction = "UPDATE commodity SET 商品状态 = 已下架 WHERE 卖家ID = ";
				instruction.append(ID);
				a.operate(instruction, 1, "0");
				cout << "封禁成功\n\n";
				break;
			}
			else if (choice == "n") {
				cout << "取消封禁\n\n";
				break;
			}
			else {
				cout << "输入有误，请重新输入\n";
				cin >> choice;
			}
		}
	}
	else cout << "\n用户不存在\n" << endl;
	getchar();
}

void Administrator::operate() {
	while (true) {
		cout << "====================================================================================" << endl;
		cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl;
		cout << "====================================================================================" << endl;
		cout << "请输入操作：";
		char choice[10];
		cin.getline(choice, 10);
		if (strcmp(choice, "1") == 0) check_commodity();
		else if (strcmp(choice, "2") == 0) search();
		else if (strcmp(choice, "3") == 0) off_shelf();
		else if (strcmp(choice, "4") == 0) check_order();
		else if (strcmp(choice, "5") == 0) check_user();
		else if (strcmp(choice, "6") == 0) ban_user();
		else if (strcmp(choice, "7") == 0) break;
		else cout << "输入错误\n";
	}
}

void Administrator::log_in() {
	char name[40]; char password[40];
	cout << "请输入管理员姓名：";
	cin.getline(name, 40);
	cout << "请输入密码：";
	cin.getline(password, 40); cout << endl;
	if (strcmp(name, "admin") == 0 && strcmp(password, "1234567") == 0) {
		cout << "-----登陆成功-----" << endl << endl;
		operate();
	}
	else cout << "----密码错误，登陆失败，返回主菜单----" << endl << endl;
}