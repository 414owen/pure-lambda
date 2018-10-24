#include <stdbool.h>
#include <stdio.h>
#include "ast.h"
#include "eval.h"

struct single_reduction_result {
  bool reduced;
  struct ast_node *val;
};

struct ast_node *rebind_placeholder(
  char placeholder,
  struct ast_node *left,
  struct ast_node *val
) {
  struct ast_node *res;
  switch (left->type) {
    case A_APP:
      res = ast_new_app(
        rebind_placeholder(placeholder, left->val.app.left, val),
        rebind_placeholder(placeholder, left->val.app.left, val)
      );
      break;
    case A_FUNC:
      if (placeholder == left->val.func.param) {
        res = left;
      } else {
        res = ast_new_func(
          res->val.func.param,
          rebind_placeholder(placeholder, res->val.func.body, val)
        );
      }
      break;
    case A_VAR:
      res = val;
      break;
  }
  return res;
}

// reduce an expression by a single beta-reduction
struct single_reduction_result eval_step_rec(struct ast_node *node) {
  struct single_reduction_result res, sub;
  switch (node->type) {
    case A_APP:
      if (node->val.app.left->type == A_FUNC) {
        res.reduced = true;
        res.val = rebind_placeholder(
          node->val.app.left->val.func.param,
          node->val.app.left->val.func.body,
          node->val.app.right
        );
      } else {
        sub = eval_step_rec(node->val.app.left);
        if (sub.reduced) {
          res.reduced = true;
          res.val = ast_new_app(sub.val, node->val.app.right);
        } else {
          sub = eval_step_rec(node->val.app.right);
          if (sub.reduced) {
            res.reduced = true;
            res.val = ast_new_app( node->val.app.left, sub.val);
          } else {
            sub.reduced = false;
            sub.val = node;
          }
        }
      }
      break;
    case A_FUNC:
      sub = eval_step_rec(node->val.func.body);
      res.reduced = sub.reduced;
      if (sub.reduced) {
        res.val = ast_new_func(node->val.func.param, sub.val);
      } else {
        res.val = node;
      }
      break;
    case A_VAR:
      res.reduced = false;
      res.val = node;
      break;
  }
  return res;
}

struct ast_node *single_reduction(struct ast_node *node) {
  struct single_reduction_result res = eval_step_rec(node);
  if (res.reduced) return res.val;
  return NULL;
}
