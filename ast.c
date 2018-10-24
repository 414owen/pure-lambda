#include <stdio.h>
#include "ast.h"

void print_ast_rec(struct ast_node *node) {
  switch (node->type) {
    case A_APP:
      print_ast_rec(node->val.app.left);
      print_ast_rec(node->val.app.right);
      break;
    case A_FUNC:
      putchar('(');
      printf("%c->", node->val.func.param);
      print_ast_rec(node->val.func.body);
      putchar(')');
      break;
    case A_VAR:
      putchar('(');
      putchar(node->val.var);
      putchar(')');
      break;
  }
}

void print_ast(struct ast_node *node) {
  print_ast_rec(node);
  putchar('\n');
}
