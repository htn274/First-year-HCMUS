#include "stack.h"
#include <malloc.h>

void innit(stack & s, int sizeStack)
{
	s.size = sizeStack;
	s.top = 0;
	s.a = (int*)malloc(sizeof(int)*s.size);
}

bool isEmpty(stack s)
{
	return (s.top ==0);
}

bool isFull(stack s)
{
	return (s.top >= s.size - 1);
}

void push(stack & s, int x)
{
	if (isFull(s)) {
		s.size = s.size * 2;
		s.a = (int*)realloc(s.a, (s.size) * sizeof(int));
	}
	s.a[s.top] = x;
	s.top++;
}

int pop(stack & s, bool &flag)
{
	flag = isEmpty(s);
	if (flag) return 0;
	return s.a[--s.top];
}

int peek(stack s, bool &flag)
{
	flag = isEmpty(s);
	if (flag) return 0;
	return s.a[s.top - 1];
}

void release(stack & s)
{
	free(s.a);
	s.size = 0;
	s.top = 0;
}

