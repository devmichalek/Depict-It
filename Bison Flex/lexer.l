%{
	#include "parser.tab.h"
	#include <stdio.h>
	#include "semantic.h"

#ifdef _WINDOWS
#define fix_strdup(X) _strdup(X)
#else
#define fix_strdup(X) strdup(X)
#endif
%}
%option noyywrap
WORD [a-zA-Z0-9]{2,}
CHARACTER [a-zA-Z0-9]{1}
FNAME ({WORD}\.png)|({CHARACTER}\.png)
%%
[ \t]			;
\n				{ yylval.svalue = fix_strdup(yytext); return ENDL; }
[0-9]+          { yylval.ivalue = atoi(yytext); return INT; }
[0-9]+\.[0-9]+	{ yylval.fvalue = (float)atof(yytext); return FLOAT; }
{WORD}			{ yylval.svalue = fix_strdup(yytext); return STRING; }
{FNAME}			{ yylval.svalue = fix_strdup(yytext); return FILENAME; }
{CHARACTER}		{ yylval.cvalue = (char)atoi(yytext); return CHAR; }
\-average		{ yylval.svalue = fix_strdup(yytext); return COMMAND_AVERAGE; }
\-blur			{ yylval.svalue = fix_strdup(yytext); return COMMAND_BLUR; }
\-brighten		{ yylval.svalue = fix_strdup(yytext); return COMMAND_BRIGHTEN; }
\-contrast		{ yylval.svalue = fix_strdup(yytext); return COMMAND_CONTRAST; }
\-decompose		{ yylval.svalue = fix_strdup(yytext); return COMMAND_DECOMPOSE; }
\-desaturate	{ yylval.svalue = fix_strdup(yytext); return COMMAND_DESATURATE; }
\-diffuse		{ yylval.svalue = fix_strdup(yytext); return COMMAND_DIFFUSE; }
\-gamma			{ yylval.svalue = fix_strdup(yytext); return COMMAND_GAMMA; }
\-grayshade		{ yylval.svalue = fix_strdup(yytext); return COMMAND_GRAYSHADE; }
\-invert		{ yylval.svalue = fix_strdup(yytext); return COMMAND_INVERT; }
\-luminance		{ yylval.svalue = fix_strdup(yytext); return COMMAND_LUMINANCE; }
\-pixelate		{ yylval.svalue = fix_strdup(yytext); return COMMAND_PIXELATE; }
\-reduce		{ yylval.svalue = fix_strdup(yytext); return COMMAND_REDUCE; }
\-singlechannel	{ yylval.svalue = fix_strdup(yytext); return COMMAND_SINGLECHANNEL; }
\-solarise		{ yylval.svalue = fix_strdup(yytext); return COMMAND_SOLARISE; }

\-exit			{
					gInterpreter.exitState = 1;
					yyterminate();

				}
.				{
					printf("Error: Unrecognized token occured\n");
					yyterminate();
				}
%%