#pragma once
#include "readBMP.h"

void splitBMPFile(char *sourceFile, char *destName, int hsplit, int wsplit);
int StringtoInt(char *s);
void makeDestName(char *s, char* cut);