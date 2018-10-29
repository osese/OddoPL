#ifndef OBJECT_INCLUDE
#define OBJECT_INCLUDE
#include "vstr.h"

#define NONE value_t_create_none()
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

struct value_t{
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


struct value_t* value_t_alloc();
struct value_t* value_t_create(int type, char* value);
struct value_t* value_t_create_none();
struct value_t* value_t_create_int(long val);
struct value_t* value_t_create_double(double val);
struct value_t* value_t_create_vstr(vstr_t vstr);
struct value_t* value_t_create_vstr_c(char* val);

struct value_t* value_t_copy(struct value_t*);

void value_t_free(struct value_t*);

void value_t_display(struct value_t*);

struct value_t* value_t_add(struct value_t*, struct value_t* );
struct value_t* value_t_mod(struct value_t*, struct value_t* );
struct value_t* value_t_sub(struct value_t*, struct value_t* );
struct value_t* value_t_mul(struct value_t*, struct value_t* );
struct value_t* value_t_div(struct value_t*, struct value_t* );
struct value_t* value_t_uminus(struct value_t*);

int value_t_cmp(struct value_t*, struct value_t*);
struct value_t* value_t_and(struct value_t*, struct value_t*);
struct value_t* value_t_or(struct value_t*, struct value_t*);
struct value_t* value_t_not(struct value_t*);
struct value_t* value_t_g(struct value_t*, struct value_t*);
struct value_t* value_t_l(struct value_t*, struct value_t*);
struct value_t* value_t_le(struct value_t*, struct value_t*);
struct value_t* value_t_ge(struct value_t*, struct value_t*);
struct value_t* value_t_ee(struct value_t*, struct value_t*);
struct value_t* value_t_ne(struct value_t*, struct value_t*);


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

typedef struct value_t* Value_t;
#endif
