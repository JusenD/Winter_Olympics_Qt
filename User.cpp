#include"User.h"
#include"SQL.h"
#include"Calculator.h"
#include<iostream>
#include <fstream>
using namespace std;

extern int len(string str);
extern string substr(string& a, int front, int rear);
extern void assign(string& a, string& b, int front, int rear);
vector<Single_User> User::all;
vector<vector<string>> User::Qall;
struct single {
	string num;
	string sign;
	string price;
};
int Myfind(string ID) {
    int i = 0;
    while (i < Commodity::all.size()) {
        if (Commodity::all[i].commodityID == ID) return i;
        i++;
    }
    return string::npos;
}
int find(string ID) {
	int i = 0;
	while (i < Commodity::all.size()) {
		if (Commodity::all[i].commodityID == ID) return i;
		i++;
	}
	return string::npos;
}
int find_seller(string ID) {
	int j = 0;
	while (j < User::all.size()) {
		if (User::all[j].userID == ID) return j;
		j++;
	}
	return 0;
}
double StringToDouble(string a) {											//将字符数转化为double
	double n1 = 0, n2 = 1; int i = 0; bool negative = false;
	if (a[0] == '-') { negative = true; i++; }
	while (a[i] >= '0' && a[i] <= '9') {
		n1 = n1 * 10 + (double)(a[i] - '0');
		++i;
	}
	if (a[i] == '.') {
		i++;
		while (a[i] >= '0' && a[i] <= '9') {
			n2 /= 10;
			n1 += (n2 * (double)(a[i] - '0'));
			++i;
		}
	}
	if (a[i] != '\0') return -1;
	if (negative) n1 *= -1;
	return n1;
}
string DoubleToString(double x) {
	string a; 
	a = to_string(x);
	int i = a.find('.');
	if(a[i+1] == '0')a.erase(i);
	else a.erase(i + 2);
	return a;
}
string GetTime() {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	char a[30];
	sprintf(a, "%d-0%d-%d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
	string t = a;
	return t;
}
string GetCommodityID() {
	int m = Commodity::all.size() + 1;
	string ID;
	char buffer[5];
	buffer[0] = 'M';
	int i = 3;
	while (i > 0) {
		while (m != 0) {
			buffer[i] = m % 10 + '0';
			m /= 10; i--;
		}
		buffer[i] = '0'; i--;
	}
	buffer[4] = '\0';
	ID = buffer;
	return ID;
}
string GetOrderID() {
	int num = Order::all.size() + 1, i = 3;
	char buffer[5];
	buffer[0] = 'T';
	while (num != 0) {
		buffer[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	while (i > 0) {
		buffer[i] = '0';
		i--;
	}
	buffer[4] = '\0';
	string ID = buffer;
	return ID;
}
string GetUserID() {
	int num = User::all.size() + 1, i = 3;
	char buffer[5];
	buffer[0] = 'U';
	while (num != 0) {
		buffer[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	while (i > 0) {
		buffer[i] = '0';
		i--;
	}
	buffer[4] = '\0';
	string ID = buffer;
	return ID;
}
bool check_num(string num) {
	int i = 0; if (num[i] == '.') return false;
	while (i < num.length()) {
		if (num[i] >= '0' && num[i] <= '9') { i++; continue; }
		else if (num[i] == '.') {
			i++; if (!(num[i] >= '0' && num[i] <= '9')) return false;
			i++;
			if (num[i] == '\0') return true;
			else return false;
		}
		else return false;
	}
}
string GetRecharge(string ID) {
	string exp;
	string line, who; char buffer[100]; bool whether = false;
    FILE* fp = fopen(".\\Winter_temp\\recharge.txt", "a+");
	fscanf(fp, "%s\n", buffer);
	int i = 0, j = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s\n", buffer);
		line = buffer;
		i = line.find(',');
		j = line.find(',', i + 1);
		if (ID != substr(line, i + 1, j - 1)) continue;
		if (whether) exp.append(" + ");
		exp.append(substr(line, 0, i - 1));
		whether = true;
	}
	return exp;
}
string GetBuy(string ID) {
	string exp;
	int i = 0;
	while (i < Order::all.size()) {
		if (Order::all[i].buyerID != ID) { i++; continue; }
		exp.append(" - ").append(Order::all[i].number).append(" * ").append(Order::all[i].unitPrice);
		i++;
	}
	return exp;
}
string GetSell(string ID) {
	string exp;
	int i = 0;
	while (i < Order::all.size()) {
		if (Order::all[i].seller != ID) { i++; continue; }
		exp.append(" + ").append(Order::all[i].number).append(" * ").append(Order::all[i].unitPrice);
		i++;
	}
	return exp;
}
string simplify(string fexp) {
	vector<single> queue;
	int i = 0, p2 = fexp.find('*'); int p1 = fexp.rfind(' ', p2 - 2), p3 = fexp.find(' ', p2 + 2);
	if (p2 == string::npos) return fexp;
	string exp = substr(fexp, 0, p1 - 3);
	string num, price;
	while (p2 != string::npos) {
		num = substr(fexp, p1 + 1, p2 - 2); bool whether = false;
		if (p3 != string::npos) price = substr(fexp, p2 + 2, p3 - 1);
		else price = substr(fexp, p2 + 2, fexp.length() - 1);
		i = 0;
		while (i < queue.size()) {
			if (queue[i].num == num) {
				whether = true;
				break;
			}
			i++;
		}
		if (whether) {
			if (queue[i].price[0] != '(') {
				string bu = "("; queue[i].price = bu.append(queue[i].price);
			}
			if (queue[i].sign == substr(fexp, p1 - 2, p1)) {
				queue[i].price.append(" + ").append(price);
			}
			else queue[i].price.append(" - ").append(price);
		}
		else {
			single new_one;
			new_one.num = num; new_one.price = price; new_one.sign = substr(fexp, p1 - 2, p1);
			queue.push_back(new_one);
		}
		if (p3 != string::npos) {
			p1 = p3 + 2; p2 = fexp.find('*', p1); p3 = fexp.find(' ', p2 + 2);
		}
		else p2 = string::npos;
	}
	i = 0;
	while (i < queue.size()) {
		exp.append(queue[i].sign).append(queue[i].num).append(" * ").append(queue[i].price);
		if (queue[i].price[0] == '(') exp.append(")");
		i++;
	}
	return exp;
}
void User::init() {
	all.clear();
	bool empty = false;
    FILE* buf = fopen(".\\Winter_temp\\user.txt", "a+");
	assert(buf != NULL && "文件打开失败\n");
	fclose(buf);
    FILE* p = fopen(".\\Winter_temp\\user.txt", "r");
	assert(p != NULL && "user文件打开失败");
	char f[100];
    fscanf(p, "%s", f);
    if (feof(p)) empty = true;
	fclose(p);
    FILE* fp = fopen(".\\Winter_temp\\user.txt", "a+");
	assert(fp != NULL && "user文件打开失败\n");
	if (empty) fprintf(fp, "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态\n");
	else {
        ifstream fp1;
        fp1.open(".\\Winter_temp\\user.txt", ios::out);
        char buffer[200];
        fp1.getline(buffer, 100);
//        fscanf(fp, "%s\n", buffer);
		string line; int i = 0; int j = 0;
        while (!fp1.eof()) {
            fp1.getline(buffer, 100);
//			fscanf(fp, "%s\n", buffer);
            line = buffer;
            if(line == "") continue;
			Single_User a;
			i = 0; j = line.find(',');
			a.userID = substr(line, i, j - 1);
			i = j, j = line.find(',', j + 1);
			a.username = substr(line, i + 1, j - 1);
			i = j, j = line.find(',', j + 1);
			a.password = substr(line, i + 1, j - 1);
			i = j, j = line.find(',', j + 1);
			a.phoneNumber = substr(line, i + 1, j - 1);
			i = j, j = line.find(',', j + 1);
			a.adress = substr(line, i + 1, j - 1);
			i = j, j = line.find(',', j + 1);
			a.balance = substr(line, i + 1, j - 1);
			i = j, j = line.find(',', j + 1);
			a.userState = substr(line, i + 1, line.length() - 1);
			all.push_back(a);
		}
        fp1.close();
	}
    fclose(fp);
    Qinit();
}
void User::Qinit(){
    Qall.clear();
    for(int i = 0; i < all.size(); i++){
        Single_User *a = &all[i];
        vector<string> b;
        b.push_back(a->userID);
        b.push_back(a->username);
        b.push_back(a->password);
        b.push_back(a->phoneNumber);
        b.push_back(a->adress);
        b.push_back(a->balance);
        b.push_back(a->userState);
        Qall.push_back(b);
    }
}
void User::preserve() {
    FILE* fp = fopen(".\\Winter_temp\\user.txt", "w+");
	assert(fp != NULL && "文件打开失败\n");
	int i = 0;
	fprintf(fp, "用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态\n");
	while (i < all.size()) {
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", all[i].userID.c_str(), all[i].username.c_str(),
			all[i].password.c_str(), all[i].phoneNumber.c_str(), all[i].adress.c_str(),
			all[i].balance.c_str(), all[i].userState.c_str());
		++i;
	}
	fclose(fp);
    init();
}
void User::operate(Single_User* me) {
	while (true) {
		cout << "===============================================" << endl;
		cout << "1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录" << endl;
		cout << "===============================================" << endl << endl;
		string choice;
		cout << "请输入操作："; cin >> choice;
		if (choice == "1") {
			Buyer a(me);
			string ins;
			while (true) {
				cout << "=======================================================================================" << endl;
				cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主页面" << endl;
				cout << "=======================================================================================" << endl << endl;
				cout << "请输入操作："; cin >> ins;
				if (ins == "1") {
					a.commodity_list();
				}
				else if (ins == "2") {
					if (!a.buy()) {
						string x;
						cout << "是否进行充值?(y/n)";
						while (true) {
							cin >> x;
							if (x == "y") {
								a.recharge(); break;
							}
							else if (x == "n") break;
							else cout << "输入错误，请重新输入" << endl;
						}
					}
				}
				else if (ins == "3") {
					a.search();
				}
				else if (ins == "4") {
					a.history_order();
				}
				else if (ins == "5") {
					a.detail();
				}
				else if (ins == "6") break;
				else {
					cout << "输入错误，请重新输入" << endl;
					cin >> ins;
				}
			}
		}
		else if (choice == "2") {
			Seller a(me);
			string ins;
			while (true) {
				cout << "===================================================================================" << endl;
				cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主页面" << endl;
				cout << "===================================================================================" << endl << endl;
				cout << "请输入操作："; cin >> ins;
				if (ins == "1") {
					a.new_commodity();
				}
				else if (ins == "2") {
					a.existing_commodity();
				}
				else if (ins == "3") {
					a.change_commodity();
				}
				else if (ins == "4") {
					a.off_shelf_commodity();
				}
				else if (ins == "5") {
					a.history_order();
				}
				else if (ins == "6") break;
				else {
					cout << "输入错误，请重新输入" << endl;
					cin >> ins;
				}
			}
		}
		else if (choice == "3") {
			information(me);
		}
		else if (choice == "4") { getchar(); break; }
		else {
			cout << "输入错误，请重新输入" << endl;
			cin >> choice;
		}
		getchar();
	}
}
void User::log_in() {
	string name, password;
	cout << "请输入用户名："; cin >> name;
	cout << "请输入密码："; cin >> password;
	User u; int i = 0; bool whether = false, ban = false;
	while (i < u.all.size()) {
		if (name == all[i].username && password == all[i].password) {
			if (all[i].userState == "正常") whether = true;
			else ban = true;
			break;
		}
		i++;
	}
	if (whether) {
		cout << "\n-----登陆成功-----\n\n";
		operate(&u.all[i]);
	}
	else if(!ban){
		cout << "用户名或密码错误" << endl << endl;
		getchar();
	}
	else {
		cout << "用户已被封禁！" << endl << endl;
		getchar();
	}
}
void User::regist() {
	string name, password1, password2, phone, adress;
	int i = 0; bool whether = true;
	char buffer[30];
	while (whether) {
		cout << "请输入用户名："; cin.getline(buffer, 30);
		name = buffer;
		if (name.find(' ') != string::npos) {
			cout << "名称不能包含空格\n"; return;
		}
		i = 0;
		while (i < all.size()) {
			if (all[i].username == name) {
				cout << "用户名已存在！请重新输入" << endl;
				break;
			}
			i++;
		}
		if (i == all.size()) whether = false;
	}
	while (true) {
		cout << "请输入密码："; cin.getline(buffer, 30);
		password1 = buffer;
		if (password1.find(' ') != string::npos) {
			cout << "密码不能包含空格\n"; continue;
		}
		cout << "请再次输入密码："; cin.getline(buffer, 30);
		password2 = buffer;
		if (password2.find(' ') != string::npos) {
			cout << "密码不能包含空格\n"; continue;
		}
		if (password1 == password2) break;
		else cout << "两次密码不一致！" << endl;
	}
	cout << "请输入联系方式："; cin.getline(buffer, 30);
	phone = buffer;
	if (phone.find(' ') != string::npos) {
		cout << "联系方式不能包含空格\n"; return;
	}
	cout << "请输入地址："; cin.getline(buffer, 30);
	adress = buffer;
	if (adress.find(' ') != string::npos) {
		cout << "地址不能包含空格\n"; return;
	}
	Single_User a;
	a.userID = GetUserID(); a.username = name;
	a.password = password1; a.phoneNumber = phone;
	a.adress = adress; a.balance = "0"; a.userState = "正常";
	all.push_back(a);
	preserve();
	cout << "注册成功！是否以此身份登录？(y/n)" << endl;
	string x;
	while (true) {
		cin >> x;
		if (x == "y") {
			operate(&all[all.size() - 1]);
			break;
		}
		else if (x == "n") { getchar(); break; }
		else cout << "输入错误，请重新输入" << endl;
	}
}
void User::information(Single_User* me) {
	Buyer a(me); string choice;
	while (true) {
		cout << "============================================" << endl;
		cout << "1.查看信息 2.修改信息 3.充值 4返回用户主页面" << endl;
		cout << "============================================" << endl << endl;
		cout << "请输入操作："; cin >> choice;
		if (choice == "1") {
			string balance, fexpression;
			fexpression = GetRecharge(me->userID);
			fexpression.append(GetBuy(me->userID)).append(GetSell(me->userID));
			string simple = simplify(fexpression);
			if (simple.length() == 0) balance = "0";
			else balance = calculator(simple);

			cout << "*******************" << endl;
			cout << "用户名：" << me->username << endl;
			cout << "联系方式：" << me->phoneNumber << endl;
			cout << "地址：" << me->adress << endl;
			cout << "钱包余额：" << balance << endl;
			cout << "*******************" << endl << endl;
		}
		else if (choice == "2") {
			string ins;
			cout << "请选择修改的属性 (1.用户名 2.联系方式 3.地址 4.取消修改)："; cin >> ins;
			if (ins == "1") {
				string name;
				cout << "请选择修改后的用户名："; cin >> name;
				if (name == me->username) cout << "修改名称不能与原名称相同！" << endl << endl;
				else {
					int i = 0; bool same = false;
					while (i < all.size()) {
						if (all[i].username == name) {
							same = true; break;
						}
						i++;
					}
					if (same) cout << "该名称已存在！" << endl << endl;
					else {
						me->username = name;
						preserve();
					}
				}

			}
			else if (ins == "2") {
				string phone;
				cin >> phone;
				me->phoneNumber = phone;
				preserve();
			}
			else if (ins == "3") {
				string address;
				cin >> address;
				me->adress = address;
				preserve();
			}
			else if (ins == "4") {
				cout << "返回上一层" << endl << endl;
			}
			else {
				cout << "输入错误，请重新输入" << endl;
			}
		}
		else if (choice == "3") {
			a.recharge();
		}
		else if (choice == "4") break;
		else cout << "输入错误，请重新输入" << endl << endl;
	}
}
int User::SELECT() {
	//			U001   南大   123456    12345678    仙林大道163号  1024.0 正常
	printf("********************************************************************\n");
	printf("用户ID 用户名 密码      联系方式    地址           钱包余额 用户状态\n");
	int i = 0, j = 0, standard = 0;
	while (i < all.size()) {
		standard = 7;
		printf("%s", all[i].userID.c_str());
		j = standard - len(all[i].userID);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].username.c_str());
		j = standard - len(all[i].username);
		for (; j > 0; j--) printf(" ");
		standard = 10;
		printf("%s", all[i].password.c_str());
		j = standard - len(all[i].password);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", all[i].phoneNumber.c_str());
		j = standard - len(all[i].phoneNumber);
		for (; j > 0; j--) printf(" ");
		standard = 15;
		printf("%s", all[i].adress.c_str());
		j = standard - len(all[i].adress);
		for (; j > 0; j--) printf(" ");
		standard = 9;
		printf("%s", all[i].balance.c_str());
		j = standard - len(all[i].balance);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].userState.c_str());
		j = standard - len(all[i].userState);
		for (; j > 0; j--) printf(" ");
		i++; printf("\n");
	}
	printf("********************************************************************\n");
	printf("\n");
	return 1;
}
int User::UPDATE(string SET, string WHERE) {
	string target, value;
	int i = 0, j = SET.find('=');
	target = substr(SET, 0, j - 2); value = substr(SET, j + 2, SET.length() - 1);
	string compare, what;
	j = WHERE.find('=');
	compare = substr(WHERE, 0, j - 2); what = substr(WHERE, j + 2, WHERE.length() - 1);
	string a;
	while (i < all.size()) {
		if (compare == "用户ID") a = all[i].userID;
		else { printf("还有这种情况？\n"); break; }
		if (a != what) { i++; continue; }
		if (target == "用户状态") all[i].userState = value;
		else if (target == "钱包余额") all[i].balance = value;
		else { printf("还有这种情况？\n"); break; }
		i++;
	}
	preserve();
	return 1;
}

