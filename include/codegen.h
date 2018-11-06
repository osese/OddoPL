#ifndef COD_GEN
#define COD_GEN

#include "object.h"
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
	op_PRNT,
	op_HALT,
	op_NOT,
	op_ASSIGN,
	op_PUSH,
	op_JMP,
	op_LOAD,
	op_STORE,
	op_GOTO,
	op_ACCESS,
	op_FBEG,
	op_FEND,
	op_CALL,
	op_RET,
};

struct instruction{
	enum opcode op;
	value_t ar1;
	value_t ar2;
};


struct instruction code[100000];
static int pc = 0;	 // program counter

void gencode(enum opcode op, value_t ar1, value_t ar2);

void genlabel();
void patch(int codeindex, int loc);

int PC();
typedef struct instruction Ins;

#endif
