#include "codegen.h"


void gencode(enum opcode op, value_t ar1, value_t ar2){
	code[pc].ar1 = ar1;
	code[pc].ar2 = ar2;
	code[pc++].op = op;
	// code[pc].op = op;
	// code[pc].ar1 = ar1->pos;
	// code[pc++].ar2 = ar2->pos;
}

int PC(){
	return pc;
}


void patch(int codeindex, int loc){
	code[codeindex].ar1->label.l1 = loc;
}

void genlabel(){

}
