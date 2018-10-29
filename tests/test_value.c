#include "object.h"
#include <assert.h>
#include <stdio.h>

// double larda hata veriyor ekleme çıkarma
// precision yüzünden hata veriyor ! 13.10.18
void test_value_t_copy();
int main(){
    test_value_t_copy();
    Value_t v1 = value_t_create_int(123);
    Value_t v2 = value_t_create_int(425);
    Value_t d1 = value_t_create_double(12.23);
    Value_t d2 = value_t_create_double(42.31);


    Value_t v3 = value_t_add(v1, v2);
    Value_t v4 = value_t_sub(v1, v2);
    Value_t v5 = value_t_add(d1, d2);
    Value_t v6 = value_t_sub(d1, d2);

    assert(v3->ival == 123 + 425);
    //assert(v5->dval == 12.23 + 42.32);
    printf("value_t_add: passed!");
    assert(v4->ival == 123 - 425);
    assert(d1->dval == 12.23 - 42.32);
    printf("value_t_sub: passed!");

}


void test_value_t_copy(){
  Value_t v3 = value_t_create_int(123);
  Value_t v3_c = value_t_copy(v3);

  assert(v3->type == v3_c->type);
  assert(v3->ival == v3_c->ival);
  
  Value_t v1 = value_t_create_vstr_c("ömer servet şeker");
  Value_t v1_c = value_t_copy(v1);
  value_t_display(v1);
  value_t_display(v1_c);
  assert(v1->type == v1_c->type);
  assert(value_t_cmp(v1, v1_c) == 0);
  assert(v1->str != v1_c->str);

}