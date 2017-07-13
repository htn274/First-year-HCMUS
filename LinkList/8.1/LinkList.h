#pragma once
struct Dnode {
	int data;
	Dnode *next, *prev;
};

struct Dlist {
	Dnode *head, *tail;
};

void Init(Dlist &l);
bool isEmpty(Dlist l);
Dnode *FindI(Dlist l, int i);
Dnode *FindX(Dlist l, int x);
Dnode *FindTail(Dlist l);
void InsertHead(Dlist &l, int x);
void InsertTail(Dlist &l, int x);
void InsertI(Dlist &l, int i, int x);
void RemoveHead(Dlist &l);
void RemoveTail(Dlist &l);
void RemoveI(Dlist &l, int i);
void RemoveAll(Dlist &l);



