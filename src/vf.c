#include "vf.h"


struct _vf* vf_create(int bas, int bit, vlist_t params, int paramlen, int ret){
  struct _vf* f = vf_alloc();
  f->bas = bas;
  f->bit = bit;
  f->params = params;
  f->paramlen = paramlen;
  f->ret = ret;
  return f;
}

