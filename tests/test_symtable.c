#include "symboltable.h"
#include <assert.h>

void test_first();
void test_multiple_scopes();
int main(){

  initScope();
  // test_first();
  test_multiple_scopes();

  return 0;
}


void test_first(){
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

  createScope();
  // scopedan sonra parent scope dan okuyabiliyor mu ? 
  Value_t p4 = sym_get("omer");
  assert(p4 != NULL); 
  assert(p4->type == t2->type);
  assert(p4->ival == t2->ival);
  
  sym_put("servet", t);
  Value_t p5 = sym_get("servet");

  assert(p5->type == t->type);
  assert(p5->ival == t->ival);  
  freeScope();

  // scopedan çıktıktan sonra scope siliniyor mu ? 
  p5 = sym_get("servet");
  assert(p5 == NULL);


}


void test_multiple_scopes(){
  Value_t a = value_t_create_int(1);
  sym_put("a", a);
  Value_t b = value_t_create_int(2);
  sym_put("b", b);

  createScope();
  
  Value_t aa = sym_get("a");
  assert(aa->ival == a->ival);
  assert(aa->type == a->type);
  
  Value_t a2 = value_t_create_int(11);
  sym_put("a2", a2);

  createScope();
  Value_t aaa2 = sym_get("a2");
  assert(a2->ival == aaa2->ival);
  assert(a2->type == aaa2->type);
  
  freeScope();
  aa = sym_get("a");
  assert(aa->ival == a->ival);
  assert(aa->type == a->type);

  freeScope();

  Value_t ar = sym_get("a");
  Value_t br = sym_get("b");
  assert(a->ival == ar->ival);
  assert(a->type == ar->type);

  assert(b->ival == br->ival);
  assert(b->type == br->type);

}