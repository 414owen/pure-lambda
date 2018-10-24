#ifndef LAMBDA_AST
#define LAMBDA_AST

enum ast_node_type {
  A_APP,
  A_FUNC,
  A_VAR,
};

struct ast_func {
  char param;
  struct ast_node *body;
};

struct ast_app {
  struct ast_node *left;
  struct ast_node *right;
};

union ast_node_val {
  struct ast_func func;
  struct ast_app app;
  char var;
};

struct ast_node {
  enum ast_node_type type;
  union ast_node_val val;
};

void free_ast(struct ast_node*);
void print_ast(struct ast_node*); 

struct ast_node *ast_new_app(struct ast_node*, struct ast_node*);
struct ast_node *ast_new_func(char, struct ast_node*);
struct ast_node *ast_new_var(char);

#endif
