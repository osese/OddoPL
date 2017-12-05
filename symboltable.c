#include "symboltable.h"


void sym_put(char* name, Value_t val){
	 table_insert(symtable, name, val);
}

void sym_update(char* name, Value_t val){
	Value_t k = table_lookup(symtable, name, val);
	if(k){
		free(k);
		table_insert(name, val);
		return 1;
	}
	return 0;
}

Value_t sym_get(char* name){
	return table_lookup(symtable, name);
}
