#include "queueDA.h"
#include <malloc.h>
#include <stdio.h>

void Init(Queue & q, int initSize)
{
	q.size = initSize;
	q.data = (int*)malloc(q.size * sizeof(int));
	q.in = 0;
	q.out = 0;
}

bool IsEmpty(Queue q)
{
	return (q.in == q.out);
}

bool IsFull(Queue q)
{
	int full = q.out - 1;
	if (full < 0) full = q.size - 1;
	return q.in == full;
}

void Enlarge(Queue &q, int sizeNew) {
	q.data = (int*)realloc(q.data, sizeNew * sizeof(int));
	if (q.in < q.out){
		int i = 0, n = q.size;
		while (i < q.in) {
			q.data[n++] = q.data[i++];
			if (n == sizeNew) n = 0;
		}
		q.in = n;
	}
	q.size = sizeNew;
}

void QueuePush(Queue & q, int x)
{
	if (IsFull(q)) Enlarge(q, q.size * 2);
	q.data[q.in++] = x;
	if (q.in == q.size) q.in = 0;
}

int QueuePop(Queue & q, bool & flag)
{
	flag = IsEmpty(q);
	if (flag) return 0;
	int x = q.data[q.out++];
	if (q.out == q.size) q.out = 0;
	return x;
}

int QueuePeek(Queue q, bool & flag)
{
	flag = IsEmpty(q);
	if (flag) return 0;
	return q.data[q.out];
}

void Release(Queue & q)
{
	free(q.data);
	q.in = q.out = 0;
	q.size = 0;
}
