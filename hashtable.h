#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include<inttypes.h>
#include "object.h"


struct list_node{   
    struct list_node* next;
    char* name;
    Value_t value;
};

struct list_node* create_list_node(const char*, Value_t);
void table_insert(struct list_node**, const char*, Value_t);
void table_delete(struct list_node**, const char*);
Value_t table_lookup(struct list_node**, const char *);

typedef struct list_node* HTable;

#endif /* HashTable.h */ 
