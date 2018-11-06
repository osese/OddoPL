#include "vlist.h"




struct _vlist* vlist_create(){
  struct _vlist* list = vlist_alloc();
  list->size = 0;
  list->capacity = 2; 
  list->arr = list_value_alloc(2);
}


struct _vlist* vlist_push(struct _vlist* list, value_t value){
  if(list->capacity == list->size){
    list->arr = list_value_realloc(list->arr, list->capacity*2);
    list->capacity *= 2;
  }
  list->arr[list->size++] = value;
}

value_t vlist_pop(struct _vlist* list){
  return  list->arr[--list->size];
}

value_t vlist_get(struct _vlist* list, int index){
  return list->arr[index];
}

void vlist_free(struct _vlist* list){ 
  for(int i=0; i<list->size; i++){
    value_free(list->arr[i]);
  }
  free(list->arr);
  free(list);
}