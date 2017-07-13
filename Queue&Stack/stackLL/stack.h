#pragma once
struct Node {
	int data;
	Node *next;
};

void init(Node *&top);
bool isEmpty(Node *top);
bool isFull(Node *top);
void push(Node *&top, int x);
int pop(Node *&top, bool &flag);
int peek(Node *&top, bool &flag);