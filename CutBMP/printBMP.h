#pragma once
#include "readBMP.h"

void printHeaderBMP(FILE *f, headerBMP header);
void printDIB(FILE *f, DIB dib);
//void printPixelArray(FILE *f, headerBMP header, DIB dib, PixelArray data);
void printPixelArray(FILE *f, PixelArray data, char padding);
void printBMPfile(char *filename, BMP b);
void delBMPPixelArray(PixelArray data);