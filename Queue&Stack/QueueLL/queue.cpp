#include "queue.h"
#include <malloc.h>
#include <stdio.h>

void init(Queue & q)
{
	q.head = NULL;
	q.tail = NULL;
}

bool isEmpty(Queue q)
{
	return (q.head == NULL);
}

bool isFull(Queue q)
{
	return false;
}

void push(Queue & q, int x)
{
	Node *newNode = new Node;
	newNode->data = x;
	newNode->next = NULL;
	if (isEmpty(q)) {
		q.head = q.tail = newNode;
	}
	else {
		q.tail->next = newNode;
		q.tail = newNode;
	}
}

int pop(Queue & q, bool &flag)
{
	flag = isEmpty(q);
	if (flag) return 0;
	int x = q.head->data;
	
	Node *p = q.head->next;
	delete q.head;
	q.head = p;
	
	return x;
}

int peek(Queue q, bool &flag)
{
	flag = isEmpty(q);
	if (flag) return 0;
	int x = q.head->data;
	return x;
}
