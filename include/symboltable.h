#ifndef SYM_TABLE
#define SYM_TABLE
// symbol table
#include "hashtable.h"
#include "object.h"
#include <stdio.h>

#define MAXVARS 255

void sym_put(char* name, Value_t val);
Value_t sym_get(char* name);

#endif
