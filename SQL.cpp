#include"SQL.h"
#include <iostream>
#include<time.h>

extern int len(string str);
extern string substr(string& a, int front, int rear);
extern void assign(string& a, string& b, int front, int rear);
string GetSystemTime()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	char a[30];
	sprintf(a, "%d-%d-%d %d:%d:%d: ", 1900 + ltm->tm_year, 1 + ltm->tm_mon,
		ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	string t = a;
	return t;
}
int SQL::read(string instruction, int identity, string ID) {

	string function, name;
	int i = 0, j = instruction.find(' ');
	function = substr(instruction, i, j - 1);
	if (function == "SELECT") {												//处理SELECT
		string new_ins = substr(instruction, 14, instruction.length() - 1);
		i = 0, j = new_ins.find(' ');
		if (j == string::npos) {
			name = substr(new_ins, 0, new_ins.length() - 1);
			if (name == "commodity") {
				Commodity c;
				if (identity != 3 && c.SELECT(identity)) return 1;
				else if (c.SELECT_SELLER(ID)) return 1;
				else return 0;
			}
			else if (name == "order") {
				Order o;
				if (identity == 1 && o.SELECT_AD()) return 1;
				else if (identity == 2 && o.SELECT_BUYER(ID)) return 1;
				else if (identity == 3 && o.SELECT_SELLER(ID)) return 1;
				return 0;
			}
			else if (name == "user") {
				User u;
				if (u.SELECT()) return 1;
				return 0;
			}
			return 0;
		}
		name = substr(new_ins, 0, j - 1);
		string WHERE, CONTAINS;
		j = new_ins.find(' ', j + 1); i = j, j = new_ins.find(' ', j + 1);
		WHERE = substr(new_ins, i + 1, j - 1);
		j = new_ins.find(' ', j + 1);
		CONTAINS = substr(new_ins, j + 1, new_ins.length() - 1);
		if (name == "commodity") {
			Commodity c;
			if (c.SELECT(WHERE, CONTAINS, identity)) return 1;
			else return 0;
		}
		else { cerr << "SELECT还有这种情况？\n"; exit(-1); }
	}
	else if (function == "UPDATE") {						//处理UPDATE
		string new_ins = substr(instruction, 7, instruction.length() - 1);
		i = 0, j = new_ins.find(' ');
		name = substr(new_ins, 0, j - 1);
		j = new_ins.find(' ', j + 1); i = j, j = new_ins.find("WHERE", j + 1);
		string SET = substr(new_ins, i + 1, j - 2);
		i = j + 6;
		string WHERE = substr(new_ins, i, new_ins.length() - 1);
		if (name == "commodity") {
			Commodity c;
			if (c.UPDATE(SET, WHERE)) return 1;
			else return 0;
		}
		else if (name == "user") {
			User u;
			if (u.UPDATE(SET, WHERE)) return 1;
			else return 0;
		}
		else { cerr << "UPDATE还有这种情况？\n"; exit(-1); }
	}
	else if (function == "INSERT") {
		string new_ins = substr(instruction, 12, instruction.length() - 1);
		i = 0, j = new_ins.find(' ');
		name = substr(new_ins, 0, j - 1);
		i = new_ins.find(' ', j + 1);
		string VALUES = substr(new_ins, i + 1, new_ins.length() - 1);
		if (name == "commodity") {
			Commodity c;
			if (c.INSERT(VALUES)) return 1;
			else return 0;
		}
		else if (name == "order") {
			Order o;
			if (o.INSERT(VALUES)) return 1;
			else return 0;
		}
		else { cerr << "INSERT还有这种情况？\n"; exit(-1); }
	}
	else { cerr << "指令还有这种情况？\n"; exit(-1); }
}
void SQL::operate(string instruction, int identity, string ID) {
	if (read(instruction, identity, ID)) {
        FILE* fp = fopen(".\\Winter_temp\\commands.txt", "a+");
		assert(fp != NULL && "commands.txt文件打开失败\n");
		string line = GetSystemTime();
		line.append(instruction);
		fprintf(fp, "%s\n", line.c_str());
		fclose(fp);
	}
}
