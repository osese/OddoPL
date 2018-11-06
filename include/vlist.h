// list for value_t objects 

#ifndef VLIST_T
#define VLIST_T
// @forward_dec
typedef struct _vlist* vlist_t;
#include "object.h"



#define list_value_alloc(X) (value_t*)malloc(sizeof(value_t)*X)
#define list_value_realloc(list, X) (value_t*)realloc(list, sizeof(value_t)*X)

struct _vlist{
  value_t* arr; 
  int size;
  int capacity;
};


#define vlist_alloc()  (struct _vlist*)malloc(sizeof(struct _vlist))

struct _vlist* vlist_create();
struct _vlist* vlist_push(struct _vlist* list, value_t value);
value_t vlist_pop(struct _vlist* list);
value_t vlist_get(struct _vlist* list, int index);
void vlist_free(struct _vlist* list);



#endif 