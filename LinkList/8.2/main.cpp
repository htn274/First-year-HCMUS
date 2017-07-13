#define _CRT_SECURE_NO_WARNINGS
#include "SList.h"
#include <stdio.h>

void main() {
	SNode *head = new SNode;
	head = NULL;

	while (true) {
		printf("1. Dem so nut\n2. Dao nguoc danh sach\n3. Them phan tu\n4. In danh sach\n");
		int c, x, i;
		scanf("%d", &c);
		switch (c) {
		case 1: {
			int count = countNode(head);
			printf("Danh sach co tat ca %d nut\n", count);
			break;
		}
		case 2: {
			printf("Danh sach dao nguoc: \n");
			ReverseList(head);
			printList(head);
			break;
		}
		case 3: {
			printf("Nhap gia tri x = "); scanf("%d", &x);
			InsertX(head, x);
			break;
		}
		case 4: {
			printf("Danh sach:");
			printList(head);
			break;
		}
		}
	}
}