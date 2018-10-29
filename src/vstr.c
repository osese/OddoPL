#include "vstr.h"
#include <string.h>	 // strcmp , memcpy

#define _bit_8(x) x >> 7
#define _bit_7(x) (((x >> 7) << 7) ^ x) >> 6
#define _bit_6(x) (((x >> 6) << 6) ^ x) >> 5
#define _bit_5(x) (((x >> 5) << 5) ^ x) >> 4
#define _bit_4(x) (((x >> 4) << 4) ^ x) >> 3
#define _bit_3(x) (((x >> 3) << 3) ^ x) >> 2
#define _bit_2(x) (((x >> 2) << 2) ^ x) >> 1
#define _bit_1(x) ((x >> 1) << 1) ^ x

#define is_utf8_3(x) (x >> 3 == 22)
#define is_utf8_2(x) (x >> 4 == 14)
#define is_utf8_1(x) (x >> 5 == 6)


struct v_str *v_str_create() {
  struct v_str *s = v_str_alloc();
  s->size = 0;
  s->length = 0;
  s->str = NULL;
  return s;
}

struct v_str *v_str_create_from(const char *str) {
  struct v_str *s = v_str_alloc();
  int size = 0;
  int len = 0;

  while (1) {
    
    if (str[size++] == '\0') {
      
      break;
    }
    unsigned char t = str[size];

    if(is_utf8_3(t)){ 
      len -= 3;
    }else if(is_utf8_2(t)){
      len -= 2;
    }else if(is_utf8_1(t)){
      len -= 1;
    }
  }

  s->size = size - 1;
  s->length = s->size + len;
  s->str = v_char_alloc(size);
  for (int i = 0; i < size; i++) {
    s->str[i] = str[i];
  }
  return s;
}

struct v_str* v_str_copy(struct v_str* str){
  struct v_str* vstr = v_str_alloc();
  vstr->str = v_char_alloc(str->size);
  memcpy(vstr->str, str->str, str->size);

  vstr->size = str->size;
  vstr->length = str->length;
  return vstr;
}

struct v_str *v_str_add(struct v_str *v1, struct v_str *v2) {
  struct v_str *t = v_str_alloc();
  t->size = v1->size + v2->size;
  t->length = v1->length + v2->length;
  
  t->str = v_char_alloc(t->size);
  for (int i = 0; i < v1->size; i++) {
    t->str[i] = v1->str[i];
  }
  for (int j = v1->size; j < v1->size + v2->size; j++) {
    t->str[j] = v2->str[j - v1->size];
  }
  return t;
}

int v_str_len(struct v_str *v1) {
  int l = 0;
  if (v1) {
    for (int i = 0; i < v1->size; i++) {
      unsigned char t = (unsigned char)v1->str[i];
      if(is_utf8_3(t)){ 
        i += 3;
      }else if(is_utf8_2(t)){
        i += 2;
      }else if(is_utf8_1(t)){
        i += 1;
      }
      l += 1;
    }
  }
  return l;
}

void v_str_free(struct v_str *v1) {
  if (v1) {
    if (v1->str) {
      free(v1->str);
    }
    free(v1);
  }
}

struct v_str *v_str_at(struct v_str *v1, int index) {
  struct v_str *v = v_str_create();
  if (index >= 0 && index < v1->size) {
    v->str = v_char_alloc(1);
    v->size = 1;
    v->str[0] = v1->str[index];
  } else {
    // error index out of range
    // or just undefined ki benim en sevdiğim.
  }
  return v;
}

struct v_str *v_str_at_from_to(struct v_str *v1, int begin, int end) {
  struct v_str *v = v_str_create();
  if (begin < 0 || end >= v1->size) {
    // error
    return v;
  }
  v->str = v_char_alloc(end - begin);
  v->size = end - begin;

  for (int i = begin; i < end; i++) {
    v->str[i - begin] = v1->str[i];
  }
  return v;
}

int v_str_cmp(struct v_str *v1, struct v_str *v2) {
  // todo string karşılaştırma olayını kontrol et.
  if (!v1 && !v2) {
    return -2;
  }

  int len = v1->size > v2->size ? v2->size : v1->size;

  for (int i = 0; i < len; i++) {
    if (v1->str[i] > v2->str[i]) {
      return 1;
    } else if (v2->str[i] > v1->str[i]) {
      return -1;
    }
  }
  if (v1->size == v2->size) {
    return 0;
  }
  if (v1->size > v2->size) {
    return 1;
  }
  return -1;
}

void v_str_display(struct v_str *v1) {
  for (int i = 0; i < v1->size; i++) putchar(v1->str[i]);
}
