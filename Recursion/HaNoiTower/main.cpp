#include <stdio.h>

void move(int &a, int &b) {
	a--;
	b++;
}

void showT(int t[3], int count) {
	printf("Buoc %d:", count);
	for (int i = 1; i < 4; i++)
		printf("%d ", t[i]);
	//printf("\n");
}

void moveT(int n, int a, int b, int t[3], int &count) {
	if (n == 1) {
		count++;
		move(t[a], t[b]);
		showT(t, count);
		//printf("Chuyen tu cot %c sang cot %c", a + 64, b + 64);
		getchar();
		return;
	}
	int c = 6 - a - b;
	moveT(n - 1, a, c, t, count);
	moveT(1, a, b, t, count);
	moveT(n - 1, c, b, t, count);
	
}

void main() {
	int t[4], n = 10, c = 0;
	t[1] = n; t[2] = 0; t[3] = 0;
	printf("A B C\n");
	showT(t, c);
	printf("\n");
	moveT(n, 1, 3, t, c);
}