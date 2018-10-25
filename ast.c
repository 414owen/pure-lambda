#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

void print_ast_rec(struct ast_node *node) {
  switch (node->type) {
    case A_APP:
      if (node->val.app.left->type == A_FUNC) putchar('(');
      print_ast_rec(node->val.app.left);
      if (node->val.app.left->type == A_FUNC) putchar(')');
      if (node->val.app.right->type != A_VAR) putchar('(');
      print_ast_rec(node->val.app.right);
      if (node->val.app.right->type != A_VAR) putchar(')');
      break;
    case A_FUNC:
      printf("%c->", node->val.func.param);
      print_ast_rec(node->val.func.body);
      break;
    case A_VAR:
      putchar(node->val.var);
      break;
  }
}

struct ast_node *ast_new_app(struct ast_node* left, struct ast_node* right) {
  struct ast_node *res = malloc(sizeof(struct ast_node));
  res->type = A_APP;
  res->val.app.left = left;
  res->val.app.right = right;
  return res;
}

struct ast_node *ast_new_func(char param, struct ast_node* body) {
  struct ast_node *res = malloc(sizeof(struct ast_node));
  res->type = A_FUNC;
  res->val.func.param = param;
  res->val.func.body = body;
  return res;
}

struct ast_node *ast_new_var(char binding) {
  struct ast_node *res = malloc(sizeof(struct ast_node));
  res->type = A_VAR;
  res->val.var = binding;
  return res;
}

void free_ast(struct ast_node *node) {
  if (node == NULL) return;
  switch (node->type) {
    case A_APP:
      free_ast(node->val.app.left);
      free_ast(node->val.app.right);
      break;
    case A_FUNC:
      free_ast(node->val.func.body);
      break;
    case A_VAR:
      break;
  }
  free(node);
}

void print_ast(struct ast_node *node) {
  print_ast_rec(node);
  putchar('\n');
}
