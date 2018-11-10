#include <stdlib.h>
#include "stack.h"

struct stack *stack_push(struct stack *old, unsigned val) {
  struct stack *res = malloc(sizeof(struct stack));
  res->val = val;
  res->next = old;
  return res;
}

struct stack *new_stack(void) {
  return stack_push(NULL, 0);
}

unsigned stack_pop(struct stack *top) {
  unsigned res = top->val;
  if (top->next) {
    top->val = top->next->val;
    top->next = top->next->next;
  } else {
    top->next = NULL;
  }
  return res;
}
