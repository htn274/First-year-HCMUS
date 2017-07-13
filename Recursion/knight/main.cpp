#include <stdio.h>

const int hx[8] = { -2,-2,-1,-1,1,1,2,2 };
const int hy[8] = { 1,-1,2,-2,2,-2,1,-1 };

bool checkBanCo(int x, int y) {
	return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

void loigiai(int a[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}

void DiTuan(int i, int banco[8][8], int x, int y) {
	if (i > 64) {
		loigiai(banco);
		getchar();
		return;
	}
	//banco[x][y] = i;
	for (int k = 0; k < 8; k++)
		if (checkBanCo(x + hx[k], y + hy[k])) {

			int u = x + hx[k]; 
			int v = y + hy[k];
			if (banco[u][v] == 0) {
				banco[u][v] = i;
				DiTuan(i + 1, banco, u, v);
				banco[u][v] = 0;
			}
		}
}

void main() {
	int banco[8][8] = { 0 };
	DiTuan(1, banco, 0, 0);
}