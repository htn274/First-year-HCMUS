#include "readBMP.h"
#include <stdlib.h>
#include <stdio.h>

bool isBMP(FILE *f)
{
	if (f == NULL) return false;
	signBMP c;
	fseek(f, 0, SEEK_SET);
	fread(&c, sizeof(signBMP), 1, f);
	if (c.s[0] == 'B' && c.s[1] == 'M') return true;
	return false;
}

void readHeaderBMP(FILE *f, headerBMP & header)
{
	if (f == NULL) return;
	fseek(f, 0, SEEK_SET);
	fread(&header, sizeof(headerBMP), 1, f);
}

void readDIB(FILE *f, DIB & dib)
{
	if (f == NULL) return;
	fseek(f, sizeof(headerBMP), SEEK_SET);
	fread(&dib, sizeof(DIB), 1, f);
}

void scanBmpPixelLine(FILE *f, color *&line, uint32_t length)
{
	if (f == NULL)
		return;

	line = (color*)malloc(sizeof(color)*length);
	fread(line, sizeof(color), length, f);
}

void skipBmpPadding(FILE *f, char count)
{
	if (f == NULL)
		return;

	if (count == 0)
		return;

	char padding[3];
	fread(padding, count, 1, f);
}

void readPixelArray(FILE * f, headerBMP header, DIB dib, PixelArray & data)
{
	if (f == NULL)
		return;

	data.rowColor = dib.height;
	data.columColor = dib.width;
	data.pixels = (color**)malloc(sizeof(color*)*data.rowColor);

	char paddingCount = (4 - (dib.width * (dib.depth / 8) % 4)) % 4;

	fseek(f, header.dataOffset, SEEK_SET);

	for (int i = 0; i < data.rowColor; i++)
	{
		scanBmpPixelLine(f, data.pixels[data.rowColor - i - 1], dib.width);
		skipBmpPadding(f, paddingCount);
	}
}

bool readBMPfile(char * filename, BMP & b)
{
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		printf("Error!\n");
		return false;
	}

	if (!isBMP(f)) {
		printf("File is not BMP\n");
		return false;
	}
	readHeaderBMP(f, b.header);
	readDIB(f, b.dib);
	readPixelArray(f, b.header, b.dib, b.pA);
	fclose(f);
	return true;
}

