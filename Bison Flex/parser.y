%{
	#include "parse.h"
	#include "semantic.h"
	#include <stdio.h>
	extern int yylex();
	extern int yyparse();
	void yyerror(const char* str);
%}

%union {
	int ivalue;
	float fvalue;
	char cvalue;
	char* svalue;
}

%token <ivalue> INT
%token <fvalue> FLOAT
%token <cvalue> CHAR
%token <svalue> STRING
%token <svalue> FILENAME
%token <svalue> ENDL

%token <svalue> COMMAND_AVERAGE
%token <svalue> COMMAND_BLUR
%token <svalue> COMMAND_BRIGHTEN
%token <svalue> COMMAND_CONTRAST
%token <svalue> COMMAND_DECOMPOSE
%token <svalue> COMMAND_DESATURATE
%token <svalue> COMMAND_DIFFUSE
%token <svalue> COMMAND_GAMMA
%token <svalue> COMMAND_GRAYSHADE
%token <svalue> COMMAND_INVERT
%token <svalue> COMMAND_LUMINANCE
%token <svalue> COMMAND_PIXELATE
%token <svalue> COMMAND_REDUCE
%token <svalue> COMMAND_SINGLECHANNEL
%token <svalue> COMMAND_SOLARISE
%%

processing:
	process ENDL {
		printf("Starting interpreter process...\n");
		if (runInterpreter())
			printf("Error: Interpreter process failed...\n\n");
		else
			printf("Success: Interpreter process finished with success!\n\n");
	}
	;

process:
	FILENAME cmd {
		printf("Input and Output specified as \"%s\"\n", (char*)$1);
		setInputFilename((char*)$1);
		setOutputFilename((char*)$1);
	}
	| FILENAME cmd FILENAME {
		printf("Input specified as \"%s\"\n", (char*)$1);
		printf("Output specified as \"%s\"\n", (char*)$3);
		setInputFilename((char*)$1);
		setOutputFilename((char*)$3);
	}
	;

cmd:
	cmd cmd_average
	| cmd cmd_blur
	| cmd cmd_brighten
	| cmd cmd_contrast
	| cmd cmd_decompose
	| cmd cmd_desaturate
	| cmd cmd_diffuse
	| cmd cmd_gamma
	| cmd cmd_grayshade
	| cmd cmd_invert
	| cmd cmd_luminance
	| cmd cmd_pixelate
	| cmd cmd_reduce
	| cmd cmd_singlechannel
	| cmd cmd_solarise
	| cmd_average
	| cmd_blur
	| cmd_brighten
	| cmd_contrast
	| cmd_decompose
	| cmd_desaturate
	| cmd_diffuse
	| cmd_gamma
	| cmd_grayshade
	| cmd_invert
	| cmd_luminance
	| cmd_pixelate
	| cmd_reduce
	| cmd_singlechannel
	| cmd_solarise
	;


cmd_average:
	COMMAND_AVERAGE {
		printf("Pushing %s state...\n", (char*)$1);
		free($1);
		pushToInterpreter(COMMAND_AVERAGE_INDEX, 0);
	}
	;

cmd_blur:
	COMMAND_BLUR INT {
		int arg = (int)$2;
		printf("Pushing %s %d state...\n", (char*)$1, arg);
		free($1);
		if (arg >= 0)
			pushToInterpreter(COMMAND_BLUR_INDEX, 1, (unsigned)arg);
		else
			printf("Error: Cannot execute Blur algorithm because its argument is negative, skipping algorithm...\n");
	}
	;

cmd_brighten:
	COMMAND_BRIGHTEN INT {
		printf("Pushing %s %d state...\n", (char*)$1, (int)$2);
		free($1);
		pushToInterpreter(COMMAND_BRIGHTEN_INDEX, 1, (int)$2);
	}
	;

cmd_contrast:
	COMMAND_CONTRAST INT {
		printf("Pushing %s %d state...\n", (char*)$1, (int)$2);
		free($1);
		pushToInterpreter(COMMAND_CONTRAST_INDEX, 1, (int)$2);
	}
	;

cmd_decompose:
	COMMAND_DECOMPOSE STRING {
		printf("Pushing %s %s state...\n", (char*)$1, (char*)$2);
		free($1);
		pushToInterpreter(COMMAND_DECOMPOSE_INDEX, 1, (char*)$2);
	}
	| COMMAND_DECOMPOSE {
		printf("Pushing %s state...\n", (char*)$1);
		free($1);
		char* ptr = NULL;
		pushToInterpreter(COMMAND_DECOMPOSE_INDEX, 1, ptr);
	}
	;

