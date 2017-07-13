#pragma once
struct Queue {
	int size;
	int in, out;
	int *data;
};

void Init(Queue &q, int initSize);
bool IsEmpty(Queue q);
bool IsFull(Queue q);
void QueuePush(Queue &q, int x);
int QueuePop(Queue &q, bool &flag);
int QueuePeek(Queue q, bool &flag);
void Release(Queue &q);
