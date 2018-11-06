R 		[0-9]
H		[a-zA-Z]

%{

#include <stdio.h>
#include "rules.tab.h"
#include "object.h"





extern value_t yylval;

int yywrap();
int lineno  = 1;
char* escape(char* str);

%}


%%

ise		{ return ISE; }
veya	{ return VEYA; }
ve		{ return VE; }
yap     { return YAP; }
son 										{ return SON; }
baska 										{ return BASKA; }
yinele 										{ return YINELE; }
ekadar										{ return EKADAR; }
iken 										{ return IKEN; }
uzre 										{ return UZRE; }
yordam 										{ return YORDAM; }
yerel 										{ return YEREL; }
don											{ return DON;	}
bırak										{ return BIRAK; }
devam										{ return DEVAM; }
sinif										{ return SINIF;	}
tür											{ return TUR; 	}
cins 										{ return CINS; 	}
yazdir										{ return YAZDIR; }
doğru										{ yylval = value_create(V_BOOL, "1"); return DOGRU; }
yanlış									    { yylval = value_create(V_BOOL, "0"); return YANLIS; }
{H}({H}|{R})*								{ yylval = value_create(V_IDENT, yytext); return TANIMLAYICI; }
{R}+										{ yylval = value_create(V_INT, yytext); return TAMSAYI; }
{R}*\.{R}+									{ yylval = value_create(V_DOUBLE, yytext); return ONDALIK;	}
'(\\.|[^\\'])+'								{ yylval = value_create(V_STR, escape(yytext)); return DIZGI; }
\"(\\.|[^\\"])*\"							{ yylval = value_create(V_STR, escape(yytext)); return DIZGI;	}
"+="										{ return ARTIESIT; }
"-="										{ return EKSIESIT; }
"*="										{ return CARPIESIT; }
"/="										{ return BOLUESIT; }
"%="										{ return MODESIT; }
"++"										{ return BIRLESTIR; }
">>"										{ return SAGKAYDIR;	}
"<<"										{ return SOLKAYDIR;	}
"&&"										{ return VE; }
"||"										{ return VEYA; }
">="										{ return BE; }
"<="										{ return KE; }
"=="										{ return EE; }
"!="										{ return ED; }
"//".*									  { /* yorum */ }
[ \t\v\f]									{ /* gözardı et */ }

\n											{ lineno++; }
.											{ return yytext[0]; }

%%


int yywrap(){
return 1;
}

char* escape(char* str){
	
	int i = 1;
	int j = 0;
	int n = strlen(str);
	str[n-1] = '\0';
	char* res = (char*)malloc(n-1);
    
	while(str[i] != '\0'){
		if(str[i] == '\\'){
			i = i + 1;
			if(str[i] == 'n'){
				*(res+j) = '\n';
			}else if(str[i] == 't'){
				*(res+j) = '\t';
			}else if(str[i] == '\\'){
				*(res+j) = '\\';
			}
		}else{
			*(res+j) = str[i];
		}
		j += 1;
		i += 1;
	}
	*(res+j) = '\0';
	return res;
}
