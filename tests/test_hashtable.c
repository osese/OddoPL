#include<stdio.h>
#include "../include/hashtable.h"
#include <assert.h>

int main(){
  HTable table[255] = {NULL};
  Value_t v1 = value_t_create_int(23);
  const char* omer = "omer";
  
  table_insert(table, omer , v1);
  table_insert(table, "merhaba", v1);

  Value_t v2 = table_lookup(table, omer);
  Value_t v3 = table_lookup(table, "merhaba");
  assert(v1->type == v2->type);
  assert(v1->ival == v2->ival);
  assert(v1->ival == v3->ival);

}
