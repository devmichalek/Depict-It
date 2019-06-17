#ifndef __SEMANTIC_H_
#define __SEMANTIC_H

#include "idx.h"

typedef struct
{
	unsigned width;
	unsigned height;
	unsigned char* image;
	char input[2048];
	char output[2048];
	Node* tree;
} Interpreter;
Interpreter gInterpreter;

void initInterpreter();
int setInputFilename(char* ptr);
int setOutputFilename(char* ptr);
int pushToInterpreter(int index, int count, ...);
int popFromInterpreter(Node** node);

#endif