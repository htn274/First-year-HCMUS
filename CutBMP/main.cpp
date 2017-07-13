#include <stdio.h>
#include <iostream>
#include "main.h"
#include "process.h"
#include "printBMP.h"

const char *HeighSign = "-h";
const char *WidthSign = "-w";

void printBmpHeader(BMP bmp)
{
	headerBMP header = bmp.header;

	printf("*** BMP Header ***\n");
	printf("- File Size  : %d byte(s)\n", header.sizeBMP);
	printf("- Reserved1  : %d\n", header.other1);
	printf("- Reserved2  : %d\n", header.other2);
	printf("- Data Offset: %d byte(s)\n", header.dataOffset);
}

void printBmpDib(BMP bmp)
{
	DIB dib = bmp.dib;

	printf("*** BMP Dib ***\n");
	printf("- DIB Size               : %d byte(s)\n", dib.sizeDIB);
	printf("- Image Width            : %d\n", dib.width);
	printf("- Image Height           : %d\n", dib.height);
}

int main(int argc, char **argv) {
	//splitBMPFile("lena.bmp", "cut_lena", 2, 2);
	int hsplit, wsplit;
	char *dest = (char*)malloc((strlen(argv[1]) + 1) * sizeof(char));
	makeDestName(argv[1], dest);

	if (argc == 4) {
		if (strcmp(HeighSign, argv[2])) {
			hsplit = StringtoInt(argv[3]);
			wsplit = 0;
		}
		else if (strcmp(WidthSign, argv[2])) {
			wsplit = StringtoInt(argv[3]);
			hsplit = 0;
		}
	}
	else
	{
		hsplit = StringtoInt(argv[3]);
		wsplit = StringtoInt(argv[3]);
	}
	splitBMPFile(argv[1], dest, hsplit, wsplit);
	return 0;
}