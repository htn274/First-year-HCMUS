#define _CRT_SECURE_NO_WARNINGS
#include "LinkList.h"
#include <stdio.h>

void main() {
	Dlist l = Dlist{ 0,0 };

	while (true) {
		printf("1 Them pt thu i\n");
		printf("2 Xoa pt thu i\n");
		printf("3 Them head\n");
		printf("4 IN mang\n");

		int c;
		scanf("%d", &c);
		int i, x;
		switch (c) {
		case 1:
			printf("Nhap i = ");
			scanf("%d", &i);
			printf("Nhap x = ");
			scanf("%d", &x);
			InsertI(l, i, x);
			break;
		
		case 2:
			printf("Nhap i = ");
			scanf("%d", &i);
			RemoveI(l, i);
			break;
		case 3:
			printf("Nhap x = ");
			scanf("%d", &x);
			InsertHead(l, x);
			break;
		case 4:
			Dnode * h = l.head;
			printf("List: ");
			while (h) {
				printf("%d, ", h->data);
				h = h->next;
			}
			printf("\n");

			h = l.tail;
			printf("Reverse List: ");
			while (h) {
				printf("%d, ", h->data);
				h = h->prev;
			}
			printf("\n");
			break;
		}

	}

}