#include "vlist.h"

int main(){


  vlist_t list = vlist_create();
  for(int xx=0; xx<10000; xx++){
      list = vlist_create();
      for(int i=0; i<1000; i++){
        vlist_push(list, value_create_int(i));
      } 

      for(int i=0; i<31; i++){
        vlist_push(list, value_create_vstr_c("omer"));
      } 
      for(int i=0; i<31; i++){
        vlist_push(list, value_create_double(i*0.1));
      } 
      for(int i=0; i < list->size; i++){
        value_display(vlist_get(list, i));
      }
      vlist_free(list);
  }
  
  return 0;
}