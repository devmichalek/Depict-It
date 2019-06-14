%{
	#include "parse.h"
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
	snazzle '\n' {

	}
	;

snazzle:
	snazzle INT {
		printf("found int: %d\n", (int)$2);
	}
	| snazzle FLOAT {
		printf("found float: %f\n", (float)$2);
	}
	| snazzle STRING {
		printf("found string: %s\n", (char*)$2); free($2);
	}
	| INT {
		printf("found int: %d\n", (int)$1);
	}
	| FLOAT {
		printf("found float: %f\n", (float)$1);
	}
	| STRING {
		printf("found string: %s\n", (char*)$1); free($1);
	}
	;

%%

void yyerror(const char* str)
{
	printf("EEK, parse error!\nMessage: %s\n", str);
}

int parse()
{
	// Lex through the input:
	yyparse();
	return 0;
}