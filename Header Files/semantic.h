#ifndef __SEMANTIC_H_
#define __SEMANTIC_H

#include "idx.h"

typedef struct
{
	unsigned width;
	unsigned height;
	unsigned char* image;
	char* input;
	char* output;
	int inputAsOutput;
	int exitState;
	Node* tree;
} Interpreter;

Interpreter gInterpreter;

void initInterpreter();
int setInputFilename(char* ptr);
int setOutputFilename(char* ptr);
int pushToInterpreter(int index, int count, ...);
int popFromInterpreter(Node** node);
void escapeFromInterpreter(Node** node);
int runInterpreter();

#endif