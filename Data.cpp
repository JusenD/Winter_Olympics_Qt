#include"Data.h"
#include<cstdio>
#include<cassert>
#include<fstream>

using namespace std;
int len(string str) {
	int i = 0, cnt1 = 0, cnt2 = 0;
	while (str[i] != '\0') {
		if (str[i] < 0) cnt1++;
		else cnt2++;
		i++;
	}
	return (cnt1 / 3) * 2 + cnt2;
}
string substr(string& a, int front, int rear) {
	string result; char p[200]; int i = 0, j = front;
	while (j < a.length() && j <= rear) {
		p[i] = a[j];
		i++; j++;
	}
	p[i] = '\0';
	result.assign(p);
	return result;
}
void assign(string& a, string& b, int front, int rear) {
	char buffer[200];
	int i = 0, j = front;
	while (j <= rear) {
		buffer[i] = b[j];
		i++; j++;
	}
	buffer[i] = '\0';
	a.assign(buffer);
}
vector<Single_Commodity> Commodity::all;
vector<vector<string>> Commodity::Qall;
void Commodity::init() {
	all.clear();
    Qall.clear();
	bool empty = false;
    FILE* buf = fopen(".\\Winter_temp\\commodity.txt", "a+");
	assert(buf != NULL && "文件打开失败\n");
	fclose(buf);
    FILE* p = fopen(".\\Winter_temp\\commodity.txt", "r");
	assert(p != NULL && "user文件打开失败");
	char f[100];
	fscanf(p, "%s", f);
	if (feof(p)) empty = true;;
	fclose(p);
    FILE* fp = fopen(".\\Winter_temp\\commodity.txt", "a+");
	assert(fp != NULL && "文件打开失败\n");
	string line; char tmp[200];
	if (empty) { fprintf(fp, "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态\n"); }
	else {
        ifstream fp1;
        fp1.open(".\\Winter_temp\\commodity.txt", ios::out);
        char buffer[200];
        fp1.getline(buffer, 100);
//		fscanf(fp, "%s\n", tmp);
		int i = 0, m = 0, n = 0;
        while (!fp1.eof()) {
			Single_Commodity a;
            vector<string> b;
            fp1.getline(buffer, 100);
//			fscanf(fp, "%s\n", tmp);
            line.assign(buffer);
            if (line == "") continue;
			m = 0, n = line.find(',');
			a.commodityID = substr(line, m, n - 1);
            b.push_back(a.commodityID);
			m = n, n = line.find(',', n + 1);
			a.commodityName = substr(line, m + 1, n - 1);
            b.push_back(a.commodityName);
			m = n, n = line.find(',', n + 1);
			a.price = substr(line, m + 1, n - 1);
            b.push_back(a.price);
			m = n, n = line.find(',', n + 1);
			a.number = substr(line, m + 1, n - 1);
            b.push_back(a.number);
			m = n, n = line.find(',', n + 1);
			a.description = substr(line, m + 1, n - 1);
            b.push_back(a.description);
			m = n, n = line.find(',', n + 1);
			a.sellerID = substr(line, m + 1, n - 1);
            b.push_back(a.sellerID);
			m = n, n = line.find(',', n + 1);
			a.addedDate = substr(line, m + 1, n - 1);
            b.push_back(a.addedDate);
			m = n, n = line.find(',', n + 1);
			a.state = substr(line, m + 1, line.length() - 1);
            b.push_back(a.state);
            ++i; all.push_back(a); Qall.push_back(b);
		}
        fp1.close();
	}
	fclose(fp);
}
void Commodity::Qinit(){
    Qall.clear();
    for(int i = 0; i < all.size(); i++){
        Single_Commodity *a = &all[i];
        vector<string> b;
        b.push_back(a->commodityID);
        b.push_back(a->commodityName);
        b.push_back(a->price);
        b.push_back(a->number);
        b.push_back(a->description);
        b.push_back(a->sellerID);
        b.push_back(a->addedDate);
        b.push_back(a->state);
        Qall.push_back(b);
    }
}
void Commodity::preserve() {
    FILE* fp = fopen(".\\Winter_temp\\commodity.txt", "w+");
	assert(fp != NULL && "文件打开失败\n");
	fprintf(fp, "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态\n");
	int i = 0;
	while (i < all.size()) {
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", all[i].commodityID.c_str(), all[i].commodityName.c_str(),
			all[i].price.c_str(), all[i].number.c_str(), all[i].description.c_str(), all[i].sellerID.c_str(),
			all[i].addedDate.c_str(), all[i].state.c_str());
		i++;
	}
	fclose(fp);
}
int Commodity::SELECT(int identity) {
	bool ad = false, buyer = false;
	if (identity == 1) {
		ad = true;
		printf("************************************************************\n");
		printf("商品ID 名称        价格   数量   卖家ID 上架时间    商品状态\n");
	}
	else if (identity == 2) {
		buyer = true;
		printf("********************************************\n");
		printf("商品ID 名称        价格   卖家ID 上架时间\n");
	}
	int i = 0, j = 0, standard = 0;

	while (i < all.size()) {
		if (buyer && all[i].state == "已下架") { i++; continue; }
		standard = 7;
		printf("%s", all[i].commodityID.c_str());
		j = standard - len(all[i].commodityID);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", all[i].commodityName.c_str());
		j = standard - len(all[i].commodityName);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].price.c_str());
		j = standard - len(all[i].price);
		for (; j > 0; j--) printf(" ");
		if (!buyer) {
			standard = 7;
			printf("%s", all[i].number.c_str());
			j = standard - len(all[i].number);
			for (; j > 0; j--) printf(" ");
		}
		standard = 7;
		printf("%s", all[i].sellerID.c_str());
		j = standard - len(all[i].sellerID);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", all[i].addedDate.c_str());
		j = standard - len(all[i].addedDate);
		for (; j > 0; j--) printf(" ");
		if (!buyer) {
			standard = 10;
			printf("%s", all[i].state.c_str());
			j = standard - len(all[i].state);
			for (; j > 0; j--) printf(" ");
		}
		printf("\n");
		i++;
	}
	if (ad) printf("************************************************************\n");
	else if (buyer) printf("********************************************\n");
	printf("\n");
	return 1;
}
int Commodity::SELECT_SELLER(string ID) {
	printf("*****************************************************\n");
	printf("商品ID 名称        价格   数量   上架时间    商品状态\n");
	int i = 0, j = 0, standard = 0;
	while (i < all.size()) {
		if (all[i].sellerID != ID) { i++; continue; }
		standard = 7;
		printf("%s", all[i].commodityID.c_str());
		j = standard - len(all[i].commodityID);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", all[i].commodityName.c_str());
		j = standard - len(all[i].commodityName);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].price.c_str());
		j = standard - len(all[i].price);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].number.c_str());
		j = standard - len(all[i].number);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", all[i].addedDate.c_str());
		j = standard - len(all[i].addedDate);
		for (; j > 0; j--) printf(" ");
		standard = 10;
		printf("%s", all[i].state.c_str());
		j = standard - len(all[i].state);
		for (; j > 0; j--) printf(" ");
		printf("\n");
		i++;
	}
	printf("*****************************************************\n");
	printf("\n");
	return 1;
}
int Commodity::SELECT(string WHERE, string CONTAINS, int identity) {
	bool ad = false, buyer = false;
	bool whether = false;
	int i = 0, j = 0, standard = 0; string compare;
	if (identity == 2 && WHERE == "商品ID") {
		while (i < all.size()) {
			compare = all[i].commodityID;
			if (compare.find(CONTAINS) == string::npos) { i++; continue; }
			if (!whether) {
				printf("*************************\n");
			}
			whether = true;
			printf("商品ID：%s\n", compare.c_str());
			printf("商品名称：%s\n", all[i].commodityName.c_str());
			printf("商品价格：%s\n", all[i].price.c_str());
			printf("上架时间：%s\n", all[i].addedDate.c_str());
			printf("商品描述：%s\n", all[i].description.c_str());
			printf("商品卖家：%s\n", all[i].sellerID.c_str());
			break;
		}
		if (whether) { printf("*************************\n\n"); return 1; }
		else {
			printf("**********************************\n");
			printf("没有找到您想要的商品！返回初始界面\n");
			printf("**********************************\n\n");
			return 0;
		}
	}
	else {
		if (identity == 1) ad = true;
		else if (identity == 2) buyer = true;
		while (i < all.size()) {
			if (WHERE == "商品ID") compare = all[i].commodityID;
			else if (WHERE == "名称")compare = all[i].commodityName;
			else if (WHERE == "价格")compare = all[i].price;
			else if (WHERE == "数量")compare = all[i].number;
			else if (WHERE == "卖家ID")compare = all[i].sellerID;
			else if (WHERE == "上架时间")compare = all[i].addedDate;
			else if (WHERE == "商品状态")compare = all[i].state;
			if (compare.find(CONTAINS) == string::npos) { i++; continue; }
			if (buyer && all[i].state == "已下架") { i++; continue; }
			if (ad && !whether) {
				printf("************************************************************\n");
				printf("商品ID 名称        价格   数量   卖家ID 上架时间    商品状态\n");
			}
			else if (buyer && !whether) {
				printf("*******************************************\n");
				printf("商品ID 名称        价格   卖家ID 上架时间\n");
			}
			whether = true;
			standard = 7;
			printf("%s", all[i].commodityID.c_str());
			j = standard - len(all[i].commodityID);
			for (; j > 0; j--) printf(" ");
			standard = 12;
			printf("%s", all[i].commodityName.c_str());
			j = standard - len(all[i].commodityName);
			for (; j > 0; j--) printf(" ");
			standard = 7;
			printf("%s", all[i].price.c_str());
			j = standard - len(all[i].price);
			for (; j > 0; j--) printf(" ");
			if (!buyer) {
				standard = 7;
				printf("%s", all[i].number.c_str());
				j = standard - len(all[i].number);
				for (; j > 0; j--) printf(" ");
			}
			standard = 7;
			printf("%s", all[i].sellerID.c_str());
			j = standard - len(all[i].sellerID);
			for (; j > 0; j--) printf(" ");
			standard = 12;
			printf("%s", all[i].addedDate.c_str());
			j = standard - len(all[i].addedDate);
			for (; j > 0; j--) printf(" ");
			if (!buyer) {
				standard = 10;
				printf("%s", all[i].state.c_str());
				j = standard - len(all[i].state);
				for (; j > 0; j--) printf(" ");
			}
			printf("\n");
			i++;
		}

		if (whether) {
			if (ad) printf("************************************************************\n");
			else if (buyer) printf("*******************************************\n");
			printf("\n");
			return 1;
		}
		else {
			printf("**********************************\n");
			printf("没有找到您想要的商品！返回初始界面\n");
			printf("**********************************\n\n");
			return 0;
		}
	}
}
int Commodity::UPDATE(string SET, string WHERE) {
	string target, value;
	string compare, what;
	int i = WHERE.find('=');
	compare = substr(WHERE, 0, i - 2); what = substr(WHERE, i + 2, WHERE.length() - 1);
	i = 0; int j = 0, standard = 0; string a;
	while (i < all.size()) {
		if (compare == "商品ID") a = all[i].commodityID;
		else if (compare == "名称")a = all[i].commodityName;
		else if (compare == "价格")a = all[i].price;
		else if (compare == "数量")a = all[i].number;
		else if (compare == "卖家ID")a = all[i].sellerID;
		else if (compare == "上架时间")a = all[i].addedDate;
		else if (compare == "商品状态")a = all[i].state;
		if (a != what) { i++; continue; }

		int m = 0, n = SET.find('=');
		while (n != string::npos) {
			target = substr(SET, m, n - 2);
			m = SET.find(',', n + 1);
			if (m != string::npos)value = substr(SET, n + 2, m - 1);
			else value = substr(SET, n + 2, SET.length() - 1);
			if (target == "商品ID") all[i].commodityID = value;
			else if (target == "名称") all[i].commodityName = value;
			else if (target == "价格") all[i].price = value;
			else if (target == "数量") {
				all[i].number = value;
				if (value == "0") all[i].state = "已下架";
			}
			else if (target == "卖家ID") all[i].sellerID = value;
			else if (target == "上架时间") all[i].addedDate = value;
			else if (target == "商品状态") all[i].state = value;
			else if (target == "描述") all[i].description = value;
			n = SET.find('=', n + 1);
			m += 2;
		}
		i++;
	}
	preserve();
	return 1;
}
int Commodity::INSERT(string VALUES) {
    FILE* fp = fopen(".\\Winter_temp\\commodity.txt", "a+");
	assert(fp != NULL && "文件打开失败\n");
	string line = substr(VALUES, 1, VALUES.length() - 2);
	fprintf(fp, "%s\n", line.c_str());
	fclose(fp);
	int m = 0, n = line.find(',');
	Single_Commodity a;
	a.commodityID = substr(line, m, n - 1);
	m = n, n = line.find(',', n + 1);
	a.commodityName = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.price = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.number = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.description = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.sellerID = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.addedDate = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.state = substr(line, m + 1, line.length() - 1);
	all.push_back(a);
	return 1;
}

