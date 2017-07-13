#pragma once
struct Node {
	int data;
	Node *next;
};

struct Queue {
	Node *head, *tail;
};

void init(Queue &q);
bool isEmpty(Queue q);
bool isFull(Queue q);
void push(Queue &q, int x);
int pop(Queue &q, bool &flag);
int peek(Queue q, bool &flag);