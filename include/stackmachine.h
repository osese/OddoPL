#ifndef STACKMACHINE
#define STACKMACHINE
#include "object.h"
// stack machine


// runtime stack
value_t stack[10000];
static int top = -1;

void push_stack(value_t var);
int print_eval_loop();

int fetch_execute_cycle();

#endif
