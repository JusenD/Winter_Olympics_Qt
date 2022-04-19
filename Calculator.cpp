#include"calculator.h"
#include<math.h>
using namespace std;

extern string DoubleToString(double);

int delete_space(char[]);

int check_brackets(char[]);

double cal(char[]);

int transform(const char[], char[]);

double num(char*&);

string calculator(string expression) {
	if (expression == "") { cout << "输入空白"; return ""; }
	char a[200];
	strcpy(a, expression.c_str());
	if(check_brackets(a) == -1) return "";
	char b[300];													//将输入转化后存在b[300]中
	if(transform(a, b) == -1) return "";
	if(b[0] == '\0') { cout << "输入空白"; return ""; }
	//	cout << b << endl;
	double x = cal(b);
    if (x == __DBL_HAS_INFINITY__) return "";
	double result = 0;
	result = round(x * 10) / 10;
	//	cout << result << endl;
	string true_result = DoubleToString(result);
	return true_result;
}

int delete_space(char a[]) {										//删除输入中的空格并检查连续数字
	int i = 0, j = 0;
	for (i = 0; i < strlen(a); ++i) {
		if (a[i] == ' ') {
			if (i != 0) {
				int j = i - 1;
				if (a[j] >= '0' && a[j] <= '9') {
					j += 2;
					while (a[j] == ' ') ++j;
					if (a[j] >= '0' && a[j] <= '9') { cerr << "连用两个数字" ; return -1; }
				}												    //检查是否连续出现两个数字
			}
			for (j = i; j < strlen(a); ++j)a[j] = a[j + 1];
		}
	}
}

int if_cal(char x) {												//判断是否为操作符同时发现非法字符
	if (x == '+' || x == '-' || x == '*' || x == '/') return 1;
	else if ((x >= '0' && x <= '9') || x == '(' || x == ')' || x == '.') return 0;
	else cerr << "输入错误";
	return -1;
}

int check_brackets(char a[]) {
	if(delete_space(a) == -1) return -1;
	int i = 0;
	int first = 0, last = 0;
	for (i = 0; a[i] != '\0'; ++i) {
		int cal = if_cal(a[i]);
		if (a[i] == '(') {
			if (i != strlen(a) - 1 && a[i + 1] != ')') first++;		//搜索左括号个数
			else { cerr << "圆括号不匹配" ; return -1; }		//避免出现 ()
		}
		else if (a[i] == ')') {
			if (i != strlen(a) - 1 && a[i + 1] == '(') { cerr << "圆括号不匹配" ; return -1; }
			last++;
		}															//搜索右括号个数
		else if (cal) {
			if (cal == -1) return -1;
			if ((i == 0 && (a[i] == '*' || a[i] == '/')) || (a[i - 1] == '(' && (a[i] == '*' || a[i] == '/')) || i == strlen(a) - 1 || a[i + 1] == ')' || if_cal(a[i + 1]))
			{
				cerr << "操作符误用" ; return -1;				//首尾出现/*或操作符与括号的搭配错误
			}
		}
		else if (a[i] >= '0' && a[i] <= '9') {
			if (i != 0 && a[i - 1] == ')') { cerr << "缺少操作符" ; return -1; }
			else if (i != strlen(a) - 1 && a[i + 1] == '(') { cerr << "缺少操作符" ; return -1; }
		}															//括号使用错误
		else if (a[i] == '.') {
			if (i == 0 || i == strlen(a) - 1 || a[i - 1] < '0' || a[i - 1] > '9' || a[i + 1] < '0' || a[i + 1] > '9')
			{
				cerr << "小数点错误" ; return -1;
			}
			int j = i + 1;
			while (a[j] >= '0' && a[j] <= '9') ++j;
			if (j != strlen(a) && a[j] == '.') { cerr << "小数点错误" ; return -1; }
		}															//检查小数点
		if (first < last) { cerr << "圆括号不匹配" ; return -1; }
	}																//左括号数不能少于右括号
	if (first != last) { cerr << "圆括号不匹配" ; return -1; }
	return 1;
}																	//最终左右括号相等

