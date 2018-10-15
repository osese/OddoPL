#include "include/symboltable.h"

// all elements in table should be null at first place
HTable symtable[MAXVARS] = {NULL};

void sym_put(char* name, Value_t val){
	 table_insert(symtable, name, val);
}

int sym_update(char* name, Value_t val){
	Value_t k = table_lookup(symtable, name);
	if(k){ // todo why free
		free(k);
		table_insert(symtable, name, val);
		return 1;
	}
	return 0;
}

Value_t sym_get(char* name){
	return table_lookup(symtable, name);
}
