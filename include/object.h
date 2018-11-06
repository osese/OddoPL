#ifndef OBJECT_INCLUDE
#define OBJECT_INCLUDE
#include "vstr.h"

#define NONE value_create_none()
enum{
	V_IDENT = 0,
	V_INT,
	V_DOUBLE,
	V_STR,
	V_CHAR,
	V_OBJ,
	V_BOOL,
	V_LBL,
	V_OTHER,
	V_NONE
};

struct _value{
	int type;
	int pos;
	union{
		vstr_t str;		// string value
		char* ident;
		double dval;	// double value
		long ival; 		// integer value
		struct { int l1; int l2; } label;
		struct { int first; int second; } other;
	};
};


struct _value* value_alloc();
struct _value* value_create(int type, char* value);
struct _value* value_create_none();
struct _value* value_create_int(long val);
struct _value* value_create_double(double val);
struct _value* value_create_vstr(vstr_t vstr);
struct _value* value_create_vstr_c(char* val);

struct _value* _value_copy(struct _value*);

void _value_free(struct _value*);

void value_display(struct _value*);

struct _value* value_add(struct _value*, struct _value* );
struct _value* value_mod(struct _value*, struct _value* );
struct _value* value_sub(struct _value*, struct _value* );
struct _value* value_mul(struct _value*, struct _value* );
struct _value* value_div(struct _value*, struct _value* );
struct _value* value_uminus(struct _value*);

int value_cmp(struct _value*, struct _value*);
struct _value* value_and(struct _value*, struct _value*);
struct _value* value_or(struct _value*, struct _value*);
struct _value* value_not(struct _value*);
struct _value* value_g(struct _value*, struct _value*);
struct _value* value_lt(struct _value*, struct _value*);
struct _value* value_le(struct _value*, struct _value*);
struct _value* value_ge(struct _value*, struct _value*);
struct _value* value_ee(struct _value*, struct _value*);
struct _value* value_ne(struct _value*, struct _value*);


#define v_iseq(t1, t2) 				(t1->type == t2->type)
#define v_isint(t1)		 			(t1->type == V_INT || t1->type == V_BOOL)
#define v_isdouble(t1) 				(t1->type == V_DOUBLE )
#define v_isbool(t1) 				(t1->type == V_BOOL)
#define v_isstr(t1)					(t1->type == V_STR)
#define v_isnumeric(t1) 		 	(v_isint(t1) || v_isdouble(t1))
#define v_isident(t1) 				(t1->type == V_IDENT)
#define v_gint(t1) 		(t1->ival)
#define v_gdouble(t1)	(t1->dval)
#define v_gvstr(t1)		(t1->str)
#define v_gident(t1)    (t1->ident)
#define v_gtype(t1) 	(t1->ident)
#define v_glabel(t1)    (t1->label)
#define v_glabel(t1)    (t1->label)

typedef struct _value* value_t;
#endif
