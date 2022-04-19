#ifndef USER_H
#define USER_H
#include<string>
#include<vector>
#include<cassert>
#include"Data.h"
using namespace std;
struct Single_User {
	string userID;
	string username;
	string password;
	string phoneNumber;
	string adress;
	string balance;
	string userState;
};
class User {
public:
	static vector<Single_User> all;
    static vector<vector<string>> Qall;
	static void init();
    static void Qinit();
    static void preserve();
	void log_in();
	void operate(Single_User*);
	void regist();
	void information(Single_User* me);
	int UPDATE(string SET, string WHERE);
	int SELECT();
};
class Seller :public User {
	Single_User* me;
public:
	Seller(Single_User* a) {
		me = a;
	}
	void new_commodity();
	void existing_commodity();
	void change_commodity();
	void off_shelf_commodity();
	void history_order();
};
class Buyer :public User {
	Single_User* me;
public:
	Buyer(Single_User* a) {
		me = a;
	}
	void commodity_list();
	void recharge();
	int buy();
	void search();
	void history_order();
	void detail();
};

#endif
