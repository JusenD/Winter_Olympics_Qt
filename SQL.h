#ifndef SQL_H
#define SQL_H

#include"Data.h"
#include"User.h"
class SQL {
public:
	void operate(string instruction, int identity, string ID);
	int read(string instruction, int identity, string ID);
};

#endif