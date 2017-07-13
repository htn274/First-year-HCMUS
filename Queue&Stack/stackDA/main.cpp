#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "stack.h"

void main() {
	stack s;
	int n, c;
	while (1) {
		printf("1. Khoi tao stack\n2. Them phan tu\n3. Lay phan tu ra khoi stack\n4. Cho biet gia tri top\n5. Huy stack");
		scanf("%d", &c);
		switch(c) {
		case 1: {
			printf("Nhap vao gioi han stack: "); scanf("%d", &n);
			innit(s, n);
			break;
		}
		case 2: {
			int x;
			printf("Nhap gia tri: ");  scanf("%d", &x);
			if (isFull(s)) printf("Stack day!"); else 
			push(s, x);
			break;
		}
		case 3: {
			int x; bool flag = false;
			x = pop(s, flag);
			if (flag == false)
				printf("Gia tri top = %d\n", x);
			else printf("Stack rong\n");
			break;
		}
		case 4: {
			int x; bool flag = false;
			x =peek(s, flag);
			if (flag == false)
				printf("Gia tri top = %d\n", x);
			else printf("Stack rong\n");
			break;
		}
		case 5: {
			release(s);
			break;
		}
		}
	}
}