#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "hashtable.h"

#define GUNCELLE(node) node->value = value;

#if DEBUG
extern int number_of_collisions;
#endif

struct list_node* create_list_node(const char* name, value_t value) {
  struct list_node* node = (struct list_node*)malloc(sizeof(struct list_node));
  if (!node) {
    fprintf(stderr, "Malloc failed");
    return NULL;
  }
  node->next = NULL;
  node->name = strdup(name);
  node->value = value;
  return node;
}

void table_insert(struct list_node** table, const char* name, value_t value) {
  unsigned key = hash(name);
  if (table[key]) {
  #if DEBUG
      number_of_collisions++;
  #endif

    struct list_node* node = table[key];
    if (!node->next) GUNCELLE(node);

    while (node->next) {
      if (strcmp(node->name, name) == 0) {  // check duplicate
        // değeri güncelleyebilir.
        GUNCELLE(node);
        return;
      }
      node = node->next;
    }

    node->next = create_list_node(name, value);
    return;
  }

  table[key] = create_list_node(name, value);
};

value_t table_lookup(struct list_node** table, const char* name) {
  unsigned key = hash(name);
  struct list_node* node = table[key];

  while (node) {
    if (strcmp(node->name, name) == 0) {
      return node->value;
    }
    node = node->next;
  }

  return 0;
}

void table_delete(struct list_node** table, const char* name) {
  unsigned key = hash(name);
  struct list_node* node = table[key];

  if (!table[key]) {  // not found
    fprintf(stderr, "There is no such entry: %s\n", name);
    return;
  }

  if (node) {
    if (node->next == NULL) {
      node = NULL;
    } else {
      while (node) {
        if (strcmp(node->next->name, name) == 0) {
          struct list_node* temp = node->next->next;
          node->next = temp;
          break;
        }
        node = node->next;
      }
    }
  }
}

struct list_node* list_node_copy(struct list_node* node){
  struct list_node* newnode = NULL;
  if(node){
    newnode = (struct list_node*)malloc(sizeof(struct list_node));
    newnode->name = node->name;
    newnode->value = _value_copy(node->value);
  }
  return newnode;
}

struct list_node** table_copy(struct list_node** table, int size) {
  struct list_node** newtable = (struct list_node**)malloc(sizeof(struct list_node*));
  for(int i=0; i<size; i++){
    if(table[i]){
      newtable[i] = list_node_copy(table[i]);
      struct list_node* ntemp = newtable[i];
      struct list_node* temp = table[i];
      while(temp->next){
        ntemp->next = list_node_copy(temp->next);
        temp = temp->next;
        ntemp = ntemp->next;
      }
    }else{
      newtable[i] = NULL;
    }
  }
  return newtable;
}


void list_node_free(struct list_node* node){
  if(node){
    value_t tv = node->value;
    char* name = node->name;  
    list_node_free(node->next);
    _value_free(tv);
    free(name);
  }
}