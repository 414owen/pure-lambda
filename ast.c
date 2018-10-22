#include <stdio.h>
#include "ast.h"

void print_ast_rec(struct ast_node *node) {
  switch (node->type) {
    case A_APP:
      putchar('(');
      print_ast_rec(node->val.app.left);
      putchar(')');
      putchar('(');
      print_ast_rec(node->val.app.right);
      putchar(')');
      break;
    case A_FUNC:
      printf("\\%c.", node->val.func.param);
      print_ast_rec(node->val.func.body);
      break;
    case A_VAR:
      putchar(node->val.var);
      break;
  }
}

void print_ast(struct ast_node *node) {
  print_ast_rec(node);
  putchar('\n');
}
