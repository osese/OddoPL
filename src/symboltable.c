#include "symboltable.h"


void sym_put(char* name, Value_t val){
	 table_insert(TCurrent->table, name, val);
}

int sym_update(char* name, Value_t val){
	Value_t k = table_lookup(TCurrent->table, name);
	if(k){ // todo why free
		free(k);
		table_insert(TCurrent->table, name, val);
		return 1;
	}
	return 0;
}

Value_t sym_get(char* name){
	
	Value_t k = table_lookup(TCurrent->table, name);
	if(k == NULL){
		Scope_t parent = TCurrent->parent;
		while(parent && !k){
			k = table_lookup(parent->table, name);
			parent = parent->parent;			
		}	
	}
	return k;
}

#define scope_alloc()\
	(struct scope_list*)malloc(sizeof(struct scope_list))



struct scope_list* initScope(){
	TCurrent = scope_alloc();
	TCurrent->parent = NULL;
	for(int i=0; i<MAXVARS; i++)
		TCurrent->table[i] = NULL;
	return TCurrent;
}

struct scope_list* getCurrentScope(){
	return TCurrent;
}

struct scope_list* createScope(){
	Scope_t s = scope_alloc();
	s->parent = TCurrent;
	for(int i=0; i<MAXVARS; i++){
		s->table[i] = NULL;
	}
	TCurrent = s;
	return s;
}

struct scope_list* freeScope(){	
	if(TCurrent->parent){
		HTable_t* temp = TCurrent->table;
		TCurrent = TCurrent->parent;	
		for(int i=0; i<MAXVARS; i++){
			if(temp[i]){
				list_node_free(temp[i]);
			}
		}
	}
	return TCurrent;
}