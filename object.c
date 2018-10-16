#include "include/object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	 // strcmp , memcpy

#define rmvquotes(str, n) \
	str[n-1] = '\0';\
	++str;


static char* makestr(char* str){
	
	int i = 1;
	int j = 0;
	int n = strlen(str);
	str[n-1] = '\0';
	char* res = (char*)malloc(n-1);

	while(str[i] != '\0'){
		if(str[i] == '\\'){
			i = i + 1;
			if(str[i] == 'n'){
				*(res+j) = '\n';
			}else if(str[i] == 't'){
				*(res+j) = '\t';
			}else if(str[i] == '\\'){
				*(res+j) = '\\';
			}
		}else{
			*(res+j) = str[i];
		}
		j += 1;
		i += 1;
	}
	*(res+j) = '\0';
	return res;
}

struct value_t* value_t_alloc(){
	struct value_t* v = (struct value_t*)malloc(sizeof(struct value_t));
	if(!v){
		fprintf(stderr, "Malloc error: value_t_create()!\n");
		return NULL;
	}
	return v;
}

struct value_t* value_t_create_none(){
	struct value_t*  t = value_t_alloc();
	t->type = V_NONE;
	t->ival = 0;
	return t;
}

struct value_t* value_t_create_int(long val){
	struct value_t* v = value_t_alloc();
	v->type = V_INT;
	v->ival = val;
	return v;
}

struct value_t* value_t_create_double(double val){
	struct value_t* v = value_t_alloc();
	v->type = V_DOUBLE;
	v->dval = val;
	return v;
}

struct value_t* value_t_create_str(char* val){
	
	struct value_t* v = value_t_alloc();
	v->type = V_STR;
	v->sval = makestr(val);
	
	return v;
}


struct value_t*
value_t_create(int type, char* value){
	if(!value){
		fprintf(stderr, "value is NULL: value_t_create()\n");
		return NULL;
	}
	struct value_t* v = (struct value_t*)malloc(sizeof(struct value_t));
	v->type = type;
	v->pos = -1;

	if(!v){
		fprintf(stderr, "Malloc error: value_t_create()!\n");
		return NULL;
	}

	switch(type){
		case V_IDENT:
			v->sval = strdup(value);
			break;
		case V_DOUBLE:
			v->dval = atof(value);
			break;
		case V_STR:
			v->sval = strdup(value);
			break;
		case V_INT:
			v->ival = atol(value);
			break;
		case V_BOOL:
			if(strcmp(value, "1") == 0){
				v->ival = 1;
			}else{
				v->ival = 0;
			}
			break;
		default:
			fprintf(stderr, "Unrecognized variable type!\n");
			break;
	}

	return v;
};

void value_t_delete(struct value_t* v1){
	if(v1){
		free(v1);
	}
}

struct value_t*
value_t_copy(struct value_t* v1){
	if(!v1){
		fprintf(stderr, "Source is null: value_t_copy()");
		return NULL;
	}

	struct value_t* val = NULL;
	val = (struct value_t*)malloc(sizeof(struct value_t));

	memcpy((void*)val, (void*)v1, sizeof(struct value_t));
	if(val == NULL){
		fprintf(stderr, "Memcopy error: value_t_copy()");
		return NULL;
	}
	return (struct value_t*)val;
}


void
value_t_display(struct value_t* val){
	if(!val){
		fprintf(stderr, "value is NULL: value_t_display()\n");
		return ;
	}
	
	switch(val->type){
		case V_DOUBLE:
			printf("%f", val->dval);
			break;
		case V_STR:
			printf("%s", val->sval);
			break;
		case V_BOOL:
			if(val->ival){
				printf("doğru");
			}else{
				printf("yanlış");
			}
			break;
		case V_INT:
			printf("%d", val->ival);
			break;
		default:
			fprintf(stderr, "Unrecognized variable type!");
			break;
	}
}

