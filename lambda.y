%{

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

// flex stuff
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);
struct ast_node *parse_res;

%}

%union {
  char var;
  struct ast_node *node;
}

%token LAMBDA DOT LBRAC RBRAC
%token<var> VAR

%type<node> expr braceexpr

%start start

%%

start:
  expr {
    parse_res = $1;
  }
  ;

expr:
  braceexpr expr {
    $$ = malloc(sizeof(struct ast_node));
    $$->type = A_APP;
    $$->val.app.left = $1;
    $$->val.app.right = $2;
  }
  | braceexpr
  | VAR {
    $$ = malloc(sizeof(struct ast_node));
    $$->type = A_VAR;
    $$->val.var = $1;
    printf("parsed a var: %c\n", $$->val.var);
  }
  | LAMBDA VAR DOT expr {
    $$ = malloc(sizeof(struct ast_node));
    $$->type = A_FUNC;
    $$->val.func.param = $2;
    $$->val.func.body = $4;
    printf("parsed a func: \\ %c . \n", $$->val.func.param);
  }
  ;

braceexpr:
  LBRAC expr RBRAC {
    $$ = $2;
  }

%%

int main(int argc, char **argv) {
  if (argc < 2) {return -1;}
  FILE *file = fopen(argv[1], "r");
	if (!file) {return -1;}
	yyin = file;
  yyparse();
  print_ast(parse_res);
  return EXIT_SUCCESS;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

