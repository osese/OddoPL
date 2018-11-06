#include <assert.h>
#include <stdio.h>
#include "hashtable.h"


void test_first();
void test_table_copy();

int main() {
  test_first();
  test_table_copy();
}

void test_first() {
  HTable_t table[255] = {NULL};
  value_t v1 = value_create_int(23);
  const char *omer = "omer";

  table_insert(table, omer, v1);
  table_insert(table, "merhaba", v1);

  value_t v2 = table_lookup(table, omer);
  value_t v3 = table_lookup(table, "merhaba");
  assert(v1->type == v2->type);
  assert(v1->ival == v2->ival);
  assert(v1->ival == v3->ival);
}

void test_table_copy() {
  HTable_t table[255] = {NULL};
  value_t v1 = value_create_int(23);
  value_t v2 = value_create_vstr_c("ömer servet");
  table_insert(table, "omer", v1);
  table_insert(table, "merhaba", v2);

  HTable_t* tc = table_copy(table, 255);

  assert(table_lookup(tc, "omer") == table_lookup(table, "omer"));
  assert(table_lookup(tc, "merhaba") !=
         table_lookup(table, "merhaba"));  // pointerlar eşit olmayacak
  assert(value_cmp(table_lookup(tc, "merhaba"),
                     table_lookup(table, "merhaba")) ==
         0);  // ama değerler eşit olacak
}