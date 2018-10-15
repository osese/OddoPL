#ifndef STACKMACHINE
#define STACKMACHINE
#include "object.h"
// stack machine


// runtime stack
Value_t stack[10000];
static int top = -1;

void push_stack(Value_t var);
int print_eval_loop();

int fetch_execute_cycle();

#endif
