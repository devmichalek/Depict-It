#ifndef __SEMANTIC_H_
#define __SEMANTIC_H

#define COMMAND_AVERAGE_INDEX 0
#define COMMAND_BLUR_INDEX 1
#define COMMAND_BRIGHTEN_INDEX 2
#define COMMAND_CONTRAST_INDEX 3
#define COMMAND_DECOMPOSE_INDEX 4
#define COMMAND_DESATURATE_INDEX 5
#define COMMAND_DIFFUSE_INDEX 6
#define COMMAND_GAMMA_INDEX 7
#define COMMAND_GRAYSHADE_INDEX 8
#define COMMAND_INVERT_INDEX 9
#define COMMAND_LUMINANCE_INDEX 10
#define COMMAND_PIXELATE 11
#define COMMAND_REDUCE_INDEX 12
#define COMMAND_SINGLECHANNEL_INDEX 13
#define COMMAND_SOLARISE_INDEX 14

//typedef struct Average;

typedef struct Blur {
	int size;
} Blur;

typedef struct Brighten {
	int level;
} Brighten;

typedef Brighten Contrast;

typedef struct Decompose {
	char* functionName;
} Decompose;

//typedef struct Desaturate;

typedef Brighten Diffuse;

typedef struct Gamma {
	double ratio;
} Gamma;

typedef struct GrayShade {
	unsigned char shades;
} GrayShade;

//typedef struct Invert;

typedef struct Luminance {
	float redRatio;
	float greenRatio;
	float blueRatio;
} Luminance;

typedef Blur Pixelate;
typedef Brighten Reduce;

typedef struct SingleChannel {
	char* channel;
} SingleChannel;

typedef struct Solarise {
	char* functionName;
	unsigned char threshold;
} Solarise;


typedef struct Node
{
	int index;
	void* ptrToStruct;
	Node* next;
} Node;

typedef struct Interpreter
{
	char input[2048];
	char output[2048];
	int bOutput;
	Node* tree;
} Interpreter;
Interpreter gInterpreter;

void initInterpreter();
int setInputFilename(char* ptr);
int setOutputFilename(char* ptr);
int pushStructToInterpreter(int index, int count, ...);

#endif