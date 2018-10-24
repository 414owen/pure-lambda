#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yy_scan_string(const char*);
extern FILE* yyin;
extern int yyparse(void);
extern struct ast_node *parse_res;

void repl(void) {
  while (true) {
    char *input = readline("> ");
    if (!input) break;
    yy_scan_string(input);
    yyparse();
    print_ast(parse_res);
  }
}

int main(int argc, char **argv) {
  if (argc > 1) {
    FILE *file = fopen(argv[1], "r");
    if (!file) {return -1;}
    yyin = file;
    yyparse();
    print_ast(parse_res);
  } else {
    repl();
  }
  return EXIT_SUCCESS;
}
