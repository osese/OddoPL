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
doðru										{ yylval.ival = 1; return DOGRU; }
yanlýþ										{ yylval.ival = 0; return YANLIS; }
{H}({H}|{R})*								{ yylval.sval = yytext; return TANIMLAYICI; }
{R}+										{ yylval.ival = atol(yytext); return TAMSAYI; }
{R}*\.{R}+									{ yylval.dval = atof(yytext); return ONDALIK;	}
'(\\.|[^\\'])+'								{ yylval.sval = strdup(yytext); return DIZGI; }
\"(\\.|[^\\"])*\"							{ yylval.sval = strdup(yytext); return DIZGI;	}
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
