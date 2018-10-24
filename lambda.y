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
  applist {
    parse_res = $1;
  };

applist:
  callableExpr applist {
    $$ = malloc(sizeof(struct ast_node));
    $$->type = A_APP;
    $$->val.app.left = $1;
    $$->val.app.right = $2;
  }
  | expr;

callableExpr:
  bracexpr
  | VAR {
    $$ = malloc(sizeof(struct ast_node));
    $$->type = A_VAR;
    $$->val.var = $1;
  }

expr:
  callableExpr
  | LAMBDA VAR DOT applist {
    $$ = malloc(sizeof(struct ast_node));
    $$->type = A_FUNC;
    $$->val.func.param = $2;
    $$->val.func.body = $4;
  };

bracexpr:
  LBRAC applist RBRAC {
    $$ = $2;
  };

%%

void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
  exit(1);
}
