#ifndef LAMBDA_STACK_H
#define LAMBDA_STACK_H

struct stack {
  unsigned val;
  struct stack *next;
};

struct stack *new_stack(void);
unsigned stack_pop(struct stack*);
struct stack *stack_push(struct stack *old, unsigned val);

#endif
