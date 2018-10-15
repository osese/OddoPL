%{

#include<stdio.h>
#include "include/codegen.h"
#include "include/symboltable.h"
#include "include/stackmachine.h"
#include "include/object.h"


int yyerror(char*);
extern void yyset_in(FILE* );
int yylex();
%}

%define api.value.type { struct value_t* }

%token TAMSAYI
%token ONDALIK
%token DIZGI
%token TANIMLAYICI
%token DOGRU
%token YANLIS

%token ISE YEREL YAP SON BASKA YINELE EKADAR IKEN UZRE DON DEVAM BIRAK
%token SAGKAYDIR SOLKAYDIR VE VEYA YS
%token SINIF YORDAM
%token BE KE EE ED
%token TUR CINS
%token BIRLESTIR
%token YAZDIR
%token ARTIESIT EKSIESIT CARPIESIT BOLUESIT MODESIT


%left '>' '<' BE KE EE ED
%right VE VEYA
%left '+' '-'
%left '*' '/'
%left '%'
%left BIRLESTIR



%%


program	:	blok	{gencode(op_HALT, 0, 0);}
					;




blok			: demec
					| demec blok
					| demec blok don_demec
					;


demec			: ';'
					| atama_ifadesi
					| fonk_cagri
					| YAP blok SON
					| BIRAK
					| dongu_demeci
					| secme_demeci
					| fonk_tanimi
					| sinif_tanimi
					| yazdir_demec
					;

yazdir_demec: YAZDIR ifade { gencode(op_PRNT, 0, 0);}
					;
don_demec
					: DON ifade
					| DON ifade ';'
					;

fonk_cagri
					: TANIMLAYICI '(' arg_list ')'
					;

atom
					: DIZGI				{ gencode(op_PUSH, $1, 0); }
					| TAMSAYI			{ gencode(op_PUSH, $1, 0); }
					| ONDALIK			{ gencode(op_PUSH, $1, 0); }
					| DOGRU				{ gencode(op_PUSH, $1, 0); }
					| YANLIS			{ gencode(op_PUSH, $1, 0); }
					| fonk_cagri
					| solsal_ifade		{ gencode(op_LOAD, $1, 0); }
					;

solsal_ifade
					: TANIMLAYICI					{ $$ = $1;  }	
					| YEREL TANIMLAYICI 			{ $$ = $2;  }	
					| solsal_ifade '[' ifade ']'
					| solsal_ifade '.' TANIMLAYICI
					;


atama_ifadesi
					: solsal_ifade '=' ifade 			{ gencode(op_ASSIGN, $1, $3); }
					| solsal_ifade '=' liste_ifadesi
					| solsal_ifade ARTIESIT ifade		{ gencode(op_ADD_E, $1, $3); }
					| solsal_ifade EKSIESIT ifade		{ gencode(op_SUB_E, $1, $3); }
					| solsal_ifade BOLUESIT ifade 		{ gencode(op_DIV_E, $1, $3); }
					| solsal_ifade CARPIESIT ifade		{ gencode(op_MUL_E, $1, $3); }
					| solsal_ifade MODESIT ifade			{ gencode(op_MOD_E, $1, $3); }
					;

ifade				: atom								{ $$ = $1; }
					| ifade '+' ifade 			{ gencode(op_ADD, $1, $3); }
					| ifade '-' ifade				{ gencode(op_SUB, $1, $3); }
					| ifade '/' ifade 			{ gencode(op_DIV, $1, $3); }
					| ifade '*' ifade				{ gencode(op_MUL, $1, $3); }
					| ifade '>' ifade				{ gencode(op_GT, $1, $3); }
					| ifade '<' ifade				{ gencode(op_LT, $1, $3); }
					| ifade BIRLESTIR ifade	{ gencode(op_CONCAT, $1, $3); }
					| ifade KE ifade 				{ gencode(op_LE, $1, $3); }
					| ifade BE ifade				{ gencode(op_GE, $1, $3); }
					| ifade EE ifade				{ gencode(op_EE, $1, $3); }
					| ifade ED ifade 				{ gencode(op_NE, $1, $3); }
					| ifade VE ifade				{ gencode(op_AND, $1, $3); }
					| ifade VEYA ifade			{ gencode(op_OR, $1, $3); }
					| '(' ifade ')'					{ $$ = $2; }
					;



secme_demeci
					: ISE ifade { $1 = value_t_alloc(); $1->label.l1 = PC(); gencode(op_JMP, $1, 0); }
						YAP blok SON  { patch($1->label.l1, PC()); }
					;

dongu_demeci
					: IKEN	{$1 = value_t_alloc();  $1->label.l2 = PC();}  
					ifade YAP { $1->label.l1 = PC(); gencode(op_JMP, $1, 0);} 
					blok SON { gencode(op_GOTO, $1, 0); patch($1->label.l1, PC()); }

					| UZRE  atama_ifadesi ',' atom ',' atom  YAP blok SON
					| YINELE blok EKADAR '(' ifade ')'
					;

arg_list			:
					| atom
					| atom ',' arg_list
					;

ilk_arg_list
					: TANIMLAYICI '=' ifade
					| TANIMLAYICI '=' ifade ',' ilk_arg_list
					;


fonk_tanimi
					: YORDAM TANIMLAYICI '(' arg_list ')' blok SON
					;

sinif_tanimi
					: SINIF TANIMLAYICI SON
					| SINIF TANIMLAYICI '(' arg_list ')' SON
					| SINIF TANIMLAYICI '(' ilk_arg_list ')' SON
					;

liste_ifadesi
					: '{' arg_list '}'
					;


%%

int main(int argc, char* argv[]){
	if(argc == 2){
		FILE* f = fopen(argv[1], "r");
		if(f){
			yyset_in(f);
			yyparse();
			fclose(f);

			return fetch_execute_cycle();
		}else{
			fprintf(stderr, "File can't open!\n");
			return -1;
		}
	}
	yyparse();
	return print_eval_loop();
}


int yyerror(char* chr){
	fprintf(stderr, "Error occured: %s", chr);
	return -1;
}
