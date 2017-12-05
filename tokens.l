R 		[0-9]
H		[a-zA-ZçöþðüýÇÖÞÐÜÝ]

%{

#include <stdio.h>

int yywrap();
int lineno  = 1;

void set(int type);
	
%}


%% 

ise 										{ return ISE; }
veya										{ return VEYA; }
ve											{ return VE;	}
yap 										{ return YAP; }
son 										{ return SON; }
baþka 										{ return BASKA; }			
yinele 										{ return YINELE; }
ekadar										{ return EKADAR; }
iken 										{ return IKEN; }
üzre 										{ return UZRE; }
yordam 										{ return YORDAM; }
yerel 										{ return YEREL; }
dön											{ return DON;	}
býrak										{ return BIRAK; }
devam										{ return DEVAM; }
sinif										{ return SINIF;	}
tür											{ return TUR; 	}
cins 										{ return CINS; 	}
yazdir										{ return YAZDIR; }
doðru										{ yylval.val = value_t_create(V_BOOL, "1"); return DOGRU; }
yanlýþ										{ yylval.val = value_t_create(V_BOOL, "0"); return YANLIS; }
{H}({H}|{R})*								{ yylval.ident = yytext; return TANIMLAYICI; }
{R}+										{ yylval.val = value_t_create(V_INT, yytext); return TAMSAYI; }
{R}*\.{R}+									{ yylval.val = value_t_create(V_DOUBLE, yytext); return ONDALIK;	}
'(\\.|[^\\'])+'								{ yylval.val = value_t_create(V_STR, yytext); return DIZGI; }
\"(\\.|[^\\"])*\"							{ yylval.val = value_t_create(V_STR, yytext); return DIZGI;	}
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

[ \t\v\f]									{ /* gözardý et */ }

\n											{ lineno++; }
.											{ return yytext[0]; }

%% 


int yywrap(){
return 1;
}

void set(int type){
	if(type == OLONG){
		long t = atol(yytext); 
		yylval = ctn(object_t_create(OLONG, &t));
	}
	else if(type == ODOUBLE){
		double t = atof(yytext);
		yylval = ctn(object_t_create(ODOUBLE, &t));
	}
	else if(type == OSTR){
		yylval = ctn(object_t_create(OSTR, yytext)); 
	}
	else if(type == OIDENT){
		yylval = ctn(object_t_create(OIDENT, yytext)); 
	}
}
