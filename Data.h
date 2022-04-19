#ifndef DATA_H
#define DATA_H
#include<string>
#include<vector>
using namespace std;
struct Single_Commodity {
	string commodityID;
	string commodityName;
	string price;
	string number;
	string description;
	string sellerID;
	string addedDate;
	string state;
};
struct Single_Order {
	string orderID;
	string commodityID;
	string unitPrice;
	string number;
	string date;
	string buyerID;
	string seller;
};
class Commodity {
public:
	static vector<Single_Commodity> all;
    static vector<vector<string>> Qall;
	static void init();
    static void Qinit();
    static void preserve();
	int UPDATE(string SET, string WHERE);
	int SELECT(int identity);
	int SELECT_SELLER(string me);
	int SELECT(string WHERE, string CONTAINS, int identity);
	int INSERT(string VALUES);
};
class Order {
public:
	static vector<Single_Order> all;
    static vector<vector<string>> Qall;
	static void init();
    static void Qinit();
    static void preserve();
	int SELECT_AD();
	int SELECT_BUYER(string ID);
	int SELECT_SELLER(string ID);
	int INSERT(string VALUES);
};

#endif





