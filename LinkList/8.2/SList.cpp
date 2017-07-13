#include "SList.h"
#include <malloc.h>
#include <stdio.h>

int countNode(SNode * head)
{
	int c = 0;
	while (head) {
		c++;
		head = head->next;
	}
	return c;
}

void ReverseList(SNode *&head)
{
	SNode *newHead, *next, *h;
	newHead = NULL;
	h = head;
	while (h) {
		next = h->next;
		h->next = newHead;
		newHead = h;
		h = next;
	}
	head = newHead;
}

void InsertHead(SNode *&head, int x) {
	SNode *newHead = new SNode;
	newHead->data = x;
	newHead->next = head;
	head = newHead;
}

void printList(SNode * head)
{
	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

SNode *FindI(SNode *head, int i){
	while (i > 0 && head!=NULL) {
		i--;
		head = head->next;
	}
	return head;
}

void InsertX(SNode *&head, int x) {
	if (head == NULL) {
		InsertHead(head, x);
		return;
	}

	SNode *nodeX = head, *prevNode = NULL;
	while (nodeX != NULL && nodeX ->data <=x){
		prevNode = nodeX;
		nodeX = nodeX->next;
	}

	if (nodeX == head) {
		InsertHead(head, x);
		return;
	}

	SNode *newNode = new SNode;
	newNode->data = x;
	newNode->next = nodeX;

	prevNode->next = newNode;
}