int transform(const char c[], char b[]) {
	Stack x;
	char a[200];
	strcpy_s(a, c);													//将c复制到a进行负数处理并检查+1
	int i = 0, j = 0;
	for (i = 0; i < strlen(a); ++i) {
		int j = 0;
		if (i != 0 && a[i - 1] == '(' && (a[i] == '-' || a[i] == '+')) {
			if (a[i] == '+') { cerr << "操作符误用" ; return -1; }
			for (j = strlen(a) + 1; j > i; --j) a[j] = a[j - 1];
			a[i] = '0';
		}
		if (i == 0 && (a[i] == '+' || a[i] == '-')) {
			if (a[i] == '+') { cerr << "操作符误用" ; return -1; }
			for (j = strlen(a) + 1; j > i; --j) a[j] = a[j - 1];
			a[i] = '0';
		}
	}																//在负数或正数前添0形成合法表达式
	for (i = 0; i <= strlen(a); ++i) {
		if (i == strlen(a)) {
			while (!x.empty()) {
				char m;
				x.pop(m);
				b[j] = m; ++j;
			}
			b[j] = '\0';
			break;													//在表达式末尾处将栈内元素全部弹出
		}
		int whether = 0;
		while ((a[i] >= '0' && a[i] <= '9') || a[i] == '.') {
			whether = 1;
			b[j] = a[i]; ++j;
			++i;
		}															//数字直接输出
		if (whether) {
			--i;
			b[j] = ' '; ++j;
			continue;
		}
		if (a[i] == '(') x.push(a[i]);
		else {
			if (x.empty()) { x.push(a[i]); continue; }				//空栈直接压入操作符
			char m;
			x.pop(m);
			if (m == '(') { x.push(m); x.push(a[i]); continue; }	//栈顶元素为'('则压入操作符
			if (a[i] == '+' || a[i] == '-') {
				while (m != '(') {
					b[j] = m; ++j;
					if (!x.empty()) x.pop(m); else break;			//压入+-号 并弹出所有左括号前的(如果有)操作符
				}
				if (m == '(') x.push(m);
				x.push(a[i]);
			}
			else if (a[i] == '*' || a[i] == '/') {
				while (m == '*' || m == '/') {						//压入*/号 弹出所有左括号前的(如果有)*/号
					b[j] = m; ++j;
					if (!x.empty()) x.pop(m); else break;
				}
				if (m == '+' || m == '-' || m == '(') x.push(m);
				x.push(a[i]);
			}
			else if (a[i] == ')') {
				while (m != '(') {									//遇到右括号时弹出左括号前所有操作符
					b[j] = m; ++j;
					x.pop(m);
				}
			}
		}
	}
	return 1;
}

double num(char*& p) {												//将字符数转化为double
	double n1 = 0, n2 = 1;
	while (*p >= '0' && *p <= '9') {
		n1 = n1 * 10 + (double)(*p - '0');
		++p;
	}
	if (*p == '.') {
		p++;
		while (*p >= '0' && *p <= '9') {
			n2 /= 10;
			n1 += (n2 * (double)(*p - '0'));
			++p;
		}
	}
	--p;
	return n1;
}

double cal(char b[]) {												//计算操作 并检查除数为0错误
	Reg op;
	char* p = b;
	while (*p != '\0') {
		if (*p >= '0' && *p <= '9') {
			double n = num(p);
			op.push(n);
		}
		else {
			double m, n;
			switch (*p) {
			case '+':
				op.pop(m); op.pop(n); op.push(m + n);
				break;
			case '-':
				op.pop(m); op.pop(n); op.push(n - m);
				break;
			case '*':
				op.pop(m); op.pop(n); op.push(m * n);
				break;
			case '/':
				op.pop(m); op.pop(n);
				if (m == 0) { cerr << "除数为零"; return INFINITY; }
				op.push(n / m);
				break;
			}
		}
		++p;
	}
	double result;
	op.pop(result);
	return result;
}
