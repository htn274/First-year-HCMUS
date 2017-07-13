#pragma once
#pragma once
#pragma pack(1)

#include <stdint.h>
#include <stdio.h>
#include <string.h>


struct signBMP {
	unsigned char s[2];
};

struct headerBMP {
	signBMP sign;
	uint32_t sizeBMP;
	uint16_t other1, other2;
	uint32_t dataOffset;
};

struct DIB {
	uint32_t sizeDIB, width, height;
	uint16_t numColorPlane, depth;
	uint32_t compressMethod, sizePixel, horizontalPixel, verticalPixel, numColor, numMainColor;
};

struct color {
	unsigned char blue, green, red;
};

struct ColorTable {
	color *colors;
	uint32_t length;
};

struct PixelArray {
	color **pixels;
	uint32_t rowColor, columColor;
};

struct BMP {
	headerBMP header;
	DIB dib;
	PixelArray pA;
	ColorTable cT;
};

bool isBMP(FILE *f);
void readHeaderBMP(FILE *f, headerBMP &header);
void readDIB(FILE *f, DIB &dib);
void readPixelArray(FILE *f, headerBMP header, DIB dib, PixelArray &data);
bool readBMPfile(char *filename, BMP &b);
