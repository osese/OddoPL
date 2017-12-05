
enum opcode{
	op_ADD = 0,
	op_MUL,
	op_DIV,
	op_SUB,
	op_MOD,
	op_ADD_E,
	op_SUB_E,
	op_MUL_E,
	op_DIV_E,
	op_MOD_E,
	op_LT,
	op_GT,
	op_LE,
	op_GE,
	op_EE,
	op_NE,
	op_AND,
	op_OR,
	op_CONCAT,
	op_UMINUS,
	op_print,
	op_HALT
};

struct instruction{
	enum opcode op; 
	int ar1;
	int ar2;
};


struct instruction code[100000];
int pc = 0;	 // program counter 
 
void gencode(enum opcode op, Value_t ar1, Value_t ar2){
	code[pc].op = op;
	code[pc].ar1 = ar1->pos; 
	code[pc++].ar2 = ar2->pos; 
}

void genlabel(){	

}

typedef struct instruction* Ins;