void Seller::new_commodity() {
	string name, price, number, description;
	cout << "请输入商品名称："; cin >> name;
	cout << "请输入商品价格："; cin >> price;
	if (!check_num(price)) { cout << "请输入数字！" << endl; return; }
	cout << "请输入商品数量："; cin >> number;
	if (!check_num(number)) { cout << "请输入数字！" << endl; return; }
	cout << "请输入商品描述："; cin >> description;
	cout << endl;
	Single_Commodity c;
	c.commodityName = name;
	c.price = price;
	c.number = number;
	c.description = description;
	c.sellerID = me->userID;
	cout << "请确认发布的商品信息无误！" << endl;
	cout << "*****************************" << endl;
	cout << "商品名称：" << name << endl;
	cout << "商品价格：" << price << endl;
	cout << "商品数量：" << number << endl;
	cout << "商品描述：" << description << endl;
	cout << "*****************************" << endl;
	cout << endl;
	string x;
	cout << "您确认要发布商品吗？(y/n)"; cin >> x;
	while (true) {
		if (x == "y") {
			Single_Commodity c;
			c.commodityName = name;
			c.price = price;
			c.number = number;
			c.description = description;
			c.sellerID = me->userID;
			c.addedDate = GetTime();
			c.state = "销售中";
			c.commodityID = GetCommodityID();
			Commodity j;
			string VALUES = c.commodityID;
			char buffer[500];
			sprintf(buffer, "(%s,%s,%s,%s,%s,%s,%s,%s)", c.commodityID.c_str(), c.commodityName.c_str(),
				c.price.c_str(), c.number.c_str(), c.description.c_str(), c.sellerID.c_str(), c.addedDate.c_str(), c.state.c_str());
			VALUES = buffer;
			j.INSERT(VALUES);
			cout << "发布商品成功！" << endl << endl;
			break;
		}
		else if (x == "n") {
			cout << "取消发布" << endl;
			break;
		}
		else {
			cout << "输入错误，请重新输入" << endl;
			cin >> x;
		}
	}
}
void Seller::existing_commodity() {
	string instruction = "SELECT * FROM commodity";
	SQL a;
	a.operate(instruction, 3, me->userID);
}
void Seller::change_commodity() {
	string ID, choice, price, description;
	cout << "请输入被修改商品的ID："; cin >> ID;
	int i = find(ID);
	if (i==string::npos || Commodity::all[i].sellerID != me->userID) { cout << "未找到该商品" << endl; return; }
	cout << "请输入被修改商品的属性（1.价格 2.描述 3.取消修改）："; cin >> choice;
	while (true) {
		if (choice == "1") {
			cout << "请输入被修改商品的价格："; cin >> price;
			description = Commodity::all[i].description;
			break;
		}
		else if (choice == "2") {
			cout << "请输入被修改商品的描述："; cin >> description;
			price = Commodity::all[i].price;
			break;
		}
		else if (choice == "3") {
			cout << "返回上一层" << endl << endl;
			return;
		}
		else {
			cout << "输入错误，请重新输入" << endl;
			cin >> choice;
		}
	}
	cout << "请确认修改的商品信息无误！" << endl;
	cout << "***************************************" << endl;
	cout << "商品ID：" << ID << endl;
	cout << "商品名称：" << Commodity::all[i].commodityName << endl;
	cout << "商品价格：" << price << endl;
	cout << "商品描述：" << description << endl;
	cout << "***************************************" << endl;
	string x;
	cout << "确认修改？(y/n)"; cin >> x;
	while (true) {
		if (x == "y") {
			string instruction = "UPDATE commodity SET ";
			if (choice == "1") {
				instruction.append("价格 = ").append(price).append(" WHERE 商品ID = ").append(ID);
			}
			else if (choice == "2") {
				instruction.append("描述 = ").append(description).append(" WHERE 商品ID = ").append(ID);
			}
			SQL a;
			a.operate(instruction, 3, me->userID);
			cout << "修改成功！" << endl << endl;
			break;
		}
		else if (x == "n") {
			cout << "取消修改" << endl << endl;
			break;
		}
		else {
			cout << "输入错误，请重新输入" << endl;
			cin >> x;
		}
	}
}

