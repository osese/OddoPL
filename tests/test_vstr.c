#include "../include/vstr.h"
#include <stdio.h>
#include <assert.h>

void test_v_str_at();
void test_v_str_add();
void test_v_str_cmp();
void test_v_str_at_from_to();
void test_v_str_display();
void test_v_str_free(); // WARN. bunun testini pek yapamadım.
void test_v_str_len();

int main(){

    test_v_str_cmp();
    test_v_str_add();
    test_v_str_at();
    test_v_str_display();
    test_v_str_at_from_to();
    test_v_str_free();
    test_v_str_len();
    return 0;
}


void test_v_str_add(){
    vstr_t t  = v_str_create_from("omer servet"); 
    vstr_t t2 = v_str_create_from("seker"); 
    vstr_t t3 = v_str_add(t, t2);

    assert(t3->size == 16);
    assert(v_str_cmp(t3, v_str_create_from("omer servetseker")) == 0);
}

void test_v_str_cmp(){
    vstr_t v1 = v_str_create_from("omer servet"); 
    vstr_t v2 = v_str_create_from("omer servet"); 
    vstr_t v3 = v_str_create_from("omer"); 
    assert(v_str_cmp(v1, v2) == 0);
    assert(v_str_cmp(v1, v3) == 1);
    assert(v_str_cmp(v3, v1) == -1);
}

void test_v_str_display(){
    vstr_t t  = v_str_create_from("omer servet");
    for(int i=0; i<t->size; i++){
        v_str_display(v_str_at(t,i));
    }
}

void test_v_str_at(){
    vstr_t t  = v_str_create_from("omer servet");
    assert(v_str_cmp(v_str_at(t, 0), v_str_create_from("o")) != 1);
    assert(v_str_cmp( v_str_at(t, 10), v_str_create_from("t")) == 0);
    assert(v_str_cmp( v_str_at(t, 4), v_str_create_from(" ")) == 0);
}

void test_v_str_at_from_to(){
    vstr_t v1 = v_str_create_from("omer servet"); 
    assert(v_str_cmp(v_str_at_from_to(v1, 0, 4), v_str_create_from("omer")) == 0);
    assert(v_str_cmp(v_str_at_from_to(v1, 0, 3), v_str_create_from("omer ")) != 0);
}

void test_v_str_free(){
    vstr_t v1 = v_str_create_from("omer babba");
    char* p = v1->str;
    v_str_free(v1);
    assert(1 == 1);
}

void test_v_str_len(){
    /* 
    Each octak or hexadecimal escape sequence is 
    the longest sequence of characters that can constitue the 
    escape sequence. */ 
    /* bu yüzden \xc5\x9feker yazamadık. \xc5\x9f\x65ker yazdık. */

    vstr_t v1 = v_str_create_from("\xc3\xb6mereker");
    
    assert(v1->size == 9);
    assert(v_str_len(v1) == 8);
    vstr_t v2 = v_str_create_from("\xc3\xb6mer\xc5\x9f\x65ker");
    v_str_display(v2);
    assert(v2->size == 11);
    assert(v_str_len(v2) == 9);
    v_str_display(v2);

}