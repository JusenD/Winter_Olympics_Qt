#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<iostream>
#include<string.h>
#include<string>
using namespace std;
struct Node {
	char num;
	Node* next;
};

class Stack {
public:
	bool empty() {
		if (head == NULL) return true;
		else return false;
	}
	void push(char x) {

		if (head == NULL) {
			head = new Node;
			head->num = x;
			head->next = NULL;
		}
		else {
			Node* then = new Node;
			if (then == NULL) {
				printf("Stack Overflow!!!!\n");
				exit(-1);
			}
			then->num = x;
			then->next = head;
			head = then;
		}
	}
	void pop(char& x) {
		if (head == NULL) {
			printf("Stack is empty!\n");
			exit(-1);
		}
		x = head->num;
		head = head->next;
	}
	~Stack() {
		while (head != NULL) {
			Node* p = head;
			head = head->next;
			delete p;
		}
	}
private:
	Node* head = NULL;
};

struct Node1 {
	double num;
	Node1* next;
};

class Reg {
public:
	bool empty() {
		if (head == NULL) return true;
		else return false;
	}
	void push(double x) {

		if (head == NULL) {
			head = new Node1;
			head->num = x;
			head->next = NULL;
		}
		else {
			Node1* then = new Node1;
			if (then == NULL) {
				printf("Stack Overflow!!!!\n");
				exit(-1);
			}
			then->num = x;
			then->next = head;
			head = then;
		}
	}
	void pop(double& x) {
		if (head == NULL) {
			printf("Stack is empty!\n");
			exit(-1);
		}
		x = head->num;
		head = head->next;
	}
	~Reg() {
		while (head != NULL) {
			Node1* p = head;
			head = head->next;
			delete p;
		}
	}
private:
	Node1* head = NULL;
};

string calculator(string);

#endif