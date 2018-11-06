#ifndef SYM_TABLE
#define SYM_TABLE
// symbol table
#include "hashtable.h"
#include "object.h"
#include <stdio.h>

#define MAXVARS 255




struct scope_list{
  struct scope_list* parent;
  HTable_t table[MAXVARS];
};

static struct scope_list* TCurrent = NULL;

struct scope_list* getCurrentScope();
struct scope_list* createScope();
struct scope_list* freeScope();
struct scope_list* initScope();

typedef struct scope_list* Scope_t; 
void sym_put(char* name, value_t val);
value_t sym_get(char* name);
#endif