void Seller::off_shelf_commodity() {
	string ID;
	cout << "请输入要下架的商品ID："; cin >> ID;
	int i = find(ID);
	if (i == string::npos) { cout << "未找到此商品" << endl; return; }
	cout << "确认要下架该商品吗?" << endl;
	cout << "*****************************************************\n";
	cout << "商品ID 名称        价格   数量   上架时间    商品状态\n";
	int standard = 0, j = 0;
	standard = 7;
	printf("%s", Commodity::all[i].commodityID.c_str());
	j = standard - len(Commodity::all[i].commodityID);
	for (; j > 0; j--) printf(" ");
	standard = 12;
	printf("%s", Commodity::all[i].commodityName.c_str());
	j = standard - len(Commodity::all[i].commodityName);
	for (; j > 0; j--) printf(" ");
	standard = 7;
	printf("%s", Commodity::all[i].price.c_str());
	j = standard - len(Commodity::all[i].price);
	for (; j > 0; j--) printf(" ");
	standard = 7;
	printf("%s", Commodity::all[i].number.c_str());
	j = standard - len(Commodity::all[i].number);
	for (; j > 0; j--) printf(" ");
	standard = 12;
	printf("%s", Commodity::all[i].addedDate.c_str());
	j = standard - len(Commodity::all[i].addedDate);
	for (; j > 0; j--) printf(" ");
	standard = 10;
	printf("%s", Commodity::all[i].state.c_str());
	j = standard - len(Commodity::all[i].state);
	for (; j > 0; j--) printf(" ");
	printf("\n");
	cout << "*****************************************************\n";
	cout << "请选择(y/n)："; string choice;
	cin >> choice;
	while (true) {
		if (choice == "y") {
			string instruction = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
			instruction.append(ID);
			SQL a;
			a.operate(instruction, 3, ID);
			cout << "修改成功\n\n";
			break;
		}
		else if (choice == "n") {
			cout << "取消下架\n\n";
			break;
		}
		else {
			cout << "输入错误，请重新输入\n";
			cin >> choice;
		}
	}
}
void Seller::history_order() {
	string instruction = "SELECT * FROM order";
	SQL a;
	a.operate(instruction, 3, me->userID);
}

