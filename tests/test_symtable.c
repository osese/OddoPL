#include "../include/symboltable.h"
#include <assert.h>


int main(){
    Value_t t = value_t_create_int(12);

    Value_t t2 = value_t_create_int(112);

    sym_put("omer", t);
    sym_put("namik", t);

    Value_t p = sym_get("omer");
    Value_t p2 = sym_get("namik");

    assert(p->type == t->type);
    assert(p->ival == t->ival);
    assert(p2->ival == t->ival);

    sym_put("omer", t2);

    Value_t p3 = sym_get("omer");

    assert(p->ival != p3->ival);

    return 0;
}
