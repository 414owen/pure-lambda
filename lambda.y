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

%type<node> expr bracexpr applist callableExpr

%start start

%%

start:
  applist { parse_res = $1; };

applist:
  callableExpr applist { $$ = ast_new_app($1, $2); }
  | expr;

callableExpr:
  bracexpr
  | VAR { $$ = ast_new_var($1); };

expr:
  callableExpr
  | LAMBDA VAR DOT applist { $$ = ast_new_func($2, $4); };

bracexpr:
  LBRAC applist RBRAC { $$ = $2; };

%%

void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
  exit(1);
}
