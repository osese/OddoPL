R 		[0-9]
H		[a-zA-Z]

%{

#include <stdio.h>
#include "rules.tab.h"
#include "include/object.h"
extern Value_t yylval;

int yywrap();
int lineno  = 1;

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
doğru										{ yylval = value_t_create(V_BOOL, "1"); return DOGRU; }
yanlış									    { yylval = value_t_create(V_BOOL, "0"); return YANLIS; }
{H}({H}|{R})*								{ yylval = value_t_create(V_IDENT, yytext); return TANIMLAYICI; }
{R}+										{ yylval = value_t_create(V_INT, yytext); return TAMSAYI; }
{R}*\.{R}+									{ yylval = value_t_create(V_DOUBLE, yytext); return ONDALIK;	}
'(\\.|[^\\'])+'								{ yylval = value_t_create(V_STR, yytext); return DIZGI; }
\"(\\.|[^\\"])*\"							{ yylval = value_t_create(V_STR, yytext); return DIZGI;	}
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

[ \t\v\f]									{ /* g�zard� et */ }

\n											{ lineno++; }
.											{ return yytext[0]; }

%%


int yywrap(){
return 1;
}
