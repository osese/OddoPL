#ifndef VF_H
#define VF_H

// @forward_dec
typedef struct _vf* vf_t; 
#include "vlist.h"



/*
  bas: başlangıç kod indexi
  bit: bitiş kod indexi
  params: parametreler
  paramlen: parametre sayısı 
  ret: döneceği index
*/
struct _vf{
  int bas;
  int bit;
  vlist_t params;
  int paramlen;
  int ret;
};

#define vf_alloc() (struct _vf*)malloc(sizeof(struct _vf))

struct _vf* vf_create(int bas, int bit, vlist_t params, int paramlen, int ret);

#endif 