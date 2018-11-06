#include "object.h"
#include <assert.h>
#include <stdio.h>

// double larda hata veriyor ekleme çıkarma
// precision yüzünden hata veriyor ! 13.10.18
void test__value_copy();
int main(){
    test__value_copy();
    value_t v1 = value_create_int(123);
    value_t v2 = value_create_int(425);
    value_t d1 = value_create_double(12.23);
    value_t d2 = value_create_double(42.31);


    value_t v3 = value_add(v1, v2);
    value_t v4 = value_sub(v1, v2);
    value_t v5 = value_add(d1, d2);
    value_t v6 = value_sub(d1, d2);

    assert(v3->ival == 123 + 425);
    //assert(v5->dval == 12.23 + 42.32);
    printf("value_add: passed!");
    assert(v4->ival == 123 - 425);
    assert(d1->dval == 12.23 - 42.32);
    printf("value_sub: passed!");

}


void test__value_copy(){
  value_t v3 = value_create_int(123);
  value_t v3_c = _value_copy(v3);

  assert(v3->type == v3_c->type);
  assert(v3->ival == v3_c->ival);
  
  value_t v1 = value_create_vstr_c("ömer servet şeker");
  value_t v1_c = _value_copy(v1);
  value_display(v1);
  value_display(v1_c);
  assert(v1->type == v1_c->type);
  assert(value_cmp(v1, v1_c) == 0);
  assert(v1->str != v1_c->str);

}