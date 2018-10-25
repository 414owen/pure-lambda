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
%token<var> IDENT

%type<node> bracexpr applist callableExpr var expr lambda curry lastapp

%start start

%%

start: expr { parse_res = $1; };
expr: applist | lastapp | lambda;
lastapp: applist lambda { $$ = ast_new_app($1, $2); };
applist: applist callableExpr { $$ = ast_new_app($1, $2); } | callableExpr;
callableExpr: bracexpr | var;
lambda: LAMBDA curry { $$ = $2; };
curry: DOT expr { $$ = $2; } | IDENT curry { $$ = ast_new_func($1, $2); };
bracexpr: LBRAC expr RBRAC { $$ = $2; };
var: IDENT { $$ = ast_new_var($1); };

%%

void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
  exit(1);
}
