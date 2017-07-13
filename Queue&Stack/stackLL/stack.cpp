#include "stack.h"
#include <malloc.h>
#include <stdio.h>

void init(Node *& top)
{
	top = NULL;
}

bool isEmpty(Node * top)
{
	return top == NULL;
}

bool isFull(Node * top)
{
	return false;
}

void push(Node *& top, int x)
{
	Node *newtop = new Node;
	newtop->data = x;
	newtop->next = top;
	top = newtop;
}

int pop(Node *& top, bool &flag)
{
	flag = isEmpty(top);
	if (flag) return 0;
	int x = top->data;
	
	Node *p = top->next;
	delete top;
	top = p;
	return x;
}

int peek(Node *& top, bool &flag)
{
	flag = isEmpty(top);
	if (flag) return 0;
	return top->data;
}
