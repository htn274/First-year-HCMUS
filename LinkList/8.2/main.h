#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "SList.h"
#include <stdio.h>

void main() {
	SNode *head = new SNode;
	head = NULL;

	while (true) {
		printf("1. Them phan tu dau vao danh sach\n2.Dem so nut\n");
		printf("3. Dao nguoc danh sach\n4. Them phan tu thu i\n");
		printf("5. In danh sach\n");
		int c, x, i;
		scanf("%d", &c);
		switch (c) {
		case 1: {
			printf("Nhap gia tri x = "); scanf("%d", &x);
			InsertHead(head, x);
			break;
		}
		case 2: {
			int count = countNode(head);
			printf("Danh sach co tat ca %d nut\n", count);
			break;
		}
		case 3: {
			printf("Danh sach dao nguoc: \n");
			SNode *h = ReverseList(head);
			printList(h);
			break;
		}
		case 4: {
			printf("Nhap vi tri i = "); scanf("%d", &i);
			printf("Nhap gia tri x = "); scanf("%d", &x);
			InsertI(head, i, x);
			break;
		}
		case 5: {
			printList(head);
			break;
		}
		}
	}
}