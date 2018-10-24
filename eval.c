#include <stdbool.h>
#include <stdio.h>
#include "ast.h"
#include "eval.h"

struct ast_node *rebind_placeholder(
  char placeholder,
  struct ast_node *node,
  struct ast_node *val
) {
  struct ast_node *res;
  res = node;
  switch (node->type) {
    case A_APP:
      res = ast_new_app(
        rebind_placeholder(placeholder, node->val.app.left, val),
        rebind_placeholder(placeholder, node->val.app.right, val)
      );
      break;
    case A_FUNC:
      if (placeholder != node->val.func.param) {
        res = ast_new_func(
          node->val.func.param,
          rebind_placeholder(placeholder, node->val.func.body, val)
        );
      }
      break;
    case A_VAR:
      if (node->val.var == placeholder) {
        res = val;
      }
      break;
  }
  return res;
}

// reduce an expression by a single beta-reduction
struct ast_node *single_reduction(struct ast_node *node) {
  if (node->type == A_APP && node->val.app.left->type == A_FUNC) {
    return rebind_placeholder(
      node->val.app.left->val.func.param,
      node->val.app.left->val.func.body,
      node->val.app.right
    );
  }
  return NULL;
}
