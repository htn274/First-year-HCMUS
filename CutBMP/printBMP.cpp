#include "printBMP.h"
#include <stdio.h>
#include <stdlib.h>

void printHeaderBMP(FILE * f, headerBMP header)
{
	if (f == NULL) return;
	fseek(f, 0, SEEK_SET);
	fwrite(&header, sizeof(headerBMP), 1, f);
}

void printDIB(FILE * f, DIB dib)
{
	if (f == NULL) return;
	fseek(f, sizeof(headerBMP), SEEK_SET);
	fwrite(&dib, sizeof(DIB), 1, f);
}

void printBMPfile(char * filename, BMP b)
{
	FILE *f = fopen(filename, "wb");
	if (f == NULL) return;
	printHeaderBMP(f, b.header);
	printDIB(f, b.dib);
	char paddingCount = (4 - (b.dib.width * (b.dib.depth/ 8) % 4)) % 4;
	printPixelArray(f, b.pA, paddingCount);
	fclose(f);
}

void printPixelArray(FILE *f, PixelArray data, char padding) {
	char * p = "\0\0\0";
	for (int i = data.rowColor - 1; i >= 0; i--) {
		fwrite(data.pixels[i], sizeof(color), data.columColor, f);
		fwrite(p, sizeof(char), padding, f);
	}
}

void delBMPPixelArray(PixelArray data)
{
	for (int i = 0; i < data.rowColor; i++)
		free(data.pixels[i]);
	free(data.pixels);
}