cmd_desaturate:
	COMMAND_DESATURATE {
		printf("Pushing %s state...\n", (char*)$1);
		free($1);
		pushToInterpreter(COMMAND_DESATURATE_INDEX, 0);
	}
	;

cmd_diffuse:
	COMMAND_DIFFUSE INT {
		int arg = (int)$2;
		printf("Pushing %s %d state...\n", (char*)$1, (int)arg);
		free($1);
		if (arg >= 0)
			pushToInterpreter(COMMAND_DIFFUSE_INDEX, 1, (unsigned)arg);
		else
			printf("Error: Cannot execute Diffuse algorithm because its argument is negative, skipping algorithm...\n");
	}
	;

cmd_gamma:
	COMMAND_GAMMA FLOAT {
		printf("Pushing %s %f state...\n", (char*)$1, (double)$2);
		free($1);
		pushToInterpreter(COMMAND_GAMMA_INDEX, 1, (double)$2);
	}
	;

cmd_grayshade:
	COMMAND_GRAYSHADE INT {
		int arg = (int)$2;
		printf("Pushing %s %d state...\n", (char*)$1, arg);
		free($1);
		if (arg >= 0)
			pushToInterpreter(COMMAND_GRAYSHADE_INDEX, 1, (unsigned)arg);
		else
			printf("Error: Cannot execute Grayshade algorithm because its argument is negative, skipping algorithm...\n");
	}
	;

cmd_invert:
	COMMAND_INVERT {
		printf("Pushing %s state...\n", (char*)$1);
		free($1);
		pushToInterpreter(COMMAND_INVERT_INDEX, 0);
	}
	;

cmd_luminance:
	COMMAND_LUMINANCE FLOAT FLOAT FLOAT {
		float rf = (float)$2;
		float gf = (float)$3;
		float bf = (float)$4;
		printf("Pushing %s %f %f %f state...\n", (char*)$1, rf, gf, bf);
		free($1);
		pushToInterpreter(COMMAND_LUMINANCE_INDEX, 3, rf, gf, bf);
	}
	;

cmd_pixelate:
	COMMAND_PIXELATE INT {
		int arg = (int)$2;
		printf("Pushing %s %d state...\n", (char*)$1, arg);
		free($1);
		if (arg >= 0)
			pushToInterpreter(COMMAND_PIXELATE_INDEX, 1, (unsigned)arg);
		else
			printf("Error: Cannot execute Pixelate algorithm because its argument is negative, skipping algorithm...\n");
	}
	;
		
cmd_reduce:
	COMMAND_REDUCE INT {
		int arg = (int)$2;
		printf("Pushing %s %d state...\n", (char*)$1, arg);
		free($1);
		if (arg >= 0)
			pushToInterpreter(COMMAND_REDUCE_INDEX, 1, (unsigned)arg);
		else
			printf("Error: Cannot execute Reduce algorithm because its argument is negative, skipping algorithm...\n");
	}
	;

cmd_singlechannel:
	COMMAND_SINGLECHANNEL CHAR {
		printf("Pushing %s %c state...\n", (char*)$1, (char)$2);
		pushToInterpreter(COMMAND_SINGLECHANNEL_INDEX, 1, (char)$2);
	}
	;

cmd_solarise:
	COMMAND_SOLARISE INT STRING {
		int arg = (int)$2;
		printf("Pushing %s %d %s state...\n", (char*)$1, arg, (char*)$3);
		free($1);
		if (arg >= 0)
			pushToInterpreter(COMMAND_SOLARISE_INDEX, 2, (unsigned)arg, (char*)$3);
		else {
			free((char*)$3);
			printf("Error: Cannot execute Solarise algorithm because its argument is negative, skipping algorithm...\n");
		}
	}
	| COMMAND_SOLARISE INT {
		int arg = (int)$2;
		printf("Pushing %s %d state...\n", (char*)$1, arg);
		free($1);
		char* ptr = NULL;
		if (arg >= 0)
			pushToInterpreter(COMMAND_SOLARISE_INDEX, 2, (unsigned)arg, ptr);
		else
			printf("Error: Cannot execute Solarise algorithm because its argument is negative, skipping algorithm...\n");
	}
	;
%%

void yyerror(const char* str)
{
	printf("Error: Parse error...\n");
}

int parse()
{
	// Lex through the input:
	yyparse();
	return 0;
}