#include "splitBMP.h"
#include <malloc.h>

void CopyHeader(BMP &dest, BMP src, uint32_t height, uint32_t width)
{
	dest.header = src.header;
	char paddingCount = (4 - (width * (src.dib.depth / 8) % 4)) % 4;
	dest.header.sizeBMP = (width * src.dib.depth / 8 + paddingCount) * height + src.header.dataOffset;
}

void CopyDIB(BMP &dest, BMP src, uint32_t height, uint32_t width)
{
	dest.dib = src.dib;
	dest.dib.height = height;
	dest.dib.width = width;
	char paddingCount = (4 - (width * (src.dib.depth / 8) % 4)) % 4;
	dest.dib.sizePixel = (width * src.dib.depth / 8 + paddingCount) * height;

}

BMP cutBMPfile(BMP bmp, uint32_t startRow, uint32_t startColum, uint32_t sizeRow, uint32_t sizeColum)
{
	BMP b_new;
	CopyHeader(b_new, bmp, sizeRow, sizeColum);
	CopyDIB(b_new, bmp, sizeRow, sizeColum);
	//Copy Pixels Array

	PixelArray data = bmp.pA, data_new;
	data_new.rowColor = sizeRow;
	data_new.columColor = sizeColum;

	data_new.pixels = (color**)malloc(sizeRow * sizeof(color*));
	for (int i = 0; i < sizeRow; i++) {
		data_new.pixels[i] = (color*)malloc(sizeColum * sizeof(color));
		for (int j=0; j < sizeColum; j++)
			data_new.pixels[i][j] = data.pixels[i + startRow][j + startColum];
	}

	b_new.pA = data_new;
	return b_new;
}
