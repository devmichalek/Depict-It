#ifndef __IDX_H_
#define __IDX_H_

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
#define COMMAND_PIXELATE_INDEX 11
#define COMMAND_REDUCE_INDEX 12
#define COMMAND_SINGLECHANNEL_INDEX 13
#define COMMAND_SOLARISE_INDEX 14

//typedef struct Average;

typedef struct Blur {
	unsigned asis;
} Blur;

typedef struct Brighten {
	int level;
} Brighten;

typedef Brighten Contrast;

typedef struct Decompose {
	char* fname;
} Decompose;

//typedef struct Desaturate;

typedef struct Diffuse {
	unsigned count;
} Diffuse;

typedef struct Gamma {
	double ratio;
} Gamma;

typedef Diffuse GrayShade;

//typedef struct Invert;

typedef struct Luminance {
	float red_ratio;
	float green_ratio;
	float blue_ratio;
} Luminance;

typedef struct Pixelate {
	unsigned pixel_size;
} Pixelate;

typedef Diffuse Reduce;

typedef struct SingleChannel {
	char channel;
} SingleChannel;

typedef struct Solarise {
	unsigned threshold;
	char* fname;
	
} Solarise;


typedef struct Node
{
	int index;
	void* ptrToStruct;
	struct Node* next;
} Node;

#endif