#include "include/stackmachine.h"
#include "include/codegen.h"
#include "include/object.h"
#include "include/symboltable.h"
#include <assert.h>
#define DEBUG
#define sorv_get(v1)	\
				if(v_isident(v1)){\
					v1 = sym_get(v_gident(v1));\
				}

void push_stack(Value_t var){
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
// 				stack[top++] = value_t_add(stack[top-1], stack[top]);
// 				break;
// 			case op_MUL:
// 				stack[top++] = value_t_mul(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_ASSIGN:
// 				;
// 				sym_put(stack[top-1]->sval, stack[top]);
// 				top-= 2;
// 				break;
// 			case op_DIV:
// 				stack[top++] = value_t_div(stack[a.ar1], stack[a.ar2]);
// 				break;
//
// 			case op_SUB:
// 				stack[top++] = value_t_sub(stack[a.ar1], stack[a.ar2]);
// 				break;
//
// 			// case op_MOD:
// 			// 	stack[top++] = value_t_mod(stack[a.ar1], stack[a.ar2]);
// 			// 	break;
//
// 			case op_ADD_E:
// 				stack[a.ar1] = value_t_add(stack[a.ar1], stack[a.ar2]);
// 				break;
//
// 			case op_SUB_E:
// 				stack[a.ar1] = value_t_sub(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_MUL_E:
// 				stack[a.ar1] = value_t_mul(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_DIV_E:
// 				stack[a.ar1] = value_t_div(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			// case op_MOD_E:
// 			// 	stack[a.ar1] = value_t_mod(stack[a.ar1], stack[a.ar2]);
// 			// 	break;
//
// 			case op_LT:
// 				stack[top++] =  value_t_l(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_GT:
// 				stack[top++] =  value_t_g(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_LE:
// 				stack[top++] =  value_t_le(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_GE:
// 				stack[top++] =  value_t_ge(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_EE:
// 				stack[top++] =  value_t_ee(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_NE:
// 				stack[top++] =  value_t_ne(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_AND:
// 				stack[top++] =  value_t_and(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_OR:
// 				stack[top++] =  value_t_or(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_NOT:
// 				stack[top++] =  value_t_not(stack[a.ar1]);
// 				break;
// 			case op_CONCAT:
// 				break;
// 			case op_UMINUS:
// 				stack[top++] =  value_t_l(stack[a.ar1], stack[a.ar2]);
// 				break;
// 			case op_PRNT:
// 				value_t_display(stack[top]);
// 				// if(stack[a.ar1]->type == V_IDENT){
// 				// 	value_t_display(sym_get(stack[a.ar1]->sval));
// 				// }else {
// 				// 	value_t_display(stack[a.ar1]);
// 				// }
// 				break;
// 			case op_HALT:
// 				break;
// 		}
// 		//value_t_display(stack[top]);
// 		pc++;
// 	}while(a.op != op_HALT);
// }

int fetch_execute_cycle(){
	Ins a ;
	Value_t v1;
	Value_t v2;
	do{
		a = code[pc];
		switch(a.op){
			case op_LOAD:
				;
				a.ar1->pos = top;
				push_stack(sym_get(v_gstr(a.ar1)));
				break;
			case op_STORE:
				;
				sym_put(v_gident(a.ar1), NONE);
				break;
			case op_PUSH:
				push_stack(a.ar1);
				break;
			case op_JMP:
				#ifdef DEBUG 
					assert(stack[top] != NULL);
					assert(stack[top]->type == V_INT);
				#endif 

				if(v_gint(stack[top]) == 0){
					pc = a.ar1->label.l1 - 1;
				}
				break;
			case op_ADD:
				;
				v1 = stack[top-1];
				v2 = stack[top];
				sorv_get(v1);
				sorv_get(v2);
				push_stack(value_t_add(v1, v2));
				break;
			case op_ASSIGN:
				;
				sym_put(v_gident(a.ar1), stack[top]);
				break;

			case op_GOTO:
				;
				pc = a.ar1->label.l2;
				break;
			case op_SUB:
				;
				#ifdef DEBUG
					assert(v1 != NULL);
					assert(v2 != NULL);
					assert(v1->type != V_STR);
					assert(v2->type != V_STR);
				#endif 
				v1 = stack[top-1];
				v2 = stack[top];
				if(v_isident(v1)){
					v1 = sym_get(v_gident(v1));
				}
				if(v_isident(v2)){
					v2 = sym_get(v_gident(v2));
				}
				push_stack(value_t_sub(v1, v2));
				break;
			case op_PRNT:
				if(v_isident(stack[top])){
					value_t_display(sym_get(stack[top]->sval));
				}else {
					value_t_display(stack[top]);
				}
				break;
			case op_HALT:
				//clear stack ..
				break;
			case op_LT:
				;
				v1 = stack[top-1];
				v2 = stack[top];
				sorv_get(v1);
				sorv_get(v2);
				push_stack(value_t_l(v1, v2));
				break;
			case op_GT:
				;
				v1 = stack[top-1];
				v2 = stack[top];
				sorv_get(v1);
				sorv_get(v2);
				push_stack(value_t_g(v1, v2));
				break;
			default: 
				assert("Hey wtf!! ");
				break;
		}
		//value_t_display(stack[top]);
		pc++;
	}while(a.op != op_HALT);
}
