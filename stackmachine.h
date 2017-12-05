// stack machine 


// runtime stack 
Value_t stack[10000];
int top = 0;

void setup_var(Value_t var){	
	var->spos = top;
	stack[top++] = var; 	
}

int print_eval_loop(){
	Ins a = code[pc];
	do{
		switch(a->op){
			case op_ADD:
				stack[top++] = value_t_add(stack[a->ar1], stack[a->ar2]);
				break;
			case op_MUL:
				stack[top++] = value_t_mul(stack[a->ar1], stack[a->ar2]);
				break;
			
			case op_DIV:
				stack[top++] = value_t_div(stack[a->ar1], stack[a->ar2]);
				break;
			
			case op_SUB:
				stack[top++] = value_t_sub(stack[a->ar1], stack[a->ar2]);
				break;

			case op_MOD:
				stack[top++] = value_t_mod(stack[a->ar1], stack[a->ar2]);
				break;
				
			case op_ADD_E:
				stack[a->ar1] = value_t_add(stack[a->ar1], stack[a->ar2]);
				break;

			case op_SUB_E:
				stack[a->ar1] = value_t_sub(stack[a->ar1], stack[a->ar2]);
				break;
			case op_MUL_E:
				stack[a->ar1] = value_t_mul(stack[a->ar1], stack[a->ar2];
				break;
			case op_DIV_E:
				stack[a->ar1] = value_t_div(stack[a->ar1], stack[a->ar2]);
				break;
			case op_MOD_E:
				stack[a->ar1] = value_t_mod(stack[a->ar1], stack[a->ar2]);
				break;
			
			case op_LT:
				stack[top++] =  value_t_l(stack[a->ar1], stack[a->ar2]);
				break;
			case op_GT:
				stack[top++] =  value_t_g(stack[a->ar1], stack[a->ar2]);
				break;
			case op_LE:
				stack[top++] =  value_t_le(stack[a->ar1], stack[a->ar2]);
				break;
			case op_GE:
				stack[top++] =  value_t_ge(stack[a->ar1], stack[a->ar2]);
				break;
			case op_EE:
				stack[top++] =  value_t_ee(stack[a->ar1], stack[a->ar2]);
				break;
			case op_NE:
				stack[top++] =  value_t_ne(stack[a->ar1], stack[a->ar2]);
				break;
			case op_AND:
				stack[top++] =  value_t_and(stack[a->ar1], stack[a->ar2]);
				break;
			case op_OR:
				stack[top++] =  value_t_or(stack[a->ar1], stack[a->ar2]);
				break;
			case op_NOT:
				stack[top++] =  value_t_not(stack[a->ar1]);
				break;
			case op_CONCAT:
				break; 
			case op_UMINUS:
				stack[top++] =  value_t_l(stack[a->ar1], stack[a->ar2]);
				break;
			case op_HALT:
				break;
		}
		value_t_display(stack[top]);
		pc++;
	}while(a->op != op_HALT);
}

int fetch_execute_cycle(){
	
	return 1;
}