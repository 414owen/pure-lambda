%{
#include <stdio.h>
#include "lambda.tab.h"
extern int yylex();
%}

%option noyywrap

%%
[ \t\n]         ;
\\              { return LAMBDA; }
\.              { return DOT; }
[a-z]           { yylval.var = yytext[0]; return IDENT; }
\(              { return LBRAC; }
\)              { return RBRAC; }
%%

