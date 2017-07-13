#pragma once
struct stack {
	int top;
	int size;
	int *a;
};

void innit(stack &s, int sizeStack);
bool isEmpty(stack s);
bool isFull(stack s);
void push(stack &s, int x);
int pop(stack &s, bool &flag);
int peek(stack s, bool &flag);
void release(stack &s);