vector<Single_Order> Order::all;
vector<vector<string>> Order::Qall;
void Order::init() {
	all.clear();
	bool empty = false;
    FILE* buf = fopen(".\\Winter_temp\\order.txt", "a+");
	assert(buf != NULL && "文件打开失败\n");
	fclose(buf);
    FILE* p = fopen(".\\Winter_temp\\order.txt", "r");
	assert(p != NULL && "user文件打开失败");
	char f[100];
	fscanf(p, "%s", f);
	if (feof(p)) empty = true;;
	fclose(p);
    FILE* fp = fopen(".\\Winter_temp\\order.txt", "a+");
	assert(fp != NULL && "文件打开失败\n");
	if (empty) { fprintf(fp, "订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID\n"); }
	else {
		string line; char tmp[200];
		fscanf(fp, "%s\n", tmp);
		int i = 0, m = 0, n = 0;
		while (!feof(fp)) {
			Single_Order a;
			fscanf(fp, "%s\n", tmp); line.assign(tmp);
			m = 0, n = line.find(',');
			a.orderID = substr(line, m, n - 1);
			m = n, n = line.find(',', n + 1);
			a.commodityID = substr(line, m + 1, n - 1);
			m = n, n = line.find(',', n + 1);
			a.unitPrice = substr(line, m + 1, n - 1);
			m = n, n = line.find(',', n + 1);
			a.number = substr(line, m + 1, n - 1);
			m = n, n = line.find(',', n + 1);
			a.date = substr(line, m + 1, n - 1);
			m = n, n = line.find(',', n + 1);
			a.seller = substr(line, m + 1, n - 1);
			m = n, n = line.find(',', n + 1);
			a.buyerID = substr(line, m + 1, line.length() - 1);
			++i; all.push_back(a);
		}
	}
	fclose(fp);
    Qinit();
}
void Order::Qinit(){
    Qall.clear();
    for(int i = 0; i < all.size(); i++){
        Single_Order *a = &all[i];
        vector<string> b;
        b.push_back(a->orderID);
        b.push_back(a->commodityID);
        b.push_back(a->unitPrice);
        b.push_back(a->number);
        b.push_back(a->date);
        b.push_back(a->seller);
        b.push_back(a->buyerID);
        Qall.push_back(b);
    }
}
void Order::preserve() {
    FILE* fp = fopen(".\\Winter_temp\\order.txt", "w+");
	assert(fp != NULL && "文件打开失败\n");
	fprintf(fp, "商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态\n");
	int i = 0;
	while (i < all.size()) {
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", all[i].orderID.c_str(), all[i].commodityID.c_str(),
			all[i].unitPrice.c_str(), all[i].number.c_str(), all[i].date.c_str(), all[i].seller.c_str(),
			all[i].buyerID.c_str());
		i++;
	}
	fclose(fp);
}
int Order::SELECT_AD() {
	//		T001   M001   10.0     10     2022-02-15  U001   U002
	printf("*******************************************************\n");
	printf("订单ID 商品ID 交易单价 数量   交易时间    卖家ID 买家ID\n");
	int i = 0, j = 0, standard = 0;
	while (i < all.size()) {
		standard = 7;
		printf("%s", all[i].orderID.c_str());
		j = standard - len(all[i].orderID);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].commodityID.c_str());
		j = standard - len(all[i].commodityID);
		for (; j > 0; j--) printf(" ");
		standard = 9;
		printf("%s", all[i].unitPrice.c_str());
		j = standard - len(all[i].unitPrice);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].number.c_str());
		j = standard - len(all[i].number);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", all[i].date.c_str());
		j = standard - len(all[i].date);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].seller.c_str());
		j = standard - len(all[i].seller);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].buyerID.c_str());
		j = standard - len(all[i].buyerID);
		for (; j > 0; j--) printf(" ");
		printf("\n");
		i++;
	}
	printf("*******************************************************\n");
	printf("\n");
	return 1;
}
int Order::SELECT_SELLER(string ID) {
	printf("************************************************\n");
	printf("订单ID 商品ID 交易单价 数量   交易时间    卖家ID\n");
	int i = 0, j = 0, standard = 0;
	while (i < all.size()) {
		if (all[i].seller != ID) { i++; continue; }
		standard = 7;
		printf("%s", all[i].orderID.c_str());
		j = standard - len(all[i].orderID);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].commodityID.c_str());
		j = standard - len(all[i].commodityID);
		for (; j > 0; j--) printf(" ");
		standard = 9;
		printf("%s", all[i].unitPrice.c_str());
		j = standard - len(all[i].unitPrice);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].number.c_str());
		j = standard - len(all[i].number);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", all[i].date.c_str());
		j = standard - len(all[i].date);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].seller.c_str());
		j = standard - len(all[i].seller);
		for (; j > 0; j--) printf(" ");
		printf("\n");
		i++;
	}
	printf("************************************************\n");
	printf("\n");
	return 1;
}
int Order::SELECT_BUYER(string ID) {
	printf("************************************************\n");
	printf("订单ID 商品ID 交易单价 数量   交易时间    卖家ID\n");
	int i = 0, j = 0, standard = 0;
	while (i < all.size()) {
		if (all[i].buyerID != ID) { i++; continue; }
		standard = 7;
		printf("%s", all[i].orderID.c_str());
		j = standard - len(all[i].orderID);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].commodityID.c_str());
		j = standard - len(all[i].commodityID);
		for (; j > 0; j--) printf(" ");
		standard = 9;
		printf("%s", all[i].unitPrice.c_str());
		j = standard - len(all[i].unitPrice);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].number.c_str());
		j = standard - len(all[i].number);
		for (; j > 0; j--) printf(" ");
		standard = 12;
		printf("%s", all[i].date.c_str());
		j = standard - len(all[i].date);
		for (; j > 0; j--) printf(" ");
		standard = 7;
		printf("%s", all[i].seller.c_str());
		j = standard - len(all[i].seller);
		for (; j > 0; j--) printf(" ");
		printf("\n");
		i++;
	}
	printf("************************************************\n");
	printf("\n");
	return 1;
}
int Order::INSERT(string VALUES) {
    FILE* fp = fopen(".\\Winter_temp\\order.txt", "a+");
	assert(fp != NULL && "文件打开失败\n");
	string line = substr(VALUES, 1, VALUES.length() - 2);
	fprintf(fp, "%s\n", line.c_str());
	fclose(fp);
	int m = 0, n = line.find(',');
	Single_Order a;
	a.orderID = substr(line, m, n - 1);
	m = n, n = line.find(',', n + 1);
	a.commodityID = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.unitPrice = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.number = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.date = substr(line, m + 1, n - 1);
	m = n, n = line.find(',', n + 1);
	a.seller = substr(line, m + 1, n - 1);
	m = n;
	a.buyerID = substr(line, m + 1, line.length() - 1);
	all.push_back(a);
	return 1;
}