void Buyer::commodity_list() {
	string instruction = "SELECT * FROM commodity";
	SQL a;
	a.operate(instruction, 2, me->userID);
}
int Buyer::buy() {
	string ID; string num; int i;
	cout << "请输入商品ID："; cin >> ID;
	i = find(ID);
	if (i == string::npos) { cout << "未找到该商品" << endl << endl; return 1; }
	else if(Commodity::all[i].sellerID == me->userID) { cout << "不能购买自己的商品！" << endl << endl; return 1; }
	cout << "请输入数量："; cin >> num;
	double x = StringToDouble(num);
	if (x == -1 || num.find('.') != string::npos) { cout << "请输入整数" << endl; return 1; }
	if(x > StringToDouble(Commodity::all[i].number)) { cout << "库存不足！" << endl; return 1; }
	double Buybalance = StringToDouble(me->balance)
		- StringToDouble(Commodity::all[i].price) * x;
	if (Buybalance < 0) {
		cout << "余额不足" << endl;
		return 0;
	}
	string sellID = Commodity::all[i].sellerID;
	int j = find_seller(sellID);
	double Sellbalance = StringToDouble(User::all[j].balance)
		+ StringToDouble(Commodity::all[i].price) * x;
	me->balance = DoubleToString(Buybalance);
	all[j].balance = DoubleToString(Sellbalance);
	preserve();
	SQL a;
	string instruction = "INSERT INTO order VALUES ";
	string VALUES; char v[100];
	string time = GetTime();
	sprintf(v, "(%s,%s,%s,%s,%s,%s,%s)", GetOrderID().c_str(), Commodity::all[i].commodityID.c_str(),
		Commodity::all[i].price.c_str(), num.c_str(), time.c_str(), sellID.c_str(), me->userID.c_str());
	VALUES = v;
	instruction.append(v);
	a.operate(instruction, 2, me->userID);
	double n = StringToDouble(Commodity::all[i].number) - x;
	string number = DoubleToString(n);
	instruction = "UPDATE commodity SET 数量 = ";
	instruction.append(number).append(" WHERE 商品ID = ").append(ID);
	a.operate(instruction, 2, me->userID);

	cout << "*************************" << endl;
	cout << "交易提醒！" << endl;
	cout << "交易时间：" << time << endl;
	cout << "交易单价：" << Commodity::all[i].price << endl;
	cout << "交易数量：" << num << endl;
	cout << "交易状态：交易成功" << endl;
	cout << "您的余额：" << me->balance << endl;
	cout << "*************************" << endl << endl;
	return 1;
}
void Buyer::search() {
	string name;
	cout << "请输入商品名称："; cin >> name;
	string instruction = "SELECT * FROM commodity WHERE 名称 CONTAINS ";
	instruction.append(name);
	SQL a;
	a.operate(instruction, 2, me->userID);
}
void Buyer::history_order() {
	SQL a;
	string instruction = "SELECT * FROM order";
	a.operate(instruction, 2, me->userID);
}
void Buyer::detail() {
	string ID;
	cout << "请输入您想要查看的商品ID："; cin >> ID;
	string instruction = "SELECT * FROM commodity WHERE 商品ID = ";
	instruction.append(ID);
	SQL a;
	a.operate(instruction, 2, me->userID);
}
void Buyer::recharge() {
	string num;
	cout << "请输入充值金额："; cin >> num;										//可能输入错误数字
	if (check_num(num)) {
		bool empty = false;
        FILE* buf = fopen("63..\\Winter_temp\\recharge.txt", "a+");
		assert(buf != NULL && "文件打开失败\n");
		fclose(buf);
        FILE* p = fopen(".\\Winter_temp\\recharge.txt", "r");
		assert(p != NULL && "recharge文件打开失败");
		char f[100];
		fscanf(p, "%s", f);
		if (feof(p)) empty = true;;
		fclose(p);
        FILE* fp = fopen(".\\Winter_temp\\recharge.txt", "a+");
		assert(fp != NULL && "recharge文件打开失败");
		char buffer[100];
		if (empty) fprintf(fp, "充值金额,ID,充值时间\n");
		fprintf(fp, "%s,%s,%s\n", num.c_str(), me->userID.c_str(), GetTime().c_str());
		fclose(fp);
		double now = StringToDouble(me->balance) + StringToDouble(num);
		me->balance = DoubleToString(now);
		preserve();
		cout << "充值成功！当前余额：" << me->balance << endl << endl;
	}
	else {
		cout << "输入数字有误(至多精确至一位小数)" << endl << endl;
	}
}
