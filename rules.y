%{

#include<stdio.h>
#include "tree.h"
#include "codegen.h"
#include "symtable.h"
#include "stackmachine.h"

%}
%define api.value.type {Value_t}

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


program				: blok 					
					;


 
						
blok				: demec					 				
					| demec blok				
					| demec blok don_demec			
					;


demec				: ';'					
					| atama_ifadesi 
					| fonk_cagri
					| YAP blok SON	
					| BIRAK	
					| dongu_demeci	
					| secme_demeci		
					| fonk_tanimi	
					| sinif_tanimi	
					;


don_demec 			
					: DON ifade			 
					| DON ifade ';'	
					;

fonk_cagri 	
					: TANIMLAYICI '(' arg_list ')'	 
					;

atom				 
					: DIZGI				{ setup_var($1); }											
					| TAMSAYI			{ setup_var($1); }
					| ONDALIK			{ setup_var($1); }
					| DOGRU				{ setup_var($1); }
					| YANLIS			{ setup_var($1); }
					| fonk_cagri		 
					| solsal_ifade		{ setup_var($1); }		
					;

solsal_ifade
					: TANIMLAYICI 													
					| YEREL TANIMLAYICI 			{ $$ = $2; }
					| solsal_ifade '[' ifade ']' 	
					| solsal_ifade '.' TANIMLAYICI 
					;


atama_ifadesi
					: solsal_ifade '=' ifade 			{ codegen(o_MOV, $1, $3); }			  		
					| solsal_ifade '=' liste_ifadesi	
					| solsal_ifade ARTIESIT ifade		{ codegen(op_ADD_E, $1, $3); }
					| solsal_ifade EKSIESIT ifade		{ codegen(op_SUB_E, $1, $3); }
					| solsal_ifade BOLUESIT ifade 		{ codegen(o_DIV_E, $1, $3); }
					| solsal_ifade CARPIESIT ifade		{ codegen(op_MUL_E, $1, $3); }
					| solsal_ifade MODESIT ifade		{ codegen(op_MOD_E, $1, $3); }
					;

ifade				: atom								{ $$ = $1; } 	
					| ifade '+' ifade 					{ codegen(op_ADD, $1, $3); }
					| ifade '-' ifade					{ codegen(op_SUB, $1, $3); }
					| ifade '/' ifade 					{ codegen(op_DIV, $1, $3); }
					| ifade '*' ifade					{ codegen(op_MUL, $1, $3); }
					| '-' ifade   						{ codegen(op_UMINUS, $1, $3); }
					| ifade '>' ifade					{ codegen(op_BT, $1, $3); }
					| ifade '<' ifade					{ codegen(op_LT, $1, $3); }
					| ifade BIRLESTIR ifade				{ codegen(op_CONCAT, $1, $3); }
					| ifade KE ifade 					{ codegen(op_LE, $1, $3); }
					| ifade BE ifade					{ codegen(op_GE, $1, $3); }
					| ifade EE ifade					{ codegen(op_EE, $1, $3); }
					| ifade ED ifade 					{ codegen(op_NE, $1, $3); }
					| ifade VE ifade					{ codegen(op_AND, $1, $3); }
					| ifade VEYA ifade					{ codegen(op_OR, $1, $3); }
					| '(' ifade ')'						{ $$ = $2; }
					;



secme_demeci 
					: ISE ifade YAP blok SON  
					| ISE ifade YAP blok BASKA blok SON
					;
		
dongu_demeci	
					: IKEN  ifade YAP blok SON 
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
