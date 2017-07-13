#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "stack.h"

void main() {
	Node* top;
	int n, c;
	top = new Node;
	while (1) {
		printf("1. Khoi tao stack\n2. Them phan tu\n3. Lay phan tu ra khoi stack\n4. Cho biet gia tri top\n");
		scanf("%d", &c);
		switch (c) {
		case 1: {
			init(top);
			break;
		}
		case 2: {
			int x;
			printf("Nhap gia tri: ");  scanf("%d", &x);
			push(top, x);
			break;
		}
		case 3: {
			int x; bool flag = false;
			x = pop(top, flag);
			if (flag == false)
				printf("Gia tri top = %d\n", x);
			else printf("Stack rong\n");
			break;
		}
		case 4: {
			int x; bool flag = false;
			x = peek(top, flag);
			if (flag == false)
				printf("Gia tri top = %d\n", x);
			else printf("Stack rong\n");
			break;
		}
		}
	}
}