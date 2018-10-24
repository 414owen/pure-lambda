#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "eval.h"

extern int yy_scan_string(const char*);
extern FILE* yyin;
extern int yyparse(void);
extern struct ast_node *parse_res;

void print_eval_steps(struct ast_node *node) {
  while (node) {
    print_ast(node);
    node = single_reduction(node);
  }
}

void repl(void) {
  while (true) {
    char *input = readline("> \e[0;34m");
    fputs("\e[0m", stdout);
    if (!input) break;
    yy_scan_string(input);
    yyparse();
    print_eval_steps(parse_res);
  }
}

int main(int argc, char **argv) {
  if (argc > 1) {
    FILE *file = fopen(argv[1], "r");
    if (!file) {return -1;}
    yyin = file;
    yyparse();
    print_eval_steps(parse_res);
  } else {
    repl();
  }
  return EXIT_SUCCESS;
}
