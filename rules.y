%{

#include<stdio.h>
#include "tree.h"


%}

%union{
	long 	ival;
	double  dval;
	char* 	sval;
};


%token<ival> TAMSAYI
%token<dval> ONDALIK
%token<sval> DIZGI
%token<sval> TANIMLAYICI
%token<lval> DOGRU
%token<lval> YANLIS

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
					: DIZGI				{ install($1); }											
					| TAMSAYI			{ install($1); }
					| ONDALIK			{ install($1); }
					| DOGRU
					| YANLIS
					| fonk_cagri		 
					| solsal_ifade				
					;

solsal_ifade
					:	TANIMLAYICI 									
					| YEREL TANIMLAYICI 
					| solsal_ifade '[' ifade ']' 
					| solsal_ifade '.' TANIMLAYICI 
					;


atama_ifadesi
					: solsal_ifade '=' ifade 				  		
					| solsal_ifade '=' liste_ifadesi
					| solsal_ifade ARTIESIT ifade
					| solsal_ifade EKSIESIT ifade	
					| solsal_ifade BOLUESIT ifade 
					| solsal_ifade CARPIESIT ifade
					| solsal_ifade MODESIT ifade
					;

ifade				: atom
					| ifade '+' ifade 
					| ifade '-' ifade
					| ifade '/' ifade 
					| ifade '*' ifade
					| '-' ifade   	
					| ifade '>' ifade
					| ifade '<' ifade
					| ifade BIRLESTIR ifade
					| ifade KE ifade 
					| ifade BE ifade
					| ifade EE ifade
					| ifade ED ifade 
					| ifade VE ifade
					| ifade VEYA ifade
					| '(' ifade ')'
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
			return 1;
		}else{
			fprintf(stderr, "File can't open!\n"); 
			return -1;
		}
	}
	return yyparse();
}
