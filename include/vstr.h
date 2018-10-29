#ifndef V_STRING
#define V_STRING 

#include <stdlib.h>
#include <stdio.h>

#define v_str_g_size(X)\
    X->size

#define v_str_alloc()\
    (struct v_str*)malloc(sizeof(struct v_str))

#define v_char_alloc(X)\
    (char*)malloc(sizeof(char)*X)

struct v_str{
    char* str;
    int size;    // Tek byte karakterlerin sayısı 
    int length;  // Çoklu bytelar 'tek' kabul edilen karakter sayısı 
};


struct v_str* v_str_create();
struct v_str* v_str_create_from(const char* str);
struct v_str* v_str_copy(struct v_str* str);
struct v_str* v_str_add(struct v_str* v1, struct v_str* v2);
void v_str_free(struct v_str* v1);
struct v_str* v_str_at(struct v_str* v1, int index);
struct v_str* v_str_at_from_to(struct v_str* v1, int begin, int end);
int v_str_len(struct v_str* v1);

/*
    @return 
        eşitse : 0
        1.büyükse: 1
        2.büyükse: -1
        herhangi biri null ise : -2
*/
int v_str_cmp(struct v_str* v1, struct v_str* v2);



void v_str_display(struct v_str* v1);

   
typedef struct v_str* vstr_t;

#endif 


