#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include<iostream>
#include<string.h>
using namespace std;

class Administrator {
public:
	void check_commodity();
	void search();
	void off_shelf();
	void check_order();
	void check_user();
	void ban_user();
	void operate();
	void log_in();
};

#endif