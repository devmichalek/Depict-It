%{
	#include "parser.tab.h"
	#include <stdio.h>

#ifdef _WINDOWS
#define fix_strdup(X) _strdup(X)
#else
#define fix_strdup(X) strdup(X)
#endif
%}
%option noyywrap
WORD [a-zA-Z0-9]+
%%
[ \t]			;
[0-9]+          { yylval.ivalue = atoi(yytext); return INT; }
[0-9]+\.[0-9]+	{ yylval.fvalue = (float)atof(yytext); return FLOAT; }
{WORD}			{ yylval.svalue = fix_strdup(yytext); return STRING; }
{WORD}\.png		{ yylval.svalue = fix_strdup(yytext); return FILENAME; }

\-blur			{ yylval.svalue = fix_strdup(yytext); return COMMAND_BLUR; }
\-brighten		{ yylval.svalue = fix_strdup(yytext); return COMMAND_BRIGHTEN; }
\-reduce		{ yylval.svalue = fix_strdup(yytext); return COMMAND_REDUCE; }
\-contrast		{ yylval.svalue = fix_strdup(yytext); return COMMAND_CONTRAST; }
\-diffuse		{ yylval.svalue = fix_strdup(yytext); return COMMAND_DIFFUSE; }
\-gamma			{ yylval.svalue = fix_strdup(yytext); return COMMAND_GAMMA; }
\-average		{ yylval.svalue = fix_strdup(yytext); return COMMAND_AVERAGE; }
\-luminance		{ yylval.svalue = fix_strdup(yytext); return COMMAND_LUMINANCE; }
\-desaturate	{ yylval.svalue = fix_strdup(yytext); return COMMAND_DESATURATE; }
\-decompose		{ yylval.svalue = fix_strdup(yytext); return COMMAND_DECOMPOSE; }
\-grayshade		{ yylval.svalue = fix_strdup(yytext); return COMMAND_GRAYSHADE; }
\-invert		{ yylval.svalue = fix_strdup(yytext); return COMMAND_INVERT; }
\-solarise		{ yylval.svalue = fix_strdup(yytext); return COMMAND_SOLARISE; }
\-singlechannel	{ yylval.svalue = fix_strdup(yytext); return COMMAND_SINGLECHANNEL; }


.				{
					printf("Error: Unrecognized token occured.\n");
					printf("Press enter to continue...\n");
					char enter = 0;
					while (enter != '\r' && enter != '\n')
						enter = getchar();
					yyterminate();
				}

%%