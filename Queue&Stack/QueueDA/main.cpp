#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "QueueDA.h"

void main() {
	Queue q;
	int n, c;
	while (1) {
		printf("1. Khoi tao hang doi\n2. Them phan tu\n3. Lay phan tu ra khoi hang doi\n4. Cho biet gia tri hang doi\n5. Xoa hang doi\n");
		scanf("%d", &c);
		switch (c) {
		case 1: {
			printf("Nhap vao kich thuoc hang doi: "); scanf("%d", &n);
			Init(q, n);
			break;
		}
		case 2: {
			int x;
			printf("Nhap gia tri: ");  scanf("%d", &x);
			QueuePush(q, x);
			break;
		}
		case 3: {
			int x; bool flag = false;
			x = QueuePop(q, flag);
			if (flag) printf("Hang doi rong\n");
			else
				printf("Gia tri dau cua hang doi: %d\n", x);
			break;
		}
		case 4: {
			int x; bool flag = false;
			x = QueuePeek(q, flag);
			if (flag) printf("Hang doi rong\n");
			printf("Gia tri dau cua hang doi: %d\n", x);
			break;
		}
		case 5: {
			Release(q);
			break;
		}
		}
	}
}