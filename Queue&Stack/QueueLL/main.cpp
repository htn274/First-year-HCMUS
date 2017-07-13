#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "queue.h"

void main() {
	Queue q;
	int n, c;
	q.head = q.tail = new Node;
	while (1) {
		printf("1. Khoi tao hang doi\n2. Them phan tu\n3. Lay phan tu ra khoi hang doi\n4. Cho biet gia tri hang doi\n");
		scanf("%d", &c);
		switch (c) {
		case 1: {
			init(q);
			break;
		}
		case 2: {
			int x;
			printf("Nhap gia tri: ");  scanf("%d", &x);
			push(q, x);
			break;
		}
		case 3: {
			int x; bool flag = false;
			x = pop(q, flag);
			if (flag) printf("Hang doi rong\n");
			else 
				printf("Gia tri dau cua hang doi: %d\n", x);
			break;
		}
		case 4: {
			int x; bool flag = false;
			x = peek(q, flag);
			if (flag) printf("Hang doi rong\n");
				printf("Gia tri dau cua hang doi: %d\n", x);
			break;
		}
		}
	}
}