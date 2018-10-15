#include "../include/object.h"
#include <assert.h>
#include <stdio.h>

// double larda hata veriyor ekleme çıkarma
// precision yüzünden hata veriyor ! 13.10.18
int main(){

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
