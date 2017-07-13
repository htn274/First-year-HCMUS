#pragma once
struct SNode {
	int data;
	SNode *next;
};
int countNode(SNode *head);
void ReverseList(SNode *&head);
void InsertHead(SNode *&head, int x);
void InsertX(SNode *&head, int x);
void printList(SNode *head);