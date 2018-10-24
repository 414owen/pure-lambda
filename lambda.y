%{

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
void yyerror(const char* s);
struct ast_node *parse_res;

%}

%union {
  char var;
  struct ast_node *node;
}

%token LAMBDA DOT LBRAC RBRAC
%token<var> VAR

%type<node> bracexpr applist callableExpr var expr lambda

%start start

%%

start: expr { parse_res = $1; };
expr: applist | lambda;
applist: applist callableExpr { $$ = ast_new_app($1, $2); } | callableExpr;
callableExpr: bracexpr | var;
var: VAR { $$ = ast_new_var($1); };
lambda: LAMBDA VAR DOT expr{ $$ = ast_new_func($2, $4); };
bracexpr: LBRAC expr RBRAC { $$ = $2; };

%%

void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
  exit(1);
}
