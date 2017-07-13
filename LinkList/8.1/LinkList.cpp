#include "LinkList.h"
#include <malloc.h>

void Init(Dlist & l)
{
	l.head = NULL;
	l.tail = NULL;
}

bool isEmpty(Dlist l)
{
	return (l.head == NULL);
}

Dnode *FindI(Dlist l, int i)
{
	Dnode *h = l.head;
	while (i > 0 && h!=NULL) {
		h = h->next;
		i--;
	}
	return h;
}

Dnode *FindX(Dlist l, int x)
{
	Dnode *h = l.head;
	while (h->data != x && h->next != NULL) {
		h = h->next;
		if (h->data == x) return h;
	}
	return h;
}

Dnode *FindTail(Dlist l)
{
	return l.tail;
}

void InsertHead(Dlist & l, int x)
{
	Dnode *nHead = new Dnode;
	nHead->data = x;
	nHead->next = l.head;
	nHead->prev = NULL;
	if (l.head == NULL) { l.tail = nHead; }
	else l.head->prev = nHead;
	l.head = nHead;
}

void InsertTail(Dlist & l, int x)
{
	if (isEmpty(l)) {
		InsertHead(l, x);
		return;
	}
	Dnode *nTail = new Dnode;
	nTail->data = x;
	nTail->next = NULL;
	nTail->prev = l.tail;
	l.tail->next = nTail;
	l.tail = nTail;
}

void InsertI(Dlist & l, int i, int x)
{
	Dnode *nodeI = FindI(l, i);
	if (nodeI == NULL) return;

	if (nodeI == l.tail) {
		InsertTail(l, x);
		return;
	}
	Dnode *newNode = new Dnode;
	newNode->data = x;
	newNode->prev = nodeI;
	newNode->next = nodeI->next;

	nodeI->next->prev = newNode;
	nodeI->next = newNode;
}

void RemoveHead(Dlist & l)
{
	Dnode * head = l.head;
	if (head == NULL) return;
	
	if (head != l.tail)
		head->next->prev = NULL;
	else
		l.tail = NULL;

	l.head = head->next;
	delete head;
}

void RemoveTail(Dlist & l)
{
	Dnode * tail = l.tail;
	if (isEmpty(l)) return;

	if (tail != l.head)
		tail->prev->next = NULL;
	else l.head = NULL;

	l.tail = tail->prev;
	delete tail;
}

void RemoveI(Dlist & l, int i)
{
	Dnode *nodeI = FindI(l, i);
	if (nodeI == NULL) return;
	if (nodeI == l.head) {
		RemoveHead(l);
		return;
	}

	if (nodeI == l.tail) {
		RemoveTail(l);
		return;
	}

	nodeI->prev->next = nodeI->next;
	nodeI->next->prev = nodeI->prev;
	delete nodeI;
}

void RemoveAll(Dlist & l)
{
	while (isEmpty(l))
	{
		RemoveHead(l);
	}
}
