#pragma once
#include "readBMP.h"

void CopyHeader(BMP &dest, BMP src, uint32_t width, uint32_t height);
void CopyDIB(BMP &dest, BMP src, uint32_t width, uint32_t height);
BMP cutBMPfile(BMP bmp, uint32_t startRow, uint32_t startColum, uint32_t sizeRow, uint32_t sizeColum);