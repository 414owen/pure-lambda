%{

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "stack.h"

extern int yylex();
void yyerror(const char* s);
struct ast_node *parse_res;
struct stack *backups;
unsigned debruijn = 0;
unsigned indices[256] = {0};

%}

%union {
  char var;
  struct ast_node *node;
}

%token LAMBDA DOT LBRAC RBRAC
%token<var> IDENT

%type<node> bracexpr applist callableExpr var expr lambda curry lastapp

%start start

%initial-action {
  debruijn = 1;
  backups = new_stack();
  for (int i = 0; i < 256; i++) {
    indices[i] = 0;
  }
}

%%

start: expr { parse_res = $1; };
expr: applist | lastapp | lambda;
lastapp: applist lambda { $$ = ast_new_app($1, $2); };
applist: applist callableExpr { $$ = ast_new_app($1, $2); } | callableExpr;
callableExpr: bracexpr | var;
lambda: LAMBDA curry { $$ = $2; };
curry: DOT expr { $$ = $2; }
     | IDENT {
       backups = stack_push(backups, indices[$1]);
       indices[$1] = debruijn++;
     } curry {
       $$ = ast_new_func($1, $3);
       indices[$1] = stack_pop(backups);
       debruijn--;
     };
bracexpr: LBRAC expr RBRAC { $$ = $2; };
var: IDENT { $$ = ast_new_var($1,
   indices[$1] == 0 ? 0 : debruijn - indices[$1]); };

%%

void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
  exit(1);
}
