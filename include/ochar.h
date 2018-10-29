#ifndef OCHAR
#define OCHAR
#include <stdio.h>
#include <stdlib.h>

struct ochar {
  unsigned char ch[4];
  int used;
};

typedef struct ochar* ochar_t;

#define ochar_alloc() (ochar_t) malloc(sizeof(struct ochar))

void ochar_display(ochar_t oc) {
  for (int i = 0; i < oc->used; i++) {
    putchar(oc->ch[i]);
  }
}

ochar_t ochar_create(char t) { 
  ochar_t a = ochar_alloc(); 
  a->ch[0] = t;
  a->used = 1;
}

// multichar 
ochar_t ochar_create_m(char* t, int len){
  ochar_t a = ochar_alloc(); 
  if(len > 4){
    fprintf(stderr, "böyle bir karakter tanımıyorum.\n");
    exit(1);
  } 
  
  for(int i=0; i<len; i++){
    a->ch[i] = t[i];
  }
  a->used = len;
  return a;
}
#endif