// symbol table 
#include "hashtable"

#define MAXVARS 255

HTable symtable[MAXVARS];

int sym_put(char* name, Value_t val);
Value_t sym_get(char* name);
