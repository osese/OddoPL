#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp , memcpy



struct _value *value_create_none() {
  struct _value *t = value_alloc();
  t->type = V_NONE;
  t->ival = 0;
  return t;
}

struct _value *value_create_int(long val) {
  struct _value *v = value_alloc();
  v->type = V_INT;
  v->ival = val;
  return v;
}

struct _value *value_create_double(double val) {
  struct _value *v = value_alloc();
  v->type = V_DOUBLE;
  v->dval = val;
  return v;
}

struct _value *value_create_vstr_c(char *val) {
  struct _value *v = value_alloc();
  v->type = V_STR;
  v->str = v_str_create_from(val);
  return v;
}

struct _value *value_create_vstr(vstr_t vstr) {
  struct _value *v = value_alloc();
  v->type = V_STR;
  v->str = vstr;
  return v;
}

struct _value* value_create_f(vf_t f){
  struct _value *v = value_alloc();
  v->type = V_FUNC;
  v->f = f; 
  return v;
}

struct _value* value_create_vlist(vlist_t list){
  struct _value *v = value_alloc();
  v->type = V_LIST;
  v->list = list; 
  return v;
}

struct _value *value_create(int type, char *value) {
  if (!value) {
    fprintf(stderr, "value is NULL: value_create()\n");
    return NULL;
  }
  struct _value *v = (struct _value *)malloc(sizeof(struct _value));
  v->type = type;
  v->pos = -1;

  if (!v) {
    fprintf(stderr, "Malloc error: value_create()!\n");
    return NULL;
  }

  switch (type) {
  case V_IDENT:
    v->ident = strdup(value);
    break;
  case V_DOUBLE:
    v->dval = atof(value);
    break;
  case V_STR:
    v->str = v_str_create_from(value);
    break;
  case V_INT:
    v->ival = atol(value);
    break;
  case V_BOOL:
    if (strcmp(value, "1") == 0) {
      v->ival = 1;
    } else {
      v->ival = 0;
    }
    break;
  default:
    fprintf(stderr, "Unrecognized variable type!\n");
    break;
  }

  return v;
};

void value_free(struct _value *v1) {
  if (v1) {
    if (v1->type == V_STR) {
      v_str_free(v1->str);
      free(v1);
    } else if (v1->type == V_IDENT) {
      free(v1->ident);
      free(v1);
    } else {
      free(v1);
    }
  }
}

struct _value *_value_copy(struct _value *v1) {
  if (!v1) {
    fprintf(stderr, "Source is null: _value_copy()");
    return NULL;
  }

  struct _value *val = NULL;
  val = value_alloc();

  memcpy((void *)val, (void *)v1, sizeof(struct _value));

  if (val->type == V_STR) {
    val->str = v_str_copy(v1->str);
  }

  return (struct _value *)val;
}

void value_display(struct _value *val) {
  if (!val) {
    fprintf(stderr, "value is NULL: value_display()\n");
    return;
  }

  switch (val->type) {
  case V_DOUBLE:
    printf("%f", val->dval);
    break;
  case V_STR:
    v_str_display(val->str);
    break;
  case V_BOOL:
    if (val->ival) {
      printf("doğru");
    } else {
      printf("yanlış");
    }
    break;
  case V_INT:
    printf("%ld", val->ival);
    break;
  default:
    fprintf(stderr, "Unrecognized variable type!");
    break;
  }
}

struct _value *value_add(struct _value *v1, struct _value *v2) {
  struct _value *temp = NULL;

  if (v_isint(v1) && v_isint(v2)) {
    temp = value_create_int((v1->ival + v2->ival));
  } else if (v_isint(v1) && v_isdouble(v2)) {
    double t = (v2->dval + v1->ival);
    temp = value_create_double(t);
  } else if (v_isdouble(v1) && v_isint(v2)) {
    double t = (v1->dval + v2->ival);
    temp = value_create_double(t);
  } else if (v_isdouble(v1) && v_isdouble(v2)) {
    double t = (v1->dval + v2->dval);
    temp = value_create_double(t);
  } else if (v_isstr(v1) && v_isstr(v2)) {
    temp = value_create_vstr(v_str_add(v1->str, v2->str));
  } else {
    fprintf(stderr, "'+' operatör için yanlış tip.\n");
  }

  return temp;
}

struct _value *value_sub(struct _value *v1, struct _value *v2) {
  struct _value *temp = NULL;

  if (v_isint(v1) && v_isint(v2)) {
    int t = (v1->ival - v2->ival);
    temp = value_create_int(t);
  } else if (v_isint(v1) && v_isdouble(v2)) {
    double t = ((double)v1->ival - v2->dval);
    temp = value_create_double(t);
  } else if (v_isdouble(v1) && v_isint(v2)) {
    double t = (v1->dval - v2->ival);
    temp = value_create_double(t);
  } else if (v_isdouble(v1) && v_isdouble(v2)) {
    double t = (v1->dval - v2->dval);
    temp = value_create_double(t);
  } else {
    fprintf(stderr, "'-' operatörü için yanlış tip.\n");
  }
  return temp;
}
struct _value *value_mod(struct _value *v1, struct _value *v2) {
  struct _value *temp = NULL;

  if (v_isint(v1) && v_isint(v2)) {
    int t = (v1->ival % v2->ival);
    temp = value_create_int(t);
  } else {
    fprintf(stderr, "'-' operatörü için yanlış tip.\n");
  }
  return temp;
}

struct _value *value_mul(struct _value *v1, struct _value *v2) {
  struct _value *temp = NULL;

