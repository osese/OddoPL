#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/hash.h"
#include "include/hashtable.h"

#define GUNCELLE(node) \
            node->value = value;\

#if DEBUG
	extern int number_of_collisions;
#endif


struct list_node*
create_list_node(const char* name, Value_t value){
    struct list_node* node = (struct list_node*)malloc(sizeof(struct list_node));
    if(!node){
        fprintf(stderr, "Malloc failed");
        return NULL;
    }
    node->next = NULL;
    node->name= strdup(name);
    node->value = value;
}

void
table_insert(struct list_node** table,
		const char* name,
		Value_t value)
{
    unsigned key = hash(name);
    if(table[key]){

		#if DEBUG
			number_of_collisions++;
		#endif

        
        struct list_node* node = table[key];
        if(!node->next)
            GUNCELLE(node);
        
        while(node->next){
            if(strcmp(node->name, name) == 0){ // check duplicate
                // değeri güncelleyebilir. 
                GUNCELLE(node);
                return;
            }
            node = node->next;
        }

		node->next = create_list_node(name, value);
        return ;
    }

    table[key] = create_list_node(name, value);
};


Value_t
table_lookup(struct list_node** table, const char* name){

    unsigned key = hash(name);
    struct list_node* node = table[key];

    while(node){
        if(strcmp(node->name, name) == 0){
            return node->value;
        }
        node = node->next;
    }

    return 0;
}

void table_delete(struct list_node** table, const char* name){

    unsigned key = hash(name);
    struct list_node* node = table[key];

    if(!table[key]){   // not found
        fprintf(stderr, "There is no such entry: %s\n", name);
        return;
    }

    if(node){
        if(node->next == NULL){
            node = NULL;
        }else{
            while(node){
                if( strcmp(node->next->name, name) == 0 ){
                    struct list_node* temp = node->next->next;
                    node->next = temp;
                    break;
                }
                node = node->next;
            }
        }
    }
}
