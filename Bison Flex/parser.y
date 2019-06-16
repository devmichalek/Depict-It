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
	unsigned char cvalue;
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
		printf("Starting process...\n");
	}
	;

process:
	FILENAME cmd {
		printf("Input and Output specified as \"%s\"\n", (char*)$1);
		setInputFilename((char*)$1);
		setOutputFilename((char*)$1);
		free($1);
	}
	| FILENAME cmd FILENAME {
		printf("Input specified as \"%s\"\n", (char*)$1);
		printf("Output specified as \"%s\"\n", (char*)$3);
		setInputFilename((char*)$1);
		setOutputFilename((char*)$3);
		free($1);
		free($3);
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
		printf("Pushing  %s\n", (char*)$1);
		free($1);
		pushStructToInterpreter(COMMAND_AVERAGE_INDEX, 0);
	}
	;

cmd_blur:
	COMMAND_BLUR INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
		pushStructToInterpreter(COMMAND_BLUR_INDEX, 1, (int)$2);
	}
	;

cmd_brighten:
	COMMAND_BRIGHTEN INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
		pushStructToInterpreter(COMMAND_BRIGHTEN_INDEX, 1, (int)$2);
	}
	;

cmd_contrast:
	COMMAND_CONTRAST INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
		pushStructToInterpreter(COMMAND_CONTRAST_INDEX, 1, (int)$2);
	}
	;

cmd_decompose:
	COMMAND_DECOMPOSE STRING {
		printf("Pushing  %s %s\n", (char*)$1, (char*)$2);
		free($1);
		pushStructToInterpreter(COMMAND_DECOMPOSE_INDEX, 1, (char*)$2);
	}
	;

cmd_desaturate:
	COMMAND_DESATURATE {
		printf("Pushing  %s\n", (char*)$1);
		free($1);
		pushStructToInterpreter(COMMAND_DESATURATE_INDEX, 0);
	}
	;

cmd_diffuse:
	COMMAND_DIFFUSE INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
		pushStructToInterpreter(COMMAND_DIFFUSE_INDEX, 1, (int)$2);
	}
	;

cmd_gamma:
	COMMAND_GAMMA INT {
		printf("Pushing  %s %f\n", (char*)$1, (double)$2);
		free($1);
		pushStructToInterpreter(COMMAND_GAMMA_INDEX, 1, (double)$2);
	}
	;

cmd_grayshade:
	COMMAND_GRAYSHADE CHAR {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
		pushStructToInterpreter(COMMAND_GRAYSHADE_INDEX, 1, (char)$2);
	}
	;

cmd_invert:
	COMMAND_INVERT {
		printf("Pushing  %s\n", (char*)$1);
		free($1);
		pushStructToInterpreter(COMMAND_INVERT_INDEX, 0);
	}
	;

cmd_luminance:
	COMMAND_LUMINANCE FLOAT FLOAT FLOAT {
		printf("Pushing  %s %f %f %f\n", (char*)$1, (float)$2, (float)$3, (float)$4);
		free($1);
		pushStructToInterpreter(COMMAND_LUMINANCE_INDEX, 3, (float)$2, (float)$3, (float)$4);
	}
	;

cmd_pixelate:
	COMMAND_PIXELATE INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
		pushStructToInterpreter(COMMAND_PIXELATE_INDEX, 1, (int)$2);
	}
	;
		
cmd_reduce:
	COMMAND_REDUCE INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
		pushStructToInterpreter(COMMAND_REDUCE_INDEX, 1, (int)$2);
	}
	;

cmd_singlechannel:
	COMMAND_SINGLECHANNEL CHAR {
		printf("Pushing  %s %c\n", (char*)$1, (char)$2);
		pushStructToInterpreter(COMMAND_SINGLECHANNEL_INDEX, 1, (unsigned char)$2);
	}
	;

cmd_solarise:
	COMMAND_SOLARISE STRING CHAR {
		printf("Pushing  %s %c\n", (char*)$1, (unsigned char)$2);
		free($1);
		pushStructToInterpreter(COMMAND_SOLARISE_INDEX, 1, (char*)$2, (unsigned char)$3);
	}
	;
%%

void yyerror(const char* str)
{
	printf("EEK, parse error!\nMessage: %s\n", str);
	printf("Press enter to continue...\n");
	char enter = 0;
	while (enter != '\r' && enter != '\n')
		enter = getchar();
}

int parse()
{
	// Lex through the input:
	yyparse();
	return 0;
}