struct value_t*
value_t_add(struct value_t* v1, struct value_t* v2){
	struct value_t* temp = NULL;

	if(v_isint(v1) && v_isint(v2)){
		temp = value_t_create_int((v1->ival + v2->ival));
	}else if(v_isint(v1) && v_isdouble(v2)){
		double t = (v2->dval + v1->ival);
		temp = value_t_create_double(t);
	}else if(v_isdouble( v1) && v_isint(v2)){
		double t = (v1->dval + v2->ival);
		temp = value_t_create_double(t);
	}else if(v_isdouble(v1) && v_isdouble(v2)){
		double t = (v1->dval + v2->dval);
		temp = value_t_create_double(t);
	}else{
		fprintf(stderr, "'+' operatör için yanlış tip.\n");
	}
	return temp;
}

struct value_t*
value_t_sub(struct value_t* v1, struct value_t* v2){
	struct value_t* temp = NULL;

	if(v_isint(v1) && v_isint(v2)){
		int t = (v1->ival - v2->ival);
		temp = value_t_create_int(t);
	}else if(v_isint(v1) && v_isdouble(v2)){
		double t = ((double)v1->ival - v2->dval);
		temp = value_t_create_double(t);
	}else if(v_isdouble(v1) && v_isint(v2)){
		double t = (v1->dval - v2->ival);
		temp = value_t_create_double(t);
	}else if(v_isdouble(v1) && v_isdouble(v2)){
		double t = (v1->dval - v2->dval);
		temp = value_t_create_double(t);
	}else{
		fprintf(stderr, "'-' operatörü için yanlış tip.\n");
	}
	return temp;
}
struct value_t* value_t_mod(struct value_t* v1, struct value_t* v2){
	struct value_t* temp = NULL;

	if(v_isint(v1) && v_isint(v2)){
		int t = (v1->ival % v2->ival);
		temp = value_t_create_int(t);
	}else{
		fprintf(stderr, "'-' operatörü için yanlış tip.\n");
	}
	return temp;
}


struct value_t*
value_t_mul(struct value_t* v1, struct value_t* v2){
	struct value_t* temp = NULL;

	if(v_isint(v1) && v_isint(v2)){
		int t = (v1->ival * v2->ival);
		temp = value_t_create(V_INT, (void*)&t);
	}else if(v_isint(v1) && v_isdouble(v2)){
		double t = ((double)v1->ival * v2->dval);
		temp = value_t_create(V_DOUBLE, (void*)&t);
	}else if(v_isdouble(v1) && v_isint(v2)){
		double t = (v1->dval * v2->ival);
		temp = value_t_create(V_DOUBLE, (void*)&t);
	}else if(v_isdouble(v1) && v_isdouble(v2)){
		double t = (v1->dval * v2->dval);
		temp = value_t_create(V_DOUBLE, (void*)&t);
	}else{
		fprintf(stderr, "'*' operatör için yanlış tip.\n");
	}
	return temp;
}

struct value_t*
value_t_div(struct value_t* v1, struct value_t* v2){
	struct value_t* temp = NULL;
	if(v_isnumeric(v2)){
		if(v2->ival == 0 || v2->dval == 0){
			fprintf(stderr, "Sıfıra bölme hatası.");
			return NULL;
		}
	}
	if(v_isint(v1) && v_isint(v2)){
		double t = ((double)v1->ival / (double)v2->ival);
		temp = value_t_create(V_INT, (void*)&t);
	}else if(v_isint(v1) && v_isdouble(v2)){
		double t = ((double)v1->ival / v2->dval);
		temp = value_t_create(V_DOUBLE, (void*)&t);
	}else if(v_isdouble(v1) && v_isint(v2)){
		double t = (v1->dval / v2->ival);
		temp = value_t_create(V_DOUBLE, (void*)&t);
	}else if(v_isdouble(v1) && v_isdouble(v2)){
		double t = (v1->dval / v2->dval);
		temp = value_t_create(V_DOUBLE, (void*)&t);
	}else{
		fprintf(stderr, "'+' operatörü için yanlış tip.\n");
	}

	return temp;
}

