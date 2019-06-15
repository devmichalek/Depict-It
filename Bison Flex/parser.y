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
	char* svalue;
}

%token <ivalue> INT
%token <fvalue> FLOAT
%token <svalue> STRING
%token <svalue> FILENAME
%token <svalue> ENDL

%token <svalue> COMMAND_BLUR
%token <svalue> COMMAND_BRIGHTEN
%token <svalue> COMMAND_REDUCE
%token <svalue> COMMAND_CONTRAST
%token <svalue> COMMAND_DIFFUSE
%token <svalue> COMMAND_GAMMA
%token <svalue> COMMAND_AVERAGE
%token <svalue> COMMAND_LUMINANCE
%token <svalue> COMMAND_DESATURATE
%token <svalue> COMMAND_DECOMPOSE
%token <svalue> COMMAND_GRAYSHADE
%token <svalue> COMMAND_INVERT
%token <svalue> COMMAND_SOLARISE
%token <svalue> COMMAND_SINGLECHANNEL
%%

processing:
	process ENDL {
		printf("Starting process...\n");
	}
	;

process:
	FILENAME cmd {
		printf("Input and Output specified as \"%s\"\n", (char*)$1);
		free($1);
	}
	| FILENAME cmd FILENAME {
		printf("Input specified as \"%s\"\n", (char*)$1);
		printf("Output specified as \"%s\"\n", (char*)$3);
		free($1);
		free($3);
	}
	;

cmd:
	cmd cmd_blur
	| cmd cmd_brighten
	| cmd cmd_reduce
	| cmd cmd_contrast
	| cmd cmd_diffuse
	| cmd cmd_gamma
	| cmd cmd_average
	| cmd cmd_luminance
	| cmd cmd_desaturate
	| cmd cmd_decompose
	| cmd cmd_grayshade
	| cmd cmd_invert
	| cmd cmd_solarise
	| cmd cmd_singlechannel
	| cmd_blur
	| cmd_brighten
	| cmd_reduce
	| cmd_contrast
	| cmd_diffuse
	| cmd_gamma
	| cmd_average
	| cmd_luminance
	| cmd_desaturate
	| cmd_decompose
	| cmd_grayshade
	| cmd_invert
	| cmd_solarise
	| cmd_singlechannel
	;

cmd_blur:
	COMMAND_BLUR INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
	}
	;

cmd_brighten:
	COMMAND_BRIGHTEN INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
	}
	;

cmd_reduce:
	COMMAND_REDUCE INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
	}
	;

cmd_contrast:
	COMMAND_CONTRAST INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
	}
	;

cmd_diffuse:
	COMMAND_DIFFUSE INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
	}
	;

cmd_gamma:
	COMMAND_GAMMA INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
	}
	;

cmd_average:
	COMMAND_AVERAGE {
		printf("Pushing  %s\n", (char*)$1);
		free($1);
	}
	;

cmd_luminance:
	COMMAND_LUMINANCE FLOAT FLOAT FLOAT {
		printf("Pushing  %s %f %f %f\n", (char*)$1, (float)$2, (float)$3, (float)$4);
		free($1);
	}
	;

cmd_desaturate:
	COMMAND_DESATURATE {
		printf("Pushing  %s\n", (char*)$1);
		free($1);
	}
	;

cmd_decompose:
	COMMAND_DECOMPOSE STRING {
		printf("Pushing  %s %s\n", (char*)$1, (char*)$2);
		free($1);
		free($2);
	}
	;

cmd_grayshade:
	COMMAND_GRAYSHADE INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
	}
	;

cmd_invert:
	COMMAND_INVERT {
		printf("Pushing  %s\n", (char*)$1);
		free($1);
	}
	;

cmd_solarise:
	COMMAND_SOLARISE INT {
		printf("Pushing  %s %d\n", (char*)$1, (int)$2);
		free($1);
	}
	;

cmd_singlechannel:
	COMMAND_SINGLECHANNEL STRING {
		printf("Pushing  %s %s\n", (char*)$1, (char*)$2);
		free($1);
		free($2);
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