  if (v_isint(v1) && v_isint(v2)) {
    int t = (v1->ival * v2->ival);
    temp = value_create(V_INT, (void *)&t);
  } else if (v_isint(v1) && v_isdouble(v2)) {
    double t = ((double)v1->ival * v2->dval);
    temp = value_create(V_DOUBLE, (void *)&t);
  } else if (v_isdouble(v1) && v_isint(v2)) {
    double t = (v1->dval * v2->ival);
    temp = value_create(V_DOUBLE, (void *)&t);
  } else if (v_isdouble(v1) && v_isdouble(v2)) {
    double t = (v1->dval * v2->dval);
    temp = value_create(V_DOUBLE, (void *)&t);
  } else {
    fprintf(stderr, "'*' operatör için yanlış tip.\n");
  }
  return temp;
}

struct _value *value_div(struct _value *v1, struct _value *v2) {
  struct _value *temp = NULL;
  if (v_isnumeric(v2)) {
    if (v2->ival == 0 || v2->dval == 0) {
      fprintf(stderr, "Sıfıra bölme hatası.");
      return NULL;
    }
  }
  if (v_isint(v1) && v_isint(v2)) {
    double t = ((double)v1->ival / (double)v2->ival);
    temp = value_create(V_INT, (void *)&t);
  } else if (v_isint(v1) && v_isdouble(v2)) {
    double t = ((double)v1->ival / v2->dval);
    temp = value_create(V_DOUBLE, (void *)&t);
  } else if (v_isdouble(v1) && v_isint(v2)) {
    double t = (v1->dval / v2->ival);
    temp = value_create(V_DOUBLE, (void *)&t);
  } else if (v_isdouble(v1) && v_isdouble(v2)) {
    double t = (v1->dval / v2->dval);
    temp = value_create(V_DOUBLE, (void *)&t);
  } else {
    fprintf(stderr, "'+' operatörü için yanlış tip.\n");
  }

  return temp;
}

struct _value *value_uminus(struct _value *v1) {
  struct _value *temp = NULL;
  if (v_isint(v1)) { // int ve bool
    int k = -(v1->ival);
    temp = value_create(V_INT, (void *)&k);
  } else if (v_isdouble(v1)) {
    double k = -(v1->dval);
    temp = value_create(V_DOUBLE, (void *)&k);
  } else {
    fprintf(stderr, "'-' operatörü için yanlış tip.\n");
  }
  return temp;
}

int value_cmp(struct _value *v1, struct _value *v2) {
  if (v_iseq(v1, v2)) {
    if (v_isbool(v1)) {
      if (v1->ival == v2->ival)
        return 0;
      return -2;
    }
    if (v_isint(v1)) {
      if (v1->ival == v2->ival)
        return 0;
      if (v1->ival < v2->ival)
        return -1;
      if (v1->ival > v2->ival)
        return 1;
    }
    if (v_isdouble(v1)) {
      if (v1->dval == v2->dval)
        return 0;
      if (v1->dval < v2->dval)
        return -1;
      if (v1->dval > v2->dval)
        return 1;
    }
    if (v_isstr(v1))
      return v_str_cmp(v1->str, v2->str);
  }

  return -2;
}

struct _value *value_and(struct _value *v1, struct _value *v2) {
  if (v_isint(v1)) {
    if (v1->ival)
      return v2;
    return v1;
  }
  if (v_isdouble(v1)) {
    if (v1->dval)
      return v2;
    return v1;
  }

  if (v_isstr(v1)) {
    if (v1->str)
      return v2;
    return v1;
  }
}

struct _value *value_or(struct _value *v1, struct _value *v2) {
  if (v_isint(v1)) {
    if (v1->ival)
      return v1;
    return v2;
  }
  if (v_isdouble(v1)) {
    if (v1->dval)
      return v1;
    return v2;
  }

  if (v_isstr(v1)) {
    if (v1->str)
      return v1;
    return v2;
  }
}

struct _value *value_not(struct _value *v1) {
  int d = 1;
  struct _value *val = NULL;

  if (v_isint(v1)) {
    if (v1->ival)
      d = 0;
  }
  if (v_isdouble(v1)) {
    if (v1->dval)
      d = 0;
  }

  if (v_isstr(v1)) {
    if (v1->str)
      d = 0;
  }

  val = value_create_int(d);
  return val;
}

struct _value *value_g(struct _value *v1, struct _value *v2) {
  struct _value *val = NULL;
  int k = value_cmp(v1, v2);
  if (k == 1)
    k = 1;
  else
    k = 0;

  val = value_create_int(k);
  return val;
}

struct _value *value_lt(struct _value *v1, struct _value *v2) {
  struct _value *val = NULL;
  int k = value_cmp(v1, v2);
  if (k == 1 || k == 0)
    k = 0;
  else
    k = 1;
  val = value_create_int(k);
  return val;
}

struct _value *value_lte(struct _value *v1, struct _value *v2) {
  struct _value *val = NULL;
  int k = value_cmp(v1, v2);
  if (k == 1)
    k = 0;
  else
    k = 1;

  val = value_create_int(k);
  return val;
}

struct _value *value_ge(struct _value *v1, struct _value *v2) {
  struct _value *val = NULL;
  int k = value_cmp(v1, v2);
  if (k != -1)
    k = 1;
  else
    k = 0;

  val = value_create_int(k);
  return val;
}

struct _value *value_ee(struct _value *v1, struct _value *v2) {
  struct _value *val = NULL;
  int k = value_cmp(v1, v2);
  if (k == 0)
    k = 1;
  else
    k = 0;

  val = value_create_int(k);
  return val;
}

struct _value *value_ne(struct _value *v1, struct _value *v2) {
  struct _value *val = NULL;
  int k = value_cmp(v1, v2);
  if (k != 0)
    k = 1;
  else
    k = 0;

  val = value_create_int(k);
  return val;
}