struct value_t*
value_t_uminus(struct value_t* v1){
	struct value_t* temp = NULL;
	if(v_isint(v1)){			 // int ve bool
		int k = -(v1->ival);
		temp = value_t_create(V_INT, (void*)&k);
	}else if(v_isdouble(v1)){
		double k = -(v1->dval);
		temp = value_t_create(V_DOUBLE, (void*)&k);
	}else{
		fprintf(stderr, "'-' operatörü için yanlış tip.\n");
	}
	return temp;
}


int
value_t_cmp(struct value_t* v1, struct value_t* v2){
	if(v_iseq(v1, v2)){
		if(v_isbool(v1)){
			if(v1->ival == v2->ival)
				return 0;
			return -2;
		}
		if(v_isint(v1)){

			if(v1->ival == v2->ival)
				return 0;
			if(v1->ival < v2->ival)
				return -1;
			if(v1->ival > v2->ival)
				return 1;
		}
		if(v_isdouble(v1)){
			if(v1->dval == v2->dval)
				return 0;
			if(v1->dval < v2->dval)
				return -1;
			if(v1->dval > v2->dval)
				return 1;
		}
		if(v_isstr(v1))
			return strcmp(v1->sval, v2->sval);
	}

	return -2;
}

struct value_t*
value_t_and(struct value_t* v1, struct value_t* v2){
	struct value_t* temp = NULL;
	if(v_isint(v1)){
		if(v1->ival)
			return v2;
		return v1;
	}
	if(v_isdouble(v1)){
		if(v1->dval)
			return v2;
		return v1;
	}

	if(v_isstr(v1)){
		if(v1->sval)
			return v2;
		return v1;
	}
}


struct value_t*
value_t_or(struct value_t* v1, struct value_t* v2){
	struct value_t* temp = NULL;
	if(v_isint(v1)){
		if(v1->ival)
			return v1;
		return v2;
	}
	if(v_isdouble(v1)){
		if(v1->dval)
			return v1;
		return v2;
	}

	if(v_isstr(v1)){
		if(v1->sval)
			return v1;
		return v2;
	}
}

struct value_t*
value_t_not(struct value_t* v1){
	int d = 1;
	struct value_t* val = NULL;

	if(v_isint(v1)){
		if(v1->ival)
			d = 0;
	}
	if(v_isdouble(v1)){
		if(v1->dval)
			d = 0;
	}

	if(v_isstr(v1)){
		if(v1->sval)
			d = 0;
	}

	val = value_t_create_int(d);
	return val;
}

struct value_t*
value_t_g(struct value_t* v1, struct value_t* v2){
	struct value_t* val = NULL;
	int k =	value_t_cmp(v1, v2);
	if( k == 1)
		k = 1;
	else
		k = 0;

	val = value_t_create_int(k);
	return val;
}

struct value_t*
value_t_l(struct value_t* v1, struct value_t* v2){
	struct value_t* val = NULL;
	int k =	value_t_cmp(v1, v2);
	if( k ==  1  || k == 0)
		k = 0;
	else
  		k = 1;
	val = value_t_create_int(k);
	return val;
}

struct value_t*
value_t_le(struct value_t* v1, struct value_t* v2){
	struct value_t* val = NULL;
	int k =	value_t_cmp(v1, v2);
	if( k ==  1 )
		k = 0;
	else
		k = 1;

	val = value_t_create_int(k);
	return val;
}

struct value_t*
value_t_ge(struct value_t* v1, struct value_t* v2){
	struct value_t* val = NULL;
	int k =	value_t_cmp(v1, v2);
	if( k != -1 )
		k = 1;
	else
		k = 0;

	val = value_t_create_int(k);
	return val;
}

struct value_t*
value_t_ee(struct value_t* v1, struct value_t* v2){
	struct value_t* val = NULL;
	int k =	value_t_cmp(v1, v2);
	if( k == 0 )
		k = 1;
	else
		k = 0;

	val = value_t_create_int(k);
	return val;
}

struct value_t*
value_t_ne(struct value_t* v1, struct value_t* v2){
	struct value_t* val = NULL;
	int k =	value_t_cmp(v1, v2);
	if( k != 0 )
		k = 1;
	else
		k = 0;

	val = value_t_create_int(k);
	return val;
}
