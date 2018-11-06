#include "stackmachine.h"
#include "codegen.h"
#include "object.h"
#include "symboltable.h"
#include <assert.h>
#define DEBUG

#define sm_add(x,y) \

void push_stack(value_t var){
	var->pos = top;
	stack[++top] = var;
}

int print_eval_loop(){}

// int fetch_execute_cycle(){
// 	Ins a ;
// 	do{
// 		a = code[pc];
// 		switch(a.op){
//
// 			case op_ADD:
// 				stack[top++] = value_add(stack[top-1], stack[top]);
// 				break;
// 			case op_MUL:
// 				stack[top++] = value_mul(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_ASSIGN:
// 				;
// 				sym_put(stack[top-1]->sval, stack[top]);
// 				top-= 2;
// 				break;
// 			case op_DIV:
// 				stack[top++] = value_div(stack[a.ar1], stack[a.ar2]);
// 				break;
//
// 			case op_SUB:
// 				stack[top++] = value_sub(stack[a.ar1], stack[a.ar2]);
// 				break;
//
// 			// case op_MOD:
// 			// 	stack[top++] = value_mod(stack[a.ar1], stack[a.ar2]);
// 			// 	break;
//
// 			case op_ADD_E:
// 				stack[a.ar1] = value_add(stack[a.ar1], stack[a.ar2]);
// 				break;
//
// 			case op_SUB_E:
// 				stack[a.ar1] = value_sub(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_MUL_E:
// 				stack[a.ar1] = value_mul(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_DIV_E:
// 				stack[a.ar1] = value_div(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			// case op_MOD_E:
// 			// 	stack[a.ar1] = value_mod(stack[a.ar1], stack[a.ar2]);
// 			// 	break;
//
// 			case op_LT:
// 				stack[top++] =  value_lt(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_GT:
// 				stack[top++] =  value_g(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_LE:
// 				stack[top++] =  value_lte(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_GE:
// 				stack[top++] =  value_ge(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_EE:
// 				stack[top++] =  value_ee(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_NE:
// 				stack[top++] =  value_ne(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_AND:
// 				stack[top++] =  value_and(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_OR:
// 				stack[top++] =  value_or(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_NOT:
// 				stack[top++] =  value_not(stack[a.ar1]);
// 				break;
// 			case op_CONCAT:
// 				break;
// 			case op_UMINUS:
// 				stack[top++] =  value_lt(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_PRNT:
// 				value_display(stack[top]);
// 				// if(stack[a.ar1]->type == V_IDENT){
// 				// 	value_display(sym_get(stack[a.ar1]->sval));
// 				// }else {
// 				// 	value_display(stack[a.ar1]);
// 				// }
// 				break;
// 			case op_HALT:
// 				break;
// 		}
// 		//value_display(stack[top]);
// 		pc++;
// 	}while(a.op != op_HALT);
// }

int fetch_execute_cycle(){
	Ins a ;
	value_t v1;
	value_t v2;
	initScope();
	do{
		a = code[pc];
		switch(a.op){
			case op_LOAD:
				;
				stack[++top] = sym_get(v_gident(a.ar1));
				break;
			case op_STORE:
				;
				sym_put(v_gident(a.ar1), NONE);
				break;
			case op_PUSH:
				stack[++top] = a.ar1;
				break;
			case op_MOD:
				;
				v1 = stack[top-1];
				v2 = stack[top];
				stack[--top] = value_mod(v1, v2);
				break;
			case op_EE: 
				;
				v1 = stack[top-1];
				v2 = stack[top];
				stack[--top] = value_ee(v1, v2);
				break;
			case op_JMP:
				#ifdef DEBUG 
					assert(stack[top] != NULL);
					assert(stack[top]->type == V_INT);
				#endif 

				if(v_gint(stack[top]) == 0){
					pc = a.ar1->label.l1 - 1;
				}
				top--;
				break;
			case op_ADD:
				;
				v1 = stack[top-1];
				v2 = stack[top];
				stack[top-1] = value_add(v1, v2);
				top = top - 1;
				break;
			case op_ASSIGN:
				;
				sym_put(v_gident(a.ar1), stack[top]);
				top--;
				break;

			case op_GOTO:
				;
				pc = a.ar1->label.l2-1;
				break;
			case op_SUB:
				;
				v1 = stack[top-1];
				v2 = stack[top];
				stack[top-1] = value_sub(v1, v2);
				top = top - 1;
				break;
			case op_PRNT:
				value_display(stack[top--]); // toptaki elemana ne olacak. 
				break;
			case op_HALT:
				//clear stack ..
				break;
			case op_LT:
				;
				v1 = stack[top-1];
				v2 = stack[top];
				stack[--top] = value_lt(v1, v2);
				break;
			case op_GT:
				;
				v1 = stack[top-1];
				v2 = stack[top];
				stack[--top] = value_g(v1, v2);
				break;
			case op_ACCESS:
				v1 = sym_get(v_gident(a.ar1));
				v2 = stack[top];
				if(v_isstr(v1)){
					stack[top] = value_create_vstr(v_str_at(v_gvstr(v1), v_gint(v2)));
				}else{
					// error 
					top--;
				}
				break;
			default: 
				assert("Hey wtf!! ");
				break;
		}
		//value_display(stack[top]);
		pc++;
	}while(a.op != op_HALT);
	assert(1 == 1);
}
