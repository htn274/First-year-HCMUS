#include <stdio.h>
#include <malloc.h>
#include <string.h>

void display(int a[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
	getchar();
}

void datHau(int &songhiem, int i, int banco[8][8], bool cot[8], bool cheochinh[15], bool cheophu[15]) {
	if (i == 8) {
		songhiem++;
		display(banco);
		return;
	}
	for (int j = 0; j < 8; j++) 
	if (banco[i][j]==0 && cot[j] && cheochinh[i+j] && cheophu[i-j+7]){
		banco[i][j] = i+1;
		cot[j] = false;
		cheochinh[i + j] = false;
		cheophu[i - j + 7] = false;
		datHau(songhiem, i + 1, banco, cot, cheochinh, cheophu);
		banco[i][j] = 0;
		cot[j] = true;
		cheochinh[i + j] = true;
		cheophu[i - j + 7] = true;
	}
}

void main() {
	int banco[8][8] = { 0 }, sn = 0;
	bool cot[8], cheochinh[15], cheophu[15];
	memset(cot, true, 8); memset(cheochinh, true, 15); memset(cheochinh, true, 15);
	datHau(sn, 0, banco, cot, cheochinh, cheophu);
	printf("Co tat ca %d nghiem \n", sn);
	getchar();
}